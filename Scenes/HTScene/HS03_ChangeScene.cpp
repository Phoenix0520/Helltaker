#include "framework.h"
#include "HS03_ChangeScene.h"

HS03_ChangeScene::HS03_ChangeScene()
{
	wstring imageFile1 = L"./Images/Translation/Changing (1).png";
	wstring shaderFile = L"./Shader/HLSL/Texture.hlsl";

	animation = new Animation(imageFile1, shaderFile);

	// Scene
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::State::once);
		animation->AddClip(clip);

		for (int i = 1; i < 30; i++)
		{
			wstring str = L"./Images/Translation/Changing (" + to_wstring(i) + L").png";
			clip->AddFrame(animation->GetTexture(), str, 0, 0.0f, 1924.0f, 1084.0f, 0.04f);
		}
	}

	SetActive(false);

	sceneName = "HS03_ChangeScene";
	SetNextScene("HS04_Chapter01");
}

HS03_ChangeScene::~HS03_ChangeScene()
{
	SAFE_DELETE(animation);
}

void HS03_ChangeScene::Update()
{
	CAMERA->Update();

	Matrix V, P;

	V = CAMERA->GetViewMatrix();
	P = CAMERA->GetProjMatrix();

	if (!animation->IsPlay()) // Rendering End
	{
		SCENEMANAGER->ChangeScene(nextSceneName);

		if (!ISPLAYING("MAINBGM"))
			PLAYSOUND("MAINBGM", bgmSize);

		CAMERA->SetPosition(Vector2(0.0f, 0.0f));
		return;
	}

	animation->Update(V, P);
}

void HS03_ChangeScene::Render()
{
	animation->Render();
}

void HS03_ChangeScene::ChangeScene()
{
	STOPSOUND("INTRO");

	PLAYSOUND("Change", sfxSize);
	SetActive(true);
	animation->SetPlay(0);
}