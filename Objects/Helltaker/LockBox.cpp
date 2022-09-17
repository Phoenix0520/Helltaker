#include "framework.h"
#include "LockBox.h"

LockBox::LockBox()
{
	wstring imageFile1 = L"./Images/Box/LockBox.png";
	wstring shaderFile = L"./Shader/HLSL/Texture.hlsl";

	texture = new Texture(imageFile1, shaderFile);

	SetActive(true);
}

LockBox::~LockBox()
{
	SAFE_DELETE(texture);
}

void LockBox::Update(Matrix V, Matrix P)
{
	if (!IsActive())
	{
		return;
	}

	Vector2 position = GetPosition();
	position.y -= 27.5f;

	texture->SetPosition(position);

	texture->Update(V, P);
}

void LockBox::Render()
{
	if (!IsActive())
	{
		return;
	}

	texture->Render();
}

void LockBox::Reset()
{
	SetActive(false);
}