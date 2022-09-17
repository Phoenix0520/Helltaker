#include "framework.h"
#include "Key.h"

Key::Key()
{
	wstring imageFile1 = L"./Images/Key/Key.png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	animation = new Animation(imageFile1, shaderFile);

	AnimationClip* clip = new AnimationClip(AnimationClip::State::loop);
	animation->AddClip(clip);

	float x = 0.0f;
	for (int i = 1; i <= 12; i++)
	{
		clip->AddFrame(animation->GetTexture(), imageFile1, x, 20.0f, x + 100.0f, 150.0f, 0.06f);
		x += 100.0f;
	}

	SetActive(true);
}

Key::~Key()
{
	SAFE_DELETE(animation);
}

void Key::Update(Matrix V, Matrix P)
{
	if (!IsActive())
	{
		return;
	}
	Vector2 position = GetPosition();
	
	animation->SetPlay(0);
	animation->SetPosition(position);
	animation->SetScale(scale);
	animation->SetRotation(rotation);
	
	animation->Update(V, P);
}

void Key::Render()
{
	if (!IsActive())
	{
		return;
	}
	animation->Render();
}

void Key::Reset()
{
	SetActive(false);
}