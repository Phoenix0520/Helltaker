#include "framework.h"
#include "SinPistone.h"
#include "Animation.h"
#include "AnimationClip.h"
#include "Chain.h"
#include "SinSkull.h"

//////////////////////////////////////////
//
SinPistone::SinPistone()
{
	this->SetActive(true);

	wstring ImageFile = L"./Images/Boss/SinPiston (1).png";
	wstring shaderFile = L"./Shader/HLSL/Texture.hlsl";

	m_pAnimation = new Animation(ImageFile, shaderFile);

	// 막혀있는것 정지
	{
		AnimationClip *pClip = new AnimationClip(AnimationClip::end);
		m_pAnimation->AddClip(pClip);
		Texture *pTexture = m_pAnimation->GetTexture();
		wstring str = L"./Images/Boss/SinPiston (" + to_wstring(1) + L").png";
		pClip->AddFrame(pTexture, str, 0.0f, 0.0f, 240.0f, 800.0f, 0.1f);

	}

	// 열려있는것 정지
	{
		AnimationClip *pClip = new AnimationClip(AnimationClip::end);
		m_pAnimation->AddClip(pClip);
		Texture *pTexture = m_pAnimation->GetTexture();
		wstring str = L"./Images/Boss/SinPiston (" + to_wstring(7) + L").png";
		pClip->AddFrame(pTexture, str, 0.0f, 0.0f, 240.0f, 800.0f, 0.03f);
	}

	// 막혀져 있는것 도는거
	{
		AnimationClip *pClip = new AnimationClip(AnimationClip::once);
		m_pAnimation->AddClip(pClip);
		Texture *pTexture = m_pAnimation->GetTexture();
		for (int i = 1; i <=6 ; i++)
		{
			wstring str = L"./Images/Boss/SinPiston (" + to_wstring(i) + L").png";
			pClip->AddFrame(pTexture, str, 0.0f, 0.0f, 240.0f, 800.0f, 0.05f);
		}
	}


	// 열려져 있는거 도는거
	{
		AnimationClip *pClip = new AnimationClip(AnimationClip::once);
		m_pAnimation->AddClip(pClip);
		Texture *pTexture = m_pAnimation->GetTexture();
		for (int i = 7; i < 13; i++)
		{
			wstring str = L"./Images/Boss/SinPiston (" + to_wstring(i) + L").png";
			pClip->AddFrame(pTexture, str, 0.0f, 0.0f, 240.0f, 800.0f, 0.05f);
		}
	}
	
	// 막혀져 있는거 정지
	{
		AnimationClip *pClip = new AnimationClip(AnimationClip::end);
		m_pAnimation->AddClip(pClip);
		Texture *pTexture = m_pAnimation->GetTexture();

		wstring str = L"./Images/Boss/SinPiston (" + to_wstring(1) + L").png";
		pClip->AddFrame(pTexture, str, 0.0f, 0.0f, 240.0f, 800.0f, 0.1f);
	}

//	SetRotation(0.0f, 180.0f, 0.0f);
}

SinPistone::~SinPistone()
{
	SAFE_DELETE(m_pAnimation);
}
void SinPistone::Update(Matrix V, Matrix P)
{
	Vector2 position = GetPosition();

	// Timer를 이용하여 
	// 상하 움직이게
	m_Time = m_Time + TIMEMANAGER->Delta();

	if (m_nState != 4)
	{
		switch (m_nStep)
		{
		case 0:   // 내려오는 경우
			position.y -= 250.0f * DELTA;
			if (m_MinHeight >= position.y)
			{
				m_nStep++;
				position.y = m_MinHeight;
				SetState(m_nState + 2);
			}
			break;
		case 1:
			position.y += 250.0f * DELTA;
			{
				if (m_MaxHeight <= position.y)
				{
					m_nStep++;
					position.y = m_MaxHeight;
					SetState(m_nState - 2);
					SinSkull* pSinSkull = (SinSkull*)OBJMANAGER->FindObject("SinSkull");
					pSinSkull->SetStep(1);
				}
			}
			break;
		}
	}

	SetPosition(position);
	m_pAnimation->SetPosition(GetPosition());
	m_pAnimation->SetScale(scale);
	m_pAnimation->SetRotation(rotation);
	m_pAnimation->Update(V, P);

}

void SinPistone::Render()
{
	Matrix V, P;

	V = CAMERA->GetViewMatrix();
	P = CAMERA->GetProjMatrix();

	if (!IsActive())
		return;
	m_pAnimation->Render();

	Texture *pTexture = m_pAnimation->GetTexture();
	Vector2 position = pTexture->GetPosition();

	pTexture->SetPosition(position.x + 1700.0f, position.y);
	pTexture->Update(V, P);
	pTexture->Render();
	pTexture->SetPosition(position);

}

void SinPistone::Reset()
{
	SetActive(true);
	m_bMove = false;
	m_Time = 0.0f;
	m_nStep = 0;
}

void SinPistone::SetState(UINT state)
{
	m_nState = state;
	m_pAnimation->SetStop();
	m_pAnimation->SetPlay(m_nState);
}


