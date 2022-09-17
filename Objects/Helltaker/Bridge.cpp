#include "framework.h"
#include "Bridge.h"
#include "Animation.h"
#include "AnimationClip.h"
#include "Trap.h"
#include "Helltaker.h"
#include "HelltakerMap.h"

//////////////////////////////////////////
//
Bridge::Bridge()
{
	this->SetActive(false);

	wstring ImageFile = L"./Images/Boss/BridgeAll.png";
	wstring shaderFile = L"./Shader/HLSL/Texture.hlsl";

	m_pTexture[0] = new Texture(ImageFile, shaderFile);
	m_pTexture[0]->SetPosition(0.0f, 100.0f);

	ImageFile = L"./Images/Boss/BridgeALL.png";
	m_pTexture[1] = new Texture(ImageFile, shaderFile);


	Vector2 size  = m_pTexture[0]->GetTextureRealSize();
	m_pTexture[1]->SetPosition(0.0f, -size.y+100);

	ImageFile = L"./Images/Boss/BridgeALL.png";
	m_pTexture[2] = new Texture(ImageFile, shaderFile);
	m_pTexture[2]->SetPosition(0.0f, -size.y*2 + 100);
}

Bridge::~Bridge()
{
	SAFE_DELETE(m_pTexture[0]);
	SAFE_DELETE(m_pTexture[1]);
	SAFE_DELETE(m_pTexture[2]);
}

void Bridge::Update(Matrix V, Matrix P)
{
	Vector2 position = GetPosition();

	Helltaker *pObject = dynamic_cast<Helltaker*>(OBJMANAGER->FindObject("Helltaker"));

	POINT pt = HTMAP->GetMapXY(pObject->GetPosition());

	if (m_bMove)
	{
		// 무한배경
		m_pTexture[0]->SetPosition(0.0f,
			m_pTexture[0]->GetPosition().y + 1.5f);
		m_pTexture[1]->SetPosition(0.0f,
			m_pTexture[1]->GetPosition().y + 1.5f);

		m_pTexture[2]->SetPosition(0.0f,
			m_pTexture[2]->GetPosition().y + 1.5f);

		for (int i = 0; i < 3; i++)
		{
			Vector2 pos = m_pTexture[i]->GetPosition();
			Vector2 size = m_pTexture[i]->GetTextureRealSize();

			if (pos.y >= 0)
			{
				if (i == 0)
				{
					m_pTexture[1]->SetPosition(0.0f,
						m_pTexture[0]->GetPosition().y - 600.0f);
					m_pTexture[2]->SetPosition(0.0f,
						m_pTexture[1]->GetPosition().y - 600.0f);
				}
				if (i == 1)
				{
					m_pTexture[2]->SetPosition(0.0f,
						m_pTexture[1]->GetPosition().y - 600.0f);
					m_pTexture[0]->SetPosition(0.0f,
						m_pTexture[2]->GetPosition().y - 600.0f);
				}
				if (i == 2)
				{
					m_pTexture[0]->SetPosition(0.0f,
						m_pTexture[2]->GetPosition().y - 600.0f);
					m_pTexture[1]->SetPosition(0.0f,
						m_pTexture[0]->GetPosition().y - 600.0f);
				}
			}

		}	// 무한배경
	}
	

	m_pTexture[0]->Update(V, P);
	m_pTexture[1]->Update(V, P);
	m_pTexture[2]->Update(V, P);
}

void Bridge::Render()
{
	m_pTexture[0]->Render();
	m_pTexture[1]->Render();
	m_pTexture[2]->Render();
}

void Bridge::Reset()
{
	m_Time = 0.0f;
	m_bMove = false;

	m_pTexture[0]->SetPosition(0.0f, 100.0f);
	Vector2 size = m_pTexture[0]->GetTextureRealSize();
	m_pTexture[1]->SetPosition(0.0f, -size.y + 100);
	m_pTexture[2]->SetPosition(0.0f, -size.y * 2 + 100);
}

void Bridge::SetMove(bool value)
{
	if (value == true)
	{
		if (m_fpCallback)
			m_fpCallback();
	}
	m_bMove = value;
	m_Time = 0.0f; 

}

float Bridge::Gap()
{
	Vector2 pos1 = m_pTexture[0]->GetPosition();
	Vector2 pos2 = m_pTexture[1]->GetPosition();
	Vector2 pos3 = m_pTexture[2]->GetPosition();

	pos1.y = pos1.y + 210.0f;
	pos2.y = pos2.y + 210.0f;
	pos3.y = pos3.y + 210.0f;

	float min = FLT_MAX;

	min = fabs(pos1.y - 542);
	if(fabs(pos2.y - 542) < min)
		min = fabs(pos2.y - 542);
	if (fabs(pos3.y - 542) < min)
		min = fabs(pos3.y - 542);
	return min;
}


