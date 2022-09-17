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


HS08_Chapter04::HS08_Chapter04()
{
	wstring imageFile1 = L"./Images/Background/Chapter04.png";

	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	texture = new Texture(imageFile1, shaderFile);

	sceneName = "HS08_Chapter04";
	sceneNum = 4;

	SetActive(false);
	SetDisplay(true);
}

HS08_Chapter04::~HS08_Chapter04()
{
	SAFE_DELETE(texture);
}

void HS08_Chapter04::Update()
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
		SCENEMANAGER->GetScene("HS08_Chapter04")->SetReset(true);
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

void HS08_Chapter04::Render()
{
	texture->Render();
	OBJMANAGER->RenderAll();
}

void HS08_Chapter04::ChangeScene()
{
	SetActive(true);

	cout << endl << "Chapter04!";

	HS03_ChangeScene* scene = (HS03_ChangeScene*)SCENEMANAGER->GetScene("HS03_ChangeScene");
	scene->SetNextScene("HS08_Chapter04");

	HS05_Dialogue* Dialogue = (HS05_Dialogue*)SCENEMANAGER->GetScene("HS05_Dialogue");
	Dialogue->SetSceneID(3);

	Goal* goal = (Goal*)OBJMANAGER->FindObject("Goal6");
	goal->Reset();
	goal->SetState(Goal::MALINA);

	texture->UpdateColorBuffer(Color(), 0, 0.0f, 0.0f, 0.0f);

	if (!reset)	// Goal 에서 Select 하는 Dialogue 가 되었을때
	{
		//reset = true;
		/*HTMAP->SetSize(10, 7);
		HTMAP->SetOffset(-450.0f, 325.0f);

		HTMAP->SetMapValue(1, 1, 5);
		HTMAP->ReSetValue(2, 1, HTMAPSTATE::move);

		HTMAP->SetMapValue(2, 1, 7);
		HTMAP->SetMapValue(3, 1, 8);
		HTMAP->SetMapValue(4, 1, 8);
		HTMAP->SetMapValue(4, 1, 8);
		HTMAP->SetMapValue(5, 2, 6);*/

		return;
	}

	HTMAP->Clear();
	HTMAP->SetSize(10, 7);
	HTMAP->SetOffset(-450.0f, 325.0f);
	OBJMANAGER->ClearObjectStrings();

	// Move
	// SetValue Map 의 번호에 값을 더해준다.

	HTMAP->SetMapValue(1, 1, 5);
	HTMAP->ReSetValue(2, 1, HTMAPSTATE::move);

	HTMAP->SetMapValue(2, 1, 7);
	HTMAP->SetMapValue(3, 1, 8);
	HTMAP->SetMapValue(4, 1, 8);
	HTMAP->SetMapValue(4, 1, 8);
	HTMAP->SetMapValue(5, 2, 6);

	// Trap
	{
		HTMAP->AssignTrap("Trap1", 4, 2);
		HTMAP->AssignTrap("Trap2", 5, 2);
	}

	// Key
	{
		HTMAP->AssignKey("Key", 3, 1);
		Key* key = (Key*)OBJMANAGER->FindObject("Key");
		key->SetActive(true);
	}

	// LockBox
	{
		HTMAP->AssignLockBox("LockBox", 6, 2);
		LockBox* lbox = (LockBox*)OBJMANAGER->FindObject("LockBox");
		lbox->SetActive(true);
	}

	// Fire
	{
		HTMAP->AssignFire("Fire1", -250.0f, 285.0f, 1);
		HTMAP->AssignFire("Fire2", 152.5f, 335.0f, 0);
		HTMAP->AssignFire("Fire3", 355.0f, 325.0f, 0);
		HTMAP->AssignFire("Fire4", 455.0f, 130.0f, 1);
	}

	// Slate
	{
		HTMAP->AssignSlate("Slate", 7, 4);
		Slate* slate = (Slate*)HTMAP->GetSecondObject(7, 4);
		slate->SetState(0);
		slate->SetActive(true);
	}

	// Box
	{
		HTMAP->AssignBox("Box1", 5, 1);
		HTMAP->AssignBox("Box2", 2, 2);
		HTMAP->AssignBox("Box3", 4, 2);
		HTMAP->AssignBox("Box4", 1, 3);
		HTMAP->AssignBox("Box5", 3, 3);
		HTMAP->AssignBox("Box6", 5, 3);
		HTMAP->AssignBox("Box7", 6, 3);
		HTMAP->AssignBox("Box8", 2, 4);
		HTMAP->AssignBox("Box9", 4, 4);
		HTMAP->AssignBox("Box10", 6, 4);
		HTMAP->AssignBox("Box11", 7, 4);

		Box* box = (Box*)HTMAP->GetGameObject(7, 4);
		box->SetID(8);

		HTMAP->AssignBox("Box12", 3, 5);
		HTMAP->AssignBox("Box13", 5, 5);
	}

	// Goal
	{
		HTMAP->AssignGoal("Goal6", 8, 3);
	}


	// HT
	{
		HTMAP->AssignHelltaker(1, 1, 23);
	}

}