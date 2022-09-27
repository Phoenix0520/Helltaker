#include "framework.h"
#include "HS17_BossScene.h"

HS17_BossScene::HS17_BossScene()
{
	wstring imageFile1 = L"./Images/Boss/Background.png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	background = new Texture(imageFile1, shaderFile);
	background->UpdateColorBuffer(Color(0.755f, 0.175f, 0.045f, 0.725f), 9, 0, 0, 0);

	SetActive(false);
	SetDisplay(false);

	sceneName = "HS17_BossScene";
}

HS17_BossScene::~HS17_BossScene()
{
	SAFE_DELETE(background);
}

void HS17_BossScene::Update()
{
	CAMERA->Update();
	Matrix V = CAMERA->GetViewMatrix();
	Matrix P = CAMERA->GetProjMatrix();

	background->Update(V, P);
}

void HS17_BossScene::Render()
{
	background->Render();
}

void HS17_BossScene::ChangeScene()
{
	SetActive(true);
}
