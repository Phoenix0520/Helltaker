#include "framework.h"
#include "Chain.h"
#include "Animation.h"
#include "AnimationClip.h"

//////////////////////////////////////////
//
Chain::Chain()
{
	this->SetActive(false);

	wstring ImageFile = L"./Images/Boss/ChainAll.png";
	wstring shaderFile = L"./Shader/HLSL/Texture.hlsl";


	ImageFile = L"./Images/Boss/ChainAll.png";
	m_pTexture[0] = new Texture(ImageFile, shaderFile);

	ImageFile = L"./Images/Boss/ChainAll.png";
	m_pTexture[1] = new Texture(ImageFile, shaderFile);

}

Chain::~Chain()
{
	SAFE_DELETE(m_pTexture[0]);
	SAFE_DELETE(m_pTexture[1]);

}
void Chain::Update(Matrix V, Matrix P)
{
	Vector2 position = GetPosition();

	m_pTexture[0]->SetPosition(GetPosition().x,
		m_pTexture[0]->GetPosition().y);
	m_pTexture[1]->SetPosition(GetPosition().x,
		m_pTexture[1]->GetPosition().y);

	if (m_bMove)
	{
		// 무한배경
		m_pTexture[0]->SetPosition(GetPosition().x,
			m_pTexture[0]->GetPosition().y + 1.0f);
		m_pTexture[1]->SetPosition(GetPosition().x,
			m_pTexture[1]->GetPosition().y + 1.0f);

	}
	for (int i = 0; i < 2; i++)
	{
		Vector2 pos = m_pTexture[i]->GetPosition();
		Vector2 size = m_pTexture[i]->GetTextureRealSize();

		if (pos.y >= (0.0f))
		{
			if (i == 0)
			{
				m_pTexture[1]->SetPosition(pos.x,
					m_pTexture[0]->GetPosition().y - 1400.0f*0.825f);
			}
			if (i == 1)
			{
				m_pTexture[0]->SetPosition(pos.x,
					m_pTexture[1]->GetPosition().y - 1400.0f*0.825f);
			}

		}

	}	// 무한배경
	m_pTexture[0]->SetScale(GetScale());
	m_pTexture[1]->SetScale(GetScale());
	m_pTexture[0]->Update(V, P);
	m_pTexture[1]->Update(V, P);

}

void Chain::Render()
{
	Vector2 position = GetPosition();
	Matrix V, P;

	V = CAMERA->GetViewMatrix();
	P = CAMERA->GetProjMatrix();

	// Left
	m_pTexture[0]->Render();
	m_pTexture[1]->Render();

	// Right
	Vector2 position1 = m_pTexture[0]->GetPosition();
	Vector2 position2 = m_pTexture[1]->GetPosition();

	m_pTexture[0]->SetPosition(position1.x + 1700.0f, position1.y);
	m_pTexture[1]->SetPosition(position2.x + 1700.0f, position2.y);
	m_pTexture[0]->Update(V, P);
	m_pTexture[1]->Update(V, P);

	m_pTexture[0]->Render();
	m_pTexture[1]->Render();

	m_pTexture[0]->SetPosition(position1);
	m_pTexture[1]->SetPosition(position2);
	m_pTexture[0]->Update(V, P);
	m_pTexture[1]->Update(V, P);

}

void Chain::Reset()
{
	m_Time  = 0.0f;
	m_bMove = false;

}


