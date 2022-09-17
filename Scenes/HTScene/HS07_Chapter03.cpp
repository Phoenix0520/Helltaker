#include "framework.h"
#include "SceneList.h"
#include "Helltaker.h"
#include "HelltakerMap.h"
#include "Graphic2D.h"
#include "Mob.h"
#include "Box.h"
#include "Trap.h"
#include "Slate.h"
#include "LockBox.h"
#include "Key.h"
#include "Goal.h"
#include "Fire.h"

HS07_Chapter03::HS07_Chapter03()
{
	wstring imageFile1 = L"./Images/Background/Chapter03.png";

	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	texture = new Texture(imageFile1, shaderFile);

	sceneName = "HS07_Chapter03";
	sceneNum = 3;

	SetActive(false);
	SetDisplay(true);
}

HS07_Chapter03::~HS07_Chapter03()
{
	SAFE_DELETE(texture);
}

void HS07_Chapter03::Update()
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
	if (helltaker->GetHP() <= -1)
	{
		printf("\nDead!");
		SCENEMANAGER->ChangeScene("HS00_DeadScene");
		return;
	}

	//Camera를 이용한다.
	CAMERA->Update();

	Matrix V, P;
	V = CAMERA->GetViewMatrix();
	P = CAMERA->GetProjMatrix();

	//해당 오브젝트를 Update

	texture->Update(V, P);
	OBJMANAGER->UpdateAll(V, P);
}

void HS07_Chapter03::Render()
{
	texture->Render();
	OBJMANAGER->RenderAll();
}

void HS07_Chapter03::ChangeScene()
{
	SetActive(true);

	cout << endl << "Chapter03!";

	HS03_ChangeScene* scene = (HS03_ChangeScene*)SCENEMANAGER->GetScene("HS03_ChangeScene");
	scene->SetNextScene("HS07_Chapter03");

	HS05_Dialogue* Dialogue = (HS05_Dialogue*)SCENEMANAGER->GetScene("HS05_Dialogue");
	Dialogue->SetSceneID(2);

	for (int i = 3; i <= 5; i++)
	{
		Goal* goal = (Goal*)OBJMANAGER->FindObject("Goal" + to_string(i));
		goal->Reset();
		goal->SetState(Goal::CERBERUS);
	}

	texture->UpdateColorBuffer(Color(), 0, 0.0f, 0.0f, 0.0f);

	if (!reset)	// Goal 에서 Select 하는 Dialogue 가 되었을때
	{
		//reset = true;
		HTMAP->SetSize(9, 8);
		HTMAP->SetOffset(-450.0f, 325.0f);
		return;
	}

	HTMAP->Clear();
	HTMAP->SetSize(9, 8);
	HTMAP->SetOffset(-450.0f, 325.0f);
	OBJMANAGER->ClearObjectStrings();

	// Move
	// SetValue Map 의 번호에 값을 더해준다.

	HTMAP->SetMapValue(0, 4, 7);
	HTMAP->SetValue(7, 1, HTMAPSTATE::move, nullptr);

	HTMAP->SetMapValue(2, 3, 8);

	//SetMapValue(3, 3, 8);
	for (int i = 3; i <= 8; i++)
	{
		if (i == 4)
			HTMAP->SetValue(3, 4, HTMAPSTATE::wall, nullptr);
		else if (i == 6)
			HTMAP->SetValue(3, 6, HTMAPSTATE::wall, nullptr);
		else
			HTMAP->SetValue(i, 3, HTMAPSTATE::move, nullptr);
	}

	HTMAP->SetMapValue(4, 3, 7);

	//SetMapValue(5, 3, 8);
	for (int i = 1; i <= 7; i++)
	{
		if (i == 2)
			HTMAP->SetValue(5, 2, HTMAPSTATE::wall, nullptr);
		else if (i == 4)
			HTMAP->SetValue(5, 4, HTMAPSTATE::wall, nullptr);
		else if (i == 6)
			HTMAP->SetValue(5, 6, HTMAPSTATE::wall, nullptr);
		else
			HTMAP->SetValue(i, 5, HTMAPSTATE::move, nullptr);
	}

	HTMAP->SetMapValue(6, 1, 7);

	// Trap
	{
		HTMAP->AssignTrap("Trap1", 4, 2);
		HTMAP->AssignTrap("Trap2", 5, 2);
		HTMAP->AssignTrap("Trap3", 3, 3);
		HTMAP->AssignTrap("Trap4", 5, 3);
		HTMAP->AssignTrap("Trap5", 6, 4);
		HTMAP->AssignTrap("Trap6", 7, 4);
		HTMAP->AssignTrap("Trap7", 3, 5);
		HTMAP->AssignTrap("Trap8", 5, 5);
	}

	// Mob
	{
		HTMAP->AssignMob("Mob1", 5, 4);
		HTMAP->AssignMob("Mob2", 6, 6);
	}

	// Goal
	{
		HTMAP->AssignGoal("Goal3", 4, 0);
		HTMAP->AssignGoal("Goal4", 5, 0);
		HTMAP->AssignGoal("Goal5", 6, 0);
	}

	// Key
	{
		HTMAP->AssignKey("Key", 1, 5);
		Key* key = (Key*)OBJMANAGER->FindObject("Key");
		key->SetActive(true);
	}

	// LockBox
	{
		HTMAP->AssignLockBox("LockBox", 7, 1);
		LockBox* lbox = (LockBox*)OBJMANAGER->FindObject("LockBox");
		lbox->SetActive(true);
	}

	// Fire
	{
		HTMAP->AssignFire("Fire1", -255.0f, -60.0f, 1);
		HTMAP->AssignFire("Fire2", 355.0f, 285.0f, 1);
	}

	// HT
	{
		HTMAP->AssignHelltaker(8, 2, 32);
	}
}