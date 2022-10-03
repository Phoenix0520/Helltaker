#include "framework.h"
#include "HS17_BossScene.h"
#include "Helltaker.h"
#include "HelltakerMap.h"
#include "Piston.h"
#include "LifeCount.h"
#include "Bridge.h"
#include "Trap.h"
#include "ChainVH.h"
#include "BossManager.h"

HS17_BossScene::HS17_BossScene()
{
	wstring imageFile1 = L"./Images/Boss/Background.png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	background = new Texture(imageFile1, shaderFile);

	rect = new Texture(imageFile1, shaderFile);
	rect->UpdateColorBuffer(Color(0.675f, 0.225f, 0.085f, 0.75f), 4);

	wstring imageFile2 = L"./Images/Boss/uprBorder.png";
	uprBorder = new Texture(imageFile2, shaderFile);
	imageFile2 = L"./Images/Boss/uprBorder2.png";
	uprBorder2 = new Texture(imageFile2, shaderFile);
	imageFile2 = L"./Images/Boss/udrBorder.png";
	udrBorder = new Texture(imageFile2, shaderFile);

	wstring imageFile3 = L"./Images/Boss/Gear/Gear (1).png";
	gear[0] = new Animation(imageFile3, shaderFile);
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::loop);
		gear[0]->AddClip(clip);
		
		for (UINT i = 1; i <= 15; i++)
		{
			wstring str = L"./Images/Boss/Gear/Gear (" + to_wstring(i) + L").png";
			clip->AddFrame(gear[0]->GetTexture(), str, 0, 0, 400, 300, 0.02f);
		}
	}
	gear[0]->SetPosition(-770.0f, -420.0f);
	gear[0]->SetPlay(0);

	gear[1] = new Animation(imageFile3, shaderFile);
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::loop);
		gear[1]->AddClip(clip);

		for (UINT i = 1; i <= 15; i++)
		{
			wstring str = L"./Images/Boss/Gear/Gear (" + to_wstring(i) + L").png";
			clip->AddFrame(gear[1]->GetTexture(), str, 0, 0, 400, 300, 0.02f);
		}
	}
	gear[1]->SetRotation(0.0f, 180.0f, 0.0f);
	gear[1]->SetPosition(770.0f, -420.0f);
	gear[1]->SetPlay(0);

	piston[0] = new Piston(-790.0f, endTime);
	piston[1] = new Piston(790.0f, endTime);
	piston[1]->SetRotation(0.0f, 180.0f, 0.0f);

	lifeCount = new LifeCount();

	bridge = new Bridge();

	manager = new BossManager();
	//chainVH = new ChainVH();

	//SetActive(false);
	SetDisplay(false);

	sceneName = "HS17_BossScene";

	helltaker = (Helltaker*)OBJMANAGER->FindObject("Helltaker");

	ChangeScene();
}

HS17_BossScene::~HS17_BossScene()
{
	SAFE_DELETE(background);
}

void HS17_BossScene::Update()
{
	CAMERA->Update();
	Matrix V = CAMERA->GetViewMatrix();
	Matrix P = CAMERA->GetProjMatrix();

	time += DELTA;

	if (DOWN('M'))
		lifeCount->DiscardLife();

	if (DOWN('R'))
	{
		Scene* scene = SCENEMANAGER->GetScene("HS03_ChangeScene");
		scene->SetNextScene("HS17_BossScene");
		SCENEMANAGER->ChangeScene("HS03_ChangeScene");
	}

	if (lifeCount->IsDead())
	{	
		helltaker->SetBoss(true);

		lifeCount->Reset();
		SCENEMANAGER->ChangeScene("HS00_DeadScene");

		Scene* scene = SCENEMANAGER->GetScene("HS03_ChangeScene");
		scene->SetNextScene("HS17_BossScene");
	}

	if (time > 3.0f);
	{
		for (UINT i = 0; i < 28; i++)
			traps[i]->SetActive(true);
	}

	background->Update(V, P);
	rect->Update(V, P);

	gear[0]->Update(V, P);
	gear[1]->Update(V, P);

	uprBorder->Update(V, P);
	uprBorder2->Update(V, P);

	piston[0]->Update(V, P);
	piston[1]->Update(V, P);

	udrBorder->Update(V, P);

	lifeCount->Update(V, P);

	if (time >= 1.5f)
	{
		working = true;
		bridge->SetMove(true);
	}
	if (time >= endTime - 1.25f)
	{
		working = false;
		bridge->SetMove(false);
	}

	bridge->Update(V, P);

	Vector2 pPos = helltaker->GetPosition();

	if (pPos.y > 180.0f || pPos.y < -320.0f)
	{
		//while (!lifeCount->IsDead())
			//lifeCount->DiscardLife();
	}

	if (working)
	{
		if (moveVal < 150.0f)
			moveVal += 150.0f * DELTA;
	}
	else
	{
		if (moveVal > 0.0f)
			moveVal -= 75.0f * DELTA;
		else
			moveVal = 0.0f;
	}

	pPos.y += moveVal * DELTA;

	helltaker->SetPosition(pPos);
	helltaker->Update(V, P);

	for (UINT i = 0; i < traps.size(); i++)
	{
		if (traps[i])
			traps[i]->Update(V, P);
	}

	MoveingTrap();

	//chainVH->Update(V, P);

	//for (UINT i = 0; i < 12; i++)
		//ChainAttacking(i);
	manager->Update(V, P);
}

void HS17_BossScene::Render()
{
	background->Render();
	rect->Render();
	gear[0]->Render();
	gear[1]->Render();

	uprBorder->Render();

	piston[0]->Render();
	piston[1]->Render();
	
	bridge->Render();

	for (UINT i = 0; i < traps.size(); i++)
	{
		if (traps[i])
			traps[i]->Render();
	}

	uprBorder2->Render();
	udrBorder->Render();

	lifeCount->Render();

	helltaker->Render();
	manager->Render();
	//chainVH->Render();
}

void HS17_BossScene::ChangeScene()
{
	cout << "ChangeScene : HS17_BossScene" << endl;

	SetActive(true);
	HTMAP->Clear();

	time = 0.0f;
	moveVal = 0.0f;
	working = false;

	lifeCount->Reset();
	helltaker->Reset();
	helltaker->SetPosition(0.0f, -100.0f);
	helltaker->SetBoss(true);
	
	bridge->Reset();
	piston[0]->Reset();
	piston[1]->Reset();

	traps.clear();

	for (UINT i = 0; i < 28; i++)
	{
		Trap* trap = (Trap*)OBJMANAGER->FindObject("Trap" + to_string(i + 1));
		traps.push_back(trap);
	}

	float x = -300.0f; 
	for (UINT i = 0; i < 7; i++)
	{
		if (!traps[27])
			return;

		traps[i]->SetPosition(x, 330.0f);
		traps[i]->SetActive(false);
		traps[i + 7]->SetPosition(x, 230.0f);

		traps[i + 14]->SetPosition(x, -280.0f);
		traps[i + 14]->SetActive(false);
		traps[i + 21]->SetPosition(x, -380.0f);
		x += 100.0f;
	}

	manager->Reset();
	SetPhase();
	//chainVH->SetActive(true);
}

void HS17_BossScene::MoveingTrap()
{
	static bool stop = false;

	if (DOWN('X'))
		stop = true;
	if (DOWN('C'))
		stop = false;

	if (stop)
		return;

	float x = -300.0f;

	for (UINT i = 0; i < 14; i++)
	{
		Vector2 pos = traps[i]->GetPosition();

		if (pos.y > 250.0f)
		{
			traps[i]->SetState(2);
		}

		if (pos.y > 330.0f)
		{
			pos.y = 130.0f;
			traps[i]->SetState(3);
		}

		{
			pos.y += bridge->GetMoveVal();
			traps[i]->SetPosition(pos);
		}

		x += 100.0f;

		if (i == 6)
			x = 0.0f;
	}

	for (UINT i = 14; i < 28; i++)
	{
		Vector2 pos = traps[i]->GetPosition();

		if (pos.y > -310.0f)
		{
			traps[i]->SetState(2);
		}

		if (pos.y > -280.0f)
		{
			pos.y = -480.0f;
			traps[i]->SetState(3);
		}

		{
			pos.y += bridge->GetMoveVal();
			traps[i]->SetPosition(pos);
		}

		x += 100.0f;

		if (i == 21)
			x = 0.0f;
	}
}

void HS17_BossScene::SetPhase()
{
	manager->PushChain(0, 0x0000000, 3.0f);

	manager->PushChain(0, 0x0001000, 0.0f);
	manager->PushChain(1, 0x00100, 1.25f);
	manager->PushChain(0, 0x0010100, 0.0f);
	manager->PushChain(1, 0x01010, 1.25f);
	manager->PushChain(0, 0x1000001, 0.0f);
	manager->PushChain(1, 0x10001, 1.25f);

	manager->PushChain(0, 0x1001000, 0.0f);
	manager->PushChain(1, 0x01000, 1.25f);
	manager->PushChain(0, 0x0100100, 0.0f);
	manager->PushChain(1, 0x00010, 1.25f);
	manager->PushChain(0, 0x0001001, 0.0f);
	manager->PushChain(1, 0x01000, 1.25f);

	manager->PushChain(0, 0x1000001, 0.75f);
	manager->PushChain(0, 0x0100010, 0.75f);
	manager->PushChain(0, 0x0010100, 0.75f);
	manager->PushChain(0, 0x0001000, 0.75f);
	manager->PushChain(0, 0x0010100, 0.75f);
	manager->PushChain(0, 0x0100010, 0.75f);
	manager->PushChain(0, 0x1000001, 1.5f);

	manager->PushChain(0, 0x1000001, 0.75f);
	manager->PushChain(0, 0x0100010, 0.75f);
	manager->PushChain(0, 0x0010100, 0.75f);
	manager->PushChain(0, 0x0001000, 0.75f);

	manager->PushChain(0, 0x1000001, 0.0f);
	manager->PushChain(1, 0x10001, 1.0f);
	manager->PushChain(0, 0x0100010, 0.0f);
	manager->PushChain(1, 0x010010, 1.0f);
	manager->PushChain(0, 0x0001000, 0.0f);
	manager->PushChain(1, 0x00100, 1.25f);

	manager->PushChain(0, 0x0010100, 0.0f);
	manager->PushChain(1, 0x10001, 1.0f);
	manager->PushChain(0, 0x0001000, 0.0f);
	manager->PushChain(1, 0x01010, 1.0f);
	manager->PushChain(0, 0x0011100, 1.25f);

	manager->PushChain(0, 0x1000001, 0.0f);
	manager->PushChain(1, 0x10001, 1.0f);
	manager->PushChain(0, 0x1100011, 0.0f);
	manager->PushChain(1, 0x00100, 1.0f);
	manager->PushChain(0, 0x1110111, 2.0f);

	for (UINT i = 0; i < 10; i++)
	{
		manager->PushChain(0, 0x1000001, 1.35f);
		manager->PushChain(1, 0x10001, 1.35f);
		manager->PushChain(0, 0x0100010, 0.0f);
		manager->PushChain(1, 0x10010, 1.35f);
		manager->PushChain(0, 0x0010100, 0.0f);
		manager->PushChain(1, 0x01001, 1.35f);
	}

	//cout << "Phase 4 Start!" << endl;
	//PushChain(0, 0x1010101);
	//PushChain(0, 0x0101010);
	//PushChain(1, 0x01010);
	//PushChain(1, 0x10101);
}

void HS17_BossScene::PushChain(int type, int val)
{
	//chainVH->PushChain(push, type, val);
	//push++;
}

void HS17_BossScene::DiscardLife()
{
	helltaker->Attacked();

	if (lifeCount)
		lifeCount->DiscardLife();
}

//void HS17_BossScene::Activate(float time)
//{
//	if (time > ctime)
//	{
//		ctime += DELTA;
//		return;
//	}
//	else if (ctime < 777.7f)
//	{
//		cout << "Activate!" << endl;
//
//		for (UINT i = 0; i < chainWork.size(); i++)
//		{
//			if (chainWork[i])
//			{
//				chainVH->SetPosByID(i);
//				chainVH->Reset();
//			}
//		}
//
//		ctime = 777.7f;
//	}
//}

//void HS17_BossScene::ChainAttacking(int index)
//{
//	if (Collider::InterSect(helltaker->GetCollider(), chainVH->GetCollider()))
//	{
//		if (chainVH->IsAttacking(index) && !attacked)
//		{
//			lifeCount->DiscardLife();
//			helltaker->Attacked();
//			attacked = true;
//		}
//	}
//}
