#include "framework.h"
#include "Clear.h"

Clear::Clear()
{
	wstring imageFile1 = L"./Images/Effects/Clear/Clear (1).png";
	// 340 x 340
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	animation = new Animation(imageFile1, shaderFile);

	// Clear
	{
		AnimationClip* clip = new AnimationClip(AnimationClip::State::end);
		animation->AddClip(clip);

		for (int i = 1; i <= 4; i++)
		{
			wstring str = L"./Images/Effects/Clear/Clear (" + to_wstring(i) + L").png";
			clip->AddFrame(animation->GetTexture(), str, 0.0f, 0.0f, 340.0f, 340.0f, 0.045f);
		}
		for (int i = 5; i <= 9; i++)
		{
			wstring str = L"./Images/Effects/Clear/Clear (" + to_wstring(i) + L").png";
			clip->AddFrame(animation->GetTexture(), str, 0.0f, 0.0f, 340.0f, 340.0f, 0.095f);
		}
		for (int i = 10; i <= 15; i++)
		{
			wstring str = L"./Images/Effects/Clear/Clear (" + to_wstring(i) + L").png";
			clip->AddFrame(animation->GetTexture(), str, 0.0f, 0.0f, 340.0f, 340.0f, 0.045f);
		}
	}

	// Particle

	wstring imageFile2 = L"./Images/Effects/Heart.png";
	//heart
	{
		for (int i = 0; i < 10; i++)
		{
			heart[i] = new Texture(imageFile2, shaderFile);
		}
	}
	wstring imageFile3 = L"./Images/Effects/Star.png";
	//star
	{
		for (int i = 0; i < 10; i++)
		{
			star[i] = new Texture(imageFile3, shaderFile);
		}
	}
	
	Random();

 	Vector2 position = GetPosition();


	Color color = Color(189.0f / 255.0f, 7.0f / 255.0f, 66.0f / 255.0f, 0.75f);
	Color color2 = Color(212.0f / 255.0f, 95.0f / 255.0f, 103.0f / 255.0f, 0.75f);

	for (int i = 0; i < 10; i++)
	{
		heart[i]->UpdateColorBuffer(color, 4, 0.0f, 0.0f, 0.0f);
	}
	for (int i = 0; i < 10; i++)
	{
		star[i]->UpdateColorBuffer(color2, 4, 0.0f, 0.0f, 0.0f);
	}

	SetActive(false);
	//SetActive(true);

}

Clear::~Clear()
{
	SAFE_DELETE(animation);
}

void Clear::Update(Matrix V, Matrix P)
{
	Vector2 position = GetPosition();

	animation->SetScale(1.5f, 1.5f);
	animation->SetPosition(position);
	animation->SetRotation(rotation);
	animation->Update(V, P);

	if (IsActive())
	{
		for (int i = 0; i < 10; i++)
		{
			heart[i]->SetPosition(position.x - hPos[i].x * (val / 0.5f), position.y - hPos[i].y * (val / 0.5f));
			heart[i]->SetScale(sc[i], sc[i]);
		}

		for (int i = 0; i < 10; i++)
		{
			star[i]->SetPosition(position.x - sPos[i].x * (val / 0.5f), position.y - sPos[i].y * (val / 0.5f));
			star[i]->SetScale(sc[i] * 0.75f, sc[i] * 0.75f);
		}
		
		if (val < 1.0f)
			val += DELTA * 0.65f;
	}

	for (int i = 0; i < 10; i++)
	{
		heart[i]->Update(V, P);
		star[i]->Update(V, P);
	}
}
	
void Clear::Render()
{
	if (IsActive())
	{
		animation->Render();
		for (int i = 0; i < 10; i++)
		{
			heart[i]->Render();
			star[i]->Render();
		}
	}
}

void Clear::Reset()
{
	Random();

	Vector2 pos = GetPosition();

	for (int i = 0; i < 10; i++)
	{
		heart[i]->SetPosition(pos);
		star[i]->SetPosition(pos);
	}

	animation->SetPlay(0);

	val = 0.0f;
	SetActive(false);
}

void Clear::Random()
{
	mt19937 engine((unsigned int)time(NULL));                    // MT19937 난수 엔진
	uniform_int_distribution<int> distribution(-250, 250);          // 생성 범위
	auto generator = bind(distribution, engine);
	uniform_int_distribution<int> distribution2(10, 30);          // 생성 범위
	auto generator2 = bind(distribution2, engine);

	for (int i = 0; i < 10; i++)
	{
		hPos[i] = Vector2((float)generator(), (float)generator());
		sPos[i] = Vector2((float)generator(), (float)generator());
		sc[i] = (float)generator2() / 10;
	}
}

bool Clear::IsPlay()
{
	return animation->IsPlay();
}
