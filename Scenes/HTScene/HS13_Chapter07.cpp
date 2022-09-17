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


HS13_Chapter07::HS13_Chapter07()
{
	wstring imageFile1 = L"./Images/Background/Chapter07.png";

	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	texture = new Texture(imageFile1, shaderFile);
	
	sceneName = "HS13_Chapter07";
	sceneNum = 7;

	SetDisplay(true);
	SetActive(false);
}

HS13_Chapter07::~HS13_Chapter07()
{
	SAFE_DELETE(texture);
}

void HS13_Chapter07::Update()
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

	//Camera를 이용한다.
	CAMERA->Update();

	Matrix V, P;
	V = CAMERA->GetViewMatrix();
	P = CAMERA->GetProjMatrix();

	//해당 오브젝트를 Update

	texture->Update(V, P);
	OBJMANAGER->UpdateAll(V, P);
}

void HS13_Chapter07::Render()
{
	texture->Render();
	OBJMANAGER->RenderAll();
}

void HS13_Chapter07::ChangeScene()
{
	SetActive(true);

	cout << endl << "Chapter07!";

	HS03_ChangeScene* scene = (HS03_ChangeScene*)SCENEMANAGER->GetScene("HS03_ChangeScene");
	scene->SetNextScene("HS13_Chapter07");

	HS05_Dialogue* Dialogue = (HS05_Dialogue*)SCENEMANAGER->GetScene("HS05_Dialogue");
	Dialogue->SetSceneID(6);

	Goal* goal = (Goal*)OBJMANAGER->FindObject("Goal9");
	goal->Reset();
	goal->SetState(Goal::JUSTIS);

	texture->UpdateColorBuffer(Color(), 0, 0.0f, 0.0f, 0.0f);

	if (!reset)	// Goal 에서 Select 하는 Dialogue 가 되었을때
	{
		//reset = true;
		HTMAP->SetSize(9, 9);
		HTMAP->SetOffset(-350.0f, 427.5f);
		return;
	}

	HTMAP->Clear();
	HTMAP->SetSize(9, 9);
	HTMAP->SetOffset(-350.0f, 427.5f);
	OBJMANAGER->ClearObjectStrings();

	// Move
	// SetValue Map 의 번호에 값을 더해준다.
	{
		HTMAP->SetMapValue(1, 4, 5);

		HTMAP->SetMapValue(2, 4, 6);

		HTMAP->SetMapValue(3, 1, 2);
		HTMAP->SetMapValue(3, 3, 6);

		HTMAP->SetMapValue(4, 1, 6);

		HTMAP->SetMapValue(5, 1, 1);
		HTMAP->SetMapValue(5, 3, 6);

		HTMAP->SetMapValue(6, 1, 1);
		HTMAP->SetMapValue(6, 4, 4);

		HTMAP->SetMapValue(7, 1, 4);
	}

	// Trap
	{
		HTMAP->AssignTrap("Trap1", 1, 6, 0);
		HTMAP->AssignTrap("Trap2", 1, 7, 1);
		HTMAP->AssignTrap("Trap3", 2, 7, 0);
		HTMAP->AssignTrap("Trap4", 3, 7, 1);
		HTMAP->AssignTrap("Trap5", 4, 7, 0);
		HTMAP->AssignTrap("Trap6", 4, 6, 1);
	}

	// Key
	{
		HTMAP->AssignKey("Key", 2, 3);
		Key* key = (Key*)OBJMANAGER->FindObject("Key");
		key->SetActive(true);
	}

	// LockBox
	{
		HTMAP->AssignLockBox("LockBox", 5, 2);
		LockBox* lbox = (LockBox*)OBJMANAGER->FindObject("LockBox");
		lbox->SetActive(true);
	}

	// Fire
	{
		HTMAP->AssignFire("Fire1", -360.0f, -110.0f, 1);
		HTMAP->AssignFire("Fire2", 255.0f, 390.0f, 0);
		HTMAP->AssignFire("Fire3", 360.0f, 335.0f, 1);
	}

	// Box
	{
		HTMAP->AssignBox("Box1", 4, 3);
		HTMAP->AssignBox("Box2", 5, 3);
		HTMAP->AssignBox("Box3", 6, 3);

		HTMAP->AssignBox("Box4", 5, 4);
		HTMAP->AssignBox("Box5", 2, 4);
	}

	// Mob
	{
		HTMAP->AssignMob("Mob1", 1, 4);
		HTMAP->AssignMob("Mob2", 4, 4);
		HTMAP->AssignMob("Mob3", 3, 5);
	}

	// Goal
	{
		HTMAP->AssignGoal("Goal9", 4, 1);
	}

	// HT
	{
		HTMAP->AssignHelltaker(6, 5, 32);
	}

}