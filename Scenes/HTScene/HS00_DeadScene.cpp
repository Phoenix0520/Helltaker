#include "framework.h"
#include "SceneList.h"
#include "Rect.h"
#include "Helltaker.h"

HS00_DeadScene::HS00_DeadScene()
{
	wstring imageFile1 = L"./Images/Character/Dead/Death (1).png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	animation = new Animation(imageFile1, shaderFile);

	// Death
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::State::once);
		animation->AddClip(clip);
		
		for (int i = 1; i <= 18; i++)
		{
			wstring str = L"./Images/Character/Dead/Death (" + to_wstring(i) + L").png";
			clip->AddFrame(animation->GetTexture(), str, 0, 0, 720, 1232, 0.06f);	
		}
	}

	imageFile1 = L"./Images/BadEnd/Bad End (1).png";
	animation2 = new Animation(imageFile1, shaderFile);
	// BadEnd
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::State::end);
		animation2->AddClip(clip);

		for (int i = 1; i <= 9; i++)
		{
			wstring str = L"./Images/BadEnd/Bad End (" + to_wstring(i) + L").png";
			clip->AddFrame(animation2->GetTexture(), str, 0, 0, 1568, 480, 0.09f);
		}
		Vector2 position = animation2->GetPosition();
		position.y += 100.0f;
		animation2->SetPosition(position);
		
	}

	// Rect
	{
		rect = new Rect2(L"./Shader/HLSL/Color.hlsl");
		rect->SetPosition(0.0f, 0.0f);
		rect->SetScale(1920.0f, 1080.0f);
		rect->UpdateBlock(Color(0.85f, 0.15f, 0.1f, 1.0f));
	}

	sceneName = "HS00_DeadScene";
	SetNextScene("HS03_ChangeScene");
	SetActive(false);
}

HS00_DeadScene::~HS00_DeadScene()
{
	SAFE_DELETE(animation);
	SAFE_DELETE(animation2);
	SAFE_DELETE(rect);
}

void HS00_DeadScene::Update()
{
	CAMERA->Update();

	Matrix V, P;

	V = CAMERA->GetViewMatrix();
	P = CAMERA->GetProjMatrix();

	Vector2 position;

	// Animation

	Helltaker* helltaker = (Helltaker*)OBJMANAGER->FindObject("Helltaker");
	
	if (helltaker->GetHP() <= -1 || helltaker->IsBoss())
	{
		state = 0;
	}
	else
	{
		state = 1;
	}

	if (state == 0)
	{
		if (!soundPlay)
		{
			PLAYSOUND("DEATH", sfxSize);
			soundPlay = true;
		}

		if (!animation->IsPlay()) // Rendering Death
		{
			SCENEMANAGER->ChangeScene(nextSceneName);
			return;
		}
		animation->Update(V, P);
	}
	else if (state == 1)
	{
		if (!soundPlay)
		{
			PLAYSOUND("BADEND", sfxSize);
			soundPlay = true;
		}

		if (!animation2->IsPlay()) // Rendering End
		{	
			if (DOWN(VK_SPACE))
			{
				SCENEMANAGER->ChangeScene(nextSceneName);
				state = 0;
			}
			return;
		}

		string name = SCENEMANAGER->GetScene("HS03_ChangeScene")->GetNextSceneName();

		SCENEMANAGER->GetScene(name)->SetReset(true);


		animation2->Update(V, P);
		//rect->Update(V, P);
	}
}

void HS00_DeadScene::Render()
{
	if (state == 0)
		animation->Render();
	else if (state == 1)
	{
		DirectWrite::GetDC()->BeginDraw();
		{
			Vector2 position;
			wstring str;

			DirectWrite::ChangeTextType
			(
				L"맑은고딕체",
				DWRITE_FONT_WEIGHT_BOLD,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_CONDENSED
			);

			//str = L"판데모니카는 당신의 얼굴을 손아귀로 가져가더니";
			str = script[0];
			position = Vector2(-(str.length() * 32.5f * 0.5f), -185.0f);
			CAMERA->VCToWC(position);
			DirectWrite::RenderText(str, position, 255, 0, 0, 32.5f);

			//str = L"전문가다운 부드러운 동작으로 목을 꺽어 버렸다.";
			str = script[1];
			position = Vector2(-(str.length() * 32.5f * 0.5f), -235.0f);
			CAMERA->VCToWC(position);
			DirectWrite::RenderText(str, position, 255, 0, 0, 32.5f);

			DirectWrite::ChangeTextType
			(
				L"맑은고딕체",
				DWRITE_FONT_WEIGHT_MEDIUM,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_CONDENSED
			);

		}
		DirectWrite::GetDC()->EndDraw();

		animation2->Render();
		//rect->Render();
	}
}

void HS00_DeadScene::ChangeScene()
{
	SetActive(true);
	alpha = 0.0f;
	bloodTime = 0.0f;
	soundPlay = false;
	animation->SetPlay(0);
	animation2->SetPlay(0);
}
