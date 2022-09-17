#include "framework.h"
#include "OptionButton.h"

OptionButton::OptionButton()
{
	wstring imageFile1 = L"./Images/OptionMenu/Button.png";
	wstring imageFile2 = L"./Images/OptionMenu/ComboList.png";
	wstring imageFile3 = L"./Images/OptionMenu/ComboHover.png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	texture = new Texture(imageFile1, shaderFile);
	comboList = new Texture(imageFile2, shaderFile);
	cHover = new Texture(imageFile3, shaderFile);
}

OptionButton::~OptionButton()
{
	SAFE_DELETE(texture);
	SAFE_DELETE(comboList);
	SAFE_DELETE(cHover);
}

void OptionButton::Update(Matrix V, Matrix P)
{
	if (hover)
	{
		texture->UpdateColorBuffer(Color(0.9f, 0.3f, 0.3f, 1.0f), 4, 0.0f);
	}
	else
	{
		if (disable)
			texture->UpdateColorBuffer(Color(0.29f, 0.13f, 0.18f, 0.8f), 4, 0.0f);
		else
			texture->UpdateColorBuffer(Color(0.39f, 0.23f, 0.28f, 1.0f), 4, 0.0f);
	}

	if (combo && click)
	{
		if (comboScripts.size() < 10)
		{
			if (scale < 50.0f * comboScripts.size() + 10.0f)
				scale += comboScripts.size() * 300.0f * DELTA;
			else
				scale = 50.0f * comboScripts.size() + 10.0f;

			comboList->SetScale(1.0f, scale);

			Vector2 pos = GetPosition() - Vector2(0.0f, 20.0f);
			pos.y -= comboList->GetTextureRealSize().y / 2.0f;

			comboList->SetPosition(pos);
			comboList->Update(V, P);

			if (comboHover != 0)
				if (DOWN(VK_UP) || DOWN('W'))
					comboHover--;
			if (comboHover != comboScripts.size() - 1)
				if (DOWN(VK_DOWN) || DOWN('S'))
					comboHover++;

			Vector2 hpos = GetPosition();
			hpos.y -= 10.0f + 50.0f * (comboHover + 1);
			cHover->SetPosition(hpos);
			cHover->Update(V, P);
		}
		else
		{
			if (scale < 50.0f * 10.0f)
				scale += 10.0f * 300.0f * DELTA;
			else
				scale = 500.0f;

			comboList->SetScale(1.0f, scale);

			Vector2 pos = GetPosition() - Vector2(0.0f, 20.0f);
			pos.y -= comboList->GetTextureRealSize().y / 2.0f;

			comboList->SetPosition(pos);
			comboList->Update(V, P);

			if (comboHover > 0)
			{
				if (DOWN(VK_UP) || DOWN('W'))
				{
					comboHover--;

					if (comboHover <= end && begin > 0)
					{
						begin--;
						end--;
					}
				}

				static float ptime = 0.0f;

				if (PRESS(VK_UP) || PRESS('W'))
				{
					cout << "Pressing!" << endl;
					ptime += DELTA;

					if (ptime >= 0.25f)
					{
						ptime = 0.0f;

						comboHover--;

						if (comboHover <= end && begin > 0)
						{
							begin--;
							end--;
						}
					}
				}
				else
					ptime = 0.0f;
			}
			if (comboHover < comboScripts.size() - 1)
			{
				if (DOWN(VK_DOWN) || DOWN('S'))
				{
					comboHover++;

					if (comboHover > end)
					{
						begin++;
						end++;
					}
				}

				static float ptime = 0.0f;

				if (PRESS(VK_DOWN) || PRESS('S'))
				{
					cout << "Pressing! : " << ptime << endl;
					ptime += DELTA;

					if (ptime >= 0.25f)
					{
						ptime = 0.0f;

						comboHover++;

						if (comboHover > end)
						{
							begin++;
							end++;
						}
					}
				}
				else
					ptime = 0.0f;
			}

			Vector2 hpos = GetPosition();

			if (comboHover > 9)
				hpos.y -= 510.0f;
			else
				hpos.y -= 10.0f + 50.0f * (comboHover + 1);

			cHover->SetPosition(hpos);
			cHover->Update(V, P);
		}

	}
	else
		scale = 0.0f;

	texture->SetPosition(GetPosition());
	texture->Update(V, P);
}

void OptionButton::Render()
{
	DirectWrite::GetDC()->BeginDraw();
	{
		if (combo && click)
		{
			comboList->Render();
			cHover->Render();

			if (comboScripts.size() < 10)
			{
				for (UINT i = 0; i < comboScripts.size(); i++)
				{
					Vector2 pos;
					pos.x = GetPosition().x - comboScripts[i].length() * 10.0f;
					pos.y = GetPosition().y - 45.0f - (50.0f * i);
					CAMERA->VCToWC(pos);

					if (i == comboHover)
						DirectWrite::RenderText(comboScripts[i], pos, 255, 255, 255, 20.0f);
					else
						DirectWrite::RenderText(comboScripts[i], pos, 222, 200, 200, 20.0f);
				}
			}
			else
			{
				UINT index = 0;

				for (UINT i = begin; i < end + 1; i++)
				{
					Vector2 pos;
					pos.x = GetPosition().x - comboScripts[i].length() * 10.0f;
					pos.y = GetPosition().y - 45.0f - (50.0f * index);
					CAMERA->VCToWC(pos);

					if (i == comboHover)
						DirectWrite::RenderText(comboScripts[i], pos, 255, 255, 255, 20.0f);
					else
						DirectWrite::RenderText(comboScripts[i], pos, 222, 200, 200, 20.0f);

					index++;
				}
			}

			Vector2 pos1 = Vector2(-450.0f, 60.0f);
			Vector2 pos2 = Vector2(-450.0f, 20.0f);
			Vector2 pos3 = Vector2(-450.0f, -20.0f);

			CAMERA->VCToWC(pos1);
			CAMERA->VCToWC(pos2);
			CAMERA->VCToWC(pos3);

			DirectWrite::RenderText(to_wstring(comboHover), pos1, 255, 255, 255, 30.0f);
			DirectWrite::RenderText(to_wstring(begin), pos2, 255, 255, 255, 30.0f);
			DirectWrite::RenderText(to_wstring(end), pos3, 255, 255, 255, 30.0f);
		}
		else if (combo)
		{
			Vector2 pos;
			pos.x = GetPosition().x - comboScripts[comboHover].length() * 15.0f;
			pos.y = GetPosition().y - 35.0f;
			CAMERA->VCToWC(pos);

			if (hover)
				DirectWrite::RenderText(comboScripts[comboHover], pos, 255, 255, 255, 30.0f);
			else
				DirectWrite::RenderText(comboScripts[comboHover], pos, 222, 200, 200, 30.0f);

		}

		texture->Render();

		Vector2 pos = GetPosition();
		pos.x -= script.length() * 15.0f;
		pos.y += 23.0f;
		CAMERA->VCToWC(pos);

		wstring str = L"";

		switch (level)
		{
		case OptionButton::DISABLE:
			break;
		case OptionButton::MUTE:
			str = L"음소거";
			break;
		case OptionButton::LOW:
			str = L"낮음";
			break;
		case OptionButton::MIDDLE:
			str = L"중간";
			break;
		case OptionButton::HIGH:
			str = L"높음";
			break;
		default:
			break;
		}

		if (hover)
		{
			texture->SetScale(1.125f, 1.0f);
			DirectWrite::RenderText(script, pos, 255, 255, 255, 30.0f);

			if ((UINT)level >= 0)
			{
				pos = GetPosition();
				pos.x -= str.length() * 15.0f;
				pos.y -= 30.0f;
				CAMERA->VCToWC(pos);

				DirectWrite::RenderText(str, pos, 255, 255, 255, 30.0f);
			}
		}
		else
		{
			texture->SetScale(1.0f, 1.0f);
			DirectWrite::RenderText(script, pos, 222, 200, 200, 30.0f);

			if ((UINT)level >= 0)
			{
				pos = GetPosition();
				pos.x -= str.length() * 15.0f;
				pos.y -= 30.0f;
				CAMERA->VCToWC(pos);

				DirectWrite::RenderText(str, pos, 222, 200, 200, 30.0f);
			}
		}

	}
	DirectWrite::GetDC()->EndDraw();
}

void OptionButton::Reset()
{
}
