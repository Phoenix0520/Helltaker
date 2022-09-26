#include "framework.h"
#include "HS19_MapEditor.h"
#include "HelltakerMap.h"
#include "Helltaker.h"

HS19_MapEditor::HS19_MapEditor()
{
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	vector<wstring> imageFile;
	imageFile.push_back(L"./Images/Background/Chapter01.png");
	imageFile.push_back(L"./Images/MapEditor/Road.png");
	imageFile.push_back(L"./Images/MapEditor/Helltaker.png");
	imageFile.push_back(L"./Images/MapEditor/Box.png");
	imageFile.push_back(L"./Images/MapEditor/Mob.png");
	imageFile.push_back(L"./Images/MapEditor/Trap.png");
	imageFile.push_back(L"./Images/MapEditor/Goal.png");
	imageFile.push_back(L"./Images/MapEditor/Key.png");
	imageFile.push_back(L"./Images/MapEditor/LockBox.png");
	imageFile.push_back(L"./Images/MapEditor/Slate.png");
	imageFile.push_back(L"./Images/MapEditor/Fire.png");
	
	mapBG = new Texture(imageFile[0], shaderFile);

	for (UINT i = 1; i <= 8; i++)
		tempTexture.push_back(new Texture(imageFile[i], shaderFile));

	sceneName = "HS19_MapEditor";

	SetDisplay(true);
	SetActive(false);
}

HS19_MapEditor::~HS19_MapEditor()
{
	SAFE_DELETE(background);
	SAFE_DELETE(mapBG);

	for (UINT i = 0; i < tempTexture.size(); i++)
		SAFE_DELETE(tempTexture[i]);
	for (UINT i = 0; i < mapTile.size(); i++)
		SAFE_DELETE(mapTile[i]);
	for (UINT i = 0; i < obj.size(); i++)
		SAFE_DELETE(obj[i]);
}

void HS19_MapEditor::Update()
{
	visibleMap = true;

	CAMERA->Update();
	Matrix V = VM;
	Matrix P = PM;

	mapBG->Update(V, P);

	if (inserting)
	{
		Vector2 pos = mouse->GetPosition();
		CAMERA->WCToVC(pos);

		tempTexture[combo]->SetPosition(pos);
		tempTexture[combo]->Update(V, P);
	}

	OBJMANAGER->UpdateAll(V, P);
}

void HS19_MapEditor::Render()
{
	DirectWrite::GetDC()->BeginDraw();
	mapBG->Render();

	if (inserting)
	{
		tempTexture[combo]->Render();
	}

	if (1)
		ShowGUI();
	DirectWrite::GetDC()->EndDraw();

	OBJMANAGER->RenderAll();
}

void HS19_MapEditor::ChangeScene()
{
	SetActive(true);
	ShowCursor(true);
}

void HS19_MapEditor::ShowGUI()
{
	ImGui::GetIO().NavActive = false;
	ImGui::GetIO().WantCaptureMouse = true;

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin(u8"맵 에디터");
	{
		ImGui::BeginTabBar("");
		{
			if (ImGui::BeginTabItem(u8"스테이지 설정")) // Map 세팅
			{
				GUISetMap();
				
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem(u8"오브젝트 추가"))
			{
				GUIAddObj();

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem(u8"설정 저장"))
			{
				GUISaveMap();

				ImGui::EndTabItem();
			}
		}
		ImGui::EndTabBar();
	}
	ImGui::End();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void HS19_MapEditor::GUISetMap()
{
	static const char* scenes[] =
	{ u8"챕터 1", u8"챕터 2", u8"챕터 3", u8"챕터 4", u8"챕터 5", u8"챕터 6", u8"챕터 7", u8"챕터 8", u8"챕터 9" };

	if (ImGui::Combo(u8"챕터 선택", &chapter, scenes, ARRAYSIZE(scenes)))
	{
		switch (chapter)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
			mapBG->SetImageFile(L"./Images/Background/Chapter0" + to_wstring(chapter + 1) + L".png");
			break;
		}
	}

	static int mapSize[2] = { 0, 0 };
	static Vector2 mapOffset = offset;

	if (ImGui::InputInt(u8"스테이지 체력", &stageHp))
	{
		Helltaker* ht = (Helltaker*)OBJMANAGER->FindObject("Helltaker");
		ht->SetHP(stageHp);
	}

	if (ImGui::InputInt2(u8"맵 크기", mapSize))
	{
		init = false;

		mapObj.resize((UINT)mapSize[0]);
		for (UINT i = 0; i < mapObj.size(); i++)
			mapObj[i].resize(mapSize[1]);

		mapObjX.resize((UINT)mapSize[0]);
		mapObjY.resize((UINT)mapSize[1]);

		HTMAP->SetSize(mapObjX.size(), mapObjY.size());
	}

	if (ImGui::InputFloat2(u8"맵 오프셋", mapOffset, "%.1f"))
	{
		offset = mapOffset;
		HTMAP->SetOffset(offset);
	}

	static bool toggle = false;

	if (ImGui::Checkbox(u8"토글 트랩", &toggle))
	{
		toggleTrap = toggle;
	}
}

void HS19_MapEditor::GUIAddObj()
{
	static const char* objects[] =
	{ u8"길", u8"헬테이커", u8"박스",  u8"몬스터", u8"가시", u8"도착지", u8"열쇠", u8"잠긴박스", u8"슬레이트", u8"화로" };

	if (ImGui::Combo(u8"오브젝트 타입", &combo, objects, ARRAYSIZE(objects)))
	{
		switch (combo)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		}
	}

	cout << "Inserting : " << inserting << " Deleting : " << deleting << endl;

	if (mouse->Up(0))
	{
		inserting = false;
		deleting = false;
	}

	if (!inserting && !deleting)
	{
		if (ImGui::Button(u8"추가"))
		{
			inserting = true;
		}
		ImGui::SameLine();
		if (ImGui::Button(u8"삭제"))
		{
			deleting = true;
		}
	}
	else
	{
		for (UINT x = 0; x < mapObj.size(); x++)
		{
			for (UINT y = 0; y < mapObj[x].size(); y++)
			{
				Vector2 pos = HTMAP->GetPosition(x, y);
				Vector2 size = Vector2(100.0f, 100.0f) / 2;
				Vector2 mPos = mouse->GetPosition();
				CAMERA->WCToVC(mPos);

				if (mPos.x > pos.x - size.x && mPos.x < pos.x + size.x &&
					mPos.y > pos.y - size.y && mPos.y < pos.y + size.y)
				{
					if (drag)
					{
						if (mouse->Press(0))
						{
							mapObj[x][y] = pow(2, combo);
							HTMAP->ReSetValue(x, y);

							if (!deleting)
							{
								string name = "";

								switch (combo)
								{
								case 0:
									HTMAP->SetValue(x, y, (HelltakerMap::State)combo, nullptr);
									break;
								case 1:
									HTMAP->AssignHelltaker(x, y, stageHp);
									break;
								case 2:
									name = "Box" + to_string(boxes.size());
									HTMAP->AssignBox(name, x, y);
									boxes.push_back(name);
									break;
								case 3:
								case 4:
								case 5:
								case 6:
								case 7:
								case 8:
								}

								
							}
						}
					}
					else if (mouse->Down(0))
					{
						mapObj[x][y] = pow(2, combo);
						HTMAP->ReSetValue(x, y);
						
						if (!deleting)
							HTMAP->SetValue(x, y, (HelltakerMap::State)mapObj[x][y], nullptr);
					}

					wstring str = to_wstring(x) + L" , " + to_wstring(y);
					mPos.x -= str.length() * 10.0f + 20.0f;
					mPos.y -= 40.0f;
					CAMERA->VCToWC(mPos);

					DirectWrite::RenderText(str, mPos, 0, 255, 255, 20.0f);
				}
			}
		}
	}

	ImGui::Checkbox(u8"드래그로 추가", &drag);
	{
		//inserting = true;
	}
}

void HS19_MapEditor::GUISaveMap()
{
	if (ImGui::Button(u8"저장"))
	{

	}

	if (ImGui::Button(u8"불러오기"))
	{

	}
}
