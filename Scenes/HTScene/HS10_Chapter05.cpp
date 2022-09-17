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


HS10_Chapter05::HS10_Chapter05()
{
	wstring imageFile1 = L"./Images/Background/Chapter05.png";

	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	texture = new Texture(imageFile1, shaderFile);

	sceneName = "HS10_Chapter05";
	sceneNum = 5;

	SetDisplay(true);
	SetActive(false);
}

HS10_Chapter05::~HS10_Chapter05()
{
	SAFE_DELETE(texture);
}

void HS10_Chapter05::Update()
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
		SCENEMANAGER->GetScene("HS10_Chapter05")->SetReset(true);
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

void HS10_Chapter05::Render()
{
	texture->Render();
	OBJMANAGER->RenderAll();
}

void HS10_Chapter05::ChangeScene()
{
	SetActive(true);
	//CAMERA->ChangeXY(0.75f, 0.75f);

	cout << endl << "Chapter05!";

	HS03_ChangeScene* scene = (HS03_ChangeScene*)SCENEMANAGER->GetScene("HS03_ChangeScene");
	scene->SetNextScene("HS10_Chapter05");

	HS05_Dialogue* Dialogue = (HS05_Dialogue*)SCENEMANAGER->GetScene("HS05_Dialogue");
	Dialogue->SetSceneID(4);

	Goal* goal = (Goal*)OBJMANAGER->FindObject("Goal7");
	goal->Reset();
	goal->SetState(Goal::ZDRADA);

	texture->UpdateColorBuffer(Color(), 0, 0.0f, 0.0f, 0.0f);

	if (!reset)	// Goal 에서 Select 하는 Dialogue 가 되었을때
	{
		//reset = true;
		return;
	}

	HTMAP->Clear();
	HTMAP->SetSize(9, 8);
	HTMAP->SetOffset(-450.0f, 325.0f);

	OBJMANAGER->ClearObjectStrings();

	// Move
	// SetValue Map 의 번호에 값을 더해준다.
	{
		HTMAP->SetMapValue(0, 5, 6);

		HTMAP->SetMapValue(1, 4, 7);

		HTMAP->SetMapValue(2, 2, 2);
		HTMAP->SetMapValue(2, 4, 7);

		HTMAP->SetMapValue(3, 2, 2);
		HTMAP->SetMapValue(3, 4, 7);

		HTMAP->SetMapValue(4, 2, 2);
		HTMAP->SetMapValue(4, 4, 7);

		HTMAP->SetMapValue(5, 2, 7);
		
		HTMAP->SetMapValue(6, 7, 7);
	}

	// Trap
	{
		HTMAP->AssignTrap("Trap1", 4, 2, 1);
		HTMAP->AssignTrap("Trap2", 5, 3, 1);
		HTMAP->AssignTrap("Trap3", 7, 3, 1);
		HTMAP->AssignTrap("Trap4", 2, 5, 1);
		HTMAP->AssignTrap("Trap5", 4, 5, 1);
		HTMAP->AssignTrap("Trap6", 7, 5, 1);
	}

	// Key
	{
		HTMAP->AssignKey("Key", 7, 6);
		Key* key = (Key*)OBJMANAGER->FindObject("Key");
		key->SetActive(true);
	}

	// LockBox
	{
		HTMAP->AssignLockBox("LockBox", 5, 1);
		LockBox* lbox = (LockBox*)OBJMANAGER->FindObject("LockBox");
		lbox->SetActive(true);
	}

	// Fire
	{
		HTMAP->AssignFire("Fire1", -350.0f, -10.0f, 1);
		HTMAP->AssignFire("Fire2", -150.0f, 32.5f, 1);
		HTMAP->AssignFire("Fire3", 355.0f, -112.5f, 0);
	}

	// Slate
	{
		HTMAP->AssignSlate("Slate", 6, 1);
		Slate* slate = (Slate*)HTMAP->GetSecondObject(6, 1);
		slate->SetState(1);
		slate->SetActive(true);
	}

	// Box
	{
		HTMAP->AssignBox("Box1", 6, 1);
		HTMAP->AssignBox("Box2", 6, 2);
		HTMAP->AssignBox("Box4", 4, 4);
		HTMAP->AssignBox("Box5", 5, 4);
		HTMAP->AssignBox("Box3", 6, 4);
		HTMAP->AssignBox("Box6", 7, 4);

		Box* box = (Box*)HTMAP->GetGameObject(6, 1);
		box->SetID(9);
	}

	// Mob
	{
		HTMAP->AssignMob("Mob1", 2, 4);
	}

	// Goal
	{
		HTMAP->AssignGoal("Goal7", 6, 0);
	}

	// HT
	{
		HTMAP->AssignHelltaker(2, 2, 23);
	}
}
	