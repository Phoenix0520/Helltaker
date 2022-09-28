#include "framework.h"
#include "LifeCount.h"

LifeCount::LifeCount()
{
	wstring imageFile1 = L"./Images/Boss/SinPyre.png"; // 248 120
	wstring imageFile2 = L"./Images/Boss/Fire (1).png"; // 120 116
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	texture.push_back(new Texture(imageFile1, shaderFile));
	texture.push_back(new Texture(imageFile1, shaderFile));
	texture.push_back(new Texture(imageFile1, shaderFile));
	texture.push_back(new Texture(imageFile1, shaderFile));

	for (UINT i = 0; i < 4; i++)
	{
		texture[i]->SetOffset(208.0f, 0.0f);
		texture[i]->SetOffsetSize(207.0f, 100.0f);
	
		fire[i] = new Animation(imageFile2, shaderFile);

		AnimationClip* clip = new AnimationClip(AnimationClip::loop);
		fire[i]->AddClip(clip);

		for (UINT j = 1; j <= 12; j++)
		{
			wstring str = L"./Images/Boss/Fire (" + to_wstring(j) + L").png";
			clip->AddFrame(fire[i]->GetTexture(), str, 0, 0, 120.0f, 116.0f, 0.1f);
		}

		float x = 0.0f;
		switch (i)
		{
		case 0:
			x = -425.0f;
			break;
		case 1:
			x = -255.0f;
			break;
		case 2:
			x = 255.0f;
			break;
		case 3:
			x = 425.0f;
			break;
		}
		fire[i]->SetScale(0.9f, 0.9f);

		texture[i]->SetPosition(x, -490.0f);
		fire[i]->SetPosition(x, -470.0f);

	
		life[i] = true;
	}
}

LifeCount::~LifeCount()
{
	for (UINT i = 0; i < 4; i++)
	{
		SAFE_DELETE(texture[i]);
		SAFE_DELETE(fire[i]);
	}
}

void LifeCount::Update(Matrix V, Matrix P)
{
	for (UINT i = 0; i < 4; i++)
	{
		if (life[i])
		{
			fire[i]->Update(V, P);
			texture[i]->SetOffset(208.0f, 0.0f);
		}
		else
			texture[i]->SetOffset(0.0f, 0.0f);

		texture[i]->Update(V, P);
	}
}

void LifeCount::Render()
{
	for (UINT i = 0; i < texture.size(); i++)
	{
		texture[i]->Render();

		if (life[i])
		{
			fire[i]->Render();
		}
	}
}

void LifeCount::Reset()
{
}

void LifeCount::DiscardLife()
{
	for (UINT i = 0; i < 4; i++)
	{
		if (life[i])
		{
			life[i] = false;
			break;
		}
	}
}
