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


HS11_Chapter06::HS11_Chapter06()
{
	wstring imageFile1 = L"./Images/Background/Chapter06.png";

	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	texture = new Texture(imageFile1, shaderFile);

	sceneName = "HS11_Chapter06";
	sceneNum = 6;

	SetDisplay(true);
	SetActive(false);
}

HS11_Chapter06::~HS11_Chapter06()
{
	SAFE_DELETE(texture);
}

void HS11_Chapter06::Update()
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

void HS11_Chapter06::Render()
{
	texture->Render();
	OBJMANAGER->RenderAll();
}

void HS11_Chapter06::ChangeScene()
{
	SetActive(true);

	cout << endl << "Chapter06!";

	HS03_ChangeScene* scene = (HS03_ChangeScene*)SCENEMANAGER->GetScene("HS03_ChangeScene");
	scene->SetNextScene("HS11_Chapter06");

	HS05_Dialogue* Dialogue = (HS05_Dialogue*)SCENEMANAGER->GetScene("HS05_Dialogue");
	Dialogue->SetSceneID(5);

	Goal* goal = (Goal*)OBJMANAGER->FindObject("Goal8");
	goal->Reset();
	goal->SetState(Goal::AZAZEL);

	texture->UpdateColorBuffer(Color(), 0, 0.0f, 0.0f, 0.0f);

	if (!reset)	// Goal 에서 Select 하는 Dialogue 가 되었을때
	{
		//reset = true;
		return;
	}

	HTMAP->Clear();
	HTMAP->SetSize(9, 9);
	HTMAP->SetOffset(-400.0f, 477.5f);
	OBJMANAGER->ClearObjectStrings();

	// Move
	// SetValue Map 의 번호에 값을 더해준다.
	{
		HTMAP->SetMapValue(1, 2, 4);

		HTMAP->SetMapValue(2, 2, 4);

		HTMAP->SetMapValue(3, 1, 4);

		HTMAP->SetMapValue(4, 2, 5);

		HTMAP->SetMapValue(5, 2, 2);
		HTMAP->SetMapValue(5, 4, 7);

		HTMAP->SetMapValue(6, 2, 7);

		HTMAP->SetMapValue(7, 5, 7);

		HTMAP->SetMapValue(8, 5, 6);
	}

	// Trap
	{
		HTMAP->AssignTrap("Trap1", 2, 4, 1);
		HTMAP->AssignTrap("Trap2", 3, 4, 1);
	}

	// Key
	{
		HTMAP->AssignKey("Key", 4, 3);
		Key* key = (Key*)OBJMANAGER->FindObject("Key");
		key->SetActive(true);
	}

	// LockBox
	{
		HTMAP->AssignLockBox("LockBox", 5, 7);
		LockBox* lbox = (LockBox*)OBJMANAGER->FindObject("LockBox");
		lbox->SetActive(true);
	}

	// Fire
	{
		HTMAP->AssignFire("Fire1", -305.0f, 335.0f, 1);
		HTMAP->AssignFire("Fire2", 100.0f, 235.0f, 0);
		HTMAP->AssignFire("Fire3", 205.0f, 285.0f, 1);
	}

	// Slate
	{
		HTMAP->AssignSlate("Slate", 6, 7);
		Slate* slate = (Slate*)HTMAP->GetSecondObject(6, 7);
		slate->SetActive(true);
		slate->SetState(2);
	}

	// Box
	{
		HTMAP->AssignBox("Box1", 2, 2);
		HTMAP->AssignBox("Box2", 3, 2);
		HTMAP->AssignBox("Box3", 4, 2);

		HTMAP->AssignBox("Box4", 3, 4);

		HTMAP->AssignBox("Box5", 4, 5);
		HTMAP->AssignBox("Box6", 5, 5);


		HTMAP->AssignBox("Box7", 4, 6);
		HTMAP->AssignBox("Box8", 6, 7);

		Box* box = (Box*)HTMAP->GetGameObject(6, 7);
		box->SetID(10);
	}

	// Mob
	{
		HTMAP->AssignMob("Mob1", 2, 5);
		HTMAP->AssignMob("Mob2", 6, 6);
	}

	// Goal
	{
		HTMAP->AssignGoal("Goal8", 6, 8);
	}

	// HT
	{
		HTMAP->AssignHelltaker(3, 1, 43);
	}

}