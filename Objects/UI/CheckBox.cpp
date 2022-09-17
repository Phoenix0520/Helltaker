#include "framework.h"
#include "CheckBox.h"

CheckBox::CheckBox()
{
	wstring imageFile1 = L"./Images/OptionMenu/CheckBox.png";
	wstring imageFile2 = L"./Images/OptionMenu/CheckMark.png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	texture = new Texture(imageFile1, shaderFile);
	texture->SetOffsetSize(117.0f, 117.0f);

	checkMark = new Texture(imageFile2, shaderFile);
}

CheckBox::~CheckBox()
{
	SAFE_DELETE(texture);
}

void CheckBox::Update(Matrix V, Matrix P)
{
	if (hover)
		texture->SetOffset(117.0f, 0.0f);
	else
		texture->SetOffset(0.0f, 0.0f);

	Vector2 pos = GetPosition();

	texture->SetScale(scale);
	texture->SetPosition(pos);
	texture->Update(V, P);

	if (check)
	{
		checkMark->SetScale(0.3f, 0.3f);
		checkMark->SetPosition(pos);
		checkMark->Update(V, P);
	}
}

void CheckBox::Render()
{
	texture->Render();

	if (check)
		checkMark->Render();
}

void CheckBox::Reset()
{
}
