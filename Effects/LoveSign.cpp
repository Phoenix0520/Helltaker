#include "framework.h"
#include "LoveSign.h"

LoveSign::LoveSign()
{
	wstring imageFile1 = L"./Images/Goals/LoveSign.png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	loveSign = new Texture(imageFile1, shaderFile);
}

LoveSign::~LoveSign()
{
	SAFE_DELETE(loveSign);
}

void LoveSign::Update(Matrix V, Matrix P)
{
	Vector2 pos = GetPosition();

	// Love Sign
	if (plus)
		val += 0.75f;
	else
		val -= 0.75f;

	if (val >= 35.0f)
		plus = false;

	if (val <= 25.0f)
		plus = true;

	loveSign->Update(V, P);
	loveSign->SetPosition(position.x - 45.0f, position.y + val);
}

void LoveSign::Render()
{
	loveSign->Render();
}

void LoveSign::Reset()
{
	val = 35.0f;
}
