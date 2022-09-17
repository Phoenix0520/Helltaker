#include "framework.h"
#include "OptionMenu.h"
#include "OptionButton.h"
#include "Helltaker.h"
#include "HS01_IntroScene.h"
#include "CheckBox.h"

OptionMenu::OptionMenu()
{
	wstring imageFile1 = L"./Images/OptionMenu/BackGround.png";
	wstring imageFile2 = L"./Images/OptionMenu/Border.png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	background = new Texture(imageFile1, shaderFile);
	background->UpdateColorBuffer(Color(0, 0, 0, 0.9f), 7, 0, 0, 0);
	background->SetPosition(0.0f, 0.0f);
	background->SetScale(MAIN->GetWidth(), MAIN->GetHeight());

	border = new Texture(imageFile2, shaderFile);
	border->SetPosition(0.0f, 5.0f);

	checkBox = new CheckBox();
	checkBox->SetPosition(275.0f, 390.0f);
	checkBox->SetScale(0.4f, 0.4f);

	button[0] = new OptionButton();
	button[0]->SetPosition(0.0f, 305.0f);
	button[0]->SetHover(true);

	button[1] = new OptionButton();
	button[1]->SetPosition(0.0f, 220.0f);

	button[2] = new OptionButton();
	button[2]->SetPosition(0.0f, 135.0f);
	button[2]->SetLevel(OptionButton::Level::LOW);

	button[3] = new OptionButton();
	button[3]->SetPosition(0.0f, 15.0f);
	button[3]->SetLevel(OptionButton::Level::LOW);

	button[4] = new OptionButton();
	button[4]->SetPosition(0.0f, -115.0f);

	EnumerateAdapterOutputResolution();

	vector<wstring> temp;
	temp.push_back(L"전체 화면");
	temp.push_back(L"전체 화면 창모드");
	temp.push_back(L"창모드");
	button[0]->SetComboScript(temp);
	temp.clear();

	for (UINT i = 0; i < resList.size(); i++)
	{
		wstring val = to_wstring(resList[i].first) + L" X " + to_wstring(resList[i].second);
		temp.push_back(val);
	}
	button[1]->SetComboScript(temp);

	button[1]->SetComboHover(1);
}

OptionMenu::~OptionMenu()
{
	SAFE_DELETE(background);
}

void OptionMenu::Update(Matrix V, Matrix P)
{
	CAMERA->SetObject(nullptr);
	CAMERA->SetPosition(0.0f, 0.0f);

	Vector2 camPos = Vector2(0.0f, 0.0f);
	if (SCENEMANAGER->GetScene("HS14_Chapter08") == SCENEMANAGER->GetCurScene())
	{
		Helltaker* ht = (Helltaker*)OBJMANAGER->FindObject("Helltaker");
		camPos = ht->GetPosition();
	}

	background->SetPosition(0.0f, camPos.y);
	border->SetPosition(0.0f, camPos.y + 5.0f);
	background->Update(V, P);
	border->Update(V, P);

	checkBox->SetPosition(275.0f, camPos.y + 390.0f);
	checkBox->Update(V, P);

	if (DOWN(VK_ESCAPE))
	{
		for (int i = 0; i < 5; i++)
		{
			button[i]->SetHover(false);
			button[i]->SetClick(false);
			button[i]->SetCombo(false);
		}

		button[0]->SetComboHover(comboTemp1);
		button[1]->SetComboHover(comboTemp2);

		button[0]->SetHover(true);

		windowSetting = false;
		checkBox->SetHover(false);
		checkBox->SetCheck(false);


		SCENEMANAGER->Pause();
	}

	if (checkBox->GetHover())
	{
		if (DOWN(VK_DOWN) || DOWN('S'))
		{
			checkBox->SetHover(false);
			button[0]->SetHover(true);
		}

		if (DOWN(VK_SPACE) || DOWN(VK_RETURN))
		{
			if (!checkBox->GetCheck())
			{
				windowSetting = true;
				checkBox->SetCheck(true);
			}
			else
			{
				windowSetting = false;
				button[0]->SetCombo(false);
				button[1]->SetCombo(false);
				checkBox->SetCheck(false);
			}
		}
	}

	if (windowSetting)
	{
		WinSetUpdate();
		return;
	}

	button[1]->SetDisable(false);

	button[0]->SetScript(L"게임 재개");
	button[1]->SetScript(L"퍼즐 건너뛰기");
	button[2]->SetScript(L"음악");
	button[3]->SetScript(L"효과음");
	button[4]->SetScript(L"메인 화면으로");

	button[0]->SetPosition(0.0f, camPos.y + 305.0f);
	button[1]->SetPosition(0.0f, camPos.y + 220.0f);
	button[2]->SetPosition(0.0f, camPos.y + 135.0f);
	button[3]->SetPosition(0.0f, camPos.y + 15.0f);
	button[4]->SetPosition(0.0f, camPos.y - 115.0f);

	if (button[0]->GetHover())
	{
		if (DOWN(VK_UP) || DOWN('W'))
		{
			checkBox->SetHover(true);
			button[0]->SetHover(false);
		}
		if (DOWN(VK_DOWN) || DOWN('S'))
		{
			button[0]->SetHover(false);
			button[1]->SetHover(true);
		}

		if (DOWN(VK_SPACE) || DOWN(VK_RETURN))
		{
			SCENEMANAGER->Pause();
		}
	}
	if (button[1]->GetHover())
	{
		if (DOWN(VK_UP) || DOWN('W'))
		{
			button[0]->SetHover(true);
			button[1]->SetHover(false);
		}
		if (DOWN(VK_DOWN) || DOWN('S'))
		{
			button[1]->SetHover(false);
			button[2]->SetHover(true);
		}

		if (DOWN(VK_SPACE) || DOWN(VK_RETURN))
		{
			SCENEMANAGER->Pause();
			SCENEMANAGER->ChangeScene("HS05_Dialogue");
			Helltaker* ht = (Helltaker*)OBJMANAGER->FindObject("Helltaker");
			ht->SetGoal(true);
			button[1]->SetHover(false);
			button[0]->SetHover(true);
		}
	}
	if (button[2]->GetHover())
	{
		if (DOWN(VK_UP) || DOWN('W'))
		{
			button[1]->SetHover(true);
			button[2]->SetHover(false);
		}

		if (DOWN(VK_DOWN) || DOWN('S'))
		{
			button[2]->SetHover(false);
			button[3]->SetHover(true);
		}

		if (DOWN(VK_LEFT) || DOWN('A'))
		{
			if (button[2]->GetLevel() == 0)
				button[2]->SetLevel(3);
			else
				button[2]->SetLevel(button[2]->GetLevel() - 1);
		}

		if (DOWN(VK_RIGHT) || DOWN('D'))
		{
			if (button[2]->GetLevel() == 3)
				button[2]->SetLevel(0);
			else
				button[2]->SetLevel(button[2]->GetLevel() + 1);
		}

		bgmSize = button[2]->GetLevel() * 0.15f;

		VOLUME("MAINBGM", bgmSize);
		VOLUME("INTRO", bgmSize);
	}
	if (button[3]->GetHover())
	{
		if (DOWN(VK_UP) || DOWN('W'))
		{
			button[2]->SetHover(true);
			button[3]->SetHover(false);
		}
		if (DOWN(VK_DOWN) || DOWN('S'))
		{
			button[3]->SetHover(false);
			button[4]->SetHover(true);
		}

		if (DOWN(VK_LEFT) || DOWN('A'))
		{
			if (button[3]->GetLevel() == 0)
				button[3]->SetLevel(3);
			else
				button[3]->SetLevel(button[3]->GetLevel() - 1);
		}

		if (DOWN(VK_RIGHT) || DOWN('D'))
		{
			if (button[3]->GetLevel() == 3)
				button[3]->SetLevel(0);
			else
				button[3]->SetLevel(button[3]->GetLevel() + 1);
		}

		sfxSize = button[3]->GetLevel() * 0.15f;
	}
	if (button[4]->GetHover())
	{
		if (DOWN(VK_UP) || DOWN('W'))
		{
			button[3]->SetHover(true);
			button[4]->SetHover(false);
		}

		if (DOWN(VK_SPACE) || DOWN(VK_RETURN))
		{
			SCENEMANAGER->Pause();
			SCENEMANAGER->ChangeScene("HS01_IntroScene");
			HS01_IntroScene* scene = (HS01_IntroScene*)SCENEMANAGER->GetScene("HS01_IntroScene");
			scene->SetClick(2);
			button[4]->SetHover(false);
			button[0]->SetHover(true);
			STOPSOUND("MAINBGM");
		}
	}

	for (int i = 0; i < 5; i++)
		button[i]->Update(V, P);
}

void OptionMenu::Render()
{
	background->Render();
	border->Render();
	checkBox->Render();

	DirectWrite::GetDC()->BeginDraw();
	{
		DirectWrite::ChangeTextType
		(
			L"맑은 고딕",
			DWRITE_FONT_WEIGHT_SEMI_BOLD,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL
		);

		wstring str = L"• 일시정지 메뉴 •";

		float y = 0.0f;

		if (SCENEMANAGER->GetScene("HS14_Chapter08") == SCENEMANAGER->GetCurScene())
		{
			Helltaker* ht = (Helltaker*)OBJMANAGER->FindObject("Helltaker");
			y = ht->GetPosition().y;
		}

		Vector2 pos = Vector2(0.0f, y + 430.0f);
		pos.x -= str.length() * 20.0f;
		CAMERA->VCToWC(pos);

		DirectWrite::RenderText(str, pos, 230, 77, 81, 40.0f);

		str = L"화면 설정";
		pos = Vector2(275.0f, y + 465.0f);
		pos.x -= str.length() * 12.5f;
		CAMERA->VCToWC(pos);

		DirectWrite::RenderText(str, pos, 230, 77, 81, 25.0f);


		DirectWrite::ChangeTextType
		(
			L"맑은 고딕",
			DWRITE_FONT_WEIGHT_MEDIUM,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL
		);
	}
	DirectWrite::GetDC()->EndDraw();


	if (windowSetting)
	{
		WinSetRender();
		return;
	}

	for (int i = 0; i < 5; i++)
		button[i]->Render();

}

void OptionMenu::Reset()
{
}

void OptionMenu::WinSetUpdate()
{
	button[0]->SetCombo(true);
	button[1]->SetCombo(true);

	if (type == FULLSCREEN)
		button[1]->SetDisable(true);
	else
		button[1]->SetDisable(false);

	button[0]->SetScript(L"창 스타일 변경");
	button[1]->SetScript(L"창 해상도 변경");

	Vector2 camPos = CAMERA->GetPosition();
	button[0]->SetPosition(0.0f, camPos.y + 305.0f);
	button[1]->SetPosition(0.0f, camPos.y + 185.0f);

	if (button[0]->GetHover())
	{
		if (button[0]->GetClick())
		{
			if (DOWN(VK_SPACE) || DOWN(VK_RETURN))
			{
				type = (WinType)button[0]->GetComboHover();

				UINT index = button[1]->GetComboHover();

				switch (type)
				{
				case FULLSCREEN:
					MAIN->SetWindowSize(0, 0);
					break;
				case WINDOWEDFULLSCREEN:
					MAIN->SetWindowSize(resList[index].first, resList[index].second, true);
					break;
				case WINDOWED:
					MAIN->SetWindowSize(resList[index].first, resList[index].second);
					break;
				}

				comboTemp1 = type;
				button[0]->SetClick(false);
			}
		}
		else
		{
			if (DOWN(VK_UP) || DOWN('W'))
			{
				checkBox->SetHover(true);
				button[0]->SetHover(false);
			}
			else if (DOWN(VK_DOWN) || DOWN('S'))
			{
				if (!button[1]->GetDisable())
				{
					button[0]->SetHover(false);
					button[1]->SetHover(true);
				}
			}

			if (DOWN(VK_SPACE) || DOWN(VK_RETURN))
			{
				comboTemp1 = button[0]->GetComboHover();

				button[0]->SetClick(true);
			}
		}
	}
	if (button[1]->GetHover())
	{
		if (button[1]->GetClick())
		{
			if (DOWN(VK_SPACE) || DOWN(VK_RETURN))
			{
				UINT index = button[1]->GetComboHover();

				switch (type)
				{
				case FULLSCREEN:
					CAMERA->ChangeXY(resList[index].first, resList[index].second);
					break;
				case WINDOWEDFULLSCREEN:
					MAIN->SetWindowSize(resList[index].first, resList[index].second, true);
					break;
				case WINDOWED:
					if (index == 0)
					{
						MAIN->SetWindowSize(resList[1].first, resList[1].second);
						break;
					}

					MAIN->SetWindowSize(resList[index].first, resList[index].second);
					break;
				}

				comboTemp2 = index;
				button[1]->SetClick(false);
			}
		}
		else
		{
			if (DOWN(VK_UP) || DOWN('W'))
			{
				button[0]->SetHover(true);
				button[1]->SetHover(false);
			}

			if (DOWN(VK_SPACE) || DOWN(VK_RETURN))
			{
				comboTemp2 = button[1]->GetComboHover();
				button[1]->SetClick(true);
			}
		}
	}

	for (int i = 0; i < 2; i++)
		button[i]->Update(VM, PM);
}

void OptionMenu::WinSetRender()
{

	button[1]->Render();
	button[0]->Render();
}

void OptionMenu::EnumerateAdapterOutputResolution()
{
	IDXGIFactory1* factory; // Display Adapter 의 정보를 전부 들고있다.

	if (FAILED(CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&factory)))
		return;

	UINT index = 0;

	IDXGIAdapter1* adapter;

	HRESULT hr = factory->EnumAdapters1(index, &adapter);
	Check(hr);

	SAFE_RELEASE(factory);

	IDXGIOutput* output = nullptr;

	hr = adapter->EnumOutputs(0, &output);
	Check(hr);

	SAFE_RELEASE(adapter);

	UINT numModes = 0;
	DXGI_MODE_DESC* displayModes = nullptr;
	DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;

	hr = output->GetDisplayModeList(format, DXGI_ENUM_MODES_INTERLACED, &numModes, nullptr);
	// progressive intelaced 를 포함하여 가져온다
	Check(hr);

	displayModes = new DXGI_MODE_DESC[numModes];

	hr = output->GetDisplayModeList(format, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModes);
	// progressive intelaced 를 포함하여 가져온다
	Check(hr);

	for (UINT i = numModes - 1; i > 0; i--)
	{
		resList.push_back(make_pair(displayModes[i].Width, displayModes[i].Height));
	}

	resList.erase(unique(resList.begin(), resList.end()), resList.end());

	SAFE_DELETE_ARRAY(displayModes);
	SAFE_RELEASE(output);
}
