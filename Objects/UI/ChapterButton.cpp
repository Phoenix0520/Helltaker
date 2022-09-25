#include "framework.h"
#include "ChapterButton.h"
#include "HS01_IntroScene.h"

ChapterButton::ChapterButton(UINT num)
{
	sceneNum = num;

	wstring imageFile1 = L"./Images/ChapterSelect/Button.png";
	wstring imageFile2 = L"./Images/ChapterSelect/Button_Map.png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	if (sceneNum > 0)
		texture = new Texture(imageFile1, shaderFile);
	else
		texture = new Texture(imageFile2, shaderFile);

	texture->SetOffset(0.0f, 0.0f);
	texture->SetOffsetSize(110.0f, 76.0f);
}

ChapterButton::~ChapterButton()
{
	SAFE_DELETE(texture);
}

void ChapterButton::Update(Matrix V, Matrix P)
{
	if (hover)
		texture->SetOffset(111.0f, 0.0f);
	else
		texture->SetOffset(0.0f, 0.0f);

	Scene* scene = nullptr;

	switch (sceneNum)
	{
	case 0:
		script = L"Map";
		scene = SCENEMANAGER->GetScene("HS19_MapEditor");
		break;
	case 1:
		script = L"•∞";
		script = L"I";
		scene = SCENEMANAGER->GetScene("HS04_Chapter01");
		break;
	case 2:
		script = L"•±";
		script = L"II";
		scene = SCENEMANAGER->GetScene("HS06_Chapter02");
		break;
	case 3:
		script = L"•≤";
		script = L"III";
		scene = SCENEMANAGER->GetScene("HS07_Chapter03");
		break;
	case 4:
		script = L"•≥";
		script = L"IV";
		scene = SCENEMANAGER->GetScene("HS08_Chapter04");
		break;
	case 5:
		script = L"•¥";
		script = L"V";
		scene = SCENEMANAGER->GetScene("HS10_Chapter05");
		break;
	case 6:
		script = L"•µ";
		script = L"VI";
		scene = SCENEMANAGER->GetScene("HS11_Chapter06");
		break;
	case 7:
		script = L"•∂";
		script = L"VII";
		scene = SCENEMANAGER->GetScene("HS13_Chapter07");
		break;
	case 8:
		script = L"•∑";
		script = L"VIII";
		scene = SCENEMANAGER->GetScene("HS14_Chapter08");
		break;
	case 9:
		script = L"•∏";
		script = L"IX";
		scene = SCENEMANAGER->GetScene("HS15_Chapter09");
		break;
	case 10:
		script = L"•π";
		script = L"X";
		//scene = SCENEMANAGER->GetScene("HS18_Epilogue");
		break;
	default:
		scene = nullptr;
		break;
	}

	if (hover)
	{
		if (DOWN(VK_SPACE) || DOWN(VK_RETURN))
		{
			if (sceneNum == 1)
			{
				HS01_IntroScene* rScene = (HS01_IntroScene*)SCENEMANAGER->GetCurScene();
				rScene->ChangeScene();
				rScene->SetClick(3);
				rScene->SetChapter(false);
			}
			else
			{
				string sceneName = scene->GetSceneName();
				scene->SetReset(true);

				Scene* cScene = SCENEMANAGER->GetScene("HS03_ChangeScene");
				cScene->SetNextScene(sceneName);
				
				switch (sceneNum)
				{
				case 0:
					break;
				case 9:
					break;
				case 10:
					break;
				default:
					
					break;
				}

				SCENEMANAGER->ChangeScene(cScene->GetSceneName());
			}
		}
	}

	texture->SetPosition(GetPosition());
	texture->Update(V, P);
}

void ChapterButton::Render()
{
	texture->Render();

	DirectWrite::ChangeTextType
	(
		L"Amiri",
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_CONDENSED
	);

	Vector2 pos = GetPosition();
	bool map = script == L"Map";

	if (map)
		pos += Vector2(script.size() * -18.0f, 29.0f);
	else
		pos += Vector2(script.size() * -19.0f, 31.0f);

	CAMERA->VCToWC(pos);

	if (hover && !map)
		DirectWrite::RenderText(script, pos, 255, 255, 255, 38.0f);
	else if (!hover && !map)
		DirectWrite::RenderText(script, pos, 103, 103, 118, 38.0f);
	else if (hover)
		DirectWrite::RenderText(script, pos, 255, 77, 81, 36.0f);
	else if (!hover)
		DirectWrite::RenderText(script, pos, 93, 32, 49, 36.0f);

	DirectWrite::ChangeTextType
	(
		L"∏º¿∫∞ÌµÒ√º",
		DWRITE_FONT_WEIGHT_MEDIUM,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_CONDENSED
	);

}

void ChapterButton::Reset()
{
}
