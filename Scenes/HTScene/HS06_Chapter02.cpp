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


HS06_Chapter02::HS06_Chapter02()
{
	wstring imageFile1 = L"./Images/Background/Chapter02.png";

	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	texture = new Texture(imageFile1, shaderFile);
	
	sceneName = "HS06_Chapter02";
	sceneNum = 2;

	SetActive(false);
	SetDisplay(true);
}

HS06_Chapter02::~HS06_Chapter02()
{
	SAFE_DELETE(texture);
}

void HS06_Chapter02::Update()
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

void HS06_Chapter02::Render()
{
	texture->Render();
	OBJMANAGER->RenderAll();
}

void HS06_Chapter02::ChangeScene()
{
	SetActive(true);

	cout << endl << "Chapter02!";

	HS03_ChangeScene* scene = (HS03_ChangeScene*)SCENEMANAGER->GetScene("HS03_ChangeScene");
	scene->SetNextScene("HS06_Chapter02");

	HS05_Dialogue* Dialogue = (HS05_Dialogue*)SCENEMANAGER->GetScene("HS05_Dialogue");
	Dialogue->SetSceneID(1);

	Goal* goal = (Goal*)OBJMANAGER->FindObject("Goal2");
	goal->Reset();
	goal->SetState(Goal::MODEUS);

	texture->UpdateColorBuffer(Color(), 0, 0.0f, 0.0f, 0.0f);

	if (!reset)	// Goal 에서 Select 하는 Dialogue 가 되었을때
	{
		//reset = true;
		HTMAP->SetSize(9, 8);
		HTMAP->SetOffset(-400.0f, 372.5f);
		return;
	}

	HTMAP->Clear();
	HTMAP->SetSize(9, 8);
	HTMAP->SetOffset(-400.0f, 372.5f);
	OBJMANAGER->ClearObjectStrings();

	// Move
	// SetValue Map 의 번호에 값을 더해준다.

	HTMAP->SetMapValue(1, 2, 5);

	//SetMapValue(2, 2, 7);
	for (int i = 2; i <= 7; i++)
	{
		if (i == 3)
			HTMAP->SetValue(2, 3, HTMAPSTATE::wall, nullptr);
		else
			HTMAP->SetValue(i, 2, HTMAPSTATE::move, nullptr);
	}
	
	//SetMapValue(3, 1, 7);
	for (int i = 1; i <= 7; i++)
	{
		if (i == 3)
			HTMAP->SetValue(3, 3, HTMAPSTATE::wall, nullptr);
		else if (i == 4)
			HTMAP->SetValue(3, 4, HTMAPSTATE::wall, nullptr);
		else
			HTMAP->SetValue(i, 3, HTMAPSTATE::move, nullptr);
	}

	//SetMapValue(4, 1, 7);
	for (int i = 1; i <= 7; i++)
	{
		if (i == 3)
			HTMAP->SetValue(4, 3, HTMAPSTATE::wall, nullptr);
		else if (i == 4)
			HTMAP->SetValue(4, 4, HTMAPSTATE::wall, nullptr);
		else
			HTMAP->SetValue(i, 4, HTMAPSTATE::move, nullptr);
	}

	//SetMapValue(5, 1, 7);
	for (int i = 1; i <= 7; i++)
	{
		if (i == 3)
			HTMAP->SetValue(5, 3, HTMAPSTATE::wall, nullptr);
		else if (i == 4)
			HTMAP->SetValue(5, 4, HTMAPSTATE::wall, nullptr);
		else
			HTMAP->SetValue(i, 5, HTMAPSTATE::move, nullptr);
	}
	
	HTMAP->SetMapValue(6, 5, 7);


	// Trap
	{
		HTMAP->AssignTrap("Trap1", 2, 3);
		HTMAP->AssignTrap("Trap2", 4, 2);
		HTMAP->AssignTrap("Trap3", 5, 2);
		HTMAP->AssignTrap("Trap4", 5, 3);
		HTMAP->AssignTrap("Trap5", 6, 3);
		HTMAP->AssignTrap("Trap6", 6, 4);
	}


	// Box
	{
		HTMAP->AssignBox("Box1", 5, 3);
		HTMAP->AssignBox("Box2", 6, 3);
		HTMAP->AssignBox("Box3", 7, 3);
	}

	// Mob
	{
		HTMAP->AssignMob("Mob1", 2, 2);
		HTMAP->AssignMob("Mob2", 6, 5);
		HTMAP->AssignMob("Mob3", 7, 6);
	}


	// Fire
	{
		HTMAP->AssignFire("Fire1", -305.0f, 330.0f, 1);
		HTMAP->AssignFire("Fire2", 205.0f, 385.0f, 0);
		HTMAP->AssignFire("Fire3", 407.5f, -7.5f, 1);
	}

	// Goal
	{
		HTMAP->AssignGoal("Goal2", 5, 6);
	}

	// HT
	{
		HTMAP->AssignHelltaker(1, 5, 24);
	}
}