#include "framework.h"
#include "SceneList.h"
#include "Rect.h"
#include "Booper.h"

HS02_Prologue::HS02_Prologue()
{
	wstring imageFile1 = L"./Images/Prologue/Prologue (1).png";
	wstring imageFile2 = L"";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	Vector2 position;
	// Prologue
	{
		for (int i = 1; i <= 3; i++)
		{
			imageFile1 = L"./Images/Prologue/Prologue (" + to_wstring(i) + L").png";
			scenes[i - 1] = new Texture(imageFile1, shaderFile);

			position = scenes[i - 1]->GetPosition();
			position.y += 117.5f;
			scenes[i - 1]->SetPosition(position);
			scenes[i - 1]->SetRotation(0.0f, 0.0f, 0.0f);
		}
	}

	// Rect
	{
		shaderFile = L"./Shader/HLSL/Color.hlsl";
		rect = new Rect2(shaderFile);
		rect->SetScale(1280.0f, 652.0f);
		rect->UpdateBlock(Color(116.0f / 255.0f, 40.0f / 255.0f, 54.0f / 255.0f, 1.0f));
		rect->SetPosition(position);	
	}

	// booper
	{
		booper = (Booper*)OBJMANAGER->FindObject("Booper");
	}

	SetActive(false);

	sceneName = "HS02_Prologue";

	SetNextScene("HS03_ChangeScene");
}

HS02_Prologue::~HS02_Prologue()
{
	for (int i = 0; i < 3; i++)
		SAFE_DELETE(scenes[i]);
}

void HS02_Prologue::Update()
{
	Matrix V, P;

	V = CAMERA->GetViewMatrix();
	P = CAMERA->GetProjMatrix();

	if (DOWN(VK_SPACE) || DOWN(VK_RETURN))
	{
		sceneNum++;
		booper->SetClick(true);
	}

	switch (sceneNum)
	{
	case 0:
		rect->SetRotation(0.0f, 0.0f, 2.5f);
		break;
	case 1:
		rect->SetRotation(0.0f, 0.0f, -2.5f);
		break;
	case 2:
		rect->SetRotation(0.0f, 0.0f, 2.5f);
		break;
	case 3:
		SCENEMANAGER->ChangeScene(nextSceneName);
		CAMERA->SetPosition(Vector2(0.0f, 0.0f));
		return;
		break;
	default:
		break;
	}

	rect->Update(V, P);
	booper->SetActive(true);
	booper->Update(V, P);

	scenes[sceneNum]->Update(V, P);
}

void HS02_Prologue::Render()
{
	rect->Render();
	booper->Render();
	scenes[sceneNum]->Render();

	DirectWrite::GetDC()->BeginDraw();
	{
		switch (sceneNum)
		{
		case 0:
			script[0] = L"어느날 당신은 악마들로 가득한 하렘을";
			script[1] = L"꿈꾸고 일어났네.";
			break;
		case 1:
			script[0] = L"하지만 결코 이루기 쉽지않은 꿈이지.";
			script[1] = L"어쩌면 네 목숨을 앗아갈지도 모르고.";
			break;
		case 2:
			script[0] = L"\"악마 하렘이 달렸다면 그 어떤 대가도 싸지.\"";
			script[1] = L"그리하여 당신은 지옥으로 모험을 떠났네.";
			break;
		default:
			break;
		}
		float x = -(script[0].length() * 37.5f * 0.5f);
		float y = -175.0f;
		Vector2 pos = Vector2(x, y - 70.0f);
		CAMERA->VCToWC(pos);
		DirectWrite::RenderText(script[0], pos, 255, 255, 255, 37.5f);
		
		x = -(script[1].length() * 37.5f * 0.5f);
		y = -220.0f;
		pos = Vector2(x, y - 70.0f);
		CAMERA->VCToWC(pos);
		DirectWrite::RenderText(script[1], pos, 255, 255, 255, 37.5f);
	}
	DirectWrite::GetDC()->EndDraw();

}

void HS02_Prologue::ChangeScene()
{
	SetActive(true);
	sceneNum = 0;
}