#include "framework.h"
#include "Kick.h"

Kick::Kick()
{
	wstring imageFile1 = L"./Images/Effects/Kick.png";
	wstring shaderFile = L"./Shader/HLSL/Texture.hlsl";

	animation = new Animation(imageFile1, shaderFile);

	SetActive(false);

	//Kick 1
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::State::once);
		animation->AddClip(clip);
		float x = 0.0f;

		for (int i = 0; i < 4; i++)
		{
			clip->AddFrame(animation->GetTexture(), imageFile1, x, 0.0f, x + 100.0f, 100.0f, 0.1f);
			x += 100.0f;
		}
	}
	// Kick 2
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::State::once);
		animation->AddClip(clip);
		float x = 500.0f;

		for (int i = 0; i < 4; i++)
		{
			clip->AddFrame(animation->GetTexture(), imageFile1, x, 0.0f, x + 100.0f, 100.0f, 0.1f);
			x += 100.0f;
		}
	}

}

Kick::~Kick()
{
	SAFE_DELETE(animation);
}

void Kick::Update(Matrix V, Matrix P)
{
	Vector2 position = GetPosition();

	
	animation->SetPlay((UINT)state);
	animation->SetScale(scale);
	animation->SetPosition(position);
	animation->SetRotation(rotation);

	animation->Update(V, P);
}

void Kick::Render()
{
	if (IsActive())
		animation->Render();
}

void Kick::Reset()
{
	SetActive(false);
}

void Kick::Random()
{
	while (1)
	{
		int id = rand() % 2;
		if (id == state) continue;

		state = id;

		break;
	}
}

bool Kick::IsPlay()
{
	return animation->IsPlay();
}
