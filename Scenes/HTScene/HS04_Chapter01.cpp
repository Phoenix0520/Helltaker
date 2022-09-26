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


HS04_Chapter01::HS04_Chapter01()
{
	wstring imageFile1 = L"./Images/Background/Chapter01.png";
	wstring shaderFile = L"./Shader/HLSL/texture.hlsl";

	texture = new Texture(imageFile1, shaderFile);

	// Scene 명칭
	sceneName = "HS04_Chapter01";
	sceneNum = 1;

	SetActive(false);
	SetDisplay(true);
}

HS04_Chapter01::~HS04_Chapter01()
{
	//SAFE_DELETE(star);
	SAFE_DELETE(texture);
}

void HS04_Chapter01::Update()
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
	{
		SCENEMANAGER->ChangeScene("HS05_Dialogue");
		Helltaker* ht = (Helltaker*)OBJMANAGER->FindObject("Helltaker");
		ht->SetGoal(true);
	}

	Helltaker* helltaker = dynamic_cast<Helltaker*>(OBJMANAGER->FindObject("Helltaker"));
	if (helltaker->GetHP() == -1)
	{
		printf("\nDead!");
		SCENEMANAGER->ChangeScene("HS00_DeadScene");
		return;
	}
	
	//View, Projection, Matrix를 넣어준다.

	//Camera를 이용한다.
	CAMERA->Update();

	Matrix V, P;
	V = CAMERA->GetViewMatrix();
	P = CAMERA->GetProjMatrix();

	//해당 오브젝트를 Update

	texture->Update(V, P);
	OBJMANAGER->UpdateAll(V, P);
}

void HS04_Chapter01::Render()
{
	texture->Render();
	OBJMANAGER->RenderAll();
}
//////////////////////////////////////////////////////////
// Map 에 대한 데이터 Update
// HP 가 0 이될경우 -> ChangeScene
//////////////////////////////////////////////////////////
void HS04_Chapter01::ChangeScene()
{
	SetActive(true);

	STOPSOUND("INTRO");

	if (!ISPLAYING("MAINBGM"))
		PLAYSOUND("MAINBGM", bgmSize);

	HS03_ChangeScene* scene = (HS03_ChangeScene*)SCENEMANAGER->GetScene("HS03_ChangeScene");
	scene->SetNextScene("HS04_Chapter01");

	HS05_Dialogue* Dialogue = (HS05_Dialogue*)SCENEMANAGER->GetScene("HS05_Dialogue");
	Dialogue->SetSceneID(0);

	Goal* goal = (Goal*)OBJMANAGER->FindObject("Goal1");
	goal->Reset();
	goal->SetState(Goal::PANDEMONICA);

	texture->UpdateColorBuffer(Color(), 0, 0.0f, 0.0f, 0.0f);

	if (!reset)	// Goal 에서 Select 하는 Dialogue 가 되었을때
	{
		//reset = true;
		HTMAP->SetSize(9, 8);
		HTMAP->SetOffset(-400.0f, 377.5f);
		return;
	}

	HTMAP->Clear();
	HTMAP->SetSize(9, 8);
	HTMAP->SetOffset(-400.0f, 377.5f);
	OBJMANAGER->ClearObjectStrings();

	// Move
	// SetValue Map 의 번호에 값을 더해준다.
	HTMAP->SetMapValue(1, 5, 6);
	HTMAP->SetMapValue(2, 2, 6);
	HTMAP->SetMapValue(3, 2, 5);
	HTMAP->SetMapValue(4, 1, 2);
	HTMAP->SetMapValue(5, 1, 6);
	HTMAP->SetMapValue(6, 1, 7);
	
	// dynamic_cast : 제대로 변환이 되지않으면 nullptr 를 반환한다.
	// static_cast : C 에서의 형변환과 비슷하다 컴파일러 상에서만 오류가 나지 않는 상황이 있을 수 있음.
	
	HTMAP->AssignBox("Box1", 5, 5);
	HTMAP->AssignBox("Box2", 2, 5);
	HTMAP->AssignBox("Box3", 2, 6);
	HTMAP->AssignBox("Box4", 4, 6);

	HTMAP->AssignMob("Mob1", 4, 2);
	HTMAP->AssignMob("Mob2", 3, 3);
	HTMAP->AssignMob("Mob3", 5, 3);


	HTMAP->AssignFire("Fire1", -295.0f, 235.0f, 1);
	HTMAP->AssignFire("Fire2", -5.0f, 340.0f, 0);
	HTMAP->AssignFire("Fire3", -402.5f, -60.0f, 0);
	HTMAP->AssignFire("Fire4", 305.0f, -15.0f, 1);

	HTMAP->AssignGoal("Goal1", 7, 6);
	
	HTMAP->AssignHelltaker(6, 1, 23);
}