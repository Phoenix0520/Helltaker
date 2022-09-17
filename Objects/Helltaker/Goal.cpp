#include "framework.h"
#include "Goal.h"
#include "HelltakerMap.h"
#include "Clear.h"
#include "Star.h"
#include "LoveSign.h"

Goal::Goal(int id)
{
	wstring imageFile1 = L"./Images/Goals/Pandemonica.png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	this->id = id;

	if (id >= 3 && id <= 5 || id == 10)
	{
		clearEffect = new Clear();
		starEffect = new Star();
		loveSign = new LoveSign();
	}
	else
	{
		clearEffect = (Clear*)OBJMANAGER->FindObject("Clear");
		starEffect = (Star*)OBJMANAGER->FindObject("Star");
		loveSign = (LoveSign*)OBJMANAGER->FindObject("LoveSign");
	}

	switch (id)
	{
	case 1:
		// Pandemonica
		{
			imageFile1 = L"./Images/Goals/Pandemonica.png";

			pandemonica = new Animation(imageFile1, shaderFile);//pandemonica이 하나 생성
			AnimationClip* pClip = new AnimationClip(AnimationClip::State::loop);//AnimationClip이 하나 생성
			pandemonica->AddClip(pClip);

			float x = 0.0f;
			for (int i = 0; i <= 11; i++)
			{
				pClip->AddFrame(pandemonica->GetTexture(), imageFile1, x, 0.0f, x + 100.0f, 100.0f, 0.06f);
				x += 100.0f;
			}
		}
		return;
	case 2:
		// Modeus
		{
			imageFile1 = L"./Images/Goals/Modeus.png";
			modeus = new Animation(imageFile1, shaderFile);

			AnimationClip* pClip = new AnimationClip(AnimationClip::State::loop);//AnimationClip이 하나 생성
			modeus->AddClip(pClip);

			float x = 0.0f;
			for (int i = 0; i <= 12; i++)
			{
				pClip->AddFrame(modeus->GetTexture(), imageFile1, x, 0.0f, x + 100.0f, 100.0f, 0.06f);
				x += 100.0f;
			}

		}
		return;
	case 3:
	case 4:
	case 5:
		// Cerberus
		{
			imageFile1 = L"./Images/Goals/Cerberus/Cerberus (1).png";

			cerberus = new Animation(imageFile1, shaderFile);

			AnimationClip* pClip = new AnimationClip(AnimationClip::State::loop);//AnimationClip이 하나 생성
			cerberus->AddClip(pClip);


			for (int i = 1; i <= 12; i++)
			{
				wstring str = L"./Images/Goals/Cerberus/Cerberus (" + to_wstring(i) + L").png";
				pClip->AddFrame(cerberus->GetTexture(), str, 0.0f, 0.0f, 100.0f, 100.0f, 0.06f);
			}
		}
		return;
	case 6:
		// Malina
		{
			imageFile1 = L"./Images/Goals/Malina/Malina (1).png";

			malina = new Animation(imageFile1, shaderFile);

			AnimationClip* pClip = new AnimationClip(AnimationClip::State::loop);//AnimationClip이 하나 생성
			malina->AddClip(pClip);

			for (int i = 1; i <= 12; i++)
			{
				wstring str = L"./Images/Goals/Malina/Malina (" + to_wstring(i) + L").png";
				pClip->AddFrame(malina->GetTexture(), str, 0.0f, 0.0f, 100.0f, 100.0f, 0.06f);
			}
		}
		return;
	case 7:
		// Zdrada
		{
			imageFile1 = L"./Images/Goals/Zdrada/Zdrada (1).png";

			zdrada = new Animation(imageFile1, shaderFile);

			AnimationClip* pClip = new AnimationClip(AnimationClip::State::loop);//AnimationClip이 하나 생성
			zdrada->AddClip(pClip);

			for (int i = 1; i <= 12; i++)
			{
				wstring str = L"./Images/Goals/Zdrada/Zdrada (" + to_wstring(i) + L").png";
				pClip->AddFrame(zdrada->GetTexture(), str, 0.0f, 0.0f, 100.0f, 100.0f, 0.06f);
			}
		}
		return;
	case 8:
		// Azazel
		{
			imageFile1 = L"./Images/Goals/Azazel/Azazel (1).png";

			azazel = new Animation(imageFile1, shaderFile);

			AnimationClip* pClip = new AnimationClip(AnimationClip::State::loop);//AnimationClip이 하나 생성
			azazel->AddClip(pClip);

			for (int i = 1; i <= 12; i++)
			{
				wstring str = L"./Images/Goals/Azazel/Azazel (" + to_wstring(i) + L").png";
				pClip->AddFrame(azazel->GetTexture(), str, 0.0f, 0.0f, 100.0f, 100.0f, 0.06f);
			}
		}
		return;
	case 9:
		// justis
		{
			imageFile1 = L"./Images/Goals/Justis/Justis (1).png";

			justis = new Animation(imageFile1, shaderFile);

			AnimationClip* pClip = new AnimationClip(AnimationClip::State::loop);//AnimationClip이 하나 생성
			justis->AddClip(pClip);

			for (int i = 1; i <= 12; i++)
			{
				wstring str = L"./Images/Goals/Justis/Justis (" + to_wstring(i) + L").png";
				pClip->AddFrame(justis->GetTexture(), str, 0.0f, 0.0f, 100.0f, 100.0f, 0.06f);
			}
		}
		return;
	case 10:
		// Lucifer 
		{
			imageFile1 = L"./Images/Goals/Lucifer/Lucifer (1).png";

			lucifer = new Animation(imageFile1, shaderFile);

			AnimationClip* pClip = new AnimationClip(AnimationClip::State::loop);//AnimationClip이 하나 생성
			lucifer->AddClip(pClip);

			for (int i = 1; i <= 12; i++)
			{
				wstring str = L"./Images/Goals/Lucifer/Lucifer (" + to_wstring(i) + L").png";
				pClip->AddFrame(lucifer->GetTexture(), str, 0.0f, 0.0f, 100.0f, 100.0f, 0.06f);
			}
		}
		return;
	}
}

Goal::~Goal()
{
	SAFE_DELETE(starEffect);
	SAFE_DELETE(clearEffect);
	SAFE_DELETE(lucifer)
	SAFE_DELETE(justis)
	SAFE_DELETE(azazel);
	SAFE_DELETE(zdrada)
	SAFE_DELETE(malina);
	SAFE_DELETE(cerberus);
	SAFE_DELETE(modeus);
	SAFE_DELETE(pandemonica);
	SAFE_DELETE(loveSign);
}

void Goal::Update(Matrix V, Matrix P)
{
	Vector2 position = GetPosition();
	Vector2 scale = GetScale();
	Vector3 rotation = GetRotation();

	Animation* animation = nullptr;
	
	switch (id)
	{
	case 1:
		pandemonica->SetPosition(position);
		pandemonica->SetScale(scale);
		pandemonica->SetRotation(rotation);

		animation = pandemonica;
		break;
	case 2:
		modeus->SetPosition(position);
		modeus->SetScale(scale);
		modeus->SetRotation(rotation);

		animation = modeus;
		break;
	case 3:
	case 4:
	case 5:
		cerberus->SetPosition(position);
		cerberus->SetScale(scale);
		cerberus->SetRotation(rotation);

		animation = cerberus;
		break;
	case 6:
		malina->SetPosition(position);
		malina->SetScale(scale);
		malina->SetRotation(rotation);

		animation = malina;
		break;
	case 7:
		zdrada->SetPosition(position);
		zdrada->SetScale(scale);
		zdrada->SetRotation(rotation);

		animation = zdrada;
		break;
	case 8:
		azazel->SetPosition(position);
		azazel->SetScale(scale);
		azazel->SetRotation(rotation);

		animation = azazel;
		break;
	case 9:
		justis->SetPosition(position);
		justis->SetScale(scale);
		justis->SetRotation(rotation);

		animation = justis;
		break;
	case 10:
		lucifer->SetPosition(position.x, position.y + 100.0f);
		lucifer->SetScale(scale);
		lucifer->SetRotation(rotation);

		animation = lucifer;
		break;
	}

	// 클리어 이펙트
	clearEffect->SetPosition(position);
	starEffect->SetPosition(position);

	if (!goal)
	{
		Vector2 pos = GetPosition();

		if (id == 10)
			loveSign->SetPosition(pos.x, pos.y + 100.0f);
		else
			loveSign->SetPosition(pos);

		loveSign->Update(V, P);

		animation->UpdateColorBuffer(Color(), 0, 0, 0, 0);
	}
	else
	{
		Color color = Color(1.0f, 1.0f, 1.0f, 0.0f);

		if (!soundPlayed)
		{
			PLAYSOUND("CLEAR", sfxSize);
			soundPlayed = true;
		}

		ctime += DELTA;
		if (ctime >= 1.25f)
			ctime = 1.25f;

		animation->UpdateColorBuffer(color, 5, 1.0f - ctime, 0.0f , 0.0f);

		if (id == 10)
		{
			Vector2 pos1 = starEffect->GetPosition();
			pos1.y += 100.0f;
			starEffect->SetPosition(pos1);

			Vector2 pos2 = clearEffect->GetPosition();
			pos2.y += 100.0f;
			clearEffect->SetPosition(pos2);
		}

		if (clearEffect->IsPlay() && ctime >= 1.25f)
		{
			starEffect->SetActive(false);
			clearEffect->SetActive(true);
			clearEffect->Update(V, P);
		}

		if (ctime < 1.25f)
		{
			starEffect->SetActive(true);
			starEffect->Update(V, P);
		}
	}

	if (ctime <= 1.25f)
		animation->Update(V, P);
}

void Goal::Render()
{
	if (!goal)
		loveSign->Render();
	else
	{
		rtime += DELTA;
		if (clearEffect->IsPlay() && rtime >= 1.25f)
		{
			clearEffect->Render();
			return;
		}
		else
			starEffect->Render();
	}

	if (rtime <= 1.25f)
	{
		if (pandemonica)
			pandemonica->Render();
		else if (modeus)
			modeus->Render();
		else if (cerberus)
			cerberus->Render();
		else if (malina)
			malina->Render();
		else if (zdrada)
			zdrada->Render();
		else if (azazel)
			azazel->Render();
		else if (justis)
			justis->Render();
		else if (lucifer)
			lucifer->Render();
	}
}

void Goal::Reset()
{
	goal = false;
	soundPlayed = false;

	clearEffect->Reset();
	clearEffect->SetPosition(GetPosition());
	clearEffect->SetActive(false);
	starEffect->Reset();
	starEffect->SetPosition(GetPosition());
	starEffect->SetActive(false);

	plus = true;

	rtime = 0.0f;
	ctime = 0.0f;
}