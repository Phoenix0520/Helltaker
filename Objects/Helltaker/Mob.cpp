#include "framework.h"
#include "Mob.h"
#include "HelltakerMap.h"
#include "Trap.h"
#include "Bone.h"

/////////////////////////////////////////////////////
// Animation Create
//
/////////////////////////////////////////////////////
Mob::Mob()
{
	wstring imageFile1 = L"./Images/MobIDLE.png";
	wstring imageFile2 = L"./Images/MobAttacked.png";
	wstring shaderFile = L"./Shader/HLSL/Texture.hlsl";
	animation = new Animation(imageFile1, shaderFile);

	for (int i = 0; i < 10; i++)
	{
		int j = rand() % 9;
		Bone* pBone = new Bone(0, i);
		pBone->SetActive(false);
		pBone->Random();
		effect.push_back(pBone);
	}

	//bone = new Bone();

	// IDLE
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::State::loop);
		animation->AddClip(clip);

		float x = 0;
		for (int i = 0; i < 11; i++)
		{
			clip->AddFrame(animation->GetTexture(), imageFile1, x, 20.0f, x + 100.0f, 150.0f, 0.06f);
			x += 100.0f;
		}
	}
	// has been attacked
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::State::once);
		animation->AddClip(clip);

		float x = 0;
		for (int i = 0; i < 7; i++)
		{
			clip->AddFrame(animation->GetTexture(), imageFile2, x, 20.0f, x + 100.0f, 150.0f, 0.06f);
			x += 100.0f;
		}
	}
}

Mob::~Mob()
{
	//SAFE_DELETE(bone);
	SAFE_DELETE(animation);
}

void Mob::Update(Matrix V, Matrix P)
{
	Vector2 position = GetPosition();
	POINT pt = HTMAP->GetMapXY(position);

	SetPosition(position);

	if (state == State::ATTACKED)
		if (!animation->IsPlay())
			state = State::IDLE;

	animation->SetPlay((UINT)state);
	animation->SetPosition(position);
	animation->SetScale(scale);
	animation->SetRotation(rotation);
	animation->Update(V, P);

	for (UINT i = 0; i < effect.size(); i++)
		effect[i]->Update(V, P);

	if (HTMAP->IsTrap(pt.x, pt.y))
	{
		Trap* trap = (Trap*)HTMAP->GetSecondObject(pt.x, pt.y);
		if (trap->IsUp())
			time += DELTA;

		if (time >= 0.125f && IsActive())
		{
			string str = "MOBDIE" + to_string(soundID);

			if (!ISPLAYING(str))
				PLAYSOUND(str, sfxSize);

			time = 0.125f;
			state = State::ATTACKED;

			HTMAP->ReSetValue(pt.x, pt.y, HTMAP->mob);

			for (UINT i = 0; i < effect.size(); i++)
			{
				effect[i]->Reset();
				effect[i]->SetPosition(position);
				effect[i]->Update(V, P);
				effect[i]->SetActive(true);
			}

			SetActive(false);
		}
	}
}

void Mob::Render()
{
	for (UINT i = 0; i < effect.size(); i++)
		effect[i]->Render();
	if (IsActive())
		animation->Render();
}

void Mob::Reset()
{
	mt19937 engine((UINT)GetTickCount());
	uniform_int_distribution<int> distribution(1, 3);
	auto generator = bind(distribution, engine);

	soundID = generator();

	animation->SetPlay(0);
	SetRotation(0.0f, 0.0f, 0.0f);
	state = State::IDLE;
	time = 0.0f;
	destroy = false;
}

/////////////////////////////////////////////////////////////////
// 1. 현재 위치 에서 다음칸이 벽이 있을경우 사망 
// 2. 현재 위치 에서 다음칸이 Mob이 있을 경우 사망
// 3. 현재 위치 에서 다음칸이 박스가 있을경우 사망
/////////////////////////////////////////////////////////////////
void Mob::MoveObject(Direction direction, Vector2 & position)
{
	POINT pt = HTMAP->GetMapXY(position);
	POINT oldpt = pt;

	if (!IsActive()) return;

	switch (direction)
	{
	case GameObject::right:
		SetRotation(0.0f, 180.0f, 0.0f);
		pt.x += 1;
		break;
	case GameObject::left:
		SetRotation(0.0f, 0.0f, 0.0f);
		pt.x -= 1;
		break;
	case GameObject::up:
		pt.y -= 1;
		break;
	case GameObject::down:
		pt.y += 1;
		break;
	}

	string str = "MOBKICK" + to_string(soundID);

	if (!ISPLAYING(str))
		PLAYSOUND(str, sfxSize);

	if (HTMAP->IsWall(pt.x, pt.y))
	{
		str = "MOBDIE" + to_string(soundID);

		if (!ISPLAYING(str))
			PLAYSOUND(str, sfxSize);

		state = State::ATTACKED;
		HTMAP->ReSetValue(oldpt.x, oldpt.y, HTMAP->mob);
		// 뼈다구 이펙트

		Matrix V, P;
		V = CAMERA->GetViewMatrix();
		P = CAMERA->GetProjMatrix();

		for (UINT i = 0; i < effect.size(); i++)
		{
			effect[i]->Reset();
			effect[i]->SetPosition(position);
			effect[i]->Update(V, P);
			effect[i]->SetActive(true);
		}

		SetActive(false);

		return;
	}
	else if (HTMAP->IsBox(pt.x, pt.y))
	{
		str = "MOBDIE" + to_string(soundID);

		if (!ISPLAYING(str))
			PLAYSOUND(str, sfxSize);

		state = State::ATTACKED;
		HTMAP->ReSetValue(oldpt.x, oldpt.y, HTMAP->mob);
		// 뼈다구 이펙트
		for (UINT i = 0; i < effect.size(); i++)
		{
			effect[i]->Reset();
			effect[i]->SetPosition(position);
			effect[i]->SetActive(true);
		}

		SetActive(false);

		return;
	}
	else if (HTMAP->IsMob(pt.x, pt.y))
	{
		str = "MOBDIE" + to_string(soundID);

		if (!ISPLAYING(str))
			PLAYSOUND(str, sfxSize);

		state = State::ATTACKED;
		HTMAP->ReSetValue(oldpt.x, oldpt.y, HTMAP->mob);
		// 뼈다구 이펙트
		for (UINT i = 0; i < effect.size(); i++)
		{
			effect[i]->Reset();
			effect[i]->SetPosition(position);
			effect[i]->SetActive(true);
		}

		SetActive(false);

		return;
	}
	else
	{
		state = State::ATTACKED;
		HTMAP->ReSetValue(oldpt.x, oldpt.y, HTMAP->mob);
		HTMAP->SetValue(pt.x, pt.y, HTMAP->mob, this);

		Vector2 pos = HTMAP->GetPosition(pt.x, pt.y);
		SetPosition(pos);

		return;
	}

}