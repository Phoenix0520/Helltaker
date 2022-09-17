#include "framework.h"
#include "SceneList.h"
#include "Rect.h"
#include "Booper.h"

HS12_HeavenScene::HS12_HeavenScene()
{
	wstring imageFile1 = L"./Images/CutScene/Heaven.png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	Vector2 position;

	// Heaven
	{
		scene = new Texture(imageFile1, shaderFile);
		scene->SetPosition(0.0f, 117.5f);
	}

	// Rect
	{
		shaderFile = L"./Shader/HLSL/Color.hlsl";
		rect = new Rect2(shaderFile);
		rect->SetScale(1280.0f, 652.0f);
		rect->UpdateBlock(Color(116.0f / 255.0f, 40.0f / 255.0f, 54.0f / 255.0f, 1.0f));
		rect->SetPosition(0.0f, 117.5f);
	}

	// booper
	{
		booper = (Booper*)OBJMANAGER->FindObject("Booper");
	}

	SetActive(false);

	sceneName = "HS12_HeavenScene";

	SetNextScene("HS03_ChangeScene");
}

HS12_HeavenScene::~HS12_HeavenScene()
{
	SAFE_DELETE(scene);
	SAFE_DELETE(rect);
	SAFE_DELETE(booper);
}

void HS12_HeavenScene::Update()
{
	Matrix V, P;

	V = CAMERA->GetViewMatrix();
	P = CAMERA->GetProjMatrix();

	if (DOWN(VK_SPACE) || DOWN(VK_RETURN))
	{
		sceneNum++;
	}

	switch (sceneNum)
	{
	case 0:
		break;
	case 1:
		rect->SetRotation(0.0f, 0.0f, 2.5f);
		rect->Update(V, P);
		scene->Update(V, P);
		break;
	case 2:
		SCENEMANAGER->GetScene("HS03_ChangeScene")->SetNextScene("HS11_Chapter06");
		SCENEMANAGER->GetScene("HS11_Chapter06")->SetReset(true);
		
		SCENEMANAGER->ChangeScene(nextSceneName);
		break;
	default:
		break;
	}

	booper->SetActive(true);
	booper->Update(V, P);
}

void HS12_HeavenScene::Render()
{
	DirectWrite::GetDC()->BeginDraw();
	{
		switch (sceneNum)
		{
		case 0:
			script = L"거짓말 때문에 천국에 가리라고 누가 예상이나 했을까.";
			break;

		case 1:
			script = L"악마 하렘과는 영영 이별이지만";
			rect->Render();
			scene->Render();
			break;
		default:
			break;
		}
		booper->Render();

		float x = -(script.length() * 37.5f * 0.5f);
		float y = -175.0f;
		Vector2 pos = Vector2(x, y - 70.0f);
		CAMERA->VCToWC(pos);

		DirectWrite::ChangeTextType
		(
			L"맑은고딕체",
			DWRITE_FONT_WEIGHT_MEDIUM,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_CONDENSED
		);

		DirectWrite::RenderText(script, pos, 255, 255, 255, 37.5f);

		DirectWrite::ChangeTextType
		(
			L"맑은고딕체",
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_CONDENSED
		);
	}
	DirectWrite::GetDC()->EndDraw();
}

void HS12_HeavenScene::ChangeScene()
{
	scene->UpdateColorBuffer(Color(), 0, 0.0f, 0.0f, 0.0f);
	SetActive(true);
	sceneNum = 0;
}