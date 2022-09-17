#include "framework.h"
#include "HS17_BossScene.h"
#include "Helltaker.h"
#include "HelltakerMap.h"
#include "Box.h"
#include "Bridge.h"
#include "SinSkull.h"
#include "SinPistone.h"
#include "Chain.h"
#include "SRVManager.h"
#include "Trap.h"
#include "SinPyre.h"
#include "Judge.h"
#include "Line.h"
#include "ChainVH.h"
#include "ChainDaigonal.h"

#define   CHAIN_VIEW   3
#define   CHAIN_END   25

HS17_BossScene::HS17_BossScene()
{
	SetActive(false);
	SetDisplay(false);
	this->sceneName = "HS17_BossScene";

	m_cvGrid = new Line();

	Matrix R;

	D3DXMatrixRotationYawPitchRoll(&R, 0.0f, 0.0f, (float)D3DXToRadian(90.0f));

	for (int i = 0; i < 360; i++)
	{
		float x1 = 0.0f + cosf(i*3.141592f / 180.0f)*600.0f;
		float y1 = 0.0f + sinf(i*3.141592f / 180.0f)*200.0f;
		float x2 = 0.0f + cosf((i+1)*3.141592f / 180.0f)*600.0f;
		float y2 = 0.0f + sinf((i+1)*3.141592f / 180.0f)*200.0f;

		Vector2 start = Vector2(x1, y1);
		Vector2 end   = Vector2(x2, y2);

		D3DXVec2TransformCoord(&start, &start, &R);
		D3DXVec2TransformCoord(&end,   &end, &R);

		m_cvGrid->AddLine(start.x, start.y, end.x, end.y);

	}
	m_cvGrid->CreateVertexBuffer();

	// background texture	
	wstring imgfile = L"./Images/boss/background.png";
	wstring shaderFile = L"./Shader/HLSL/Texture.hlsl";
	m_pBackground = new Texture(imgfile, shaderFile);

	m_pBackground->SetOffsetSize(544.0f, (float)MAIN->GetHeight());
	//m_pBackground->SetScale(MAIN->GetWidth()/544, MAIN->GetHeight()/656);

	imgfile = L"./Images/boss/background2.png";
	m_pBackground2 = new Texture(imgfile, shaderFile);
	m_pBackground2->SetOffsetSize((float)MAIN->GetWidth(), (float)MAIN->GetHeight());

	imgfile = L"./Images/boss/background3.png";
	m_pBackground3 = new Texture(imgfile, shaderFile);
	m_pBackground3->SetScale(98.0f, 1.0f);
	m_pBackground3->SetPosition(0.0f, 17.0f);
	//m_pBackground3->SetOffsetSize((float)MAIN->GetWidth(), (float)MAIN->GetHeight());



	imgfile = L"./Images/boss/blockAll.png";
	m_pBlock = new Texture(imgfile, shaderFile);
	//계산해서 position을 구해준다.
	Vector2 size = m_pBlock->GetTextureRealSize();

	Vector2 position = Vector2(0.0f, 0.0f + size.y * 0.5f);
	CAMERA->WCToVC(position);
	position.x = 0.0f;
	m_pBlock->SetPosition(position);//위로 올린다.


	// 조금 작은 Image
	imgfile = L"./Images/boss/blockTop.png";
	m_pBlock2 = new Texture(imgfile, shaderFile);
	m_pBlock2->SetPosition(position);//위로 올린다.

	//m_pSinPanel

	imgfile = L"./Images/boss/UnderPanel.png";
	m_pSinPanel = new Texture(imgfile, shaderFile);
	m_pSinPanel->SetPosition(0.0f,-490.0f);

	//m_pSinPyre1

	
	m_pSinPyre1 = new SinPyre();
	m_pSinPyre1->SetPosition(-470.0f, -535.0f);
	

	//m_pSinPyre2

	m_pSinPyre2 = new SinPyre();;
	m_pSinPyre2->SetPosition(-220.0f, -535.0f);


	m_pSinPyre3 = new SinPyre();;
	m_pSinPyre3->SetPosition(220.0f, -535.0f);



	m_pSinPyre4 = new SinPyre();;
	m_pSinPyre4->SetPosition(470.0f, -535.0f);





	//m_pSinWheel

	imgfile = L"./Images/boss/SinWheel.png";
	m_pSinWheel = new Texture(imgfile, shaderFile);
	m_pSinWheel->SetPosition(0.0f, -680.0f);
//	m_pSinWheel->SetScale(0.7f, 0.7f);
	m_pSinWheel->SetRotation(0.0f, 0.0f, 72.0f);




	//SinCoreL
	imgfile = L"./Images/boss/sincore.png";
	m_pSinCoreL = new Texture(imgfile, shaderFile);
	size = m_pBlock->GetTextureRealSize();
	Vector2 size2 = m_pSinCoreL->GetTextureRealSize();

	position = m_pBlock->GetPosition();
	position.x = position.x - size.x * 0.5f + size2.x*0.5f;
	position.y = position.y - size.y * 0.5f - size2.y*0.5f;
	m_pSinCoreL->SetPosition(position);

	imgfile = L"./Images/boss/sincore.png";
	m_pSinCoreR = new Texture(imgfile, shaderFile);
	size = m_pBlock->GetTextureRealSize();
	size2 = m_pSinCoreR->GetTextureRealSize();

	position = m_pBlock->GetPosition();
	position.x = position.x + size.x * 0.5f - size2.x*0.5f;
	position.y = position.y - size.y * 0.5f - size2.y*0.5f;
	m_pSinCoreR->SetPosition(position);
	m_pSinCoreR->SetRotation(0.0f, 180.0f, 0.0f);

	m_pChainVH = new ChainVH();
	m_pChainDaigonal = new ChainDaigonal();

	if (!OBJMANAGER->FindObject("Bridge"))
	{
		Bridge *pBridge = new Bridge();
		OBJMANAGER->AddObject("Bridge", pBridge);
		pBridge->SetPosition(0.0f, -70.0f);
		function<void()> fp;
		fp = bind(&HS17_BossScene::StartBridge, this);
		pBridge->SetCallback(fp);
	}
	else
	{
		Bridge *pBridge = (Bridge*)OBJMANAGER->FindObject("Bridge");
		pBridge->SetPosition(0.0f, -70.0f);
		function<void()> fp;
		fp = bind(&HS17_BossScene::StartBridge, this);
		pBridge->SetCallback(fp);
	}

	m_pJudge = new Judge();
	m_pJudge->SetPosition(0.0f, 380.0f);

	if (!OBJMANAGER->FindObject("Chain"))
	{
		Chain *pChain = new Chain();
		OBJMANAGER->AddObject("Chain", pChain);
		pChain->SetPosition(-820.0f, 300.0f);
		pChain->SetScale(0.825f, 0.825f);
	}

	if (!OBJMANAGER->FindObject("SinPistonBottom"))
	{
		SinPistone *pSinPistone = new SinPistone();
		OBJMANAGER->AddObject("SinPistonBottom", pSinPistone);
	}

	if (!OBJMANAGER->FindObject("SinPistonCap"))
	{
		SinPistone *pSinPistone = new SinPistone();
		OBJMANAGER->AddObject("SinPistonCap", pSinPistone);
		pSinPistone->SetPosition(-820.0f, 570.0f);
		pSinPistone->SetMaxMin(570.0f, 420.0f);
	}

	if (!OBJMANAGER->FindObject("SinPiston"))
	{
		SinPistone *pSinPistone = new SinPistone();
		OBJMANAGER->AddObject("SinPiston", pSinPistone);
		pSinPistone->SetPosition(-820.0f, 570.0f);
		pSinPistone->SetMaxMin(570.0f, 420.0f);
	}

	if (!OBJMANAGER->FindObject("SinSkull"))
	{
		SinSkull *pSinSkull = new SinSkull();
		OBJMANAGER->AddObject("SinSkull", pSinSkull);
		pSinSkull->SetPosition(-600.0f, -225.0f);
		pSinSkull->SetMaxMin(-90.0f, -225.0f);
	}
}

HS17_BossScene::~HS17_BossScene()
{
	SAFE_DELETE(m_pBackground);
	SAFE_DELETE(m_pBackground2);
	SAFE_DELETE(m_pBackground3);
	SAFE_DELETE(m_pBlock);
	SAFE_DELETE(m_pSinCoreL);
	SAFE_DELETE(m_pSinCoreR);
}

void HS17_BossScene::Update()
{
	Matrix V, P;

	CAMERA->Update();
	V = CAMERA->GetViewMatrix();
	P = CAMERA->GetProjMatrix();

	// helltaker의 hp가 -1이면 death신 호출

	Helltaker *ht = (Helltaker*)OBJMANAGER->FindObject("Helltaker");
	
	if (DOWN(VK_DELETE))
		ht->SetHP(ht->GetHP() - 1);

	if (DOWN(VK_F12))
	{
		if (ht->GetImmune())
			ht->SetImmune(false);
		else
			ht->SetImmune(true);
	}
	
	
	if (ht->GetHP() <= 0)
	{
		SCENEMANAGER->ChangeScene("HS00_DeadScene");
		Scene* scene = SCENEMANAGER->GetScene("HS03_ChangeScene");
		if (scene)
			scene->SetNextScene("HS17_BossScene");
		return;
	}


	// Synpyre Setting
	switch (ht->GetHP())
	{
	case 4:
		m_pSinPyre1->SetState(1);
		m_pSinPyre2->SetState(1);
		m_pSinPyre3->SetState(1);
		m_pSinPyre4->SetState(1);
		break;

	case 3:
		m_pSinPyre1->SetState(0);
		break;
	case 2:
		m_pSinPyre2->SetState(0);
		break;
	case 1:
		m_pSinPyre3->SetState(0);
		break;
	case 0:
		m_pSinPyre1->SetState(0);
		m_pSinPyre2->SetState(0);
		m_pSinPyre3->SetState(0);
		m_pSinPyre4->SetState(0);
		break;

	}


	Bridge *pBridge = (Bridge*)OBJMANAGER->FindObject("Bridge");
	
	switch (m_nStep)
	{
	    case 1:
			UpdateBridge();
			UpdateChain();
			break;
		case 2:
			UpdateChain();
			break;
		case 3:
			if (!m_pJudge->IsPlay())
			{
				m_pJudge->SetActive(false);
				m_nStep++;
				OnDialog();
			}
			break;
	}

	// Object
	m_pBackground->Update(V, P);
	m_pBackground2->Update(V, P);
	m_pBackground3->Update(V, P);
	m_pBlock->Update(V, P);
	m_pBlock2->Update(V, P);
	m_pSinCoreL->Update(V, P);
	m_pSinCoreR->Update(V, P);
	m_pSinPanel->Update(V, P);
	m_pSinPyre1->Update(V, P);
	m_pSinPyre2->Update(V, P);
	m_pSinPyre3->Update(V, P);
	m_pSinPyre4->Update(V, P);

	m_pSinWheel->Update(V, P);

	m_pChainVH->Update(V, P);
	m_pChainDaigonal->Update(V, P);
	m_pJudge->Update(V, P);

	OBJMANAGER->Update("SinSkull",V,P);
	OBJMANAGER->Update("SinPiston", V, P);
	OBJMANAGER->Update("SinPistonCap", V, P);
	OBJMANAGER->Update("SinPistonBottom", V, P);
	OBJMANAGER->Update("Chain", V, P);
	OBJMANAGER->Update("Bridge", V, P);
	OBJMANAGER->UpdateAll(V, P);

	m_cvGrid->Update(V, P);
}

void HS17_BossScene::Render()
{
	Matrix V, P;
	V = CAMERA->GetViewMatrix();
	P = CAMERA->GetProjMatrix();


	Vector2 size = m_pBackground->GetTextureRealSize();
	m_pBackground->SetPosition(-MAIN->GetWidth()*0.5f + size.x*0.5f, 0.0f);
	m_pBackground->Update(V, P);
	m_pBackground->Render();

	m_pBackground->SetPosition(MAIN->GetWidth()*0.5f - size.x*0.5f, 0.0f);
	m_pBackground->Update(V, P);
	m_pBackground->Render();

	m_pBackground2->Render();
	m_pBackground3->Render();

	m_pSinCoreL->Render();
	m_pSinCoreR->Render();


	SinSkull *pSkull = (SinSkull*)OBJMANAGER->FindObject("SinSkull");
	pSkull->SetState(0);
	OBJMANAGER->Render("SinSkull");


	OBJMANAGER->Render("Bridge");
	m_pBlock->Render();


	OBJMANAGER->Render("SinPiston");
	OBJMANAGER->Render("Chain");
	OBJMANAGER->Render("SinPistonCap");

	pSkull->SetState(1);
	OBJMANAGER->Render("SinSkull");


	OBJMANAGER->RenderAll();

	m_pSinWheel->Render();
	m_pSinPanel->Render();
	m_pBlock2->Render();


	OBJMANAGER->Render("SinPistonBottom");
	m_pSinPyre1->Render();
	m_pSinPyre2->Render();
	m_pSinPyre3->Render();
	m_pSinPyre4->Render();
	
	m_pChainVH->Render();
	m_pChainDaigonal->Render();
	m_pJudge->Render();

	DirectWrite::GetDC()->BeginDraw();
	{
		wstring str = L"FPS : (" + to_wstring(TIMEMANAGER->GetFrame()) + L" / " + to_wstring(TIMEMANAGER->GetLockFPS()) + L")";

		RECT rect = { 5, 5, 505, 505 };

		DirectWrite::RenderText(str, rect);
	}
	DirectWrite::GetDC()->EndDraw();
}

void HS17_BossScene::ChangeScene()
{
	TIMEMANAGER->SetLockFPS(144.0f);

	SetActive(true);
	
	switch (m_Stage)
	{
	case 1: SetScenario1(); break;
	//case 2: SetScenario2(); break;
	//case 3: SetScenario3(); break;
	//case 4: SetScenario4(); break;
	}
	m_Time = 0.0f;
	m_nScenarioCount = 0;
	m_nStep = 0;


	Vector2 size = m_pBlock->GetTextureRealSize();
	Vector2 position = Vector2(0.0f, 0.0f + size.y * 0.5f);
	CAMERA->WCToVC(position);
	position.x = 0.0f;
	m_pBlock->SetPosition(position);

	SinSkull *pSinSkull = (SinSkull*)OBJMANAGER->FindObject("SinSkull");

	if (pSinSkull)
	{
		pSinSkull->SetPosition(-600.0f, -225.0f);
		pSinSkull->SetMaxMin(-30.0f, -225.0f);
		pSinSkull->Reset();
	}

	Chain *pChain = (Chain*)OBJMANAGER->FindObject("Chain");
	if (pChain)
	{
		pChain->SetPosition(-820.0f, 300.0f);
		pChain->SetScale(0.825f, 0.825f);
		pChain->Reset();
	}

	SinPistone *pSinPistone = (SinPistone*)OBJMANAGER->FindObject("SinPistonBottom");
	if (pSinPistone)
	{
		pSinPistone->SetState(4);
		pSinPistone->SetPosition(-820.0f, -820.0f);//초기 위치
		pSinPistone->Reset();
	}
	pSinPistone = (SinPistone*)OBJMANAGER->FindObject("SinPistonCap");
	if (pSinPistone)
	{
		pSinPistone->SetState(1);     // 2
		pSinPistone->SetPosition(-820.0f, 570.0f);//초기 위치
		pSinPistone->Reset();
	}
	pSinPistone = (SinPistone*)OBJMANAGER->FindObject("SinPiston");
	if (pSinPistone)
	{
		pSinPistone->SetState(0);     // 2
		pSinPistone->SetPosition(-820.0f, 570.0f);//초기 위치
		pSinPistone->Reset();
	}

	Bridge *pBridge = (Bridge*)OBJMANAGER->FindObject("Bridge");

	if (pBridge)
	{
		pBridge->SetPosition(0.0f, -70.0f);
		pBridge->Reset();
	}

	m_pJudge->SetActive(false);


	ShowMap(-400.0f, 200.0f);

	// Helltaker : dynamic_cast , static_cast ( 구별방법)
	Helltaker *pObject = dynamic_cast<Helltaker*>(OBJMANAGER->FindObject("Helltaker"));

	//Helltaker *pObject = (Helltaker*)OBJMANAGER->FindObject("Helltaker");
	if (pObject != nullptr)
	{
		Vector2 pos = HTMAP->GetPosition(4, 3);
		pObject->SetPosition(pos);
		HTMAP->SetValue(4, 3, HelltakerMap::helltaker, pObject);
		pObject->SetHP(4);
		pObject->Reset();

		function<void()> fp;
		fp = bind(&HS17_BossScene::OnDialog, this);
	}

	OBJMANAGER->AddObjectStrings("Helltaker");

}

void HS17_BossScene::OnDialog()
{
	
}

void HS17_BossScene::Sample()//에디터를 만들어주는 창
{
	
}

void HS17_BossScene::ShowMap(float x, float y)
{
	OBJMANAGER->ClearObjectStrings();

	HTMAP->Clear();
	HTMAP->SetSize(9, 9);
	HTMAP->SetOffset(x, y);

	for (int i = 1; i < 8; i++)
	{
		for (int j = 0; j < 9; j++)
			HTMAP->SetValue(i, j, HelltakerMap::move, NULL);
	}

	// Trap
	for (int i = 1; i <= 7; i++)
	{
		string str = "Trap" + to_string(i);

		Trap *pTrap = (Trap*)OBJMANAGER->FindObject(str);

		if (y >= 260.0f)
		{
			pTrap->SetActive(true);
			HTMAP->AssignTrap(str, i, 0, 5);
		}

		else
		{
			pTrap->SetActive(true);
			HTMAP->AssignTrap(str, i, 0, 5);
		}

	}
	int id = 8;
	for (int i = 1; i <= 7; i++)
	{
		string str = "Trap" + to_string(id);

		if (y >= 230.0f  && y <= 250.0f)
		{
			HTMAP->AssignTrap(str, i, 1, 6);
			Trap *pTrap = (Trap*)OBJMANAGER->FindObject(str);
		}
		if (y >= 250.0f)
		{
			HTMAP->AssignTrap(str, i, 1, 5);
			Trap *pTrap = (Trap*)OBJMANAGER->FindObject(str);
		}
		id++;
	}


	for (int i = 1; i <= 7; i++)
	{
		string str = "Trap" + to_string(id);
		Trap *pTrap = (Trap*)OBJMANAGER->FindObject(str);

		if (y >= 280.0f && y <= 300.0f)
		{
			pTrap->SetActive(true);
			HTMAP->AssignTrap(str, i, 6, 6);
		}

		else if (y >= 200.0f)
		{
			pTrap->SetActive(true);
			HTMAP->AssignTrap(str, i, 6, 5);
		}
		id++;
	}

	for (int i = 1; i <= 7; i++)
	{
		string str = "Trap" + to_string(id);

		Trap *pTrap = (Trap*)OBJMANAGER->FindObject(str);
		if (y >= 210.0f)
			HTMAP->AssignTrap(str, i, 7, 5);

		id++;
	}
}

void HS17_BossScene::SetScenario1()
{
	m_cvScenario.clear();

	const int RDY  = 0;
	const int ATK = 1;
	const int VER   = 0;
	const int HOR   = 1;

	m_cvScenario.push_back(Scenario{ RDY, 0x00000, 0x1000000, 0.75f });
	m_cvScenario.push_back(Scenario{ ATK, 0x00000, 0x1000000, 0.25f });
	m_cvScenario.push_back(Scenario{ RDY, 0x00000, 0x0100000, 0.75f });
	m_cvScenario.push_back(Scenario{ ATK, 0x00000, 0x0100000, 0.25f });
	m_cvScenario.push_back(Scenario{ RDY, 0x00000, 0x0010000, 0.75f });
	m_cvScenario.push_back(Scenario{ ATK, 0x00000, 0x0010000, 0.25f });
	m_cvScenario.push_back(Scenario{ RDY, 0x00000, 0x0001000, 0.75f });
	m_cvScenario.push_back(Scenario{ ATK, 0x00000, 0x0001000, 0.25f });
	m_cvScenario.push_back(Scenario{ RDY, 0x00000, 0x0000100, 0.75f });
	m_cvScenario.push_back(Scenario{ ATK, 0x00000, 0x0000100, 0.25f });
	m_cvScenario.push_back(Scenario{ RDY, 0x00000, 0x0000010, 0.75f });
	m_cvScenario.push_back(Scenario{ ATK, 0x00000, 0x0000010, 0.25f });
	m_cvScenario.push_back(Scenario{ RDY, 0x00000, 0x0000001, 0.75f });
	m_cvScenario.push_back(Scenario{ ATK, 0x00000, 0x0000001, 0.25f });
	m_cvScenario.push_back(Scenario{ RDY, 0x00000, 0x0000010, 0.75f });
	m_cvScenario.push_back(Scenario{ ATK, 0x00000, 0x0000010, 0.25f });
	m_cvScenario.push_back(Scenario{ RDY, 0x00000, 0x0000100, 0.75f });
	m_cvScenario.push_back(Scenario{ ATK, 0x00000, 0x0000100, 0.25f });
	m_cvScenario.push_back(Scenario{ RDY, 0x00000, 0x0001000, 0.75f });
	m_cvScenario.push_back(Scenario{ ATK, 0x00000, 0x0001000, 0.25f });
	m_cvScenario.push_back(Scenario{ RDY, 0x00000, 0x0010000, 0.75f });
	m_cvScenario.push_back(Scenario{ ATK, 0x00000, 0x0010000, 0.25f });
	m_cvScenario.push_back(Scenario{ RDY, 0x00000, 0x0100000, 0.75f });
	m_cvScenario.push_back(Scenario{ ATK, 0x00000, 0x0100000, 0.25f });
	m_cvScenario.push_back(Scenario{ RDY, 0x00000, 0x1000000, 0.75f });
	m_cvScenario.push_back(Scenario{ ATK, 0x00000, 0x1000000, 0.25f });
	m_cvScenario.push_back(Scenario{ RDY, 0x00000, 0x1001000, 0.75f });
	m_cvScenario.push_back(Scenario{ ATK, 0x00000, 0x1001000, 0.25f });
	m_cvScenario.push_back(Scenario{ RDY, 0x00000, 0x0100100, 0.75f });
	m_cvScenario.push_back(Scenario{ ATK, 0x00000, 0x0100100, 0.25f });
	m_cvScenario.push_back(Scenario{ RDY, 0x00000, 0x0010010, 0.75f });
	m_cvScenario.push_back(Scenario{ ATK, 0x00000, 0x0010010, 0.25f });
										 		 		    
	m_cvScenario.push_back(Scenario{ CHAIN_VIEW, 0x00000, 0x010010, 0.0f });
	

	m_cvScenario.push_back(Scenario{ RDY, 0x00000, 0x0001001, 0.75f });
	m_cvScenario.push_back(Scenario{ ATK, 0x00000, 0x0001001, 0.25f });
	m_cvScenario.push_back(Scenario{ RDY, 0x00000, 0x0010010, 0.75f });
	m_cvScenario.push_back(Scenario{ ATK, 0x00000, 0x0010010, 0.25f });
	m_cvScenario.push_back(Scenario{ RDY, 0x00000, 0x0100100, 0.75f });
	m_cvScenario.push_back(Scenario{ ATK, 0x00000, 0x0100100, 0.25f });
	m_cvScenario.push_back(Scenario{ RDY, 0x00000, 0x1001000, 0.75f });
	m_cvScenario.push_back(Scenario{ ATK, 0x00000, 0x1001000, 0.25f });
	
	m_cvScenario.push_back(Scenario{ CHAIN_END, 0x0000 ,0x010010 ,50000.0f });
}

void HS17_BossScene::UpdateChain()
{
	if (m_nScenarioCount >= m_cvScenario.size())
		return;

	if (m_nScenarioCount >= m_cvScenario.size())
		return;

	Scenario p = m_cvScenario[m_nScenarioCount];

	m_Time = m_Time + TIMEMANAGER->Delta();
	if (m_Time > p.Time)
	{
		m_nScenarioCount++;
		m_Time = 0.0f;
	}
	Scenario p2 = m_cvScenario[m_nScenarioCount];
	if (p2.State == 0)
	{
		Helltaker *pObject = dynamic_cast<Helltaker*>(OBJMANAGER->FindObject("Helltaker"));
		pObject->ExternMoveObject(p2.vertical, p2.horizontal);
	}

	if (p.State == CHAIN_END || p.State == CHAIN_VIEW)
	{
		Bridge *pBridge = (Bridge*)OBJMANAGER->FindObject("Bridge");
		pBridge->SetMove(false);
	
		Chain *pChain = (Chain*)OBJMANAGER->FindObject("Chain");
		pChain->SetMove(false);
	
		if (p.State == CHAIN_END)
			m_nStep = 3;
	
		if (p.State == CHAIN_VIEW)
			m_nStep = 2;
	
	
		m_pChainVH->Reset();
		m_pChainDaigonal->Reset();
	
	
		Helltaker *pObject = dynamic_cast<Helltaker*>(OBJMANAGER->FindObject("Helltaker"));
		Vector2    pos2 = pObject->GetPosition();
		POINT      pt = HTMAP->GetMapXY(pos2);
	
	
		ShowMap(-400.0f, 200.0f);
	
		m_pChainDaigonal->SetActive(true);
		m_pChainDaigonal->SetState(p.vertical);
		//	m_pChainDaigonal->SetGapY(pBridge->Gap());
	
		m_pChainVH->SetActive(false);
	
		pBridge->SetPosition(0.0f, -70.0f);
		pBridge->Reset();
	
	
	
		HTMAP->SetValue(pt.x, pt.y, HelltakerMap::State::helltaker, pObject);
		Vector2 pos = HTMAP->GetPosition(pt.x, pt.y);
		pObject->SetPosition(pos);
	
		OBJMANAGER->AddObjectStrings("Helltaker");
	
		return;
	}

	m_pChainVH->SetActive(true);
	m_pChainVH->SetState(p.State);  // Ready, Attack
	m_pChainVH->SetValue(p.vertical, p.horizontal);

}

void HS17_BossScene::UpdateBridge()
{
	Vector2 pos = HTMAP->GetOffset();
	
	Helltaker *ht = (Helltaker*)OBJMANAGER->FindObject("Helltaker");
	Vector2 pos2 = ht->GetPosition();
	
	pos2.y = pos2.y;
	POINT pt = HTMAP->GetMapXY(pos2);
	pos2.y = pos2.y + 1.5f;
	
	pos.y = pos.y + 1.5f;
	if (pos.y >= 290)
	{
		pos.y = 200.0f;
	}
	
	ShowMap(pos.x, pos.y);
	HTMAP->SetValue(pt.x, pt.y, HelltakerMap::helltaker, ht);
	OBJMANAGER->AddObjectStrings("Helltaker");
}

void HS17_BossScene::StartBridge()
{
	m_nStep = 1;

	Scenario p2 = m_cvScenario[0];
	if (p2.State == 0)
	{
		Helltaker *pObject = dynamic_cast<Helltaker*>(OBJMANAGER->FindObject("Helltaker"));
		pObject->ExternMoveObject(p2.vertical, p2.horizontal);
	}
}

void HS17_BossScene::DrawBanner(wstring strBanner, float cx, float cy, float size, int r, int g, int b)
{
	
}
