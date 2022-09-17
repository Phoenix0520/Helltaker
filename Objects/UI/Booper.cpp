#include "framework.h"
#include "Booper.h"

Booper::Booper()
{
	wstring imageFile1 = L"./Images/Booper/Booper (1).png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	animation = new Animation(imageFile1, shaderFile);

	// normal
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::State::loop);
		animation->AddClip(clip);

		for (int i = 1; i <= 16; i++)
		{
			wstring str = L"./Images/Booper/Booper (" + to_wstring(i) + L").png";

			clip->AddFrame(animation->GetTexture(), str, 0.0f, 0.0f, 100.0f, 100.0f, 0.05f);
		}

	}

	// clicked
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::State::once);
		animation->AddClip(clip);

		for (int i = 17; i <= 28; i++)
		{
			wstring str = L"./Images/Booper/Booper (" + to_wstring(i) + L").png";

			clip->AddFrame(animation->GetTexture(), str, 0.0f, 0.0f, 100.0f, 100.0f, 0.05f);
		}

	}
	animation->UpdateColorBuffer(Color(230.0f / 255.0f, 77.0f / 255.0f, 81.0f / 255.0f, 1.0f), 1, 0.0f, 0.0f, 0.0f);
}

Booper::~Booper()
{
	SAFE_DELETE(animation);
}

void Booper::Update(Matrix V, Matrix P)
{
	Vector2 position = GetPosition();

	animation->SetPlay(0);
	animation->SetPosition(position);
	animation->SetScale(1.0f, 1.0f);
	animation->SetRotation(0.0f, 0.0f, 0.0f);

	animation->Update(V, P);
}

void Booper::Render()
{
	animation->Render();
}

void Booper::Reset()
{
	animation->SetPlay(0);
}
