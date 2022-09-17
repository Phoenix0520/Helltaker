#include "framework.h"
#include "Star.h"

Star::Star()
{
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";
	wstring imageFile1 = L"./Images/Effects/Star.png";
	
	//star
	{
		for (int i = 0; i < 12; i++)
		{
			star[i] = new Texture(imageFile1, shaderFile);
		}
	}

	//SetActive(false);
	SetActive(true);

	// 0 , 100
	// 100 , 0
	// 0 , -100
	// -100, 0

	float x = 0.0f;
	float y = 50.0f;
	for (int i = 0; i < 12; i++)
	{
		sPos[i] = Vector2(x, y);
		
		if (i < 5)
		{
			x += 10.0f;
			y -= 10.0f;
		}
		else
		{
			x -= 10.0f;
			y += 10.0f;
		}
		if (i == 5)
		{
			x = 0.0f;
			y = -50.0f;
		}
	}
}

Star::~Star()
{
	for (int i = 0; i < 10; i++)
	{
		SAFE_DELETE(star[i]);
	}
}

void Star::Update(Matrix V, Matrix P)
{
	Vector2 position = GetPosition();

	if (IsActive())
	{
		for (int i = 0; i < 12; i++)
		{
			star[i]->SetPosition(position.x - sPos[i].x * (val / 0.5f), position.y - sPos[i].y * (val / 0.5f));
			star[i]->SetScale(0.75f, 0.75f);
		}

		if (val > 0.0f)
			val -= DELTA;

		for (int i = 0; i < 12; i++)
		{
			star[i]->Update(V, P);
		}
	}
}

void Star::Render()
{
	if (IsActive())
	{
		for (int i = 0; i < 12; i++)
		{
			star[i]->Render();
		}
	}
}

void Star::Reset()
{
	val = 1.0f;

	SetActive(false);
}