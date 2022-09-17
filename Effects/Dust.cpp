#include "framework.h"
#include "Dust.h"

Dust::Dust()
{
	wstring imageFile1 = L"./Images/Effects/Dust.png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	animation = new Animation(imageFile1, shaderFile);

	SetActive(false);

	//Dust 1
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::State::once);
		animation->AddClip(clip);
		float x = 0.0f;

		for (int i = 0; i < 3; i++)
		{
			clip->AddFrame(animation->GetTexture(), imageFile1, x, 0.0f, x + 100.0f, 100.0f, 0.15f);
			x += 100.0f;
		}
	}
	// Dust 2
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::State::once);
		animation->AddClip(clip);
		float x = 400.0f;

		for (int i = 0; i < 3; i++)
		{
			clip->AddFrame(animation->GetTexture(), imageFile1, x, 0.0f, x + 100.0f, 100.0f, 0.15f);
			x += 100.0f;
		}
	}
	// Dust 3
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::State::once);
		animation->AddClip(clip);
		float x = 700.0f;

		for (int i = 0; i < 3; i++)
		{
			clip->AddFrame(animation->GetTexture(), imageFile1, x, 0.0f, x + 100.0f, 100.0f, 0.15f);
			x += 100.0f;
		}
	}
}

Dust::~Dust()
{
	SAFE_DELETE(animation);
}

void Dust::Update(Matrix V, Matrix P)
{
	Vector2 position = GetPosition();

	position.y -= 25.0f;

	Color color = Color(1.0f, 150.0f/255.0f, 165.0f/255.0f, 0.0f);

	animation->GetTexture()->UpdateColorBuffer(color, 1, 0.0f, 0.0f, 0.0f);
	animation->SetPlay((UINT)state);
	animation->SetScale(scale);
	animation->SetPosition(position);
	animation->SetRotation(rotation);

	//if (IsActive() && !audio->Playing("Move"))
	//	audio->Play("Move", 0.75f);

	animation->Update(V, P);
}

void Dust::Render()
{
	if (IsActive())
		animation->Render();
}

void Dust::Reset()
{
	SetActive(false);
}

void Dust::Random()
{
	while (1)
	{
		int id = rand() % 3;
		if (id == state) continue;

		state = id;

		break;
	}
}

bool Dust::IsPlay()
{
	return animation->IsPlay();
}
