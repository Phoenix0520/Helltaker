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

HS15_Chapter09::HS15_Chapter09()
{
	wstring imageFile1 = L"./Images/Background/Chapter09.png";

	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	texture = new Texture(imageFile1, shaderFile);

	sceneName = "HS15_Chapter09";
	sceneNum = 9;

	SetDisplay(true);
	SetActive(false);
}

HS15_Chapter09::~HS15_Chapter09()
{
	SAFE_DELETE(texture);
}

void HS15_Chapter09::Update()
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

	if (timer > 0.0f)
		timer -= DELTA;
	else
		timer = 0.0f;

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

void HS15_Chapter09::Render()
{
	texture->Render();
	OBJMANAGER->RenderAll();
}

void HS15_Chapter09::ChangeScene()
{
	SetActive(true);

	cout << endl << "Chapter09!";

	HS05_Dialogue* Dialogue = (HS05_Dialogue*)SCENEMANAGER->GetScene("HS05_Dialogue");
	Dialogue->SetSceneID(8);

	HS03_ChangeScene* scene = (HS03_ChangeScene*)SCENEMANAGER->GetScene("HS03_ChangeScene");
	scene->SetNextScene("HS15_Chapter09");

	texture->UpdateColorBuffer(Color(), 0, 0.0f, 0.0f, 0.0f);
	timer = 0.25f;

	if (!reset)	// Goal 에서 Select 하는 Dialogue 가 되었을때
	{
		HTMAP->SetSize(11, 7);
		HTMAP->SetOffset(-500.0f, 175.5f);
		return;
	}

	HTMAP->Clear();
	HTMAP->SetSize(11, 7);
	HTMAP->SetOffset(-500.0f, 175.5f);
	OBJMANAGER->ClearObjectStrings();

	// Move
	{
		HTMAP->SetMapValue(0, 4, 6);

		HTMAP->SetMapValue(1, 4, 6);

		HTMAP->SetMapValue(2, 2, 2);
		HTMAP->SetMapValue(2, 4, 6);
		HTMAP->SetMapValue(2, 8, 8);

		HTMAP->SetMapValue(3, 1, 9);
		
		HTMAP->SetMapValue(4, 1, 9);

		HTMAP->SetMapValue(5, 2, 8);
	}

	// Key
	{
		HTMAP->AssignKey("Key", 9, 3);
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
		HTMAP->AssignFire("Fire1", -296.0f, 278.0f, 1);
		HTMAP->AssignFire("Fire2", -200.0f, 85.0f, 1);
		HTMAP->AssignFire("Fire3", 200.0f, 85.0f, 1);
		HTMAP->AssignFire("Fire4", 296.0f, 278.0f, 1);
	}

	// Box
	{
		HTMAP->AssignBox("Box1", 4, 1);
		HTMAP->AssignBox("Box2", 6, 1);

		HTMAP->AssignBox("Box3", 2, 2);
		HTMAP->AssignBox("Box4", 4, 2);

		HTMAP->AssignBox("Box5", 1, 3);
		HTMAP->AssignBox("Box6", 4, 3);
		HTMAP->AssignBox("Box7", 5, 3);
		HTMAP->AssignBox("Box8", 6, 3);
		
		HTMAP->AssignBox("Box9", 2, 4);
		HTMAP->AssignBox("Box10", 3, 4);
		HTMAP->AssignBox("Box11", 4, 4);
		HTMAP->AssignBox("Box12", 7, 4);
		HTMAP->AssignBox("Box13", 8, 4);

		HTMAP->AssignBox("Box14", 4, 5);
		HTMAP->AssignBox("Box15", 7, 5);
	}

	// HT
	{
		HTMAP->AssignHelltaker(2, 5, 33);
	}
}

/*
#include "framework.h"
#include "SceneList.h"
#include "ObjectList.h"
#include "Helltaker.h"
#include "Graphic2D.h"

HS15_Chapter09::HS15_Chapter09()
{
	wstring imageFile1 = L"./Images/Background/Chapter09.png";

	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	texture = new Texture(imageFile1, shaderFile);

	sceneName = "HS15_Chapter09";
	SetDisplay(true);
	SetActive(false);
}

HS15_Chapter09::~HS15_Chapter09()
{
	SAFE_DELETE(texture);
}

void HS15_Chapter09::Update()
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

	if (timer > 0.0f)
		timer -= DELTA;
	else
		timer = 0.0f;

	Helltaker* helltaker = dynamic_cast<Helltaker*>(OBJMANAGER->FindObject("Helltaker"));

	int hp = helltaker->GetHP();
	if (hp <= -1)
	{
		printf("\nDead!");
		SCENEMANAGER->ChangeScene("HS00_DeadScene");
		reset = true;
		return;
	}

	if (HTMAP->GetGameObject(5, 1) == helltaker)
	{
		timer -= DELTA;

		if (timer > 0.0f)
		{
			SCENEMANAGER->ChangeScene("HS05_Dialogue");
			timer = 0.0f;
		}
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

void HS15_Chapter09::Render()
{
	texture->Render();
	OBJMANAGER->RenderAll();
}

void HS15_Chapter09::ChangeScene()
{
	SetActive(true);

	cout << endl << "Chapter09!";

	HS05_Dialogue* Dialogue = (HS05_Dialogue*)SCENEMANAGER->GetScene("HS05_Dialogue");
	Dialogue->SetSceneID(8);

	HS03_ChangeScene* scene = (HS03_ChangeScene*)SCENEMANAGER->GetScene("HS03_ChangeScene");
	scene->SetNextScene("HS15_Chapter09");

	texture->UpdateColorBuffer(Color(), 0, 0.0f, 0.0f, 0.0f);
	timer = 0.25f;

	if (!reset)	// Goal 에서 Select 하는 Dialogue 가 되었을때
	{
		HTMAP->SetSize(11, 8);
		HTMAP->SetOffset(-500.0f, 275.5f);
		return;
	}

	HTMAP->Clear();
	HTMAP->SetSize(11, 8);
	HTMAP->SetOffset(-500.0f, 275.5f);

	OBJMANAGER->ClearObjectStrings();

	// Move
	{
		HTMAP->SetMapValue(0, 5, 5);

		HTMAP->SetMapValue(1, 4, 6);

		HTMAP->SetMapValue(2, 4, 6);

		HTMAP->SetMapValue(3, 2, 2);
		HTMAP->SetMapValue(3, 4, 6);
		HTMAP->SetMapValue(3, 8, 8);

		HTMAP->SetMapValue(4, 1, 9);

		HTMAP->SetMapValue(5, 1, 9);

		HTMAP->SetMapValue(6, 2, 8);
	}

	// Key
	{
		HTMAP->AssignKey("Key", 9, 4);
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
		HTMAP->AssignFire("Fire1", -296.0f, 278.0f, 1);
		HTMAP->AssignFire("Fire2", -200.0f, 85.0f, 1);
		HTMAP->AssignFire("Fire3", 200.0f, 85.0f, 1);
		HTMAP->AssignFire("Fire4", 296.0f, 278.0f, 1);
	}

	// Box
	{
		HTMAP->AssignBox("Box1", 4, 2);
		HTMAP->AssignBox("Box2", 6, 2);

		HTMAP->AssignBox("Box3", 2, 3);
		HTMAP->AssignBox("Box4", 4, 3);

		HTMAP->AssignBox("Box5", 1, 4);
		HTMAP->AssignBox("Box6", 4, 4);
		HTMAP->AssignBox("Box7", 5, 4);
		HTMAP->AssignBox("Box8", 6, 4);

		HTMAP->AssignBox("Box9", 2, 5);
		HTMAP->AssignBox("Box10", 3, 5);
		HTMAP->AssignBox("Box11", 4, 5);
		HTMAP->AssignBox("Box12", 7, 5);
		HTMAP->AssignBox("Box13", 8, 5);

		HTMAP->AssignBox("Box14", 4, 6);
		HTMAP->AssignBox("Box15", 7, 6);
	}

	// HT
	{
		HTMAP->AssignHelltaker(2, 6, 33);
	}
}
*/