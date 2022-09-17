#include "framework.h"
#include "SceneList.h"
#include "Helltaker.h"
#include "HelltakerMap.h"
#include "Button.h"
#include "Booper.h"
#include "Mob.h"
#include "Box.h"
#include "Trap.h"
#include "Slate.h"
#include "LockBox.h"
#include "Key.h"
#include "Goal.h"
#include "Fire.h"

HS05_Dialogue::HS05_Dialogue()
{
	wstring imageFile1 = L"./Images/background/background (7).png";

	wstring imageFile2 = L"./Images/Dialogue/Pandemonica/IDLE.png";
	wstring imageFile3 = L"./Images/Dialogue/Pandemonica/Flust.png";
	wstring imageFile4 = L"./Images/Success/Success (1).png";

	wstring imageFile5 = L"./Images/background/background (1).png";

	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	// 화면이 어두웠다가 밝아지면서 나온다

	// background[0]
	{
		background[0] = new Texture(imageFile1, shaderFile);
		Vector2 position = background[0]->GetPosition();
		background[0]->SetPosition(position.x, position.y + 100.0f);
		background[0]->SetScale(0.995f, 0.995f);	
	}

	// background[1]
	{
		background[1] = new Texture(imageFile5, shaderFile);
		Vector2 position = background[1]->GetPosition();
		background[1]->SetPosition(position.x, position.y + 100.0f);
		background[1]->SetScale(0.995f, 0.995f);
	}
	
	// Pand 포즈
	{
		texture[0] = new Texture(imageFile2, shaderFile);
		texture[0]->SetPosition(0.0f, 162.0f);
		texture[0]->SetScale(0.995f, 0.995f);
		texture[1] = new Texture(imageFile3, shaderFile);
		texture[1]->SetPosition(0.0f, 162.0f);
		texture[1]->SetScale(0.995f, 0.995f);
	}

	imageFile2 = L"./Images/Dialogue/Modeus/IDLE.png";
	imageFile3 = L"./Images/Dialogue/Modeus/Close.png";

	// Mod 포즈
	{
		texture[2] = new Texture(imageFile2, shaderFile);
		texture[2]->SetPosition(0.0f, 162.0f);
		texture[2]->SetScale(0.995f, 0.995f);

		texture[3] = new Texture(imageFile3, shaderFile);
		texture[3]->SetPosition(0.0f, 162.0f);
		texture[3]->SetScale(0.995f, 0.995f);
	}

	imageFile2 = L"./Images/Dialogue/Cerberus/IDLE.png";
	imageFile3 = L"./Images/Dialogue/Cerberus/Happy.png";

	// Cerb 포즈
	{
		texture[4] = new Texture(imageFile2, shaderFile);
		texture[4]->SetPosition(0.0f, 162.0f);
		texture[4]->SetScale(0.995f, 0.995f);

		texture[5] = new Texture(imageFile3, shaderFile);
		texture[5]->SetPosition(0.0f, 162.0f);
		texture[5]->SetScale(0.995f, 0.995f);
	}

	imageFile2 = L"./Images/Dialogue/Malina/IDLE.png";
	imageFile3 = L"./Images/Dialogue/Malina/SUCCESS.png";

	// Mal 포즈
	{
		texture[6] = new Texture(imageFile2, shaderFile);
		texture[6]->SetPosition(0.0f, 162.0f);
		texture[6]->SetScale(0.995f, 0.995f);

		texture[7] = new Texture(imageFile3, shaderFile);
		texture[7]->SetPosition(0.0f, 162.0f);
		texture[7]->SetScale(0.995f, 0.995f);
	}

	imageFile2 = L"./Images/Dialogue/Zdrada/IDLE.png";
	imageFile3 = L"./Images/Dialogue/Zdrada/Laugh.png";

	// Zdra 포즈
	{
		texture[8] = new Texture(imageFile2, shaderFile);
		texture[8]->SetPosition(0.0f, 162.0f);
		texture[8]->SetScale(0.995f, 0.995f);

		texture[9] = new Texture(imageFile3, shaderFile);
		texture[9]->SetPosition(0.0f, 162.0f);
		texture[9]->SetScale(0.995f, 0.995f);
	}

	imageFile2 = L"./Images/Dialogue/Azazel/IDLE.png";
	imageFile3 = L"./Images/Dialogue/Azazel/Success.png";

	// Az 포즈
	{
		texture[10] = new Texture(imageFile2, shaderFile);
		texture[10]->SetPosition(0.0f, 162.0f);
		texture[10]->SetScale(0.995f, 0.995f);

		texture[11] = new Texture(imageFile3, shaderFile);
		texture[11]->SetPosition(0.0f, 162.0f);
		texture[11]->SetScale(0.995f, 0.995f);
	}

	imageFile2 = L"./Images/Dialogue/Justis/IDLE.png";
	imageFile3 = L"./Images/Dialogue/Justis/Success.png";

	// Just 포즈
	{
		texture[12] = new Texture(imageFile2, shaderFile);
		texture[12]->SetPosition(0.0f, 162.0f);
		texture[12]->SetScale(0.995f, 0.995f);

		texture[13] = new Texture(imageFile3, shaderFile);
		texture[13]->SetPosition(0.0f, 162.0f);
		texture[13]->SetScale(0.995f, 0.995f);
	}

	imageFile2 = L"./Images/Dialogue/Lucifer/Skull.png";
	imageFile3 = L"./Images/Dialogue/Lucifer/Shake (5).png";

	// Luci
	{
		texture[14] = new Texture(imageFile2, shaderFile);
		texture[14]->SetPosition(0.0f, 162.0f);
		texture[14]->SetScale(0.995f, 0.995f);
		
		texture[15] = new Texture(imageFile2, shaderFile);
		texture[15]->SetPosition(0.0f, 162.0f);
		texture[15]->SetScale(0.995f, 0.995f);
		
		texture[16] = new Texture(imageFile3, shaderFile);
		texture[16]->SetPosition(0.0f, 162.0f);
		texture[16]->SetScale(0.995f, 0.995f);

		imageFile3 = L"./Images/Dialogue/Lucifer/Angry.png";

		texture[17] = new Texture(imageFile3, shaderFile);
		texture[17]->SetPosition(0.0f, 162.0f);
		texture[17]->SetScale(0.995f, 0.995f);
		
		imageFile3 = L"./Images/Dialogue/Lucifer/Success.png";

		texture[18] = new Texture(imageFile3, shaderFile);
		texture[18]->SetPosition(0.0f, 162.0f);
		texture[18]->SetScale(0.995f, 0.995f);

		imageFile3 = L"./Images/Dialogue/Lucifer/Shake (1).png";

		lucifer = new Animation(imageFile3, shaderFile);
		lucifer->SetPosition(0.0f, 162.0f);
		lucifer->SetScale(0.995f, 0.995f);

		AnimationClip* clip = new AnimationClip(AnimationClip::State::end);
		lucifer->AddClip(clip);

		for (int i = 1; i <= 10; i++)
		{
			wstring str = L"";

			if (i > 5)
				str = L"./Images/Dialogue/Lucifer/Shake (" + to_wstring(i - 5) + L").png";
			else
				str = L"./Images/Dialogue/Lucifer/Shake (" + to_wstring(i) + L").png";

			float delta = 0.175f;
			if (i == 1)
				delta = 0.825f;

			if (i == 10)
				delta = 0.825f;

			clip->AddFrame(lucifer->GetTexture(), str, 0.0f, 0.0f, 536.0f, 748.0f, delta);
		}

		for (int j = 1; j <= 4; j++)
		{
			wstring str = L"./Images/Dialogue/Lucifer/Smile (" + to_wstring(j) + L").png";

			float delta = 0.15f;
			if (j == 1 || j == 4)
				delta = 0.825f;

			clip->AddFrame(lucifer->GetTexture(), str, 0.0f, 0.0f, 536.0f, 748.0f, delta);
		}

		wstring str = L"./Images/Dialogue/Lucifer/IDLE.png";

		clip->AddFrame(lucifer->GetTexture(), str, 0.0f, 0.0f, 536.0f, 748.0f, 2.0f);
	}

	// Button1 생성
	{
		button1 = new Button();
		//button1->SetCallBack(bind(&HS05_Dialogue::OnButtonWrong, this, placeholders::_1));
		Vector2 position = button1->GetPosition();
		button1->SetPosition(position.x, position.y - 386.0f);
		button1->SetScale(0.925f, 0.925f);
		button1->SetHover(true);
	}
	// Button2 생성
	{
		button2 = new Button();
		//button2->SetCallBack(bind(&HS05_Dialogue::OnButtonSuccess, this, placeholders::_1));
		Vector2 position = button2->GetPosition();
		button2->SetPosition(position.x, position.y - 468.5f);
		button2->SetScale(0.925f, 0.925f);
		button2->SetHover(false);
	}

	// success 문구
	{
		successMotion = new Animation(imageFile4, shaderFile);
		// animationClip
		AnimationClip* clip = new AnimationClip(AnimationClip::State::end);
		{
			successMotion->AddClip(clip);
			for (int i = 1; i <= 8; i++)
			{
				wstring str = L"./Images/Success/Success (" + to_wstring(i) + L").png";
				
				clip->AddFrame(successMotion->GetTexture(), str, 0.0f, 0.0f, 1100.0f, 225.0f, 0.05f);
			}
		}
		successMotion->SetScale(1.0f, 1.0f);
		successMotion->SetPosition(0.0f, -445.0f);
	}

	// Booper
	{
		booper = (Booper*)OBJMANAGER->FindObject("Booper");
	}
	
	SetActive(false);
	sceneName = "HS05_Dialogue";
}

HS05_Dialogue::~HS05_Dialogue()
{
	for (int i = 0; i < 20; i++)
	{
		if (texture[i])
			SAFE_DELETE(texture[i]);
	}
	SAFE_DELETE(button1);
	SAFE_DELETE(button2);
	SAFE_DELETE(background[0]);
}

void HS05_Dialogue::Update()
{
	if (sceneID == 7)
	{
		UpdateEX();
		return;
	}
	else if (sceneID == 8)
	{
		UpdateEX2();
		return;
	}

	CAMERA->Update();

	Matrix V, P;
	V = CAMERA->GetViewMatrix();
	P = CAMERA->GetProjMatrix();

	if (!enter) // PreUpdate
	{
		time += DELTA;

		// Background 설정
		{
			Vector2 size = background[0]->GetTextureRealSize();
			Vector2 origin = background[0]->GetPosition();
			CAMERA->VCToWC(origin);

			float min = origin.y - time * 1500;
			float max = origin.y + time * 1500;

			Color changeColor = Color(0.0f, 0.0f, 0.0f, 1.0f);

			background[0]->UpdateColorBuffer(changeColor, 3, 0.75f - time, min, max);
			background[0]->Update(V, P);
		}
		// Texture 설정
		{
			Vector2 pos = texture[sceneID * 2]->GetPosition();

			if (time > 0.75f)
				time = 0.75f;

			if (pos.x > 0.0f)
				pos.x -= 1500.0f * DELTA;
			else
				pos.x = 0.0f;

			texture[sceneID * 2]->SetPosition(pos.x, pos.y);
			texture[sceneID * 2]->Update(V, P);
		}

		booper->SetActive(true);
		booper->Update(V, P);

		// Button Reset
		{
			button1->Reset();
			button2->Reset();
		}

		// Enter / Space 시 버튼 선택 시작
		if ((DOWN(VK_RETURN) || DOWN(VK_SPACE)) && time >= 0.5f)
		{
			enter = true;
			time = 0.0f;
		}
	}
	else
	{
		// 클릭 하기 전에 버튼의 상태 업데이트
		if (!click)
		{
			if (button1->GetHover())
			{
				if (DOWN('W') || DOWN(VK_UP) || DOWN('S') || DOWN(VK_DOWN))
				{
					button1->SetHover(false);
					button2->SetHover(true);
				}
			}
			else if (button2->GetHover())
			{
				if (DOWN('W') || DOWN(VK_UP) || DOWN('S') || DOWN(VK_DOWN))
				{
					button1->SetHover(true);
					button2->SetHover(false);
				}
			}
		}

		// 올바른 길로가는 버튼의 위치
		switch (successRoute)
		{
		case 0:	// false, 0 아래 버튼이 맞는 길
			if (button1->IsClick())
			{
				click = true;
				badRoute = true;
			}
			else if (button2->IsClick())
			{
				click = true;
				success = true;
			}
			break;

		default: // true , !0 위 버튼이 맞는길
			if (button1->IsClick())
			{
				click = true;
				success = true;
			}
			else if (button2->IsClick())
			{
				click = true;
				badRoute = true;
			}
			break;
		}

		// 선택에 따른 결과
		if (success)
		{
			texture[sceneID * 2 + 1]->Update(V, P);

			if (!soundPlay)
			{
				PLAYSOUND("DSUCCESS", sfxSize);
				soundPlay = true;
			}
			successMotion->Update(V, P);

			time += DELTA;

			if ((DOWN(VK_RETURN) || DOWN(VK_SPACE)) && time >= 0.5f)
			{
				Scene* scene = nullptr;

				switch (sceneID)
				{
				case 0:
					scene = (HS04_Chapter01*)SCENEMANAGER->GetScene("HS04_Chapter01");
					scene->SetReset(false);
					SCENEMANAGER->ChangeScene("HS04_Chapter01");
					break;
				case 1:
					scene = (HS06_Chapter02*)SCENEMANAGER->GetScene("HS06_Chapter02");
					scene->SetReset(false);
					SCENEMANAGER->ChangeScene("HS06_Chapter02");
					break;
				case 2:
					scene = (HS07_Chapter03*)SCENEMANAGER->GetScene("HS07_Chapter03");
					scene->SetReset(false);
					SCENEMANAGER->ChangeScene("HS07_Chapter03");
					break;
				case 3:
					scene = (HS08_Chapter04*)SCENEMANAGER->GetScene("HS08_Chapter04");
					scene->SetReset(false);
					SCENEMANAGER->ChangeScene("HS08_Chapter04");
					break;
				case 4:
					scene = (HS10_Chapter05*)SCENEMANAGER->GetScene("HS10_Chapter05");
					scene->SetReset(false);
					SCENEMANAGER->ChangeScene("HS10_Chapter05");
					break;
				case 5:
					scene = (HS11_Chapter06*)SCENEMANAGER->GetScene("HS11_Chapter06");
					scene->SetReset(false);
					SCENEMANAGER->ChangeScene("HS11_Chapter06");
					break;
				case 6:
					scene = (HS13_Chapter07*)SCENEMANAGER->GetScene("HS13_Chapter07");
					scene->SetReset(false);
					SCENEMANAGER->ChangeScene("HS13_Chapter07");
					break;
				}

				Helltaker* ht = (Helltaker*)OBJMANAGER->FindObject("Helltaker");
				ht->SetGoal(true);
			}
		}
		else if (badRoute)
		{
			time += DELTA;
			
			if (sceneID == 6)
			{
				if (!soundPlay)
				{
					PLAYSOUND("DSUCCESS", sfxSize);
					soundPlay = true;
				}
				texture[sceneID * 2 + 1]->Update(V, P);
				successMotion->Update(V, P);
			}
			else
			{
				HS00_DeadScene* scene = (HS00_DeadScene*)SCENEMANAGER->GetScene("HS00_DeadScene");
				scene->SetScript(script3[0], 0);
				scene->SetScript(script3[1], 1);

				booper->Update(V, P);
				texture[sceneID * 2]->Update(V, P);
			}
			
			if ((DOWN(VK_RETURN) || DOWN(VK_SPACE)) && time >= 0.5f)
			{
				if (sceneID == 5)
				{
					SCENEMANAGER->ChangeScene("HS12_HeavenScene");
					return;
				}
				else if (sceneID == 6)
				{
					Scene* scene = (HS13_Chapter07*)SCENEMANAGER->GetScene("HS13_Chapter07");
					scene->SetReset(false);

					Helltaker* ht = (Helltaker*)OBJMANAGER->FindObject("Helltaker");
					ht->SetGoal(true);

					SCENEMANAGER->ChangeScene("HS13_Chapter07");
					return;
				}

				SCENEMANAGER->ChangeScene("HS00_DeadScene");
			}
		}
		else
		{
			texture[sceneID * 2]->Update(V, P);
			button1->Update(V, P);
			button2->Update(V, P);
		}
	}	
}

void HS05_Dialogue::Render()
{
	if (sceneID == 7)
	{
		RenderEX();
		return;
	}
	else if (sceneID == 8)
	{
		RenderEX2();
		return;
	}

	if (!enter)
	{
		booper->Render();
	}
	else if (badRoute)
	{
		if (sceneID != 6)
			booper->Render();
	}

	background[0]->Render();

	if (success)
	{
		texture[sceneID * 2 + 1]->Render();
		successMotion->Render();
	}
	else if (badRoute)
	{
		if (sceneID == 6)
		{
			texture[sceneID * 2 + 1]->Render();
			successMotion->Render();
		}
		else 
			texture[sceneID * 2]->Render();
	}
	else if (!enter)
	{
		texture[sceneID * 2]->Render();
		booper->Render();
	}
	else if (click)
	{
		texture[sceneID * 2]->Render();
	}
	else
	{
		texture[sceneID * 2]->Render();
		button1->Render();
		button2->Render();
	}

	DirectWrite::GetDC()->BeginDraw();
	{
		float x = -(banner.length() * 40.0f * 0.5f);
		float y = -205.0f;
		Vector2 pos = Vector2(x, y + 10.0f);
		CAMERA->VCToWC(pos);

		DirectWrite::ChangeTextType
		(
			L"맑은고딕체",
			DWRITE_FONT_WEIGHT_BOLD,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_CONDENSED
		);

		DirectWrite::RenderText(banner, pos, 230, 77, 81, 40.0f);

		DirectWrite::ChangeTextType
		(
			L"맑은고딕체",
			DWRITE_FONT_WEIGHT_MEDIUM,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_CONDENSED
		);

		if (success)
		{
			strbutton1 = script1[0];
			x = -(strbutton1.length() * 30.0f * 0.5f);
			pos = Vector2(x, y - 42.5f);
			CAMERA->VCToWC(pos);
			DirectWrite::RenderText(strbutton1, pos, 255, 255, 255, 30.0f);

			strbutton2 = script2[0];
			x = -(strbutton2.length() * 30.0f * 0.5f);
			pos = Vector2(x, y - 77.5f);
			CAMERA->VCToWC(pos);
			DirectWrite::RenderText(strbutton2, pos, 255, 255, 255, 30.0f);
		}
		else if (badRoute)
		{
			strbutton1 = script1[1];
			x = -(strbutton1.length() * 30.0f * 0.5f);
			pos = Vector2(x, y - 42.5f);
			CAMERA->VCToWC(pos);
			DirectWrite::RenderText(strbutton1, pos, 255, 255, 255, 30.0f);

			strbutton2 = script2[1];
			x = -(strbutton2.length() * 30.0f * 0.5f);
			pos = Vector2(x, y - 77.5f);
			CAMERA->VCToWC(pos);
			DirectWrite::RenderText(strbutton2, pos, 255, 255, 255, 30.0f);
		}
		else
		{
			strbutton1 = script1[2];
			x = -(strbutton1.length() * 30.0f * 0.5f);
			pos = Vector2(x, y - 42.5f);
			CAMERA->VCToWC(pos);
			DirectWrite::RenderText(strbutton1, pos, 255, 255, 255, 30.0f);

			strbutton2 = script2[2];
			x = -(strbutton2.length() * 30.0f * 0.5f);
			pos = Vector2(x, y - 77.5f);
			CAMERA->VCToWC(pos);
			DirectWrite::RenderText(strbutton2, pos, 255, 255, 255, 30.0f);
		}
	}
	DirectWrite::GetDC()->EndDraw();
}

void HS05_Dialogue::UpdateEX()
{
	CAMERA->Update();

	Matrix V, P;
	V = CAMERA->GetViewMatrix();
	P = CAMERA->GetProjMatrix();

	if (!(step >= 2 && step <= 5) && timer <= 0.0f && (DOWN(VK_SPACE) || DOWN(VK_RETURN)))
	{
		step++;
	}

	switch (step)
	{
	case 0:
	{
		time += DELTA;

		if (time >= 0.75f)
			time = 0.75f;

		// Background 설정
		{
			Vector2 size = background[1]->GetTextureRealSize();
			Vector2 origin = background[1]->GetPosition();
			CAMERA->VCToWC(origin);

			float min = origin.y - time * 1500;
			float max = origin.y + time * 1500;

			Color changeColor = Color(0.0f, 0.0f, 0.0f, 1.0f);

			background[1]->UpdateColorBuffer(changeColor, 3, 0.75f - time, min, max);
			background[1]->Update(V, P);
		}
		// Texture 설정
		{
			if (timer >= 0.0f)
				timer -= DELTA;
			else
				timer = 0.0f;

			if (timer <= 2.05f)
			{
				Vector2 pos = texture[14]->GetPosition();

				if (pos.x > -400.0f)
					pos.x -= 1500.0f * DELTA;
				else
					pos.x = -400.0f;

				texture[14]->SetPosition(pos);
				texture[14]->Update(V, P);

				if (timer <= 1.75f)
				{
					Vector2 pos2 = texture[15]->GetPosition();

					if (pos2.x > 400.0f)
						pos2.x -= 1500.0f * DELTA;
					else
						pos2.x = 400.0f;

					texture[15]->SetPosition(pos2);
					texture[15]->Update(V, P);
				}
			}
			else
			{
				Vector2 pos = texture[16]->GetPosition();

				if (pos.x > 0.0f)
					pos.x -= 1500.0f * DELTA;

				else
					pos.x = 0.0f;

				texture[16]->SetPosition(pos);
				texture[16]->Update(V, P);
			}

			lucifer->Update(V, P);
		}

		if (timer <= 0.0f)
			booper->Update(V, P);

		break;
	}
	case 1:
	{
		background[1]->Update(V, P);
		texture[14]->Update(V, P);
		texture[15]->Update(V, P);
		lucifer->Update(V, P);
		booper->Update(V, P);

		button1->Reset();
		button2->Reset();
		
		click = false;
		successRoute = false;

		break;
	}
	case 2:
	{
		button1->Update(V, P);
		button2->Update(V, P);

		if (!click)
		{
			if (button1->GetHover())
			{
				if (DOWN('W') || DOWN(VK_UP) || DOWN('S') || DOWN(VK_DOWN))
				{
					button1->SetHover(false);
					button2->SetHover(true);
				}
			}
			else if (button2->GetHover())
			{
				if (DOWN('W') || DOWN(VK_UP) || DOWN('S') || DOWN(VK_DOWN))
				{
					button1->SetHover(true);
					button2->SetHover(false);
				}
			}
		}

		if (button1->IsClick())
		{
			click = true;
			badRoute = true;
			step++;
		}
		else if (button2->IsClick())
		{
			click = true;
			success = true;
			step++;
		}
		
		
		background[1]->Update(V, P);

		texture[14]->Update(V, P);
		texture[15]->Update(V, P);
		lucifer->Update(V, P);

		break;
	}
	case 3:
	{
		background[1]->Update(V, P);
		texture[14]->Update(V, P);
		texture[15]->Update(V, P);
		booper->Update(V, P);

		if (success)
		{
			texture[17]->Update(V, P);
		
			if (DOWN(VK_SPACE) || DOWN(VK_RETURN))
			{
				step++;
				success = false;
				badRoute = false;
				click = false;

				button1->Reset();
				button2->Reset();

				button1->SetButtonString(L"주인님이라고 불러라. 그리고 말을 꺼내기 전에 허락을 구해라.");
				button2->SetButtonString(L"커피, 턴제 전략 게임과, 초콜릿 팬케이크를 제공할 수 있지.");
			}
		}
		else if (badRoute)
		{
			lucifer->Update(V, P);

			if (DOWN(VK_RETURN) || DOWN(VK_SPACE))
			{
				HS00_DeadScene* scene = (HS00_DeadScene*)SCENEMANAGER->GetScene("HS00_DeadScene");
				scene->SetScript(script3[0], 0);
				scene->SetScript(script3[1], 1);

				SCENEMANAGER->ChangeScene("HS00_DeadScene");
			}
		}
	}
	break;

	case 4:
	{
		background[1]->Update(V, P);
		texture[14]->Update(V, P);
		texture[15]->Update(V, P);
		texture[17]->Update(V, P);

		button1->Update(V, P);
		button2->Update(V, P);

		if (!click)
		{
			if (button1->GetHover())
			{
				if (DOWN('W') || DOWN(VK_UP) || DOWN('S') || DOWN(VK_DOWN))
				{
					button1->SetHover(false);
					button2->SetHover(true);
				}
			}
			else if (button2->GetHover())
			{
				if (DOWN('W') || DOWN(VK_UP) || DOWN('S') || DOWN(VK_DOWN))
				{
					button1->SetHover(true);
					button2->SetHover(false);
				}
			}
		}

		if (button1->IsClick())
		{
			click = true;
			badRoute = true;
			step++;
		}
		else if (button2->IsClick())
		{
			click = true;
			success = true;
			step++;
		}

		booper->Update(V, P);
	}

	case 5:
	{
		background[1]->Update(V, P);
		
		texture[14]->Update(V, P);
		texture[15]->Update(V, P);
		texture[17]->Update(V, P);

		if (success)
		{
			PLAYSOUND("DSUCCESS", sfxSize);

			if (DOWN(VK_RETURN) || DOWN(VK_SPACE))
			{
				step++;
				texture[18]->Update(V, P);
				click = false;
			}
		}
		else if (badRoute)
		{
			if (DOWN(VK_RETURN) || DOWN(VK_SPACE))
			{
				HS00_DeadScene* scene = (HS00_DeadScene*)SCENEMANAGER->GetScene("HS00_DeadScene");

				scene->SetScript(script3[2], 0);
				scene->SetScript(script3[3], 1);

				SCENEMANAGER->ChangeScene("HS00_DeadScene");
			}
		}
		
		booper->Update(V, P);

		break;
	}
	case 6:
	{
		background[1]->Update(V, P);

		texture[14]->Update(V, P);
		texture[15]->Update(V, P);
		texture[18]->Update(V, P);

		successMotion->Update(V, P);

		time = 0.0f;

		break;
	}
	case 7:
	{
		Scene* scene = (HS14_Chapter08*)SCENEMANAGER->GetScene("HS14_Chapter08");
		scene->SetReset(false);
		SCENEMANAGER->ChangeScene("HS14_Chapter08");

		Helltaker* ht = (Helltaker*)OBJMANAGER->FindObject("Helltaker");
		ht->SetGoal(true);

		break;
	}

	default:
		break;
	}
}

void HS05_Dialogue::RenderEX()
{
	background[1]->Render();

	switch (step)
	{
	case 0:
		if (timer <= 1.75f)
		{
			texture[14]->Render();
			texture[15]->Render();
			lucifer->Render();
		}
		else if (timer <= 2.05f)
		{
			texture[14]->Render();
			lucifer->Render();
		}
		else if (timer <= 4.0f)
		{
			lucifer->Render();
		}
		else
			texture[16]->Render();

		if (timer <= 0.0f)
			booper->Render();
		break;
	case 1:
		texture[14]->Render();
		texture[15]->Render();
		lucifer->Render();
		booper->Render();
		break;

	case 2:
		texture[14]->Render();
		texture[15]->Render();
		lucifer->Render();

		button1->Render();
		button2->Render();
		break;

	case 3:
		if (success)
		{
			texture[14]->Render();
			texture[15]->Render();
			texture[17]->Render();
		}
		else if (badRoute)
		{
			texture[14]->Render();
			texture[15]->Render();
			lucifer->Render();
		}

		booper->Render();

		break;
	case 4:
		texture[14]->Render();
		texture[15]->Render();
		texture[17]->Render();

		button1->Render();
		button2->Render();
		break;

	case 5:
		texture[14]->Render();
		texture[15]->Render();
		texture[17]->Render();

		booper->Render();
		break;

	case 6:
		texture[14]->Render();
		texture[15]->Render();
		texture[18]->Render();
		successMotion->Render();
		break;
	}

	if (timer <= 0.0f)
	{
		DirectWrite::GetDC()->BeginDraw();
		{
			float x = -(banner.length() * 40.0f * 0.5f);
			float y = -205.0f;
			Vector2 pos = Vector2(x, y + 10.0f);
			CAMERA->VCToWC(pos);

			DirectWrite::ChangeTextType
			(
				L"맑은고딕체",
				DWRITE_FONT_WEIGHT_BOLD,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_CONDENSED
			);

			DirectWrite::RenderText(banner, pos, 230, 77, 81, 40.0f);

			DirectWrite::ChangeTextType
			(
				L"맑은고딕체",
				DWRITE_FONT_WEIGHT_MEDIUM,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_CONDENSED
			);

			// 순서 : 선택전 -> 첫질문 -> 배드 루트 -> 성공 루트 1, 2

			switch (step)
			{
			case 0:
				strbutton1 = L"이제야 만나네. 넌 시련들을 통과하며 가치를 증명했어.";
				x = -(strbutton1.length() * 30.0f * 0.5f);
				pos = Vector2(x, y - 42.5f);
				CAMERA->VCToWC(pos);

				DirectWrite::RenderText(strbutton1, pos, 255, 255, 255, 30.0f);
				break;

			case 1:
				strbutton1 = L"영혼을 바치면 아끼는 종으로 삼아 주마.";
				
				x = -(strbutton1.length() * 30.0f * 0.5f);
				pos = Vector2(x, y - 42.5f);
				CAMERA->VCToWC(pos);

				DirectWrite::RenderText(strbutton1, pos, 255, 255, 255, 30.0f);
				break;

			case 2:
				strbutton1 = L"영혼을 바치면 아끼는 종으로 삼아 주마.";
				
				x = -(strbutton1.length() * 30.0f * 0.5f);
				pos = Vector2(x, y - 42.5f);
				CAMERA->VCToWC(pos);

				DirectWrite::RenderText(strbutton1, pos, 255, 255, 255, 30.0f);
				break;

			case 3:
				if (success)
					strbutton1 = L"뭘 하려는 거지? 악마를 굴복시킬 수 있을 거라고 생각해?";
				else
					strbutton1 = L"절절하고 어린 영혼이로고...";

				x = -(strbutton1.length() * 30.0f * 0.5f);
				pos = Vector2(x, y - 42.5f);
				CAMERA->VCToWC(pos);

				DirectWrite::RenderText(strbutton1, pos, 255, 255, 255, 30.0f);
				break;

			case 4:
				strbutton1 = L"뭘 하려는 거지? 악마를 굴복시킬 수 있을 거라고 생각해?";
				
				x = -(strbutton1.length() * 30.0f * 0.5f);
				pos = Vector2(x, y - 42.5f);
				CAMERA->VCToWC(pos);

				DirectWrite::RenderText(strbutton1, pos, 255, 255, 255, 30.0f);
				break;
			case 5:
				if (success)
					strbutton1 = L"정말? 그게 다야? 여기까지 와놓고선, 날 고작 팬케이크로 사려고?";
				else
					strbutton1 = L"네 주제를 가르쳐 줘야겠구나.";

				x = -(strbutton1.length() * 30.0f * 0.5f);
				pos = Vector2(x, y - 42.5f);
				CAMERA->VCToWC(pos);

				DirectWrite::RenderText(strbutton1, pos, 255, 255, 255, 30.0f);
				break;
			case 6:
				strbutton1 = L"내가 팬케이크를 좋아하니 운 좋은줄 알아라.";

				x = -(strbutton1.length() * 30.0f * 0.5f);
				pos = Vector2(x, y - 42.5f);
				CAMERA->VCToWC(pos);

				DirectWrite::RenderText(strbutton1, pos, 255, 255, 255, 30.0f);
				break;
			}
		}
		DirectWrite::GetDC()->EndDraw();
	}
}


void HS05_Dialogue::UpdateEX2()
{
	CAMERA->Update();

	Matrix V = CAMERA->GetViewMatrix();
	Matrix P = CAMERA->GetProjMatrix();

	time += DELTA;

	if (DOWN(VK_SPACE) || DOWN(VK_RETURN))
		step++;

	if (time >= 0.75f)
		time = 0.75f;

	// Background 설정
	{
		Vector2 size = background[0]->GetTextureRealSize();
		Vector2 origin = background[0]->GetPosition();
		CAMERA->VCToWC(origin);

		float min = origin.y - time * 1500;
		float max = origin.y + time * 1500;

		Color changeColor = Color(0.0f, 0.0f, 0.0f, 1.0f);

		background[0]->UpdateColorBuffer(changeColor, 3, 0.75f - time, min, max);
		background[0]->Update(V, P);
	}

	if (step == 2)
	{
		HS03_ChangeScene* scene1 = (HS03_ChangeScene*)SCENEMANAGER->GetScene("HS03_ChangeScene");
		scene1->SetNextScene("HS16_JudgeScene");

		HS00_DeadScene* scene2 = (HS00_DeadScene*)SCENEMANAGER->GetScene("HS00_DeadScene");
		scene2->SetScript(L"피부에 닿은 사슬로부터 살을 에는 한기가 느껴졌다.", 0);
		scene2->SetScript(L"뒤이어 뼛속까지 불태우는 불길이 느껴졌다.", 1);

		SCENEMANAGER->ChangeScene("HS00_DeadScene");
	}

	booper->Update(V, P);
}

void HS05_Dialogue::RenderEX2()
{
	background[0]->Render();
	booper->Render();

	DirectWrite::GetDC()->BeginDraw();
	{
		banner = L"• ??? •";

		float x = -(banner.length() * 40.0f * 0.5f);
		float y = -205.0f;
		Vector2 pos = Vector2(x, y + 10.0f);
		CAMERA->VCToWC(pos);

		DirectWrite::ChangeTextType
		(
			L"맑은고딕체",
			DWRITE_FONT_WEIGHT_BOLD,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_CONDENSED
		);

		DirectWrite::RenderText(banner, pos, 230, 77, 81, 40.0f);

		DirectWrite::ChangeTextType
		(
			L"맑은고딕체",
			DWRITE_FONT_WEIGHT_MEDIUM,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_CONDENSED
		);

		switch (step)
		{
		case 0:
		{
			strbutton1 = L"도망갈 수 있을 거라고 생각했느냐?";
			x = -(strbutton1.length() * 30.0f * 0.5f);
			pos = Vector2(x, y - 42.5f);
			CAMERA->VCToWC(pos);

			DirectWrite::RenderText(strbutton1, pos, 255, 255, 255, 30.0f);

			break;
		}
		case 1:
		{
			strbutton1 = L"그 짓거릴 해 놓고?";
			x = -(strbutton1.length() * 30.0f * 0.5f);
			pos = Vector2(x, y - 42.5f);
			CAMERA->VCToWC(pos);

			DirectWrite::RenderText(strbutton1, pos, 255, 255, 255, 30.0f);
			break;
		}
		}
	}
	DirectWrite::GetDC()->EndDraw();
}

void HS05_Dialogue::ChangeScene()
{
	SetActive(true);
	PLAYSOUND("DSTART", sfxSize);

	button1->Reset();
	button2->Reset();

	button1->SetHover(true);
	button2->SetHover(false);

	enter = false;
	click = false;
	success = false;
	badRoute = false;
	soundPlay = false;
	time = 0.0f;
	timer = 5.0f;
	step = 0;

	successMotion->SetPlay(0);

	lucifer->SetPlay(0);
	lucifer->SetPosition(0.0f, 162.0f);
	lucifer->UpdateColorBuffer(Color(), 0, 0.0f, 0.0f, 0.0f);

	background[0]->UpdateColorBuffer(Color(), 0, 0.0f, 0.0f, 0.0f);
	background[1]->UpdateColorBuffer(Color(), 0, 0.0f, 0.0f, 0.0f);

	for (int i = 0; i < 20; i++)
	{
		if (texture[i])
		{
			Vector2 size = texture[i]->GetTextureRealSize() * 0.5f;

			if (i % 2 == 0 && i != 18)
			{
				texture[i]->SetPosition(size.x, texture[i]->GetPosition().y);
					
			}
			texture[i]->UpdateColorBuffer(Color(), 0, 0.0f, 0.0f, 0.0f);
		}

		texture[14]->SetPosition(-200.0f, 162.0f);
		texture[15]->SetPosition(600.0f, 162.0f);
	}


	script1.clear();
	script2.clear();
	script3.clear();

	switch (sceneID)
	{
	case 0:
		banner = L"• 피곤한 악마 판데모니카 •";
		button1->SetButtonString(L"우리 집에 가면 알 수 있겠지");
		button2->SetButtonString(L"글쎄, 내가 널 도와줘야겠는데?");

		// script1, script2 = 각각 첫째, 둘째 줄
		// script3 = Dead Scene 에서 쓰일 문장

		// Success
		script1.push_back(L"참 달콤한 제안이에요. 커피를 마시고싶네요");
		script2.push_back(L"피곤해서 정신을 못차리겠어요.");

		// badRoute
		script1.push_back(L"지옥을 살아서 빠져나갈수 있으리라 생각한거야?");
		script2.push_back(L"꿈도 크셔라.");

		// Before Choose
		script1.push_back(L"지옥 고객센터의 판데모니카라고 합니다.");
		script2.push_back(L"무엇을 도와드릴까요?");

		// Dead Scene Script
		script3.push_back(L"판데모니카는 당신의 얼굴을 손아귀로 가져가더니");
		script3.push_back(L"전문가다운 부드러운 동작으로 목을 꺽어 버렸다.");

		// 아래 버튼
		successRoute = false;

		break;
	case 1:
		banner = L"• 음란한 악마 모데우스 •";
		button1->SetButtonString(L"좋아 이의 없어.");
		button2->SetButtonString(L"시간없어. 여자애들 모으기 바빠.");

		// Success
		script1.push_back(L"악마 하렘? 불쌍한 멍청이...악마들이 너를 갈갈이 찢어 버릴");
		script2.push_back(L"텐데, 그걸 놓칠순 없지.");

		// badRoute
		script1.push_back(L"다들 그렇게 말하곤... 도망가려 하더라");
		script2.push_back(L"혹시 모르니 무릎을 부숴 놔야지.");

		// Before Choose
		script1.push_back(L"너랑 나랑 지금 바로.");
		script2.push_back(L"");

		// Dead Scene Script
		script3.push_back(L"모데우스는 커다란 망치를 꺼냈다. 좋은 꼴은 못 볼 것 같다");
		script3.push_back(L"");

		// 아래 버튼
		successRoute = false;

		break;
	case 2:
		banner = L"• 세 쌍둥이 악마 케르베로스 •";
		button1->SetButtonString(L"좋아 이의 없어.");
		button2->SetButtonString(L"너무 쉬워서 의심이 가는데..");

		// Success
		script1.push_back(L"좋아, 드디어! 인간들을 타락시키러 가자!");
		script2.push_back(L"");

		// badRoute
		script1.push_back(L"지옥문을 지나기 위해선 인간이 필요해서 그래");
		script2.push_back(L"굳이 한 조각일 필욘 없지만.");

		// Before Choose
		script1.push_back(L"인간이야? 진짜 인간이야? 같이 데려가줘.");
		script2.push_back(L"");

		// Dead Scene Script
		script3.push_back(L"쌍둥이들이 미친 개마냥 당신에게 달려들었다.");
		script3.push_back(L"귀여운 강아지 소리와 함께 당신의 심장은 멈췄다.");

		// 위 버튼
		successRoute = true;

		break;
	case 3:
		banner = L"• 시큰둥한 악마 말리나 •";
		button1->SetButtonString(L"너랑 같이 놀고 싶은데.");
		button2->SetButtonString(L"기분 좋은데. 더 매도해줘.");

		// Success
		script1.push_back(L"뭐.. 게임? 그래, 안 될게 어디있어.");
		script2.push_back(L"턴제 전략 게임이 괜찮다면야");

		// badRoute
		script1.push_back(L"기가 막히네. 마조 새끼나 또 보고.");
		script2.push_back(L"");

		// Before Choose
		script1.push_back(L"대단하네. 또 골 빈 빡대가리들이야..");
		script2.push_back(L"너같이 못생긴 놈은 처음인데, 지옥에서 뭘 하고 있어?");

		// Dead Scene Script
		script3.push_back(L"말리나가 팔을 휘두르자 작살 난 당신의 목에서 피가 분수처럼");
		script3.push_back(L"터져 나왔다.");

		// 위 버튼
		successRoute = true;

		break;

	case 4:
		banner = L"• 상스러운 악마 말리나 •";
		button1->SetButtonString(L"잠깐만. 나중에 후회할 것 같은 기분인데.");
		button2->SetButtonString(L"사실 하렘같은거 때려치웠어. 턴제 전략 게임이나 할 거야");

		// Success
		script1.push_back(L"안됬지만 그래도 낄거야. 막을테면 막아 보던가.");
		script2.push_back(L"");

		// badRoute
		script1.push_back(L"어우 씨, 내가 그 고통을 끝내줄게.");
		script2.push_back(L"");

		// Before Choose
		script1.push_back(L"야. 하렘 꾸린다고 들었는데, 나도 낄래.");
		script2.push_back(L"");

		// Dead Scene Script
		script3.push_back(L"갈비뼈 사이에 자루 깊숙히 박힌 칼을 끝으로 당신의 시야는");
		script3.push_back(L"흐려졌다.");

		// 위 버튼
		successRoute = true;

		break;

	case 5:
		banner = L"• 호기심 많은 천사 아자젤 •";
		button1->SetButtonString(L"악마를 찾고 있어.");
		button2->SetButtonString(L"천사를 찾고 있어.");

		// Success
		script1.push_back(L"아, 그쪽도요? 혹시, 현대 죄악 관련 논문인가요? 아니면");
		script2.push_back(L"악마학? 같이 하는게 좋겠어요.");

		// badRoute
		script1.push_back(L"여기선 찾기 힘들 거에요. 다행히 제가 좋은곳을 알고 있죠.");
		script2.push_back(L"자, 손을 잡으세요.");

		// Before Choose
		script1.push_back(L"하느님 맙소사! 살아있는 인간이 지옥에서 뭘 하고 있는 거죠?");
		script2.push_back(L"흔치 않은 일이네요.");

		// Dead Scene Script
		script3.push_back(L"");
		script3.push_back(L"");

		// 위 버튼
		successRoute = true;

		break;

	case 6:
		banner = L"• 끝내주는 악마 저스티스 •";
		button1->SetButtonString(L"푸느라 손좀 갔지. 하렘에 들어올래?");
		button2->SetButtonString(L"메뉴에서 그냥 건너뛰었어. 하렘에 들어올래?");

		// Success1
		script1.push_back(L"뭘 굳이 물어봐. 난 파티엔 안빠져.");
		script2.push_back(L"");

		// Success2
		script1.push_back(L"나라도 그랬겠다.");
		script2.push_back(L"당연히 가지. 많을수록 즐겁잖아?");

		// Before Choose
		script1.push_back(L"야, 저 퍼즐을 풀었어? 끝내주는데!");
		script2.push_back(L"");

		// Dead Scene Script
		script3.push_back(L"");
		script3.push_back(L"");

		// 위 버튼
		successRoute = true;

		break;

	case 7:
		banner = L"• 지옥의 CEO 루시퍼 •";
		button1->SetButtonString(L"네, 여왕님!");
		button2->SetButtonString(L"사양할게. 내 하렘에 들어와라.");

		// Dead Scene Script
		script3.push_back(L"당신이 무릎을 꿇자 루시퍼는 당신의 이마에 입술을 맞췄다.");
		script3.push_back(L"당신의 생명은 그대로 녹아내렸다.");

		script3.push_back(L"루시퍼의 손짓에, 당신의 피는 모조리 식초로 변해버렸다.");
		script3.push_back(L"참으로 형언하기 어려운 느낌이다.");

		break;

	default:
		break;
	}
}

void HS05_Dialogue::DrawBanner(wstring str, float cx, float cy, float size, int r, int g, int b)
{
	DirectWrite::GetDC()->BeginDraw();
	{
		float x = -(str.length() * size * 0.5f) + cx;
		float y = cy;
		Vector2 pos = Vector2(x, y);
		CAMERA->VCToWC(pos);

		DirectWrite::RenderText(str, pos, (float)r, (float)g, (float)b, size);
	}
	DirectWrite::GetDC()->EndDraw();
}

void HS05_Dialogue::SetAttibute(wstring banner, wstring button1, wstring button2)
{
	this->banner		= banner;
	this->strbutton1	= button1;
	this->strbutton2	= button2;
}

void HS05_Dialogue::SetSceneID(int id)
{
	if (this)
		sceneID = id;
}

/*for (int i = 0; i < 3; i++)
			{
				Vector2 pos;
				switch (i)
				{
				case 0:
					pos = lucifer->GetPosition();
					if (time > 0.75f)
						time = 0.75f;

					if (pos.x > 0.0f)
						pos.x -= 1500.0f * DELTA;
					else
						pos.x = 0.0f;

					lucifer->SetPosition(pos.x, pos.y);
					lucifer->Update(V, P);
					break;

				case 1:
					if (timer <= 5.0f)
					{
						pos = texture[14]->GetPosition();

						if (time > 0.75f)
							time = 0.75f;

						if (pos.x < 0.0f)
							pos.x += 1500.0f * DELTA;
						else
							pos.x = -400.0f;

						texture[14]->SetPosition(pos.x, pos.y);
						texture[14]->Update(V, P);
					}
					break;
				case 2:
					if (timer <= 5.0f)
					{
						pos = texture[15]->GetPosition();

						if (time > 0.75f)
							time = 0.75f;

						if (pos.x > 0.0f)
							pos.x -= 1500.0f * DELTA;
						else
							pos.x = 400.0f;

						texture[15]->SetPosition(pos.x, pos.y);
						texture[15]->Update(V, P);
					}
					break;
				}
			}*/
