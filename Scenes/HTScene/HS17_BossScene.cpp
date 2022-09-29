#include "framework.h"
#include "HS17_BossScene.h"
#include "Helltaker.h"
#include "HelltakerMap.h"
#include "Piston.h"
#include "LifeCount.h"
#include "Bridge.h"

HS17_BossScene::HS17_BossScene()
{
	wstring imageFile1 = L"./Images/Boss/Background.png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	background = new Texture(imageFile1, shaderFile);

	rect = new Texture(imageFile1, shaderFile);
	rect->UpdateColorBuffer(Color(0.675f, 0.225f, 0.085f, 0.75f), 4);

	wstring imageFile2 = L"./Images/Boss/uprBorder.png";
	uprBorder = new Texture(imageFile2, shaderFile);
	imageFile2 = L"./Images/Boss/uprBorder2.png";
	uprBorder2 = new Texture(imageFile2, shaderFile);
	imageFile2 = L"./Images/Boss/udrBorder.png";
	udrBorder = new Texture(imageFile2, shaderFile);

	wstring imageFile3 = L"./Images/Boss/Gear/Gear (1).png";
	gear[0] = new Animation(imageFile3, shaderFile);
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::loop);
		gear[0]->AddClip(clip);
		
		for (UINT i = 1; i <= 15; i++)
		{
			wstring str = L"./Images/Boss/Gear/Gear (" + to_wstring(i) + L").png";
			clip->AddFrame(gear[0]->GetTexture(), str, 0, 0, 400, 300, 0.02f);
		}
	}
	gear[0]->SetPosition(-770.0f, -420.0f);
	gear[0]->SetPlay(0);

	gear[1] = new Animation(imageFile3, shaderFile);
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::loop);
		gear[1]->AddClip(clip);

		for (UINT i = 1; i <= 15; i++)
		{
			wstring str = L"./Images/Boss/Gear/Gear (" + to_wstring(i) + L").png";
			clip->AddFrame(gear[1]->GetTexture(), str, 0, 0, 400, 300, 0.02f);
		}
	}
	gear[1]->SetRotation(0.0f, 180.0f, 0.0f);
	gear[1]->SetPosition(770.0f, -420.0f);
	gear[1]->SetPlay(0);

	piston[0] = new Piston(-790.0f, endTime);
	piston[1] = new Piston(790.0f, endTime);
	piston[1]->SetRotation(0.0f, 180.0f, 0.0f);

	lifeCount = new LifeCount();

	bridge = new Bridge();

	SetActive(false);
	SetDisplay(false);

	sceneName = "HS17_BossScene";

	helltaker = (Helltaker*)OBJMANAGER->FindObject("Helltaker");
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

	time += DELTA;

	if (DOWN('M'))
		lifeCount->DiscardLife();

	if (DOWN('R'))
	{
		Scene* scene = SCENEMANAGER->GetScene("HS03_ChangeScene");
		scene->SetNextScene("HS17_BossScene");
		SCENEMANAGER->ChangeScene("HS03_ChangeScene");
	}

	if (lifeCount->IsDead())
	{	
		helltaker->SetBoss(true);

		lifeCount->Reset();
		SCENEMANAGER->ChangeScene("HS00_DeadScene");

		Scene* scene = SCENEMANAGER->GetScene("HS03_ChangeScene");
		scene->SetNextScene("HS17_BossScene");
	}

	background->Update(V, P);
	rect->Update(V, P);

	gear[0]->Update(V, P);
	gear[1]->Update(V, P);

	uprBorder->Update(V, P);
	uprBorder2->Update(V, P);

	piston[0]->Update(V, P);
	piston[1]->Update(V, P);

	udrBorder->Update(V, P);

	lifeCount->Update(V, P);

	if (time >= 1.5f)
	{
		working = true;
		bridge->SetMove(true);
	}
	if (time >= endTime - 1.0f)
	{
		working = false;
		bridge->SetMove(false);
	}

	bridge->Update(V, P);

	Vector2 pPos = helltaker->GetPosition();

	if (pPos.y > 200.0f || pPos.y < -400.0f)
	{
		while (!lifeCount->IsDead())
			lifeCount->DiscardLife();
	}

	if (working)
	{
		if (moveVal < 150.0f)
			moveVal += 150.0f * DELTA;
	}
	else
	{
		if (moveVal > 0.0f)
			moveVal -= 75.0f * DELTA;
		else
			moveVal = 0.0f;
	}

	pPos.y += moveVal * DELTA;

	helltaker->SetPosition(pPos);
	helltaker->Update(V, P);
}

void HS17_BossScene::Render()
{
	background->Render();
	rect->Render();
	gear[0]->Render();
	gear[1]->Render();
	 

	uprBorder->Render();

	piston[0]->Render();
	piston[1]->Render();
	
	bridge->Render();
	uprBorder2->Render();
	udrBorder->Render();

	lifeCount->Render();

	helltaker->Render();
}

void HS17_BossScene::ChangeScene()
{
	SetActive(true);
	HTMAP->Clear();
	time = 0.0f;
	lifeCount->Reset();
	helltaker->SetPosition(0.0f, -100.0f);
	helltaker->SetBoss(true);
	
	piston[0]->Reset();
	piston[1]->Reset();
}
