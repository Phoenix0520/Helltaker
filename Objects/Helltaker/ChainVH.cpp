#include "framework.h"
#include "ChainVH.h"
#include "Collider.h"
#include "Animation.h"
#include "AnimationClip.h"
#include "Helltaker.h"

//////////////////////////////////////////
//
ChainVH::ChainVH()
{
	this->SetActive(true);

	wstring ImageFile = L"./Images/Boss/ChainAll3.png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	m_Texture = new Texture(ImageFile, shaderFile);
	m_Texture->SetScale(0.4f,0.4f);
	collider = new Collider();
}

ChainVH::~ChainVH()
{
	SAFE_DELETE(m_Texture);
}

void ChainVH::Update(Matrix V, Matrix P)
{
	Vector2 Position[12];

	Position[0] = Vector2(-300.0f, 0.0f);
	Position[1] = Vector2(-200.0f, 0.0f);
	Position[2] = Vector2(-100.0f, 0.0f);
	Position[3] = Vector2(0.0f, 0.0f);
	Position[4] = Vector2(100.0f, 0.0f);
	Position[5] = Vector2(200.0f, 0.0f);
	Position[6] = Vector2(300.0f, 0.0f);
	Position[7] = Vector2(0.0f, 110.0f);
	Position[8] = Vector2(0.0f, 10.0f);
	Position[9] = Vector2(0.0f, -90.0f);
	Position[10] = Vector2(0.0f, -190.0f);
	Position[11] = Vector2(0.0f, -290.0f);




	Vector2 position = GetPosition();
	m_Angle = 0.0f;
	
	m_Time = m_Time + TIMEMANAGER->Delta();
	if (m_Time > 0.01f && m_Time < 0.1f)
		m_Angle = 0.0f;
	else if (m_Time >= 0.1f && m_Time < 0.2f)
		m_Angle = 40.0f;
	else if (m_Time >= 0.2f && m_Time < 0.3f)
		m_Angle = 80.0f;
	else if (m_Time >= 0.3f && m_Time < 0.4f)
		m_Angle = 120.0f;
	else if (m_Time >= 0.4f && m_Time < 0.5f)
		m_Angle = 160.0f;
	else
		;
	
	if (m_Time > 0.5f)
	{
		m_Time = 0.0f;
	//	m_nState++;
	}


	Color color(193/255.0f, 99/255.0f, 115/255.0f, 0.8f);
	if (m_nState == 1)
		color = Color(1.0f, 1.0f, 1.0f, 0.8f);

	m_Texture->UpdateColorBuffer(color, 4, 0, 0, 0);
	m_Texture->SetRotation(m_Angle, 0.0f, 0.0f);
	m_Texture->Update(V, P);

	if (!IsActive()) return;


	// Collider

	Helltaker *pHelltaker = (Helltaker*)OBJMANAGER->FindObject("Helltaker");


	if (m_nState == 1 && pHelltaker->IsAttacted() == false)
	{
		for (UINT i = 0; i < m_cvDisplay.size(); i++)
		{
			collider->SetPosition(Position[m_cvDisplay[i]]);
			if (m_cvAngle[i] == 1)
				collider->SetRotation(m_Angle, 0.0f, 90.0f);  
			else
				collider->SetRotation(0.0f, m_Angle, 0.0f);

				
			collider->SetScale(m_Texture->GetTextureRealSize());
			collider->Update(V, P);

			pHelltaker->GetCollider()->SetCollisionCheck(false);  // 색상
			collider->SetCollisionCheck(false);

			// collision check
			if (Collider::InterSect(pHelltaker->GetCollider(), collider))
			{
				pHelltaker->GetCollider()->SetCollisionCheck(true); // 색상(빨강)
				collider->SetCollisionCheck(true);
				pHelltaker->SetHuge();

				if(!pHelltaker->GetImmune())
				   pHelltaker->SetHP(pHelltaker->GetHP() - 1);
			}

		}
	}
	
}

void ChainVH::Render()
{
	if (!IsActive())
		return;

	Vector2 Position[12];

	Position[0] = Vector2(-300.0f, 0.0f);
	Position[1] = Vector2(-200.0f, 0.0f);
	Position[2] = Vector2(-100.0f, 0.0f);
	Position[3] = Vector2(0.0f, 0.0f);
	Position[4] = Vector2(100.0f, 0.0f);
	Position[5] = Vector2(200.0f, 0.0f);
	Position[6] = Vector2(300.0f, 0.0f);
	Position[7] = Vector2(0.0f, 110.0f);
	Position[8] = Vector2(0.0f, 10.0f);
	Position[9] = Vector2(0.0f, -90.0f);
	Position[10] = Vector2(0.0f, -190.0f);
	Position[11] = Vector2(0.0f, -290.0f);



	Matrix V, P;

	V = CAMERA->GetViewMatrix();
	P = CAMERA->GetProjMatrix();

	for (UINT i = 0; i < m_cvDisplay.size(); i++)
	{
		m_Texture->SetPosition(Position[m_cvDisplay[i]]);
		if (m_cvAngle[i] == 1)
			m_Texture->SetRotation(m_Angle, 0.0f, 90.0f);
		else
			m_Texture->SetRotation(0.0f, m_Angle, 0.0f);

		m_Texture->Update(V, P);
		m_Texture->Render();


		collider->SetPosition(Position[m_cvDisplay[i]]);
		if (m_cvAngle[i] == 1)
			collider->SetRotation(m_Angle, 0.0f, 90.0f);
		else
			collider->SetRotation(0.0f, m_Angle, 0.0f);
		collider->SetScale(m_Texture->GetTextureRealSize());
		collider->Update(V, P);
		collider->Render();
	}

}

void ChainVH::Reset()
{
	SetActive(false);
}

void ChainVH::SetValue(int value, int horiz)
{

	m_cvDisplay.erase(m_cvDisplay.begin(), m_cvDisplay.end());
	m_cvDisplay.shrink_to_fit();
	m_cvAngle.erase(m_cvAngle.begin(), m_cvAngle.end());
	m_cvAngle.shrink_to_fit();


	if ((value & 0x1000000) == 0x1000000)
	{// 1001000
		m_cvDisplay.push_back(0);
		m_cvAngle.push_back(0);

	}
	if ((value & 0x0100000) == 0x0100000)
	{
		m_cvDisplay.push_back(1);
		m_cvAngle.push_back(0);

	}

	if ((value & 0x0010000) == 0x0010000)
	{
		m_cvDisplay.push_back(2);
		m_cvAngle.push_back(0);
	}

	if ((value & 0x0001000) == 0x0001000)
	{
		m_cvDisplay.push_back(3);
		m_cvAngle.push_back(0);
	}
	
	if ((value & 0x0000100) == 0x0000100)
	{
		m_cvDisplay.push_back(4);
		m_cvAngle.push_back(0);
	}
	
	if ((value & 0x0000010) == 0x0000010)
	{
		m_cvDisplay.push_back(5);
		m_cvAngle.push_back(0);
	}
	
	if ((value & 0x0000001) == 0x0000001)
	{
		m_cvDisplay.push_back(6);
		m_cvAngle.push_back(0);
	}

	///////////////////////////////////////////////////


	if ((horiz & 0x10000) == 0x10000)
	{
		m_cvDisplay.push_back(7);
		m_cvAngle.push_back(1);
	}

	if ((horiz & 0x01000) == 0x01000)
	{
		m_cvDisplay.push_back(8);
		m_cvAngle.push_back(1);
	}
	if ((horiz & 0x00100) == 0x00100)
	{
		m_cvDisplay.push_back(9);
		m_cvAngle.push_back(1);
	}

	if ((horiz & 0x00010) == 0x00010)
	{
		m_cvDisplay.push_back(10);
		m_cvAngle.push_back(1);
	}
	if ((horiz & 0x00001) == 0x00001)
	{
		m_cvDisplay.push_back(11);
		m_cvAngle.push_back(1);
	}

}





