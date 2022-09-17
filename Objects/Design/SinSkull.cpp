#include "framework.h"
#include "SinSkull.h"
#include "Animation.h"
#include "AnimationClip.h"
#include "Chain.h"
#include "Bridge.h"

//////////////////////////////////////////
//
SinSkull::SinSkull()
{
	this->SetActive(false);

	wstring ImageFile = L"./Images/Boss/SinSkull.png";
	wstring shaderFile = L"./Shader/HLSL/Texture.hlsl";

	ImageFile = L"./Images/Boss/SinArm.png";
	m_pTexture[0] = new Texture(ImageFile, shaderFile);

	ImageFile = L"./Images/Boss/SinSkull.png";
	m_pTexture[1] = new Texture(ImageFile, shaderFile);

	ImageFile = L"./Images/Boss/SinSkull2.png";
	m_pTexture[2] = new Texture(ImageFile, shaderFile);


}

SinSkull::~SinSkull()
{
	SAFE_DELETE(m_pTexture[0]);
	SAFE_DELETE(m_pTexture[1]);
}
void SinSkull::Update(Matrix V, Matrix P)
{
	Vector2 position = GetPosition();
	float   gap = -220.0f;

	m_pTexture[0]->Update(V, P);
	m_pTexture[1]->Update(V, P);
	m_pTexture[2]->Update(V, P);
}

void SinSkull::Render()
{
	Matrix V, P;
	V = CAMERA->GetViewMatrix();
	P = CAMERA->GetProjMatrix();

	Vector2 position = GetPosition();
	float   gap = -220.0f;

	// Timer를 이용하여 
    // 상하 움직이게
	m_Time = m_Time + TIMEMANAGER->Delta();

	switch (m_nStep)
		{
			case 1:  // 올라가는 것
			position.y += 125.0f * DELTA;
			if (m_MaxHeight <= position.y)
			{
				m_nStep = 0;
				position.y = m_MaxHeight;
				Chain* pChain = (Chain*)OBJMANAGER->FindObject("Chain");
				pChain->SetMove(true);

				Bridge* pBridge = (Bridge*)OBJMANAGER->FindObject("Bridge");
				pBridge->SetMove(true);
			}
			break;
		   case 2:   // 내려오는 경우
			    position.y -= 125.0f * DELTA;
				if (m_MinHeight >= position.y)
				{
					m_nStep++;
					position.y = m_MinHeight;

				}
			    break;
		}



	if (m_nState == 0)
	{
		// 좌측

		m_pTexture[0]->SetRotation(0.0f, 0.0f, 0.0f);
		m_pTexture[0]->SetPosition(position);
		m_pTexture[0]->Update(V, P);

		m_pTexture[1]->SetRotation(0.0f, 0.0f, 0.0f);
		m_pTexture[1]->SetPosition(position.x - 220.0f, position.y + 10.0f);
		m_pTexture[1]->Update(V, P);

		m_pTexture[0]->Render();
		m_pTexture[1]->Render();

		// 우측
		m_pTexture[0]->SetRotation(0.0f, 180.0f, 0.0f);
		m_pTexture[0]->SetPosition(position.x + 1236.0f, position.y);
		m_pTexture[0]->Update(V, P);

		m_pTexture[1]->SetRotation(0.0f, 180.0f, 0.0f);
		gap = 220.0f;
		m_pTexture[1]->SetPosition(position.x + 1267.0f + 220.0f, position.y + 10.0f);
		m_pTexture[1]->Update(V, P);

		m_pTexture[0]->Render();
		m_pTexture[1]->Render();
	}
	else
	{
		// 좌측
		m_pTexture[2]->SetPosition(position.x - 220.0f, position.y + 10.0f);
		m_pTexture[2]->Update(V, P);
		m_pTexture[2]->Render();

		// 우측
		m_pTexture[2]->SetPosition(position.x + 1267.0f + 220.0f, position.y);
		m_pTexture[2]->Update(V, P);
		m_pTexture[2]->Render();

	}

	SetPosition(position);

}

void SinSkull::Reset()
{
	m_Time = 0.0f;
	m_nStep = 0;


}


