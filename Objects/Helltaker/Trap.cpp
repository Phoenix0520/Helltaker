#include "framework.h"
#include "Trap.h"

Trap::Trap()
{
	wstring imageFile1 = L"./Images/Trap/Trap (1).png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	trap = new Animation(imageFile1, shaderFile);
	
	// UP : UP
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::endStay);
		trap->AddClip(clip);

		Texture* texture = trap->GetTexture();
		wstring str = L"./Images/Trap/Trap (1).png";

		clip->AddFrame(texture, str, 0.0f, 0.0f, 100.0f, 220.0f, 0.08f);
	}

	// Down : DOWN
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::endStay);
		trap->AddClip(clip);

		Texture* texture = trap->GetTexture();
		wstring str = L"./Images/Trap/Trap (6).png";

		clip->AddFrame(texture, str, 0.0f, 0.0f, 100.0f, 220.0f, 0.08f);
	}

	// UP_DOWN : UP -> DOWN
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::endStay);
		trap->AddClip(clip);

		Texture* texture = trap->GetTexture();
		wstring str = L"./Images/Trap/Trap.png";

		float x = 0.0f;
		for (int i = 1; i <= 6; i++)
		{
			clip->AddFrame(texture, str, x, 0.0f, x + 100.0f, 220.0f, 0.03f);
			x += 100.0f;
		}
	}

	// DOWN_UP : DOWN -> UP
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::endStay);
		trap->AddClip(clip);

		Texture* texture = trap->GetTexture();
		wstring str = L"./Images/Trap/Trap.png";

		float x = 500.0f;
		for (int i = 1; i <= 6; i++)
		{
			clip->AddFrame(texture, str, x, 0.0f, x + 100.0f, 220.0f, 0.03f);
			x -= 100.0f;
		}
	}

	wstring ImageFile = L"./Images/Trap/Trap2.png";
	
	// Dummy
	{
		AnimationClip *pClip = new AnimationClip(AnimationClip::endStay);
		trap->AddClip(pClip);

		Texture *pTexture = trap->GetTexture();

		float x = 500.0f;

		pClip->AddFrame(pTexture, ImageFile, x, 0.0f, x + 100.0f, 220.0f, 0.03f);
	}

	// KILL_UP
	{
		AnimationClip *pClip = new AnimationClip(AnimationClip::endStay);
		trap->AddClip(pClip);

		Texture *pTexture = trap->GetTexture();

		float x = 500.0f;

		for (int i = 5; i < 6; i++)
		{
			pClip->AddFrame(pTexture, ImageFile, x, 0.0f, x + 100.0f, 220.0f, 0.03f);
			x = x + 100.0f;
		}
	}

	// KILL_DOWN
	{
		AnimationClip *pClip = new AnimationClip(AnimationClip::endStay);
		trap->AddClip(pClip);

		Texture *pTexture = trap->GetTexture();

		float x = 100.0f;

		for (int i = 1; i < 2; i++)
		{
			pClip->AddFrame(pTexture, ImageFile, x, 0.0f, x + 100.0f, 220.0f, 0.03f);
			x = x + 100.0f;
		}
	}
}

Trap::~Trap()
{
	SAFE_DELETE(trap);
}

void Trap::Update(Matrix V, Matrix P)
{
	Vector2 position = GetPosition();
	Vector2 scale = GetScale();
	Vector3 rotation = GetRotation();

	position.y -= 25.0f;

	trap->SetPlay((UINT)state);
	trap->SetPosition(position);
	trap->SetScale(scale);
	trap->SetRotation(rotation);
	trap->Update(V, P);
}

void Trap::Render()
{
	if (!active)
		return;

	trap->Render();
}

void Trap::Reset()
{
	trap->SetPlay((UINT)state);
	trap->SetStop();
}

void Trap::MoveObject(Direction direction, Vector2 & position)
{
}

void Trap::Toggle()
{
	switch (state)
	{
	case DOWN_UP:
	case UP:
		state = UP_DOWN;
		break;
	case UP_DOWN:
	case DOWN:
		state = DOWN_UP;
		break;
	}
}

bool Trap::IsUp()
{
	switch (state)
	{
	case DOWN_UP:
	case UP:
	case KILL_UP:
		return true;
		break;
	case UP_DOWN:
	case DOWN:
	case KILL_DOWN:
	default:
		return false;
		break;
	}
}
