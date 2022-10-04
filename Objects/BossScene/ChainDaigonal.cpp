#include "framework.h"
#include "HelltakerMap.h"
#include "ChainDaigonal.h"
#include "Animation.h"
#include "AnimationClip.h"
#include "Helltaker.h"
#include "Collider.h"


//////////////////////////////////////////
//
ChainDaigonal::ChainDaigonal()
{
	wstring imageFile1 = L"./Images/Boss/ChainVH2.png";
	wstring imageFile2 = L"./Images/Boss/ChainBroken.png";
	wstring imageFile3 = L"./Images/Boss/HPBorder.png";
	wstring imageFile4 = L"./Images/Boss/HPBar.png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	for (UINT i = 0; i < 4; i++)
	{
		Texture* tex = new Texture(imageFile1, shaderFile);
		tex->UpdateColorBuffer(Color(1.0f, 1.0f, 1.0f, 0.65f), 7);
		//-638 542 160

		switch (i)
		{
		case 0:
			tex->SetPosition(-640.0f, 540.0f);
			break;
		case 1:
			tex->SetPosition(-640.0f, 160.0f);
			break;
		case 2:
			tex->SetPosition(640.0f, 540.0f);
			break;
		case 3:
			tex->SetPosition(640.0f, 160.0f);
			break;
		}

		if (i < 2)
			tex->SetRotation(0.0f, 0.0f, 25.0f);
		else
			tex->SetRotation(0.0f, 180.0f, 25.0f);

		texture.push_back(tex);
	}

	broken = new Texture(imageFile2, shaderFile);

	hpBorder = new Texture(imageFile3, shaderFile);
	hpBorder->SetPosition(0.0f, 420.0f);

	hpBar = new Texture(imageFile4, shaderFile);
	hpBar->SetPosition(0.0f, 420.0f);

	hp.resize(4, 4);
	SetActive(false);
}

ChainDaigonal::~ChainDaigonal()
{
	for (UINT i = 0; i < 4; i++)
		SAFE_DELETE(texture[i]);
}

void ChainDaigonal::Update(Matrix V, Matrix P)
{
	if (!active)
		return;

	static bool plus = true;
	
	if (ctime >= 0.5f)
		plus = false;
	if (ctime <= 0.0f)
		plus = true;

	if (plus)
		ctime += DELTA * 0.5f;
	else
		ctime -= DELTA * 0.5f;

	for (UINT i = 0; i < 4; i++)
	{
		if (hp[i] > 0)
		{
			texture[i]->UpdateColorBuffer(Color(0, 0, 0, ctime + 0.25f), 7);
			texture[i]->Update(V, P);
		}

		if (hp[i] == 0)
		{
			time += DELTA;

			if (time <= 0.75f)
			{
				if (!soundPlayed)
					PLAYSOUND("CHAINBREAK", sfxSize);

				broken->UpdateColorBuffer(Color(0, 0, 0, time + 0.25f), 7);
				broken->Update(V, P);

				soundPlayed = true;
			}
		}
	}

	hpBorder->Update(V, P);

	float x = 0;
	for (UINT i = 0; i < 4; i++)
	{
		x += hp[i];
	}

	float size = hpBar->GetTextureRealSize().x / 2;
	hpBar->SetPosition(size - 264.0f, 390.0f);
	hpBar->SetScale(x / 16, 1.0f);
	hpBar->Update(V, P);
}

void ChainDaigonal::Render()
{
	if (!active)
		return;

	for (UINT i = 0; i < 4; i++)
	{
		if (hp[i] > 0)
			texture[i]->Render();

		if (time <= 0.5f)
			broken->Render();
	}

	hpBorder->Render();
	hpBar->Render();
}

void ChainDaigonal::Reset()
{
	SetActive(true);
	hp.resize(4, 4);
}

void ChainDaigonal::Attack(int index)
{
	if (index < 2)
		PLAYSOUND("CHAINKICK_L", sfxSize);
	else
		PLAYSOUND("CHAINKICK_R", sfxSize);

	if (hp[index] > 0)
	{
		hp[index]--;
	}

	if (hp[index] == 0)
	{
		broken->SetPosition(texture[index]->GetPosition());
		broken->SetRotation(texture[index]->GetRotation());

		soundPlayed = false;
		time = 0.0f;
	}
}
