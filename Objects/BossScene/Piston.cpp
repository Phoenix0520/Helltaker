#include "framework.h"
#include "Piston.h"

Piston::Piston(float time)
{
	endTime = time;

	wstring imageFile1 = L"./Images/Boss/Piston/Piston (1).png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	uprPiston[0] = new Animation(imageFile1, shaderFile);
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::endStay);
		uprPiston[0]->AddClip(clip);

		for (UINT i = 1; i <= 7; i++)
		{
			wstring str = L"./Images/Boss/Piston/Piston (" + to_wstring(i) + L").png";
			
			if (i == 7)
				str = imageFile1;
			clip->AddFrame(uprPiston[0]->GetTexture(), str, 0, 0, 240, 800, 0.01f);
		}
	}

	uprPiston[0]->SetStop();
	uprPiston[0]->SetPosition(-770.0f, 570.0f);

	udrPiston[0] = new Animation(imageFile1, shaderFile);
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::endStay);
		udrPiston[0]->AddClip(clip);

		for (UINT i = 1; i <= 7; i++)
		{
			wstring str = L"./Images/Boss/Piston/Piston (" + to_wstring(i) + L").png";

			if (i == 7)
				str = imageFile1;
			clip->AddFrame(udrPiston[0]->GetTexture(), str, 0, 0, 240, 800, 0.01f);
		}
	}

	udrPiston[0]->SetStop();

	udrPiston[0]->SetPosition(770.0f, 570.0f);
	udrPiston[0]->SetRotation(0.0f, 180.0f, 0.0f);

	//////////////////////////////////////////////////////////////////////////////////////////////

	uprPiston[1] = new Animation(imageFile1, shaderFile);
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::endStay);
		uprPiston[1]->AddClip(clip);

		for (UINT i = 1; i <= 7; i++)
		{
			wstring str = L"./Images/Boss/Piston/Piston (" + to_wstring(i + 6) + L").png";

			if (i == 7)
				str = imageFile1;
			clip->AddFrame(uprPiston[1]->GetTexture(), str, 0, 0, 240, 800, 0.01f);
		}
	}

	uprPiston[1]->SetStop();

	uprPiston[1]->SetPosition(-770.0f, -570.0f);

	udrPiston[1] = new Animation(imageFile1, shaderFile);
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::endStay);
		udrPiston[0]->AddClip(clip);

		for (UINT i = 1; i <= 7; i++)
		{
			wstring str = L"./Images/Boss/Piston/Piston (" + to_wstring(i + 6) + L").png";

			if (i == 7)
				str = imageFile1;
			clip->AddFrame(udrPiston[1]->GetTexture(), str, 0, 0, 240, 800, 0.01f);
		}
	}

	udrPiston[1]->SetStop();

	udrPiston[1]->SetPosition(770.0f, -570.0f);
	udrPiston[1]->SetRotation(0.0f, 180.0f, 0.0f);
}

Piston::~Piston()
{
	SAFE_DELETE(udrPiston[0]);
	SAFE_DELETE(uprPiston[0]);
}

void Piston::Update(Matrix V, Matrix P)
{
	Vector2 pos1 = GetPosition();
	Vector2 pos2 = GetPosition();
	
	time += DELTA;

	UINT index = 0;

	if (time <= 0.5f)
	{
		pos1.y -= 600.0f * DELTA;
		SetPosition(pos1);
	}
	else if (time > 0.5f && time <= 1.0f)
	{
		udrPiston[0]->SetPlay(0);
		uprPiston[0]->SetPlay(0);
		SetPosition(pos1);
	}
	else if (time < 1.5f)
	{
		pos1.y += 600.0f * DELTA;
		SetPosition(pos1);
	}

	else if (time >= endTime - 1.0f && time < endTime - 0.5f)
	{
		pos2.y += 600.0f * DELTA;
		SetPosition(pos2);
		index = 1;
	}
	else if (time >= endTime - 0.5f && time < endTime)
	{
		udrPiston[1]->SetPlay(0);
		uprPiston[1]->SetPlay(0);
		SetPosition(pos2);
		index = 1;
	}
	else if (time < endTime + 0.5f)
	{
		pos2.y -= 600.0f * DELTA;
		SetPosition(pos2);
		index = 1;
	}

	udrPiston[index]->SetPosition(position);
	uprPiston[index]->SetPosition(position);

	for (UINT i = 0; i < 2; i++)
	{
		udrPiston[i]->Update(V, P);
		uprPiston[i]->Update(V, P);
	}
}

void Piston::Render()
{
	udrPiston[0]->Render();
	uprPiston[0]->Render();

	udrPiston[1]->Render();
	uprPiston[1]->Render();
}

void Piston::Reset()
{
	uprPiston[0]->SetPlay(0);
	uprPiston[0]->SetPlay(0);

	udrPiston[0]->SetStop();
	udrPiston[0]->SetStop();

	uprPiston[1]->SetPlay(0);
	uprPiston[1]->SetPlay(0);

	udrPiston[1]->SetStop();
	udrPiston[1]->SetStop();

	time = 0.0f;
}
