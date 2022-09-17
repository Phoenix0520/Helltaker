#include "framework.h"
#include "SceneList.h"
#include "Helltaker.h"
#include "HelltakerMap.h"
#include "Button.h"
#include "Booper.h"
#include "Mob.h"
#include "Box.h"
#include "Trap.h"
#include "Slate.h"
#include "LockBox.h"
#include "Key.h"
#include "Goal.h"
#include "Fire.h"


HS09_SlateScene::HS09_SlateScene()
{
	wstring imageFile1 = L"./Images/background/background (7).png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	// Background
	{
		background = new Texture(imageFile1, shaderFile);

		Vector2 position = background->GetPosition();
		Color changeColor = Color(1.0f, 0.0f, 0.0f, 1.0f);

		background->SetPosition(position.x, position.y + 100.0f);
		background->SetScale(0.995f, 0.995f);
	}

	wstring imageFile2 = L"./Images/Box/Slate (1).png";
	wstring imageFile3 = L"./Images/Box/Slate (2).png";
	wstring imageFile4 = L"./Images/Box/Slate (3).png";

	// Slate
	{
		texture[0] = new Texture(imageFile2, shaderFile);
		texture[0]->SetPosition(0.0f, 162.0f);
		texture[0]->SetScale(0.995f, 0.995f);

		texture[1] = new Texture(imageFile3, shaderFile);
		texture[1]->SetPosition(0.0f, 162.0f);
		texture[1]->SetScale(0.995f, 0.995f);

		texture[2] = new Texture(imageFile4, shaderFile);
		texture[2]->SetPosition(0.0f, 162.0f);
		texture[2]->SetScale(0.995f, 0.995f);
	}

	// Booper
	{
		booper = (Booper*)OBJMANAGER->FindObject("Booper");
	}

	SetActive(false);
	sceneName = "HS09_SlateScene";
}

HS09_SlateScene::~HS09_SlateScene()
{
	SAFE_DELETE(booper);
	SAFE_DELETE(background);
	SAFE_DELETE(texture[0]);
	SAFE_DELETE(texture[1]);
	SAFE_DELETE(texture[2]);
}

void HS09_SlateScene::Update()
{
	Matrix V = CAMERA->GetViewMatrix();
	Matrix P = CAMERA->GetProjMatrix();

	// Background 설정
	{
		time += DELTA;

		Vector2 size = background->GetTextureRealSize();
		Vector2 origin = background->GetPosition();
		CAMERA->VCToWC(origin);

		float min = origin.y - time * 1500;
		float max = origin.y + time * 1500;

		Color changeColor = Color(0.0f, 0.0f, 0.0f, 1.0f);
		// Botton Check

		background->UpdateColorBuffer(changeColor, 3, 1.0f - time, min, max);

		background->Update(V, P);
	}

	// Texture[sceneID]
	{
		Vector2 pos = texture[sceneID]->GetPosition();
		
		ctime += DELTA;
		if (ctime >= 0.75f)
			ctime = 0.75f;

		if (pos.x > 0.0f)
		{
			pos.x -= 1500.0f * DELTA;
			//texture[sceneID]->UpdateColorBuffer(Color(209.0f / 255.0f, 158.0f / 255.0f, 165.0f / 255.0f, 0.1f), 5, -0.75f + ctime, 0.0f, 0.0f);
		}
		else
		{
			//texture[sceneID]->UpdateColorBuffer(Color(), 0, 0.0f, 0.0f, 0.0f);
			pos.x = 0.0f;
		}

		texture[sceneID]->SetPosition(pos.x, pos.y);
		texture[sceneID]->Update(V, P);

		switch (sceneID)
		{
		case 0:
			if (!soundPlay)
			{
				PLAYSOUND("Slate1", sfxSize);
				soundPlay = true;
			}
			break;
		case 1:
			if (!soundPlay)
			{
				PLAYSOUND("Slate2", sfxSize);
				soundPlay = true;
			}
			break;
		case 2:
			if (!soundPlay)
			{
				PLAYSOUND("Slate3", sfxSize);
				soundPlay = true;
			}
			break;
		}

	}

	booper->SetActive(true);
	booper->Update(V, P);

	if (time >= 1.0f && (PRESS(VK_RETURN) || PRESS(VK_SPACE)))
	{
		Scene* scene = nullptr;

		switch (sceneID)
		{
		case 0:
			OBJMANAGER->FindObject("Slate")->SetActive(false);
			scene = SCENEMANAGER->GetScene("HS08_Chapter04");
			scene->SetReset(false);
			SCENEMANAGER->ChangeScene("HS08_Chapter04");
			break;
		case 1:
			OBJMANAGER->FindObject("Slate")->SetActive(false);
			scene = SCENEMANAGER->GetScene("HS10_Chapter05");
			scene->SetReset(false);
			SCENEMANAGER->ChangeScene("HS10_Chapter05");
			break;
		case 2:
			OBJMANAGER->FindObject("Slate")->SetActive(false);
			scene = SCENEMANAGER->GetScene("HS11_Chapter06");
			scene->SetReset(false);
			SCENEMANAGER->ChangeScene("HS11_Chapter06");
			break;
		}
	}
}

void HS09_SlateScene::Render()
{
	background->Render();
	texture[sceneID]->Render();
	booper->Render();

	DirectWrite::GetDC()->BeginDraw();
	{
		DirectWrite::ChangeTextType
		(
			L"맑은고딕체",
			DWRITE_FONT_WEIGHT_BOLD,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_CONDENSED
		);

		wstring banner = L"• 고대의 글귀 •";
		float x = -(banner.length() * 30.0f * 0.5f);
		float y = -205.0f;
		Vector2 pos = Vector2(x, y + 10.0f);
		CAMERA->VCToWC(pos);

		DirectWrite::RenderText(banner, pos, 230, 77, 81, 30.0f);

		DirectWrite::ChangeTextType
		(
			L"맑은고딕체",
			DWRITE_FONT_WEIGHT_MEDIUM,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_CONDENSED
		);

		wstring script = L"의례의 일부. 분명히 금지된 전승일 터.";
		x = -(script.length() * 30.0f * 0.5f);
		pos = Vector2(x, y - 42.5f);
		CAMERA->VCToWC(pos);

		DirectWrite::RenderText(script, pos, 255, 255, 255, 30.0f);
	}
	DirectWrite::GetDC()->EndDraw();
}

void HS09_SlateScene::ChangeScene()
{
	SetActive(true);
	booper->SetActive(true);
	soundPlay = false;

	background->UpdateColorBuffer(Color(), 0, 0.0f, 0.0f, 0.0f);
	
	time = 0.0f;

	Slate* slate = (Slate*)OBJMANAGER->FindObject("Slate");
	sceneID = slate->GetState();


	Vector2 size = texture[0]->GetTextureRealSize() * 0.5f;
	for (int i = 0; i < 3; i++)
	{
		texture[i]->SetPosition(size.x, texture[i]->GetPosition().y);
		texture[i]->UpdateColorBuffer(Color(), 0, 0.0f, 0.0f, 0.0f);
	}

}