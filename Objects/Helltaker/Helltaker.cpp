#include "framework.h"
#include "Helltaker.h"
#include "SceneList.h"
#include "HelltakerMap.h"
#include "Mob.h"
#include "Box.h"
#include "Trap.h"
#include "Slate.h"
#include "LockBox.h"
#include "Key.h"
#include "Goal.h"
#include "Kick.h"
#include "Dust.h"
#include "Huge.h"

Helltaker::Helltaker()
{
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	animation = new Animation(L"./Images/Idle.png", shaderFile);//Animation이 하나 생성

	// Effect
	{
		kickEffect = new Kick();
		dustEffect = new Dust();
		hugeEffect = new Huge();
	}

	//IDLE
	{
		AnimationClip* pClip = new AnimationClip(AnimationClip::State::loop);//AnimationClip이 하나 생성
		//등록
		animation->AddClip(pClip);

		float x = 0;
		for (int i = 1; i <= 12; i++)
		{
			wstring str = L"./Images/Idle.png";
			pClip->AddFrame(animation->GetTexture(), str, x, 20.0f, x + 100.0f, 150.0f, 0.06f);
			x = x + 100;
			//animation을 통해서 AnimationClip까지 들어가게 된다.
		}
	}
	//Move
	{
		AnimationClip* pClip = new AnimationClip(AnimationClip::State::loop);
		//등록
		animation->AddClip(pClip);

		float x = 0;
		for (int i = 1; i <= 5; i++)
		{
			wstring str = L"./Images/Move.png";
			pClip->AddFrame(animation->GetTexture(), str, x, 20.0f, x + 100.0f, 150.0f, 0.07f);
			x = x + 100;
		}
	}
	//ATTACK
	{
		AnimationClip* pClip = new AnimationClip(AnimationClip::State::once);
		//등록
		animation->AddClip(pClip);

		float x = 0;
		for (int i = 1; i <= 13; i++)
		{
			wstring str = L"./Images/Attack.png";
			pClip->AddFrame(animation->GetTexture(), str, x, 20.0f, x + 100.0f, 150.0f, 0.05f);
			x = x + 100;
		}
	}
	//Goal
	{
		AnimationClip* pClip = new AnimationClip(AnimationClip::State::end);
		//등록
		animation->AddClip(pClip);

		float x = 0;
		for (int i = 1; i <= 5; i++)
		{
			wstring str = L"./Images/Goal.png";
			pClip->AddFrame(animation->GetTexture(), str, x, 10.0f, x + 100.0f, 130.0f, 0.055f);
			x = x + 100;
		}
		for (int i = 6; i <= 17; i++)
		{
			wstring str = L"./Images/Goal.png";
			pClip->AddFrame(animation->GetTexture(), str, x, 10.0f, x + 100.0f, 130.0f, 0.175f);
			x = x + 100;
		}
		for (int i = 18; i <= 24; i++)
		{
			wstring str = L"./Images/Goal.png";
			pClip->AddFrame(animation->GetTexture(), str, x, 10.0f, x + 100.0f, 130.0f, 0.075f);
			x = x + 100;
		}
		for (int i = 21; i <= 24; i++)
		{
			wstring str = L"./Images/Character/Goal/Hero (" + to_wstring(i) + L").png";
			pClip->AddFrame(animation->GetTexture(), str, 0, 10.0f, 100.0f, 130.0f, 0.075f);
		}
	}

	collider = new Collider();
}

Helltaker::~Helltaker()
{
	SAFE_DELETE(hugeEffect)
	SAFE_DELETE(dustEffect);
	SAFE_DELETE(kickEffect);
	SAFE_DELETE(animation);
}

void Helltaker::Update(Matrix V, Matrix P)//키 입력과 관련된 동작들을 구현한다.
{
	Vector2 position = GetPosition(); //현재의 position을 가져온다.

	POINT pt = HTMAP->GetMapXY(position);

	if (SCENEMANAGER->GetScene("HS17_BossScene") == SCENEMANAGER->GetCurScene())
	{
		HS00_DeadScene* scene = (HS00_DeadScene*)SCENEMANAGER->GetScene("HS00_DeadScene");
		boss = true;
	}

	//키보드 컨트롤
	if (hp <= -1)
	{
		state = State::IDLE;
		return;
	}
	if (state != State::WALK)
	{
		if (PRESS(VK_CONTROL));
		else if (DOWN('W') || DOWN(VK_UP))
			MoveObject(Direction::up, position);
		else if (DOWN('S') || DOWN(VK_DOWN))
			MoveObject(Direction::down, position);
		else if (DOWN('A') || DOWN(VK_LEFT))
			MoveObject(Direction::left, position);
		else if (DOWN('D') || DOWN(VK_RIGHT))
			MoveObject(Direction::right, position);
	}
	else if (state == State::WALK)
	{
		kickEffect->SetActive(false);

		time += DELTA;

		if (!ISPLAYING("Move"))
			PLAYSOUND("Move", sfxSize);

		if (time > 0.01f)
		{
			moveCount++;
			time = 0.0f;

			if (moveCount <= 10)
			{
				Vector2 pos = position;
				position.x += movePos.x;
				position.y += movePos.y;
			}
			else
			{
				STOPSOUND("Move");

				state = State::IDLE;
				dustEffect->SetActive(false);
				moveCount = 0;
			}
		}
	}

	if (state == State::ATTACK)
	{
		if (!kickEffect->IsPlay())
			kickEffect->SetActive(false);

		if (!animation->IsPlay())
		{
			kickEffect->SetActive(false);
			state = State::IDLE;
		}
	}

	if (goal)
	{
		state = State::GOAL;

		if (SCENEMANAGER->GetCurScene() == SCENEMANAGER->GetScene("HS07_Chapter03"))
		{
			for (int i = 3; i <= 5; i++)
			{
				Goal* goals = (Goal*)OBJMANAGER->FindObject("Goal" + to_string(i));

				goals->SetGoal(true);
			}
		}
		else
		{
			string str = "";
		
			Scene* scene = SCENEMANAGER->GetCurScene();
			int num = scene->GetSceneNum();

			if (num <= 3)
				str = to_string(num);
			else
				str = to_string(num + 2);

			Goal* goal = (Goal*)OBJMANAGER->FindObject("Goal" + str);
			
			if (goal)
				goal->SetGoal(true);
		}

	}
	if (state == State::GOAL)
	{
		if (!animation->IsPlay())
		{
			state = State::IDLE;

			HS03_ChangeScene* scene = (HS03_ChangeScene*)SCENEMANAGER->GetScene("HS03_ChangeScene");
			HS05_Dialogue* Dialogue = (HS05_Dialogue*)SCENEMANAGER->GetScene("HS05_Dialogue");

			switch (Dialogue->GetSceneID())
			{
			case 0:
				scene->SetNextScene("HS06_Chapter02");
				break;
			case 1:
				scene->SetNextScene("HS07_Chapter03");
				break;
			case 2:
				scene->SetNextScene("HS08_Chapter04");
				break;
			case 3:
				scene->SetNextScene("HS10_Chapter05");
				break;
			case 4:
				scene->SetNextScene("HS11_Chapter06");
				break;
			case 5:
				scene->SetNextScene("HS13_Chapter07");
				break;
			case 6:
				scene->SetNextScene("HS14_Chapter08");
				break;
			case 7:
				scene->SetNextScene("HS15_Chapter09");
				break;
			}

			SCENEMANAGER->ChangeScene("HS03_ChangeScene");
		}
	}

	SetPosition(position);

	animation->SetRotation(GetRotation());
	animation->SetPosition(GetPosition());
	animation->SetPlay((UINT)state); //캐릭터의 상태가 바뀌어진다.
	animation->Update(V, P);

	collider->SetPosition(GetPosition());
	collider->SetRotation(GetRotation());
	collider->SetScale(animation->GetTextureRealSize());

	kickEffect->Update(V, P);
	dustEffect->Update(V, P);
	hugeEffect->Update(V, P);

	if (HTMAP->IsSlate(pt.x, pt.y))
	{
		Slate* slate = (Slate*)OBJMANAGER->FindObject("Slate");
		int state = slate->GetState();
		HTMAP->ReSetValue(pt.x, pt.y, HTMAP->slate);

		SCENEMANAGER->ChangeScene("HS09_SlateScene");
	}

	if (pt.x == 5 && pt.y == 0)
	{
		Helltaker* helltaker = dynamic_cast<Helltaker*>(OBJMANAGER->FindObject("Helltaker"));

		if (SCENEMANAGER->GetCurScene() == SCENEMANAGER->GetScene("HS15_Chapter09"))
		{
			if (HTMAP->GetGameObject(5, 0) == helltaker)
			{
				SCENEMANAGER->ChangeScene("HS05_Dialogue");
			}
		}
	}
	else
	{
		if (
		!goal &&
		(
			HTMAP->IsGoal(pt.x - 1, pt.y) ||
			HTMAP->IsGoal(pt.x + 1, pt.y) ||
			HTMAP->IsGoal(pt.x, pt.y + 1) ||
			HTMAP->IsGoal(pt.x, pt.y - 1)
		)
		)
		{
			goalTime += DELTA;
			float etime = 0.0f;

			if (SCENEMANAGER->GetLatScene() == SCENEMANAGER->GetScene("HS09_SlateScene"))
				etime = 0.25f;
			else if (SCENEMANAGER->GetCurScene() == SCENEMANAGER->GetScene("HS14_Chapter08"))
				etime = 0.25f;
			else
				etime = 0.125f;

			if (goalTime >= etime)
			{
				goalTime = etime;

				goal = true;
				SCENEMANAGER->ChangeScene("HS05_Dialogue");

				HS05_Dialogue* Dialogue = (HS05_Dialogue*)SCENEMANAGER->GetScene("HS05_Dialogue");
				Dialogue->SetReset(false);

				return;
			}
		}
	}

	if (hugeEffect->IsActive())
	{
		bloodTime += DELTA;

		if (bloodTime >= 0.5f)
			bloodTime = 0.0f;

		Color color = Color(0.8f, 0.0f, 0.0f, 1.0f);
		float ctime = 0.5f;

		if (hugeEffect->GetState() == 3)
		{
			color = Color(238.0f / 255.0f, 243.0f / 255.0f, 121.0f / 255.0f, 1.0f);
			ctime = 0.35f;
		}

		animation->UpdateColorBuffer(color, 5, ctime - bloodTime, 0.0f, 0.0f);
	}
	else
		animation->UpdateColorBuffer(Color(), 0, 0.0f, 0.0f, 0.0f);
}

void Helltaker::MoveObject(Direction direction, Vector2& position)
{
	POINT pt = HTMAP->GetMapXY(position);
	POINT oldpt = pt;

	switch (direction)
	{
	case GameObject::right:
		pt.x += 1;
		movePos = Vector2(10.0f, 0.0f);	// 10 pixel
		SetRotation(0.0f, 0.0f, 0.0f);
		break;
	case GameObject::left:
		pt.x -= 1;
		movePos = Vector2(-10.0f, 0.0f);
		SetRotation(0.0f, 180.0f, 0.0f);
		break;
	case GameObject::up:
		pt.y -= 1;
		movePos = Vector2(0.0f, 10.0f);
		break;
	case GameObject::down:
		pt.y += 1;
		movePos = Vector2(0.0f, -10.0f);
		break;
	}

	if (HTMAP->IsWall(pt.x, pt.y)) // 다음 갈 자리에 Wall 이 있는가 체크
	{
		kickEffect->SetActive(false);
		dustEffect->SetActive(false);
		return;
	}

	scenes.push_back(SCENEMANAGER->GetScene("HS10_Chapter05"));
	scenes.push_back(SCENEMANAGER->GetScene("HS11_Chapter06"));
	scenes.push_back(SCENEMANAGER->GetScene("HS13_Chapter07"));

	for (auto a : scenes)
	{
		if (SCENEMANAGER->GetCurScene() == a)
		{
			for (int i = 0; i < 10; i++)
			{
				string name = "Trap" + to_string(i);
				Trap* trap = (Trap*)OBJMANAGER->FindObject(name);

				if (trap)
					trap->Toggle();
			}
			break;
		}
	}

	if (HTMAP->IsKey(pt.x, pt.y))
	{
		if (HTMAP->IsBox(pt.x, pt.y))
		{
			Box* object = (Box*)HTMAP->GetGameObject(pt.x, pt.y);
			Vector2 pos = object->GetPosition();

			// 공격을 받으면 뒤로 밀리게 만든다.
			object->MoveObject(direction, pos);

			state = State::ATTACK;
			SetHP(GetHP() - 1);

			printf("\nAttack!");

			// effect next
			kickEffect->Random();
			kickEffect->SetScale(2.0f, 2.0f);
			kickEffect->SetActive(true);
			kickEffect->SetPosition(pos);

			return;
		}

		Key* key = (Key*)HTMAP->GetSecondObject(pt.x, pt.y);
		Vector2 pos = key->GetPosition();
		key->SetActive(false);

		HTMAP->ReSetValue(pt.x, pt.y, HTMAP->key);

		PLAYSOUND("KEY", sfxSize);

		haveKey = true;

		// Effect
		{
			hugeEffect->SetState(3);
			hugeEffect->SetActive(true);
			hugeEffect->SetPosition(pos);
		}

	}
	else if (HTMAP->IsMob(pt.x, pt.y))
	{
		// 해당되는 mob 에 전달을 해줘야한다.

		Mob* object = (Mob*)HTMAP->GetGameObject(pt.x, pt.y);
		Vector2 pos = object->GetPosition();

		object->MoveObject(direction, pos);

		state = State::ATTACK;

		CheckTrap(oldpt.x, oldpt.y);

		SetHP(GetHP() - 1);

		printf("\nAttack!");

		// effect next
		kickEffect->Random();
		kickEffect->SetScale(2.0f, 2.0f);
		kickEffect->SetActive(true);
		kickEffect->SetPosition(pos);

		return;
	}
	else if (HTMAP->IsBox(pt.x, pt.y))
	{
		// 해당되는 mob 에 전달을 해줘야한다.

		Box* object = (Box*)HTMAP->GetGameObject(pt.x, pt.y);
		Vector2 pos = object->GetPosition();

		// 공격을 받으면 뒤로 밀리게 만든다.
		object->MoveObject(direction, pos);

		state = State::ATTACK;

		CheckTrap(oldpt.x, oldpt.y);

		SetHP(GetHP() - 1);

		printf("\nAttack!");

		// effect next
		kickEffect->Random();
		kickEffect->SetScale(2.0f, 2.0f);
		kickEffect->SetActive(true);
		kickEffect->SetPosition(pos);

		return;
	}
	else if (HTMAP->IsLockBox(pt.x, pt.y))
	{
		LockBox* object = (LockBox*)HTMAP->GetGameObject(pt.x, pt.y);
		Vector2 pos = object->GetPosition();

		if (!haveKey)
		{
			PLAYSOUND("LOCKBOXKICK", sfxSize);

			kickEffect->SetActive(false);
			dustEffect->SetActive(false);

			SetHP(GetHP() - 1);

			state = State::ATTACK;

			// Effect
			kickEffect->Random();
			kickEffect->SetScale(2.0f, 2.0f);
			kickEffect->SetActive(true);
			kickEffect->SetPosition(pos);

			printf("\nLockBox");

			return;
		}
		else
		{
			PLAYSOUND("LOCKBOXOPEN", sfxSize);

			hugeEffect->SetActive(true);
			hugeEffect->SetPosition(pos);
			hugeEffect->SetState(3);
			object->SetActive(false);
			HTMAP->ReSetValue(pt.x, pt.y, HTMAP->lockBox);
		}
	}

	CheckTrap(pt.x, pt.y);

	HTMAP->ReSetValue(oldpt.x, oldpt.y, HTMAP->helltaker);
	HTMAP->SetValue(pt.x, pt.y, HTMAP->helltaker, this);
	state = State::WALK;
	time = 0.0f;
	moveCount = 0;

	dustEffect->Random();
	dustEffect->SetActive(true);
	dustEffect->SetPosition(position);

	if (SCENEMANAGER->GetCurScene()->GetSceneName() != "HS17_BossScene")
		SetHP(GetHP() - 1);
}

void Helltaker::Render()
{
	animation->Render();
	kickEffect->Render();
	dustEffect->Render();
	hugeEffect->Render();
	collider->Render();
}

void Helltaker::Reset()
{
	// animation Reset
	animation->UpdateColorBuffer(Color(), 0, 0, 0, 0);

	// Character Reset
	SetRotation(0.0f, 0.0f, 0.0f);

	// Status
	time		= 0.0f;
	bloodTime	= 0.0f;
	goalTime	= 0.0f;

	moveCount	= 0;
	movePos = Vector2(0.0f, 0.0f);
	state = State::IDLE;

	goal = false;
	haveKey = false;
	soundPlayed = false;

	// Effect Reset
	kickEffect->SetActive(false);
	dustEffect->SetActive(false);
	hugeEffect->SetActive(false);
}

void Helltaker::CheckTrap(int x, int y)
{
	if (HTMAP->IsTrap(x, y))
	{
		Trap* trap = (Trap*)HTMAP->GetSecondObject(x, y);

		if (trap->IsUp())
		{
			PLAYSOUND("TRAP", sfxSize);

			Vector2 pos = HTMAP->GetPosition(x, y);

			printf("\nTrap!");

			if (trap->IsKillState())
			{
				SetHP(GetHP() - 4);
				return;
			}
			else
				SetHP(GetHP() - 1);

			hugeEffect->Reset();
			hugeEffect->SetActive(true);
			hugeEffect->SetPosition(pos);
		}
	}
}

////////////////////////////////////////////////////////////
//	Movable
//	
////////////////////////////////////////////////////////////

void Helltaker::SetHuge()
{
	hugeEffect->Reset();
	hugeEffect->SetActive(true);
	hugeEffect->SetPosition(GetPosition());
}

bool Helltaker::IsAttacted()
{
	return hugeEffect->IsActive();
}

void Helltaker::ExternMoveObject(int vert, int horiz)
{
	//int  A[7];      //0110000
	//				//    *
	//memset(A, 0x00, sizeof(int) * 7);
	//
	//if (state == State::WALK)
	//	return;
	//
	//vector<int>     m_cvDisplay;
	//Vector2 position = GetPosition();
	//POINT   pt = HTMAP->GetMapXY(position);
	//POINT   movept = pt;
	//
	//pt.x = pt.x - 1;
	//pt.y = pt.y - 1;
	//
	//
	//if ((vert & 0x1000000) == 0x1000000)
	//	A[0] = 1;
	//if ((vert & 0x0100000) == 0x0100000)
	//	A[1] = 1;
	//if ((vert & 0x0010000) == 0x0010000)
	//	A[2] = 1;
	//if ((vert & 0x0001000) == 0x0001000)
	//	A[3] = 1;
	//if ((vert & 0x0000100) == 0x0000100)
	//	A[4] = 1;
	//if ((vert & 0x0000010) == 0x0000010)
	//	A[5] = 1;
	//if ((vert & 0x0000001) == 0x0000001)
	//	A[6] = 1;
	//
	//if (A[pt.x] == 0)
	//{
	//	if (pt.x == 0 && A[pt.x + 1] == 0)
	//		MoveObject(Right, position);
	//	else if (pt.x == 6 && A[pt.x - 1] == 0)
	//		MoveObject(Left, position);
	//}
	//
	//if (A[pt.x] == 1)
	//{
	//	if (pt.x > 0 && A[pt.x - 1] == 0)
	//		MoveObject(Left, position);
	//	else if (pt.x < 6 && A[pt.x + 1] == 0)
	//		MoveObject(Right, position);
	//	else if (pt.x == 0)
	//		MoveObject(Right, position);
	//	else if (pt.x == 6)
	//		MoveObject(Left, position);
	//	else
	//		MoveObject(Right, position);
	//}
	//
	//
	//memset(A, 0x00, sizeof(int) * 7);
	//
	//if ((horiz & 0x10000) == 0x10000)
	//	A[0] = 1;
	//
	//if ((horiz & 0x01000) == 0x01000)
	//	A[1] = 1;
	//if ((horiz & 0x00100) == 0x00100)
	//	A[2] = 1;
	//
	//if ((horiz & 0x00010) == 0x00010)
	//	A[3] = 1;
	//if ((horiz & 0x00001) == 0x00001)
	//	A[4] = 1;
	//
	//if (A[pt.y] == 0)
	//{
	//	if (pt.y == 1 && A[pt.y + 1] == 0)
	//		MoveObject(Down, position);
	//	else if (pt.y == 3 && A[pt.y - 1] == 0)
	//		MoveObject(Up, position);
	//}
	//
	//if (A[pt.y] == 1)
	//{
	//	if (pt.y > 1 && A[pt.y - 1] == 0)
	//		MoveObject(Up, position);
	//	else if (pt.y < 3 && A[pt.y + 1] == 0)
	//		MoveObject(Down, position);
	//	else if (pt.y == 1)
	//		MoveObject(Down, position);
	//	else if (pt.y == 3)
	//		MoveObject(Up, position);
	//	else
	//		MoveObject(Down, position);
	//}
	//
	//
	//return;
}