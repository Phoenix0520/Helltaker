#include "framework.h"
#include "Slate.h"

Slate::Slate()
{
	wstring imageFile1 = L"./Images/Box/Slate (0).png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	texture = new Texture(imageFile1, shaderFile);

	SetActive(true);
}

Slate::~Slate()
{
	SAFE_DELETE(texture);
}

void Slate::Update(Matrix V, Matrix P)
{
	if (!IsActive())
	{
		return;
	}

	Vector2 position = GetPosition();
	
	if (plus)
		val += 0.85f;
	else
		val -= 0.85f;

	if (val >= -11.5f)
		plus = false;

	if (val <= -28.5f)
		plus = true;

	texture->SetPosition(position.x, position.y + val);
	texture->SetScale(scale);
	texture->SetRotation(rotation);

	texture->Update(V, P);
}

void Slate::Render()
{
	if (!IsActive())
	{
		return;
	}
	texture->Render();
}

void Slate::Reset()
{
	SetActive(false);
}