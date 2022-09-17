#include "framework.h"
#include "SceneList.h"
#include "Helltaker.h"
#include "HelltakerMap.h"
#include "Mob.h"
#include "Box.h"
#include "Trap.h"
#include "Slate.h"
#include "LockBox.h"
#include "Key.h"
#include "Goal.h"
#include "Fire.h"


HS14_Chapter08::HS14_Chapter08()
{
	wstring imageFile1 = L"./Images/Background/Chapter (8).png";
	wstring imageFile2 = L"./Images/Background/Chapter08.png";

	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	texture = new Texture(imageFile1, shaderFile);
	texture->SetScale(0.99275f, 0.99275f);

	UI = new Texture(imageFile2, shaderFile);

	sceneName = "HS14_Chapter08";
	sceneNum = 8;

	SetDisplay(true);
	SetActive(false);
}

HS14_Chapter08::~HS14_Chapter08()
{
	SAFE_DELETE(texture);
}

void HS14_Chapter08::Update()
{
	if (DOWN('R'))
	{
		SCENEMANAGER->ChangeScene("HS03_ChangeScene");
		reset = true;
	}
	else if (DOWN(VK_DELETE))
		SCENEMANAGER->ChangeScene("HS00_DeadScene");
	else if (DOWN(VK_HOME))
		SCENEMANAGER->ChangeScene("HS01_IntroScene");
	else if (DOWN(VK_END))
		SCENEMANAGER->ChangeScene("HS05_Dialogue");

	Helltaker* helltaker = dynamic_cast<Helltaker*>(OBJMANAGER->FindObject("Helltaker"));

	int hp = helltaker->GetHP();

	if (hp <= -1)
	{
		printf("\nDead!");
		SCENEMANAGER->ChangeScene("HS00_DeadScene");
		reset = true;
		return;
	}

	CAMERA->SetObject(helltaker);
	CAMERA->SetCenterXLock(true);
	CAMERA->Update();

	Matrix V, P;
	V = CAMERA->GetViewMatrix();
	P = CAMERA->GetProjMatrix();

	Vector2 pos = Vector2(GetSystemMetrics(SM_CXSCREEN) * 0.5f, GetSystemMetrics(SM_CYSCREEN) * 0.5f);
	CAMERA->WCToVC(pos);
	UI->SetPosition(pos);

	texture->Update(V, P);
	UI->Update(V, P);

	OBJMANAGER->UpdateAll(V, P);
}

void HS14_Chapter08::Render()
{
	texture->Render();
	UI->Render();
	OBJMANAGER->RenderAll();
}

void HS14_Chapter08::ChangeScene()
{
	SetActive(true);

	cout << endl << "Chapter07!";

	HS03_ChangeScene* scene = (HS03_ChangeScene*)SCENEMANAGER->GetScene("HS03_ChangeScene");
	scene->SetNextScene("HS14_Chapter08");

	HS05_Dialogue* Dialogue = (HS05_Dialogue*)SCENEMANAGER->GetScene("HS05_Dialogue");
	Dialogue->SetSceneID(7);

	Goal* goal = (Goal*)OBJMANAGER->FindObject("Goal10");
	goal->Reset();
	goal->SetState(Goal::LUCIFER);

	texture->UpdateColorBuffer(Color(), 0, 0.0f, 0.0f, 0.0f);
	UI->UpdateColorBuffer(Color(), 0, 0.0f, 0.0f, 0.0f);

	if (!reset)	// Goal 에서 Select 하는 Dialogue 가 되었을때
	{
		HTMAP->SetSize(11, 14);
		HTMAP->SetOffset(-502.5f, 882.5f);
		texture->SetPosition(0.0f, 500.0f);
		return;
	}

	texture->SetPosition(0.0f, 500.0f);

	HTMAP->Clear();
	HTMAP->SetSize(11, 14);
	HTMAP->SetOffset(-502.5f, 882.5f);
	OBJMANAGER->ClearObjectStrings();

	// Move 가능한 포인트
	{
		HTMAP->SetMapValue(1, 5, 5);
		
		HTMAP->SetMapValue(2, 2, 8);
		
		HTMAP->SetMapValue(3, 1, 9);

		HTMAP->SetMapValue(4, 1, 2);
		HTMAP->SetMapValue(4, 4, 6);
		HTMAP->SetMapValue(4, 8, 9);

		HTMAP->SetMapValue(5, 1, 9);

		HTMAP->SetMapValue(6, 1, 2);
		HTMAP->SetMapValue(6, 4, 6);
		HTMAP->SetMapValue(6, 8, 9);

		HTMAP->SetMapValue(7, 1, 9);

		HTMAP->SetMapValue(8, 2, 2);
		HTMAP->SetMapValue(8, 4, 6);
		HTMAP->SetMapValue(8, 8, 8);

		HTMAP->SetMapValue(9, 2, 8);

		HTMAP->SetMapValue(10, 2, 2);
		HTMAP->SetMapValue(10, 4, 6);
		HTMAP->SetMapValue(10, 8, 8);
		
		HTMAP->SetMapValue(11, 2, 8);
		HTMAP->SetMapValue(12, 4, 6);
	}

	// Fire
	{
		HTMAP->AssignFire("Fire1", -200.0f, -95.0f, 1);
		HTMAP->AssignFire("Fire2", -200.0f, 105.0f, 1);
		HTMAP->AssignFire("Fire3", -200.0f, 305.0f, 1);
		HTMAP->AssignFire("Fire4", -200.0f, 505.0f, 1);

		HTMAP->AssignFire("Fire5", 200.0f, -95.0f, 1);
		HTMAP->AssignFire("Fire6", 200.0f, 105.0f, 1);
		HTMAP->AssignFire("Fire7", 200.0f, 305.0f, 1);
		HTMAP->AssignFire("Fire8", 200.0f, 505.0f, 1);
	}

	// Mob
	{
		HTMAP->AssignMob("Mob1", 5, 2);
		HTMAP->AssignMob("Mob2", 5, 3);
		HTMAP->AssignMob("Mob3", 5, 4);
		HTMAP->AssignMob("Mob4", 5, 5);
		HTMAP->AssignMob("Mob5", 5, 6);
		HTMAP->AssignMob("Mob6", 5, 7);
		HTMAP->AssignMob("Mob7", 5, 8);
		HTMAP->AssignMob("Mob8", 5, 9);
	}

	// Goal
	{
		HTMAP->AssignGoal("Goal10", 5, 1);
	}

	// HT
	{
		HTMAP->AssignHelltaker(5, 11, 12);
	}
}