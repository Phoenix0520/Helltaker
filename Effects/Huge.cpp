#include "framework.h"
#include "Huge.h"
#include "Helltaker.h"

Huge::Huge()
{
	wstring imageFile1 = L"./Images/Effects/Huge/Huge (1).png"; // 340 x 340
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	animation = new Animation(imageFile1, shaderFile);

	//Huge 1 1 ~ 7
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::State::end);
		animation->AddClip(clip);
		
		for (int i = 1; i <= 7; i++)
		{
			wstring str = L"./Images/Effects/Huge/Huge (" + to_wstring(i) + L").png";
			clip->AddFrame(animation->GetTexture(), str, 0.0f, 0.0f, 340.0f, 340.0f, 0.05f);
		}
	}
	// Huge 2 8 ~ 13
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::State::end);
		animation->AddClip(clip);
		
		for (int i = 8; i <= 13; i++)
		{
			wstring str = L"./Images/Effects/Huge/Huge (" + to_wstring(i) + L").png";
			clip->AddFrame(animation->GetTexture(), str, 0.0f, 0.0f, 340.0f, 340.0f, 0.05f);
		}
	}
	// Huge 3 14 ~ 19
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::State::end);
		animation->AddClip(clip);

		for (int i = 14; i <= 19; i++)
		{
			wstring str = L"./Images/Effects/Huge/Huge (" + to_wstring(i) + L").png";
			clip->AddFrame(animation->GetTexture(), str, 0.0f, 0.0f, 340.0f, 340.0f, 0.05f);
		}
	}

	// Huge_Yellow 4 1 ~ 9
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::State::end);
		animation->AddClip(clip);

		for (int i = 1; i <= 9; i++)
		{
			wstring str = L"./Images/Effects/Huge/Huge_Yellow (" + to_wstring(i) + L").png";
			clip->AddFrame(animation->GetTexture(), str, 0.0f, 0.0f, 340.0f, 340.0f, 0.05f);
		}
	}

	SetActive(false);
}

Huge::~Huge()
{
	SAFE_DELETE(animation);
}

void Huge::Update(Matrix V, Matrix P)
{
	if (!IsActive())
	{
		return;
	}

	if (!animation->IsPlay())
		SetActive(false);

	Vector2 position = GetPosition();

	Helltaker* ht = (Helltaker*)OBJMANAGER->FindObject("Helltaker");

	position.x = ht->GetPosition().x;
	position.y -= 25.0f;

	animation->SetPlay((UINT)state);
	animation->SetScale(scale);
	animation->SetPosition(position);
	animation->SetRotation(rotation);


	animation->Update(V, P);
}

void Huge::Render()
{
	if (IsActive())
	{
		animation->Render();
	}
}

void Huge::Reset()
{
	Random();
	SetActive(false);
}

void Huge::Random()
{
	while (1)
	{
		int id = rand() % 3;
		if (id == state) continue;

		state = id;

		break;
	}
}

bool Huge::IsPlay()
{
	return animation->IsPlay();
}
