#include "framework.h"
#include "SceneList.h"
#include "Helltaker.h"
#include "HelltakerMap.h"
#include "Booper.h"
#include "Mob.h"
#include "Box.h"
#include "Trap.h"
#include "Slate.h"
#include "LockBox.h"
#include "Key.h"
#include "Goal.h"
#include "Fire.h"

HS16_JudgeScene::HS16_JudgeScene()
{
	wstring imageFile1 = L"./Images/background/background (2).png";
	wstring imageFile2 = L"./Images/background/background (3).png";
	wstring imageFile3 = L"./Images/background/background (9).png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	// Background
	{
		background[0] = new Texture(imageFile1, shaderFile);
		background[0]->SetPosition(0.0f, 100.0f);
		background[0]->SetOffset(0.0f, 138.0f);
		background[0]->SetOffsetSize(1960.0f, 544.0f);

		background[1] = new Texture(imageFile2, shaderFile);
		background[1]->SetPosition(0.0f, 100.0f);
		background[1]->SetOffset(0.0f, 138.0f);
		background[1]->SetOffsetSize(1960.0f, 544.0f);

		background[2] = new Texture(imageFile3, shaderFile);
		background[2]->SetPosition(0.0f, 100.0f);
		background[2]->SetOffset(0.0f, 132.0f);
		background[2]->SetOffsetSize(1960.0f, 544.0f);

		wstring imageFile4 = L"./Images/Background/Background (10).png";

		background[3] = new Texture(imageFile4, shaderFile);
		background[3]->SetPosition(0.0f, 100.0f);

		imageFile4 = L"./Images/Back/Back.png";

		// ChangeEffect
		change = new Texture(imageFile4, shaderFile);
		change->SetPosition(0.0f, 100.0f);
		change->SetOffset(0.0f, 0.0f);
		change->SetOffsetSize(1.0f, 1.0f);
		change->SetScale(1960.0f, 544.0f);	

		// 가림막
		background[4] = new Texture(imageFile1, shaderFile);
		background[4]->SetOffset(0.0f, 0.0f);
		background[4]->SetOffsetSize(1.0f, 1.0f);
		background[4]->UpdateColorBuffer(Color(2.0f / 255.0f, 2.0f / 255.0f, 27.0f / 255.0f, 1.0f), 4, 0.0f, 0.0f, 0.0f);
		background[4]->SetScale(1920.0f, 500.0f);
		background[4]->SetPosition(0.0f, -425.0f);

		// 가림막2
		background[5] = new Texture(imageFile1, shaderFile);
		background[5]->SetOffset(0.0f, 0.0f);
		background[5]->SetOffsetSize(1.0f, 1.0f);
		background[5]->UpdateColorBuffer(Color(2.0f / 255.0f, 2.0f / 255.0f, 27.0f / 255.0f, 1.0f), 4, 0.0f, 0.0f, 0.0f);
		background[5]->SetScale(1920.0f, 500.0f);
		background[5]->SetPosition(0.0f, 620.0f);
	}

	// Booper
	{
		booper = (Booper*)OBJMANAGER->FindObject("Booper");
	}

	wstring imageFile4 = L"./Images/Dialogue/Judgement/Glove (1).png";

	// Judgement
	{
		// Glove1
		{
			glove1 = new Animation(imageFile4, shaderFile);
			glove1->SetPosition(375.0f, -50.0f);
			glove1->SetScale(1.025f, 1.025f);
			glove1->SetRotation(0.0f, 0.0f, -27.5f);
			AnimationClip* clip = new AnimationClip(AnimationClip::State::end);
			glove1->AddClip(clip);

			for (int i = 0; i <= 3; i++)
			{
				float delta;
				wstring str = L"./Images/Dialogue/Judgement/Glove (" + to_wstring(i) + L").png";

				switch (i)
				{
				case 0:
					str = L"./Images/Dialogue/Judgement/Glove (2).png";
					delta = 0.06f;
					break;
				case 1:
					delta = 1.25f;
					break;
				case 2:
					delta = 0.285f;
					break;
				case 3:
					delta = 0.5f;
					break;
				}

				clip->AddFrame(glove1->GetTexture(), str, 0.0f, 0.0f, 732.0f, 524.0f, delta);
			}
		}

		// Glove2
		{
			glove2 = new Animation(imageFile4, shaderFile);
			glove2->SetPosition(-375.0f, -70.0f);
			glove2->SetScale(1.025f, 1.025f);
			glove2->SetRotation(0.0f, 180.0f, -22.5f);
			AnimationClip* clip = new AnimationClip(AnimationClip::State::end);
			glove2->AddClip(clip);

			for (int i = 0; i <= 3; i++)
			{
				wstring str = L"./Images/Dialogue/Judgement/Glove (" + to_wstring(i) + L").png";

				float delta;

				switch (i)
				{
				case 0:
					str = L"./Images/Dialogue/Judgement/Glove (2).png";
					delta = 0.06f;
					break;
				case 1:
					delta = 1.25f;
					break;
				case 2:
					delta = 0.285f;
					break;
				case 3:
					delta = 0.5f;
					break;
				}

				clip->AddFrame(glove2->GetTexture(), str, 0.0f, 0.0f, 732.0f, 524.0f, delta);
			}
		}

		// Judgement
		{
			imageFile4 = L"./Images/Dialogue/Judgement/IDLE (4).png";

			judgement = new Animation(imageFile4, shaderFile);
			judgement->SetPosition(0.0f, 162.0f);

			// IDLE
			{
				AnimationClip* clip = new AnimationClip(AnimationClip::State::end);
				judgement->AddClip(clip);

				for (int i = 1; i <= 4; i++)
				{
					wstring str = L"./Images/Dialogue/Judgement/IDLE (" + to_wstring(i) + L").png";
					clip->AddFrame(judgement->GetTexture(), str, 0.0f, 0.0f, 1072.0f, 748.0f, 0.07f);
				}
			}
		}
	}
	
	// Chain
	{
		imageFile4 = L"./Images/Dialogue/Judgement/BigChain.png";

		for (int i = 0; i < 6; i++)
		{
			chain[i] = new Texture(imageFile4, shaderFile);
			//chain[i]->CreateMultiShaderResourceView(L"./Images/Particle.png");
		}
		chain[0]->SetScale(0.425f, 0.425f);
		chain[0]->SetPosition(-475.0f, 0.0f);
		chain[0]->SetRotation(0.0f, 180.0f, 15.0f);

		chain[1]->SetScale(0.425f, 0.425f);
		chain[1]->SetPosition(475.0f, 0.0f);
		chain[1]->SetRotation(0.0f, 0.0f, 15.0f);
		
		//

		chain[2]->SetScale(0.825f, 0.825f);
		chain[2]->SetPosition(-775.0f, -150.0f);
		chain[2]->SetRotation(0.0f, 180.0f, 30.0f);

		chain[3]->SetScale(0.825f, 0.825f);
		chain[3]->SetPosition(775.0f, -150.0f);
		chain[3]->SetRotation(0.0f, 0.0f, 30.0f);

		//

		chain[4]->SetScale(0.525f, 0.525f);
		chain[4]->SetPosition(-875.0f, 250.0f);
		chain[4]->SetRotation(0.0f, 180.0f, 45.0f);

		chain[5]->SetScale(0.525f, 0.525f);
		chain[5]->SetPosition(875.0f, 250.0f);
		chain[5]->SetRotation(0.0f, 0.0f, 45.0f);
	}

	SetActive(false);
	sceneName = "HS16_JudgeScene";
	//display = true;
}

HS16_JudgeScene::~HS16_JudgeScene()
{
	for (int i = 0; i < 6; i++)
		SAFE_DELETE(chain[i]);
	SAFE_DELETE(booper);
	for (int i = 0; i < 5; i++)
		SAFE_DELETE(background[i]);
}

void HS16_JudgeScene::Update()
{
	CAMERA->Update();
	Matrix V = CAMERA->GetViewMatrix();
	Matrix P = CAMERA->GetProjMatrix();

	if (DOWN(VK_SPACE) || DOWN(VK_RETURN))
	{
		if (step == 3 && timer <= 3.0f);
		else
		{
			step++;
			plus = true;
			time = 1.0f;
		}
	}

	// Background 설정
	
	switch (step)
	{
	case 0:
		booper->SetActive(true);
		booper->Update(V, P);

		break;
	case 1:
	{
		time -= DELTA * 1.875f;

		Color color = Color(1.0f, 1.0f, 1.0f, time);

		change->UpdateColorBuffer(color, 7, 0.0f, 0.0f, 0.0f);

		change->Update(V, P);
		background[0]->Update(V, P);
		background[1]->Update(V, P);
		background[2]->Update(V, P);

		booper->Update(V, P);
		break;
	}
	case 2:
		change->Update(V, P);
		background[0]->Update(V, P);
		background[1]->Update(V, P);
		background[2]->Update(V, P);

		booper->Update(V, P);
		break;
	}


	if (step >= 3)
	{
		background[0]->Update(V, P);
		background[1]->Update(V, P);
		background[2]->Update(V, P);

		if (timer >= 0.25f)
		{
			if (time >= 1.0f)
				plus = false;

			if (plus)
				time += DELTA * 1.45f;
			else
				time -= DELTA * 1.45f;

			Color color = Color(1.0f, 1.0f, 1.0f, time);

			background[1]->UpdateColorBuffer(color, 7, 0.0f, 0.0f, 0.0f);
			background[4]->UpdateColorBuffer(Color(2.0f / 255.0f, 2.0f / 255.0f, 27.0f / 255.0f, 1.0f), 4, 0, 0, 0);
			background[5]->UpdateColorBuffer(Color(2.0f / 255.0f, 2.0f / 255.0f, 27.0f / 255.0f, 1.0f), 4, 0, 0, 0);
		}

		timer += DELTA * 1.25f;
		
		if (timer >= 4.5f)
		{
			if (cplus)
				ctime += DELTA * 0.45f;
			else
				ctime -= DELTA * 0.45f;

			if (ctime >= 1.0f)
				cplus = false;
			if (ctime <= 0.75f)
				cplus = true;
			

			background[4]->Update(V, P);
			background[5]->Update(V, P);
			// chain 1, 2
			chain[0]->Update(V, P);
			chain[1]->Update(V, P);

			
			for (int i = 0; i < 6; i++)
			{
				alpha = ctime;

				Color color = Color(0.0f, 0.0f, 0.0f, alpha);

				chain[i]->UpdateColorBuffer(color, 7, 0, 0, 0);
			}

			// chain 3, 4, 5, 6;
			background[3]->Update(V, P);

			chain[2]->Update(V, P);
			chain[3]->Update(V, P);
			chain[4]->Update(V, P);
			chain[5]->Update(V, P);
		
			
			judgement->Update(V, P);
			booper->Update(V, P);

			
			return;
		}

		if (timer >= 1.5f)
		{
			Vector2 pos = glove1->GetPosition();

			float val1 = 0.0f;
			float val2 = 0.0f;

			if (timer >= 1.5f && timer < 2.0f)
			{
				val1 = -timer * 0.5f;
				val2 = timer * 1.0f;
			}
			else if (timer >= 2.45f && timer < 2.95f)
			{
				val2 = timer * 1.35f;
			}
			else if (timer >= 3.75f && timer < 4.75f)
			{
				val1 = timer * 1.1f;
				val2 = -timer * 8.25f;
			}

			glove1->SetPosition(pos.x + val1, pos.y + val2 * 0.55f);

			pos = glove2->GetPosition();

			glove2->SetPosition(pos.x - val1, pos.y + val2 * 0.55f);

			if (timer >= 2.275f)
			{
				float val3 = (22.5f - (timer - 2.275f) * 14.5f);
				float val4 = (timer - 4.0f) * 0.35f;
				
				if (val3 > 0.0f)
				{
					glove1->SetRotation(0.0f, 0.0f, 0.0f - val3);
					glove2->SetRotation(0.0f, 180.0f, 0.0f - val3);
				}

				if (timer >= 4.0f)
				{
					glove1->SetScale(1.025f + val4, 1.025f + val4);
					glove2->SetScale(1.025f + val4, 1.025f + val4);
				}
			}

			
			glove1->Update(V, P);
			glove2->Update(V, P);


			background[4]->SetPosition(0.0f, -425.0f);
			background[4]->Update(V, P);

		}
	}
}

void HS16_JudgeScene::Render()
{
	DirectWrite::GetDC()->BeginDraw();
	{
		wstring banner = L"• ??? •";
		wstring banner2 = L"• 고위 기소관 저지먼트 •";
		wstring script;

		float x = -(banner.length() * 40.0f * 0.5f);
		float y = -205.0f;

		Vector2 pos = Vector2(x, y + 20.0f);
		
		CAMERA->VCToWC(pos);

		DirectWrite::ChangeTextType
		(
			L"맑은고딕체",
			DWRITE_FONT_WEIGHT_BOLD,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_CONDENSED
		);

		if (step >= 3)
		{
			Vector2 pos2 = Vector2(-(banner2.length() * 40.0f * 0.5f), -195.0f);
			CAMERA->VCToWC(pos2);

			if (timer >= 4.5f)
				DirectWrite::RenderText(banner2, pos2, 230, 77, 81, 40.0f);
		}
		else if (step != 0)
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
			script = L"마치 천 번은 죽은 것 같은 느낌이다. 하지만 불길은";
			x = -(script.length() * 30.0f * 0.5f);
			y = -175.0f;
			Vector2 pos = Vector2(x, y - 70.0f);
			CAMERA->VCToWC(pos);

			DirectWrite::RenderText(script, pos, 255, 255, 255, 30.0f);

			script = L"사그라들고... 어찌됐든 당신은 아직 살아있는 것 같다.";
			x = -(script.length() * 30.0f * 0.5f);
			y = -222.5f;
			pos = Vector2(x, y - 70.0f);
			CAMERA->VCToWC(pos);

			DirectWrite::RenderText(script, pos, 255, 255, 255, 30.0f);

			booper->Render();
			break;
		}
		case 1:
		{
			background[0]->Render();
			background[2]->Render();

			change->Render();

			script = L"침입자 녀석, 이제야 찾았다!";
			x = -(script.length() * 30.0f * 0.5f);
			y = -175.0f;
			Vector2 pos = Vector2(x, y - 70.0f);
			CAMERA->VCToWC(pos);

			DirectWrite::RenderText(script, pos, 255, 255, 255, 30.0f);

			script = L"넌 아직 죽을 수 없어.";
			x = -(script.length() * 30.0f * 0.5f);
			y = -220.0f;
			pos = Vector2(x, y - 70.0f);
			CAMERA->VCToWC(pos);

			DirectWrite::RenderText(script, pos, 255, 255, 255, 30.0f);

			booper->Render();
			break;
		}
		case 2:
		{
			background[0]->Render();
			background[2]->Render();

			//change->Render();

			script = L"나와 함께 오랜 시간을 보내야 할 거다.";
			x = -(script.length() * 30.0f * 0.5f);
			y = -175.0f;
			Vector2 pos = Vector2(x, y - 70.0f);
			CAMERA->VCToWC(pos);

			DirectWrite::RenderText(script, pos, 255, 255, 255, 30.0f);

			booper->Render();

			break;
		}
		case 3:
		{
			background[0]->Render();

			if (timer >= 0.25f && timer <= 1.25f)
				background[1]->Render();
			
			background[2]->Render();

			if (timer >= 4.5f)
			{
				background[3]->Render();
				chain[0]->Render();
				chain[1]->Render();
				background[4]->Render();
				background[5]->Render();
				chain[2]->Render();
				chain[3]->Render();
				chain[4]->Render();
				chain[5]->Render();
				judgement->Render();

				script = L"죄악의 기계에 시동을 걸어라! 시련을 피할 수는 없다!";
				x = -(script.length() * 37.5f * 0.5f);
				y = -205.5f;
				Vector2 pos = Vector2(x, y - 42.5f);
				CAMERA->VCToWC(pos);

				//x = -(strbutton1.length() * 30.0f * 0.5f);
				//pos = Vector2(x, y - 42.5f);

				DirectWrite::RenderText(script, pos, 255, 255, 255, 37.5f);


				booper->Render();
				break;
			}

			if (timer >= 1.5f)
			{
				glove1->Render();
				glove2->Render();
				background[4]->Render();
			}
			break;
		}
		case 4:
		{
			HS03_ChangeScene* scene = (HS03_ChangeScene*)SCENEMANAGER->GetScene("HS03_ChangeScene");
			scene->SetNextScene("HS17_BossScene");
			SCENEMANAGER->ChangeScene("HS03_ChangeScene");
			break;
		}
		}
	}
	DirectWrite::GetDC()->EndDraw();
}

void HS16_JudgeScene::ChangeScene()
{
	SetActive(true);
	booper->SetActive(true);

	judgement->SetPlay(0);
	glove1->SetPlay(0);
	glove2->SetPlay(0);

	judgement->UpdateColorBuffer(Color(), 0, 0.0f, 0.0f, 0.0f);
	glove1->UpdateColorBuffer(Color(), 0, 0.0f, 0.0f, 0.0f);
	glove2->UpdateColorBuffer(Color(), 0, 0.0f, 0.0f, 0.0f);

	for (int i = 0; i < 6; i++)
		if (background[i])
			background[i]->UpdateColorBuffer(Color(), 0, 0.0f, 0.0f, 0.0f);

	time = 1.0f;
	ctime = 1.0f;
	timer = 0.0f;
	step = 0;

	plus = true;
}