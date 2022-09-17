#include "framework.h"
#include "HS19_MapEditor.h"
#include "HelltakerMap.h"
#include "Helltaker.h"

HS19_MapEditor::HS19_MapEditor()
{
	wstring imageFile1 = L"./Images/MapEditor/TempExample.png";
	wstring imageFile2 = L"./Images/Background/Chapter01.png";

	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	tempTexture = new Texture(imageFile1, shaderFile);

	mapBG = new Texture(imageFile2, shaderFile);

	sceneName = "HS19_MapEditor";

	SetDisplay(true);
	SetActive(false);
}

HS19_MapEditor::~HS19_MapEditor()
{
	SAFE_DELETE(background);
	SAFE_DELETE(tempTexture);
	SAFE_DELETE(mapBG);

	for (UINT i = 0; i < 100; i++)
	{
		SAFE_DELETE(mapTile[i]);
		SAFE_DELETE(obj[i]);
	}
}

void HS19_MapEditor::Update()
{
	CAMERA->Update();

	Matrix V = VM;
	Matrix P = PM;

	HTMAP->SetSize(size[0], size[1]);
	HTMAP->SetOffset(offset);

	mapBG->Update(V, P);

	visibleMap = true;

	if (inserting)
	{
		if (mouse->Down(0))
			inserting = false;

		Vector2 pos = mouse->GetPosition();
		CAMERA->WCToVC(pos);

		tempTexture->SetPosition(pos);
		tempTexture->Update(V, P);
	}
}

void HS19_MapEditor::Render()
{
	mapBG->Render();

	if (inserting)
	{
		tempTexture->Render();
	}

	if (1)
		ShowGUI();
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
		}
		ImGui::EndTabBar();
	}
	ImGui::End();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void HS19_MapEditor::GUISetMap()
{
	static int stageHp = 0;
	static int mapSize[2] = { 0, 0 };
	static Vector2 mapOffset = offset;

	if (ImGui::InputInt(u8"스테이지 체력", &stageHp))
	{
		Helltaker* ht = (Helltaker*)OBJMANAGER->FindObject("Helltaker");
		ht->SetHP(stageHp);
	}

	if (ImGui::InputInt2(u8"맵 크기", mapSize))
	{
		size[0] = mapSize[0];
		size[1] = mapSize[1];
	}

	if (ImGui::InputFloat2(u8"맵 오프셋", mapOffset, "%.0f"))
	{
		offset = mapOffset;
	}
}

void HS19_MapEditor::GUIAddObj()
{
	if (!inserting)
	{
		if (ImGui::Button(u8"추가"))
		{
			inserting = true;
		}
	}
	else
	{
		if (ImGui::Button(u8"취소"))
		{
			inserting = true;
		}
	}

}
