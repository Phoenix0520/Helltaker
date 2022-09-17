#include "framework.h"
#include "SinPyre.h"
#include "Animation.h"
#include "AnimationClip.h"

//////////////////////////////////////////
//
SinPyre::SinPyre()
{
	this->SetActive(false);

	wstring ImageFile = L"./Images/Boss/fire.png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";


	m_pAnimation = new Animation(ImageFile, shaderFile);

	{
		AnimationClip *pClip = new AnimationClip(AnimationClip::loop);
		m_pAnimation->AddClip(pClip);
		float x = 0.0f;
		for (int i = 0; i < 12; i++)
		{
			pClip->AddFrame(m_pAnimation->GetTexture(), ImageFile, x, 0, x + 120, 116, 0.1f);
			x = x + 120.0f;
		}

	}
	ImageFile = L"./Images/boss/sinPyre2.png";
	m_Texture = new Texture(ImageFile, shaderFile);

	ImageFile = L"./Images/boss/sinPyre1.png";
	m_TextureNoFire = new Texture(ImageFile, shaderFile);
}

SinPyre::~SinPyre()
{
	SAFE_DELETE(m_pAnimation);
}

void SinPyre::Update(Matrix V, Matrix P)
{
	Vector2 position = GetPosition();

//	position.y = position.y - 35.0f;
//	position.x = position.x - 5.0f;
	// Texture

	m_Texture->SetPosition(position);
	m_Texture->SetScale(scale);
	m_Texture->SetRotation(rotation);
	m_Texture->Update(V, P);


	m_TextureNoFire->SetPosition(position);
	m_TextureNoFire->SetScale(scale);
	m_TextureNoFire->SetRotation(rotation);
	m_TextureNoFire->Update(V, P);

	Vector2 size = m_Texture->GetTextureRealSize();

	position.y = position.y + size.y*0.3f;


	m_pAnimation->GetTexture()->UpdateColorBuffer(0);
	m_pAnimation->SetPlay((UINT)0);
	m_pAnimation->SetPosition(position);
	m_pAnimation->SetRotation(rotation);
	m_pAnimation->Update(V, P);

}

void SinPyre::Render()
{
	switch (m_nState)
	{
	case 0:
		m_TextureNoFire->Render();
		break;

	case 1:
	case 2:
		m_Texture->Render();
		m_pAnimation->Render();
		break;
	}
}

void SinPyre::Reset()
{
	SetActive(true);
}

bool SinPyre::IsPlay()
{
	 return m_pAnimation->IsPlay(); 
}


