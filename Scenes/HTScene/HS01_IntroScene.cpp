#include "framework.h"
#include "HS01_IntroScene.h"
#include "Button.h"
#include "Booper.h"
#include "ChapterButton.h"

HS01_IntroScene::HS01_IntroScene()
{
	wstring imgFile1	= L"./Images/abyss.png";
	wstring imgFile2	= L"./Images/fly.png";
	wstring shaderFile	= L"./Shader/HLSL/TextureColor.hlsl";
	
	// Background
	{
		for (int i = 0; i < 3; i++)
			background[i] = new Texture(imgFile1, shaderFile);

		Vector2 size = background[0]->GetTextureRealSize();
		background[1]->SetPosition(-size.x + 2.0f, 100.0f);

		size = background[0]->GetTextureRealSize();
		background[2]->SetPosition((-size.x + 2.0f) * 2.0f , 100.0f);
	}

	// Beelfly
	{
		beelFly = new Texture(imgFile2, shaderFile);
		beelFly->SetScale(0.9875f, 0.9875f);
		beelFly->SetPosition(0.0f, 165.0f);
	}

	// button
	{
		button1 = new Button();
		button1->SetScale(0.925f, 0.925f);
		button1->SetButtonString(L"새 게임");

		button2 = new Button();
		button2->SetScale(0.925f, 0.925f);
		button2->SetButtonString(L"챕터 선택");

		button3 = new Button();
		button3->SetScale(0.925f, 0.925f);
		button3->SetButtonString(L"나가기");
	}

	// Loading Animation
	{
		wstring imageFile1 = L"./Images/LoadingImage.png";

		loadingAnim = new Texture(imageFile1, shaderFile);
		loadingAnim->SetPosition(840.0f, -435.0f);
		loadingAnim->SetScale(0.3f, 0.3f);
		loadingAnim->UpdateColorBuffer(Color(1.0f, 0.3f, 0.31f, 1.0f), 4, 0, 0, 0);
	}

	// Chapter Select Scene
	{
		wstring imageFile2 = L"./Images/ChapterSelect/Border.png";
		
		border = new Texture(imageFile2, shaderFile);
		border->SetPosition(0.0f, (float)-MAIN->GetHeight() / 2);

		for (UINT i = 0; i <= 10; i++)
		{
			button[i] = new ChapterButton(i);
		}
	}

	sceneName = "HS01_IntroScene";
	SetNextScene("HS02_Prologue");
	
	//SetDisplay(true);
	//SetActive(false);
}

HS01_IntroScene::~HS01_IntroScene()
{
	SAFE_DELETE(booper);
	SAFE_DELETE(button3);
	SAFE_DELETE(button2);
	SAFE_DELETE(button1);
	SAFE_DELETE(beelFly);
	SAFE_DELETE(background[1]);
	SAFE_DELETE(background[0]);
}

void HS01_IntroScene::Update()
{
	CAMERA->Update();

	Matrix V = CAMERA->GetViewMatrix();
	Matrix P = CAMERA->GetProjMatrix();

	// booper
	{
		if (booper == nullptr)
			booper = (Booper*)OBJMANAGER->FindObject("Booper");
	}
	
	if (loading)
	{
		static float rot = 0.0f;
	
		rot -= 60.0f * DELTA;
		loadingAnim->SetRotation(0.0f, 0.0f, rot);
		loadingAnim->Update(V, P);
		return;
	}

	if (!ISPLAYING("INTRO"))
	{
		PLAYSOUND("INTRO", bgmSize);
	}

	// BackGroundEffect
	{
		time += DELTA * 0.5f;

		Vector2 size = background[0]->GetTextureRealSize();
		Vector2 origin = background[0]->GetPosition();
		CAMERA->VCToWC(origin);

		float min = origin.y - time * 1500;
		float max = origin.y + time * 1500;

		Color changeColor = Color(0.0f, 0.0f, 0.0f, 1.0f);

		background[0]->UpdateColorBuffer(changeColor, 3, 0.5f - time, min, max);

		size = background[1]->GetTextureRealSize();
		origin = background[1]->GetPosition();
		CAMERA->VCToWC(origin);

		min = origin.y - time * 1500;
		max = origin.y + time * 1500;

		background[1]->UpdateColorBuffer(changeColor, 3, 0.5f - time, min, max);

		size = background[2]->GetTextureRealSize();
		origin = background[2]->GetPosition();
		CAMERA->VCToWC(origin);

		min = origin.y - time * 1500;
		max = origin.y + time * 1500;

		background[2]->UpdateColorBuffer(changeColor, 3, 0.5f - time, min, max);
	}

	// 무한배경
	if (click != 5)
	{
		background[0]->SetPosition(background[0]->GetPosition().x + 1.0f, 100.0f);
		background[1]->SetPosition(background[1]->GetPosition().x + 1.0f, 100.0f);
		background[2]->SetPosition(background[2]->GetPosition().x + 1.0f, 100.0f);

		Vector2 pos = background[0]->GetPosition();
		Vector2 size = background[0]->GetTextureRealSize();

		if (pos.x >= size.x)
		{
			background[0]->SetPosition(background[1]->GetPosition().x - (size.x / 2) - 2.0f, 100.0f);
		}

		pos = background[1]->GetPosition();
		size = background[1]->GetTextureRealSize();

		if (pos.x >= size.x)
		{
			background[1]->SetPosition(background[2]->GetPosition().x - (size.x / 2) - 2.0f, 100.0f);
		}

		pos = background[2]->GetPosition();
		size = background[2]->GetTextureRealSize();

		if (pos.x >= size.x)
		{
			background[2]->SetPosition(background[0]->GetPosition().x - (size.x / 2) - 2.0f, 100.0f);
		}
		
		for (int i = 0; i < 3; i++)
			background[i]->Update(V, P);
		
		beelFly->Update(V, P);
	}

	if (timer >= 0.0f)
		timer -= DELTA;
	
	if (chapter)
	{
		if (DOWN(VK_ESCAPE))
		{
			click--;

			border->SetPosition(0.0f, (float)-MAIN->GetHeight() / 2);
			button1->SetPosition(0.0f, (float)-MAIN->GetHeight() / 2);
			button2->SetPosition(0.0f, (float)-MAIN->GetHeight() / 2 - 75.0f);
			button3->SetPosition(0.0f, (float)-MAIN->GetHeight() / 2 - 150.0f);
			
			button1->SetHover(true);
			button2->SetHover(false);
			button3->SetHover(false);

			for (int i = 0; i <= 10; i++)
				button[i]->SetHover(false);

			chapter = false;
		}

		UpdateChapterSelect(V, P);
		return;
	}

	if (DOWN(VK_SPACE) || DOWN(VK_RETURN))
	{
		enter = true;
		click++;
	}

	if (click == 2)
	{
		if (buttonPos < -320.0f)
		{
			buttonPos += 0.0166f * 1000.0f;

			if (buttonPos > -319.9833f)
			{
				button1->SetHover(true);

				for (UINT i = 0; i < 10; i++)
					button[i]->SetHover(false);
			}
		}
		else
			buttonPos = -320.0f;

		button1->SetPosition(0.0f, buttonPos);
		button2->SetPosition(0.0f, buttonPos - 80.0f);
		button3->SetPosition(0.0f, buttonPos - 160.0f);

		if (button1->GetHover())
		{
			if (DOWN('W') || DOWN(VK_UP))
			{
				button3->SetHover(true);
				button1->SetHover(false);
			}
			else if (DOWN('S') || DOWN(VK_DOWN))
			{
				button2->SetHover(true);
				button1->SetHover(false);
			}
		}
		else if (button2->GetHover())
		{
			if (DOWN('W') || DOWN(VK_UP))
			{
				button1->SetHover(true);
				button2->SetHover(false);
			}
			else if (DOWN('S') || DOWN(VK_DOWN))
			{
				button3->SetHover(true);
				button2->SetHover(false);
			}
		}
		else if (button3->GetHover())
		{
			if (DOWN('W') || DOWN(VK_UP))
			{
				button2->SetHover(true);
				button3->SetHover(false);
			}
			else if (DOWN('S') || DOWN(VK_DOWN))
			{
				button1->SetHover(true);
				button3->SetHover(false);
			}
		}

		button1->Update(V, P);
		button2->Update(V, P);
		button3->Update(V, P);
	}
	else
	{
		if (booper)
		{
			booper->SetPosition(0.0f, -425.0f);
			booper->SetActive(true);
			booper->Update(V, P);
		}
	}


	// 시간 경과후 Scene 변경
	if (enter && click == 3)
	{
		if (button1->GetHover())
			return;
		if (button2->GetHover())
		{
			button[1]->SetHover(true);
			chapter = true;
		}
		if (button3->GetHover())
			PostQuitMessage(0);
	}
	
	if (click == 6)
	{
		SCENEMANAGER->ChangeScene(nextSceneName);
	}
}

void HS01_IntroScene::Render()
{
	if (loading)
	{
		DirectWrite::GetDC()->BeginDraw();
		{
			loadingAnim->Render();
	
			DirectWrite::ChangeTextType
			(
				L"맑은고딕체",
				DWRITE_FONT_WEIGHT_SEMI_BOLD,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_CONDENSED
			);
	
			wstring str = L"";
	
			switch (loadLevel)
			{
			case 1:
				str = L"스테이지 생성중 (" + to_wstring(loadVal) + L" / 19)";
				break;
			case 2:
				str = L"오브젝트 생성중 (" + to_wstring(loadVal) + L" / 83)";
				break;
			case 3:
				str = L"음원 등록중 (" + to_wstring(loadVal) + L" / 27)";
				break;
			}
	
			Vector2 pos = Vector2(560.0f, -399.0f);
			pos.x -= str.length() * 20.0f;
			CAMERA->VCToWC(pos);
	
			DirectWrite::RenderText(str, pos, 255, 77, 81, 40.0f);
	
			DirectWrite::ChangeTextType
			(
				L"맑은고딕체",
				DWRITE_FONT_WEIGHT_MEDIUM,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_CONDENSED
			);
	
			DirectWrite::GetDC()->EndDraw();
			return;
		}
	}

	if (click != 5)
	{
		for (int i = 0; i < 3; i++)
			background[i]->Render();

		if (enter)
			beelFly->Render();
	}

	if (chapter)
	{
		RenderChapterSelect();

		return;
	}

	DirectWrite::GetDC()->BeginDraw();
	{
		if (!enter)
		{
			DirectWrite::ChangeTextType
			(
				L"맑은고딕체",
				DWRITE_FONT_WEIGHT_MEDIUM,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_CONDENSED
			);

			wstring str = L"당신은 당신이 공허에 휩싸인것을 느꼈다.";
			float x = -(str.length() * 35.0f * 0.5f - 950.0f);
			Vector2 pos = Vector2(x, 790.0f);
			DirectWrite::RenderText(str, pos, 255, 255, 255, 35.0f);


			str = L"계속하려면 [Enter] 를 누르시오.";
			x = -(str.length() * 35.0f * 0.5f - 950.0f);
			pos = Vector2(x, 845.0f);
			DirectWrite::RenderText(str, pos, 255, 255, 255, 35.0f);

			DirectWrite::ChangeTextType
			(
				L"맑은고딕체",
				DWRITE_FONT_WEIGHT_MEDIUM,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_CONDENSED
			);

			if (booper)
				booper->Render();
		}

		if (enter)
		{
			wstring script;

			float x;
			Vector2 pos;

			switch (click)
			{
			case 1:
				script = L"• 위대한 파리 베엘제붑 •";

				x = -(script.length() * 40.0f * 0.5f);
				pos = Vector2(x, -187.5f);
				CAMERA->VCToWC(pos);

				DirectWrite::ChangeTextType
				(
					L"맑은고딕체",
					DWRITE_FONT_WEIGHT_BOLD,
					DWRITE_FONT_STYLE_NORMAL,
					DWRITE_FONT_STRETCH_CONDENSED
				);

				DirectWrite::RenderText(script, pos, 255, 77, 81, 40.0f);

				DirectWrite::ChangeTextType
				(
					L"맑은고딕체",
					DWRITE_FONT_WEIGHT_MEDIUM,
					DWRITE_FONT_STYLE_NORMAL,
					DWRITE_FONT_STRETCH_CONDENSED
				);

				script = L"반갑네 인간이여, 나를 괘념치말게.";

				x = -(script.length() * 40.0f * 0.5f - 950.0f);
				pos = Vector2(x, 790.0f);

				DirectWrite::RenderText(script, pos, 255, 255, 255, 40.0f);

				script = L"그저 당신의 오랜친구 베엘제붑일세.";
				x = -(script.length() * 40.0f * 0.5f - 950.0f);

				pos = Vector2(x, 845.0f);

				DirectWrite::RenderText(script, pos, 255, 255, 255, 40.0f);

				booper->Render();

				break;
			case 2:
				script = L"• 위대한 파리 베엘제붑 •";

				x = -(script.length() * 40.0f * 0.5f);
				pos = Vector2(x, -187.5f);
				CAMERA->VCToWC(pos);

				DirectWrite::ChangeTextType
				(
					L"맑은고딕체",
					DWRITE_FONT_WEIGHT_BOLD,
					DWRITE_FONT_STYLE_NORMAL,
					DWRITE_FONT_STRETCH_CONDENSED
				);


				DirectWrite::RenderText(script, pos, 255, 77, 81, 40.0f);

				DirectWrite::ChangeTextType
				(
					L"맑은고딕체",
					DWRITE_FONT_WEIGHT_MEDIUM,
					DWRITE_FONT_STYLE_NORMAL,
					DWRITE_FONT_STRETCH_CONDENSED
				);
				break;
			case 3:
				script = L"• 위대한 파리 베엘제붑 •";

				x = -(script.length() * 40.0f * 0.5f);
				pos = Vector2(x, -187.5f);
				CAMERA->VCToWC(pos);

				DirectWrite::ChangeTextType
				(
					L"맑은고딕체",
					DWRITE_FONT_WEIGHT_BOLD,
					DWRITE_FONT_STYLE_NORMAL,
					DWRITE_FONT_STRETCH_CONDENSED
				);

				DirectWrite::RenderText(script, pos, 255, 77, 81, 40.0f);

				DirectWrite::ChangeTextType
				(
					L"맑은고딕체",
					DWRITE_FONT_WEIGHT_MEDIUM,
					DWRITE_FONT_STYLE_NORMAL,
					DWRITE_FONT_STRETCH_CONDENSED
				);

				script = L"또 헬테이커의 이야기를 들려달라고? 재미있군...";

				x = -(script.length() * 40.0f * 0.5f - 950.0f);
				pos = Vector2(x, 790.0f);

				DirectWrite::RenderText(script, pos, 255, 255, 255, 40.0f);

				booper->Render();

				break;

			case 4:
				script = L"• 위대한 파리 베엘제붑 •";

				x = -(script.length() * 40.0f * 0.5f);
				pos = Vector2(x, -187.5f);
				CAMERA->VCToWC(pos);

				DirectWrite::ChangeTextType
				(
					L"맑은고딕체",
					DWRITE_FONT_WEIGHT_BOLD,
					DWRITE_FONT_STYLE_NORMAL,
					DWRITE_FONT_STRETCH_CONDENSED
				);


				DirectWrite::RenderText(script, pos, 255, 77, 81, 40.0f);

				DirectWrite::ChangeTextType
				(
					L"맑은고딕체",
					DWRITE_FONT_WEIGHT_MEDIUM,
					DWRITE_FONT_STYLE_NORMAL,
					DWRITE_FONT_STRETCH_CONDENSED
				);

				script = L"혹시 해설자가 필요하진 않은가?";

				x = -(script.length() * 40.0f * 0.5f - 950.0f);
				pos = Vector2(x, 790.0f);

				DirectWrite::RenderText(script, pos, 255, 255, 255, 40.0f);

				booper->Render();

				break;

			case 5:
				script = L"허락해준다면 참 고맙겠어.";

				x = -(script.length() * 40.0f * 0.5f - 950.0f);
				pos = Vector2(x, 790.0f);

				DirectWrite::RenderText(script, pos, 255, 255, 255, 40.0f);

				booper->Render();

				break;
			}
		}
	}
	DirectWrite::GetDC()->EndDraw();

	if (enter && click == 2)
	{
		button1->Render();
		button2->Render();
		button3->Render();
	}
}

void HS01_IntroScene::UpdateChapterSelect(Matrix V, Matrix P)
{
	Vector2 pos = border->GetPosition();

	if (pos.y < -325.0f)
		pos.y += 0.0166f * 1000.0f;
	else
		pos.y = -325.0f;

	border->SetPosition(pos);
	border->Update(V, P);

	for (UINT i = 0; i <= 10; i++)
	{
		if (i == 0)
		{
			button[0]->SetPosition(675.0f, pos.y);
			button[0]->Update(V, P);

			if (button[0]->GetHover())
			{
				if (DOWN(VK_LEFT) || DOWN('A'))
				{
					button[10]->SetHover(true);
					button[0]->SetHover(false);
				}
				else if (DOWN(VK_RIGHT) || DOWN('D'))
				{
					button[1]->SetHover(true);
					button[0]->SetHover(false);
				}
			}
			
			continue;
		}
		
		float x = -660.0f;

		button[i]->SetPosition(x + (i * 120.0f), pos.y);
		button[i]->Update(V, P);

		if (button[i]->GetHover())
		{
			if (i == 1)
			{
				if (DOWN(VK_LEFT) || DOWN('A'))
				{
					button[0]->SetHover(true);
					button[1]->SetHover(false);
				}
			}
			else if (i == 10)
			{
				if (DOWN(VK_RIGHT) || DOWN('D'))
				{
					button[0]->SetHover(true);
					button[10]->SetHover(false);
				}
			}

			if (button[i - 1])
			{
				if (DOWN(VK_LEFT) || DOWN('A'))
				{
					button[i - 1]->SetHover(true);
					button[i]->SetHover(false);
				}
			}
			if (button[i + 1])
			{
				if (DOWN(VK_RIGHT) || DOWN('D'))
				{
					button[i + 1]->SetHover(true);
					button[i]->SetHover(false);
				}
			}
		}
	}
}

void HS01_IntroScene::RenderChapterSelect()
{
	DirectWrite::GetDC()->BeginDraw();
	{
		border->Render();

		for (UINT i = 0; i <= 10; i++)
		{
			button[i]->Render();

			if (button[i]->GetHover())
			{
				float y = border->GetPosition().y;
				Vector2 pos = Vector2(0.0f, y - 75.0f);
				wstring str = L"";

				DirectWrite::ChangeTextType
				(
					L"Amiri",
					DWRITE_FONT_WEIGHT_MEDIUM,
					DWRITE_FONT_STYLE_NORMAL,
					DWRITE_FONT_STRETCH_CONDENSED
				);

				switch (i)
				{
				case 0:
					str = L"Map Edit Mode";
					break;
				case 1:
					str = L"Chapter I - 피곤한 악마";
					break;
				case 2:
					str = L"Chapter II - 음란한 악마";
					break;
				case 3:
					str = L"Chapter III - 세 쌍둥이 악마";
					break;
				case 4:
					str = L"Chapter IV - 시큰둥한 악마";
					break;
				case 5:
					str = L"Chapter V - 상스러운 악마";
					break;
				case 6:
					str = L"Chapter VI - 호기심 많은 천사";
					break;
				case 7:
					str = L"Chapter VII - 끝내주는 악마";
					break;
				case 8:
					str = L"Chapter VIII - 지옥의 CEO";
					break;
				case 9:
					str = L"Chapter IX - 저지먼트";
					break;
				case 10:
					str = L"Chapter X - 에필로그";
					break;
				}

				pos.x -= str.length() * 17.5f;
				CAMERA->VCToWC(pos);

				if (i == 0)
					DirectWrite::RenderText(str, pos, 255, 77, 81, 35.0f);
				else
					DirectWrite::RenderText(str, pos, 255, 255, 255, 35.0f);
			}
		}
	}
	DirectWrite::GetDC()->EndDraw();
}

void HS01_IntroScene::ChangeScene()
{
	SetActive(true);
	enter = false;
	chapter = false;

	border->SetPosition(0.0f, (float)-MAIN->GetHeight() / 2);
	button1->SetPosition(0.0f, (float)-MAIN->GetHeight() / 2);
	button2->SetPosition(0.0f, (float)-MAIN->GetHeight() / 2 - 75.0f);
	button3->SetPosition(0.0f, (float)-MAIN->GetHeight() / 2 - 150.0f);

	click = 0;
	button1->SetHover(true);
	button2->SetHover(false);
	button3->SetHover(false);
	
	//time = 0.0f;
	timer = 3.0f;
}
