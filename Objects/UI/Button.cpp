#include "framework.h"
#include "Button.h"
#include "HS05_Dialogue.h"

Button::Button()
{
	wstring imageFile1 = L"./Images/Button/Button (3).png";
	wstring imageFile2 = L"./Images/Button/Button (2).png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	texture1 = new Texture(imageFile1, shaderFile);
	texture2 = new Texture(imageFile2, shaderFile);
}

Button::~Button()
{
	SAFE_DELETE(texture2);
	SAFE_DELETE(texture1);
}

void Button::Update(Matrix V, Matrix P)
{
	// 크기 색상 위치 변경
	{
		if (time < 0.7f)
			time += DELTA;

		texture1->SetScale(0.95f, 0.95f);
		texture2->SetScale(1.0f, 1.0f);

		texture1->UpdateColorBuffer(Color(101.0f / 255.0f, 61.0f / 255.0f, 72.0f / 255.0f, 1.0f), 1, 0.0f, 0.0f, 0.0f);
		texture2->UpdateColorBuffer(Color(230.0f / 255.0f, 77.0f / 255.0f, 81.0f / 255.0f, 1.0f), 1, 0.0f, 0.0f, 0.0f);

		texture1->SetPosition(GetPosition());
		texture2->SetPosition(GetPosition());
	}

	if (!hover)
	{
		texture1->Update(V, P);
	}
	else
	{
		texture2->Update(V, P);
		
		select = true;

		if (DOWN(VK_SPACE) || DOWN(VK_RETURN))
		{
			click = true;
		}
	}
	return;
}

void Button::Render()
{
	DirectWrite::GetDC()->BeginDraw();
	{
		float x = -(buttonName.size() * 30.0f * 0.5f);

		Vector2 center = GetPosition();
		Vector2 pos = Vector2(center.x + x, position.y + texture1->GetTextureRealSize().y * 0.25f);
		CAMERA->VCToWC(pos);

		if (hover)
			DirectWrite::RenderText(buttonName, pos, 255, 255, 255, 30.0f);
		else
			DirectWrite::RenderText(buttonName, pos, 212, 185, 191, 30.0f);

		//rgb(212, 185, 191)
	}
	DirectWrite::GetDC()->EndDraw();

	if (!hover)
		texture1->Render();
	else
		texture2->Render();
}

void Button::Reset()
{
	click = false;
	select = false;
}

bool Button::IsPointInRegion(Vector2 position)
{
	Vector2 size	= texture1->GetTextureRealSize();
	Vector2 min		= Vector2(GetPosition().x - size.x * 0.5f, GetPosition().y - size.y * 0.5f);
	Vector2 max		= Vector2(GetPosition().x + size.x * 0.5f, GetPosition().y + size.y * 0.5f);

	if ((position.x >= min.x && position.x <= max.x) && (position.y >= min.y && position.y <= max.y))
	{
		return true;
	}
	else
		return false;
}
