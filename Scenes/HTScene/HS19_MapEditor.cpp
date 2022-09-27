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

	for (UINT i = 1; i <= 10; i++)
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

	if (HTMAP->GetSizeX() != 0 && HTMAP->GetSizeY() != 0)
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

	if (HTMAP->GetSizeX() != 0 && HTMAP->GetSizeY() != 0)
		OBJMANAGER->RenderAll();
}

void HS19_MapEditor::ChangeScene()
{
	SetActive(true);
	ShowCursor(true);
	HTMAP->Clear();
	OBJMANAGER->ClearObjectStrings();
	HTMAP->SetSize(0, 0);
	HTMAP->SetOffset(0.0f, 0.0f);
}

void HS19_MapEditor::ResetAnotherValue(UINT state)
{
	for (UINT x = 0; x < mapObj.size(); x++)
	{
		for (UINT y = 0; y < mapObj[x].size(); y++)
		{
			UINT index = mapObj[x][y];
			if (index == 2 || index == 3)
			{
				mapObj[x][y] -= state;
				HTMAP->ReSetValue(x, y, (HelltakerMap::State)state);
			}
		}
	}
	HTMAP->ReSetAnotherValue((HelltakerMap::State)state);
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

void HS19_MapEditor::ReadCSVFile(string file)
{
	CSVReader* reader = new CSVReader();
	reader->OpenFile(file);

	data.clear();

	for (UINT x = 0; x < 10; x++)
	{
		vector<int> datas;
		data.push_back(datas);
		for (UINT y = 0; y < 10; y++)
		{
			wstring val = L"";
			reader->GetData(x, y, val);

			string str = "";
			str.assign(val.begin(), val.end());
			char* type = new char();
			float value = 0.0f;
			value = strtof(str.c_str(), &type);
			
			data[x].push_back((int)value);
		}
	}

	SAFE_DELETE(reader);
}

void HS19_MapEditor::WriteCSVFile(string file)
{
	FILE* fp = fopen(file.c_str(), "wt");

	for (UINT y = 0; y < data.size(); y++)
	{
		for (UINT x = 0; x < data[y].size(); x++)
		{
			string str = to_string(data[y][x]);
			const char* chr = str.c_str();
			cout << chr << " ";
			fputs(chr, fp);
			
			if (x != data[y].size() - 1)
				fputc(',', fp);
		}

		cout << endl;
		fputs("\n", fp);
	}

	fclose(fp);
}

void HS19_MapEditor::GUISetMap()
{
	static const char* scenes[] =
	{ u8"챕터 1", u8"챕터 2", u8"챕터 3", u8"챕터 4", u8"챕터 5", u8"챕터 6", u8"챕터 7", u8"챕터 8", u8"챕터 9" };

	int oldCptr = chapter;

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

		if (chapter != oldCptr)
		{
			HTMAP->Clear();
			OBJMANAGER->ClearObjectStrings();
			mapObj.clear();
			mapObjX.clear();
			mapObjY.clear();

			boxes.clear();
			mobs.clear();
			traps.clear();
			goals.clear();

			mapSize[0] = 0;
			mapSize[1] = 0;
			toggleTrap = 0;
			stageHp = 0;
			offset = Vector2(0.0f, 0.0f);
		}
	}

	if (ImGui::InputInt(u8"스테이지 체력", &stageHp))
	{
		Helltaker* ht = (Helltaker*)OBJMANAGER->FindObject("Helltaker");
		ht->SetHP(stageHp);
	}

	if (ImGui::InputInt2(u8"맵 크기", mapSize))
	{
		OBJMANAGER->ClearObjectStrings();
		HTMAP->Clear();

		init = false;

		mapObj.resize((UINT)mapSize[0]);
		for (UINT i = 0; i < mapObj.size(); i++)
			mapObj[i].resize(mapSize[1]);

		mapObjX.resize((UINT)mapSize[0]);
		mapObjY.resize((UINT)mapSize[1]);

		HTMAP->SetSize(mapObjX.size(), mapObjY.size());
	}

	if (ImGui::InputFloat2(u8"맵 오프셋", offset, "%.1f"))
	{
		HTMAP->SetOffset(offset);
	}

	if (ImGui::Checkbox(u8"토글 트랩", &toggleTrap))
	{
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
							mapObj[x][y] += pow(2, combo);

							if (!deleting)
								HTMAP->SetValue(x, y, HelltakerMap::State::move, nullptr);
							else
								HTMAP->ReSetValue(x, y);
						}
					}
					else if (mouse->Down(0))
					{
						mapObj[x][y] += pow(2, combo);

						cout << mapObj[x][y] << endl;
						
						if (!deleting)
						{
							string name = "";

							switch (combo)
							{
							case 0:
								HTMAP->SetValue(x, y, HTMAPSTATE::move, nullptr);
								break;
							case 1:
								HTMAP->ReSetAnotherValue(HTMAPSTATE::helltaker);
								HTMAP->AssignHelltaker(x, y, stageHp);
								break;
							case 2:
								name = "Box" + to_string(boxes.size() + 1);
								HTMAP->AssignBox(name, x, y);
								boxes.push_back(name);
								break;
							case 3:
								name = "Mob" + to_string(mobs.size() + 1);
								HTMAP->AssignMob(name, x, y);
								mobs.push_back(name);
								break;
							case 4:
								name = "Trap" + to_string(traps.size() + 1);
								HTMAP->AssignTrap(name, x, y);
								traps.push_back(name);
								break;
							case 5:
								name = "Goal" + to_string(chapter + goals.size() + 1);
								HTMAP->AssignGoal(name, x, y);
								goals.push_back(name);
								break;
							case 6:
								name = "Key";
								HTMAP->AssignKey(name, x, y);
								break;
							case 7:
								name = "LockBox";
								HTMAP->AssignLockBox(name, x, y);
								break;
							case 8:
								name = "Slate";
								HTMAP->AssignBox(name, x, y);
								break;
							}

							OBJMANAGER->DeleteOverlapedObjectString();
						}
						else
						{
							string name = HTMAP->GetName(x, y);
							OBJMANAGER->DeleteObjectString(name);
							HTMAP->ReSetValue(x, y);
							HTMAP->SetValue(x, y, HTMAPSTATE::move, nullptr);
						}
					}

					wstring str = to_wstring(x) + L" , " + to_wstring(y);
					mPos.x -= str.length() * 10.0f - 40.0f;
					mPos.y -= 40.0f;
					CAMERA->VCToWC(mPos);

					DirectWrite::RenderText(str, mPos, 0, 255, 255, 20.0f);
				}
			}
		}
	}

	if (combo == 0)
	{
		ImGui::Checkbox(u8"드래그로 추가 / 제거", &drag);
		{
			//inserting = true;
		}
	}
	else
		drag = false;
}

void HS19_MapEditor::GUISaveMap()
{
	ImGui::Text(u8"현재 챕터 : ");
	ImGui::SameLine();
	ImGui::Text(to_string(chapter + 1).c_str());

	if (ImGui::Button(u8"현재 챕터 저장"))
	{
		data.clear();

		data.resize(mapSize[1] + 1);
		for (UINT i = 0; i < mapSize[1] + 1; i++)
			data[i].resize(mapSize[0]);

		data[0][0] = chapter + 1;
		data[0][1] = mapSize[0];
		data[0][2] = mapSize[1];
		data[0][3] = offset.x;
		data[0][4] = offset.y;
		data[0][5] = toggleTrap;
		data[0][6] = stageHp;

		for (UINT y = 1; y < mapSize[1] + 1; y++)
		{
			for (UINT x = 0; x < mapSize[0]; x++)
			{
				data[y][x] = HTMAP->GetValue(x, y - 1);
				cout << data[y][x] << " ";
			}
			cout << endl;
		}

		WriteCSVFile("./Maps/Map0" + to_string(chapter + 1) + ".csv");

		file = 2;
	}
	if (ImGui::Button(u8"챕터 불러오기"))
	{
		ReadCSVFile("./Maps/Map0" + to_string(chapter + 1) + ".csv");

		if ((int)data[0][0] != chapter + 1)
		{
			cout << "오류!" << endl;
			file = -1;
			return;
		}
		
		file = 1;

		HTMAP->Clear();
		OBJMANAGER->ClearObjectStrings();
		init = false;

		int sx = data[0][1];
		int sy = data[0][2];

		mapSize[0] = sx;
		mapObj.resize(sx);
		cout << "SizeX : " << sx;

		mapSize[1] = sy;
		for (UINT i = 0; i < sx; i++)
			mapObj[i].resize(sy);
		cout << " SizeY : " << sy << endl;

		HTMAP->SetSize(sx, sy);

		offset = Vector2((float)data[0][3], (float)data[0][4]);

		HTMAP->SetOffset(offset);

		cout << "Map Offset : " << offset.x << " , " << offset.y << endl;

		toggleTrap = data[0][5];

		cout << "Toggle Trap : " << toggleTrap << endl;

		stageHp = data[0][6];
		Helltaker* ht = (Helltaker*)OBJMANAGER->FindObject("Helltaker");
		ht->SetHP(stageHp);

		cout << "State HP : " << stageHp << endl;

		boxes.clear();
		mobs.clear();
		traps.clear();
		goals.clear();

		for (UINT y = 1; y < data.size(); y++)
		{
			for (UINT x = 0; x < data[y].size(); x++)
			{
				int value = (int)data[y][x];
				y--;
				cout << x << y << " : " << value << " ";

				if (value > 0)
				{
					HTMAP->ReSetValue(x, y);
					HTMAP->SetValue(x, y, HelltakerMap::State::move, nullptr);

					string name = "";

					switch ((HTMAPSTATE)value)
					{
					case 1:
						break;
					case 3:
						HTMAP->AssignHelltaker(x, y, stageHp);
						break;
					case 5:
						name = "Box" + to_string(boxes.size() + 1);
						HTMAP->AssignBox(name, x, y);
						boxes.push_back(name);
						break;											
					case 9:
						name = "Mob" + to_string(mobs.size() + 1);
						HTMAP->AssignMob(name, x, y);
						mobs.push_back(name);
						break;
					case 17:
						name = "Trap" + to_string(traps.size() + 1);
						HTMAP->AssignTrap(name, x, y);
						traps.push_back(name);
						break;
					case 33:
						name = "Goal" + to_string(chapter + goals.size() + 1);
						HTMAP->AssignGoal(name, x, y);
						goals.push_back(name);
						break;
					case 65:
						name = "Key";
						HTMAP->AssignKey(name, x, y);
						break;
					case 129:
						name = "LockBox";
						HTMAP->AssignLockBox(name, x, y);
						HTMAP->AssignBox(name, x, y);
						break;
					}
				}
				y++;
			}
			cout << endl;
		}
	}

	if (file == 1)
	{
		ImGui::Text(u8"파일");
		ImGui::SameLine();
		ImGui::Text(("./Maps/Map0" + to_string(chapter + 1) + ".csv").c_str());
		ImGui::SameLine();
		ImGui::Text(u8"불러오기 성공!");
	}
	else if (file == 2)
	{
		ImGui::Text(u8"파일");
		ImGui::SameLine();
		ImGui::Text(("./Maps/Map0" + to_string(chapter + 1) + ".csv").c_str());
		ImGui::SameLine();
		ImGui::Text(u8"저장 성공!");
	}
	else if (file == -1)
	{
		ImGui::Text(u8"파일");
		ImGui::SameLine();
		ImGui::Text(("./Maps/Map0" + to_string(chapter + 1) + ".csv").c_str());
		ImGui::SameLine();
		ImGui::Text(u8"불러오기 실패!");
	}
}
