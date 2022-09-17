#include "framework.h"
#include "Fire.h"

Fire::Fire()
{
	wstring imageFile1 = L"./Images/Box/FireBox (1).png"; // nonFired
	wstring imageFile2 = L"./Images/Box/FireBox (2).png"; // Fired

	wstring imageFile3 = L"./Images/Effects/Fire/Fire (1).png";

	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	texture[0] = new Texture(imageFile1, shaderFile);
	texture[1] = new Texture(imageFile2, shaderFile);

	animation = new Animation(imageFile3, shaderFile);

	AnimationClip* clip = new AnimationClip(AnimationClip::State::loop);
	animation->AddClip(clip);

	for (int i = 1; i <= 12; i++)
	{
		wstring str = L"./Images/Effects/Fire/Fire (" + to_wstring(i) + L").png";
		clip->AddFrame(animation->GetTexture(), str, 0.0f, 0.0f, 120.0f, 116.0f, 0.06f);
	}

}

Fire::~Fire()
{
	SAFE_DELETE(texture[0]);
	SAFE_DELETE(texture[1]);
	SAFE_DELETE(animation);
}

void Fire::Update(Matrix V, Matrix P)
{
	Vector2 position = GetPosition();
	//position.y -= 35.0f;
	//position.x -= 5.0f;
	Vector2 size = texture[0]->GetTextureRealSize();

	texture[0]->SetPosition(position);
	texture[0]->SetScale(scale);
	texture[0]->SetRotation(rotation);

	texture[1]->SetPosition(position);
	texture[1]->SetScale(scale);
	texture[1]->SetRotation(rotation);

	animation->SetPlay(0);
	animation->SetPosition(position.x, position.y + size.y * 0.5f);
	animation->SetScale(Vector2(0.6f, 0.6f));
	animation->SetRotation(rotation);

	Color color = Color(0.9f, 0.76f, 0.4f, 1.0f);

	switch (state)
	{
	case 0:
		animation->UpdateColorBuffer(Color(), 0, 0.0f, 0.0f, 0.0f);
		texture[0]->Update(V, P);
		//animation->Update(V, P);
		break;

	case 1:
		animation->UpdateColorBuffer(color, 1, 0.0f, 0.0f, 0.0f);
		texture[1]->Update(V, P);
		animation->Update(V, P);
		break;

	case 2:
		animation->UpdateColorBuffer(Color(), 0, 0.0f, 0.0f, 0.0f);
		animation->Update(V, P);
		texture[1]->Update(V, P);
		break;
	}

}

void Fire::Render()
{
	switch (state)
	{
	case 0:
		//animation->Render();
		texture[0]->Render();
		break;

	case 1:
		texture[1]->Render();
		animation->Render();
		break;

	case 2:
		texture[1]->Render();
		animation->Render();
		break;
	}
}

void Fire::Reset()
{
}

bool Fire::IsPlay()
{
	return false;
}
