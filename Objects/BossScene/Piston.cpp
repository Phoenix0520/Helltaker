#include "framework.h"
#include "Piston.h"
#include "Chain.h"

Piston::Piston(float x, float time)
{
	endTime = time;
	this->x = x;

	if (time < 4.0f)
		time = 6.0f;

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
	uprPiston[0]->SetPosition(x, 590.0f);

	//////////////////////////////////////////////////////////////////////////////////////

	imageFile1 = L"./Images/Boss/Piston/Piston (7).png";
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
	uprPiston[1]->SetPosition(x, 590.0f);

	////////////////////////////////////////////////////////////////////////////////////////////

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

	udrPiston[0]->SetPosition(x, -800.0f);

	//////////////////////////////////////////////////////////////////////////////////////////////
	imageFile1 = L"./Images/Boss/Piston/Piston (7).png";
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
	udrPiston[1]->SetPosition(x, -800.0f);

	////////////////////////////////////////////////////////////////

	chain = new Chain(x);

	wstring imageFile2 = L"./Images/Boss/Skull.png";
	wstring imageFile3 = L"./Images/Boss/Skull2.png";

	lwrSkull = new Texture(imageFile2, shaderFile);
	hirSkull = new Texture(imageFile3, shaderFile);
	
	if (x > 0)
	{
		lwrSkull->SetPosition(x - 100.0f, -170.0f);
		hirSkull->SetPosition(x - 100.0f, -170.0f);
	}
	else
	{
		lwrSkull->SetPosition(x + 100.0f, -170.0f);
		hirSkull->SetPosition(x + 100.0f, -170.0f);
	}

}

Piston::~Piston()
{
	SAFE_DELETE(udrPiston[0]);
	SAFE_DELETE(uprPiston[0]);
}

void Piston::Update(Matrix V, Matrix P)
{
	Vector2 pos1 = uprPiston[0]->GetPosition();
	Vector2 pos2 = udrPiston[0]->GetPosition();
	Vector2 pos3 = hirSkull->GetPosition();

	time += DELTA;

	if (time <= 0.5f)
	{
		pos1.y -= 400.0f * DELTA;
	}
	else if (time > 0.5f && time <= 1.0f)
	{
		uprPiston[0]->SetPlay(0);
		uprPiston[1]->SetPlay(0);
	}
	else if (time > 1.0f && time <= 1.5f)
	{
		pos1.y += 400.0f * DELTA;
		pos3.y += 400.0f * DELTA;
	}
	else if (time > 1.5f)
	{
		chain->SetMove(true);
	}

	if (time >= endTime - 1.5f)
	{
		chain->SetMove(false);
	}

	if (time >= endTime - 1.0f && time < endTime - 0.5f)
	{
		pos2.y += 400.0f * DELTA;
	}
	else if (time >= endTime - 0.5f && time < endTime)
	{
		udrPiston[0]->SetPlay(0);
		udrPiston[1]->SetPlay(0);
	}
	else if (time >= endTime && time < endTime + 0.5f)
	{
		pos2.y -= 400.0f * DELTA;
		pos3.y -= 400.0f * DELTA;
	}
	/*else if (time >= (endTime + 0.5f))
	{
	}*/


	uprPiston[0]->SetPosition(pos1);
	uprPiston[0]->SetRotation(rotation);

	uprPiston[1]->SetPosition(pos1);
	uprPiston[1]->SetRotation(rotation);

	udrPiston[0]->SetPosition(pos2);
	udrPiston[0]->SetRotation(rotation);

	udrPiston[1]->SetPosition(pos2);
	udrPiston[1]->SetRotation(rotation);

	uprPiston[1]->Update(V, P);
	uprPiston[0]->Update(V, P);
	udrPiston[1]->Update(V, P);
	udrPiston[0]->Update(V, P);

	
	chain->SetRotation(rotation);
	chain->Update(V, P);

	hirSkull->SetPosition(pos3);
	hirSkull->SetRotation(rotation);
	hirSkull->Update(V, P);
	
	lwrSkull->SetPosition(pos3);
	lwrSkull->SetRotation(rotation);
	lwrSkull->Update(V, P);
}

void Piston::Render()
{
	uprPiston[0]->Render();
	lwrSkull->Render();
	chain->Render();
	hirSkull->Render();
	udrPiston[0]->Render();


	udrPiston[1]->Render();
	uprPiston[1]->Render();
}

void Piston::Reset()
{
	chain->SetMove(false);
	chain->SetMoveVal(0.0f);

	uprPiston[0]->SetPlay(0);
	uprPiston[0]->SetPlay(0);

	udrPiston[0]->SetStop();
	udrPiston[0]->SetStop();

	uprPiston[1]->SetPlay(0);
	uprPiston[1]->SetPlay(0);

	udrPiston[1]->SetStop();
	udrPiston[1]->SetStop();

	time = 0.0f;

	if (x > 0)
	{
		lwrSkull->SetPosition(x - 100.0f, -170.0f);
		hirSkull->SetPosition(x - 100.0f, -170.0f);
	}
	else
	{
		lwrSkull->SetPosition(x + 100.0f, -170.0f);
		hirSkull->SetPosition(x + 100.0f, -170.0f);
	}
}

float Piston::GetMoveVal()
{
	return chain->GetMoveVal();
}
