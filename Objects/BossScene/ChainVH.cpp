#include "framework.h"
#include "ChainVH.h"

ChainVH::ChainVH()
{
	wstring imageFile1 = L"./Images/Boss/ChainVH.png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	texture = new Texture(imageFile1, shaderFile);

	collider = new Collider();

	SetScale(0.75f, 0.75f);
	SetActive(false);
}

ChainVH::~ChainVH()
{
	SAFE_DELETE(texture);
	SAFE_DELETE(collider);
}

void ChainVH::Update(Matrix V, Matrix P)
{
	if (!active)
		return;

	mt19937 engine((UINT)GetTickCount());
	uniform_int_distribution<> distribution(1, 4);
	auto generator = bind(distribution, engine);

	time += DELTA * 1.1f;

	if (time >= 0.0f && time < 0.5f)
	{
		Vector2 value = Vector2(1.5f, 0.0f);
		scale -= DELTA * value;

		texture->UpdateColorBuffer(Color(1, 1, 1, 0.25f), 4);
		texture->SetScale(scale);
		attacking = false;
	}
	else if (time >= 0.5f && time < 0.8f)
	{
		Vector2 value = Vector2(3.0f, 0.0f);

		if (time < 0.65f)
			scale += DELTA * value;
		else
			scale -= DELTA * value;

		texture->UpdateColorBuffer(Color(1, 1, 1, 1.0f), 4);
		texture->SetScale(scale);

		if (!soundPlayed)
		{
			string str = "CHAINBLINK1";// +to_string(generator());

			if (!ISPLAYING(str))
				PLAYSOUND(str, sfxSize); 
		}

		collider->SetPosition(texture->GetPosition());
		collider->SetRotation(texture->GetRotation());
		collider->SetScale(texture->GetTextureRealSize());
		collider->Update(V, P);

		attacking = true;
		soundPlayed = true;
	}
	else
	{
		soundPlayed = false;
		attacking = false;
		SetActive(false);
	}

	texture->Update(V, P);
}

void ChainVH::Render()
{
	if (!active)
		return;

	texture->Render();

	if (time >= 0.5f && time < 0.8f)
		collider->Render();
}

void ChainVH::Reset()
{
	SetScale(0.75f, 0.75f);
	time = 0.0f;
	attacking = false;
	SetActive(true);
}

void ChainVH::SetPosByID(int id)
{
	if (id < 7)
	{
		texture->SetPosition((id - 3) * -100.0f, 0.0f);
		texture->SetRotation(0.0f, 0.0f, 0.0f);

	}
	else
	{
		texture->SetPosition(0.0f, (id - 10) * 100.0f);
		texture->SetRotation(0.0f, 0.0f, 90.0f);
	}
}
