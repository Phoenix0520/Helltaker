#include "framework.h"
#include "HelltakerMap.h"
#include "ChainDaigonal.h"
#include "Animation.h"
#include "AnimationClip.h"
#include "Helltaker.h"
#include "Collider.h"


//////////////////////////////////////////
//
ChainDaigonal::ChainDaigonal()
{
	this->SetActive(false);

	wstring ImageFile = L"./Images/Boss/ChainVH.png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	m_Texture      = new Texture(ImageFile, shaderFile);
	ImageFile = L"./Images/Boss/Chain25Broken.png";
	m_TextureBroken = new Texture(ImageFile, shaderFile);
	
	
	collider = new Collider();


	MovePosition[0] = Vector2(-638.0f, 542.0f);
	MovePosition[1] = Vector2(-638.0f, 350.0f);
	MovePosition[2] = Vector2(-638.0f, 160.0f);
	MovePosition[3] = Vector2( 638.0f, 542.0f);
	MovePosition[4] = Vector2( 638.0f, 350.0f);
	MovePosition[5] = Vector2( 638.0f, 160.0f);



	MoveRotation[0] = Vector3(0.0f, 0.0f, 25.0f);
	MoveRotation[1] = Vector3(0.0f, 0.0f, 25.0f);
	MoveRotation[2] = Vector3(0.0f, 0.0f, 25.0f);
	MoveRotation[3] = Vector3(0.0f, 180.0f, 25.0f);
	MoveRotation[4] = Vector3(0.0f, 180.0f, 25.0f);
	MoveRotation[5] = Vector3(0.0f, 180.0f, 25.0f);





}

ChainDaigonal::~ChainDaigonal()
{
	SAFE_DELETE(m_Texture);
}
void ChainDaigonal::Update(Matrix V, Matrix P)
{
	if (!IsActive()) return;

	m_BrokenTime = m_BrokenTime - TIMEMANAGER->Delta();
	if (m_BrokenTime < 0.0f)
	{
		m_BrokenTime = 0.0f;
		m_BrokenMove = 0.0f;
		if (m_cvDisplay.size() == 0)
			m_bSuccess = true;
	}
	else
		m_BrokenMove = m_BrokenMove + 40.0f*3.141592f*m_BrokenMove;

	m_EffectTime = m_EffectTime - TIMEMANAGER->Delta();
	if (m_EffectTime < 0.0f)
	{
		m_EffectMove = 0.0f;
		m_EffectTime = 0.0f;
		m_EffectID = -1;
	}
	else
		m_EffectMove = m_EffectMove + 2.0f*3.141592f*m_EffectTime;

	Color color = Color(1.0f, 1.0f, 1.0f, 0.5f);
	
	m_Texture->UpdateColorBuffer(color, 11);
	m_Texture->SetPosition(GetPosition());
	m_Texture->SetScale(GetScale());
	m_Texture->SetRotation(GetRotation());
	m_Texture->Update(V, P);

	m_TextureBroken->UpdateColorBuffer(color, 11);
	m_TextureBroken->SetPosition(GetPosition());
	m_TextureBroken->SetScale(GetScale());
	m_TextureBroken->SetRotation(GetRotation());
	m_TextureBroken->Update(V, P);

}

void ChainDaigonal::Render()
{
	if (!IsActive())
		return;


	Matrix V, P;

	V = CAMERA->GetViewMatrix();
	P = CAMERA->GetProjMatrix();


	for (UINT i = 0; i < m_cvDisplay.size(); i++)
	{
		if (m_EffectID == m_cvDisplay[i])
		{
			m_Texture->UpdateColorBuffer(0);
			m_Texture->SetPosition(MovePosition[m_cvDisplay[i]].x,
				MovePosition[m_cvDisplay[i]].y + m_EffectMove + m_Gap);
		}
		else
		{
			Color color = Color(1.0f, 1.0f, 1.0f, 0.5f);
			m_Texture->UpdateColorBuffer(color, 11);
			m_Texture->SetPosition(MovePosition[m_cvDisplay[i]].x,
				MovePosition[m_cvDisplay[i]].y + m_Gap);
		}
		  
		m_Texture->SetRotation(MoveRotation[m_cvDisplay[i]]);
		m_Texture->Update(V, P);
		m_Texture->Render();

		if (m_EffectID == m_cvDisplay[i])
			collider->SetPosition(MovePosition[m_cvDisplay[i]].x,
				MovePosition[m_cvDisplay[i]].y + m_EffectMove);
		else
			collider->SetPosition(MovePosition[m_cvDisplay[i]]);
		collider->SetRotation(MoveRotation[m_cvDisplay[i]]);
		collider->SetScale(m_Texture->GetTextureRealSize());
		collider->Update(V, P);
		collider->Render();
	}

	if (m_BrokenTime > 0.0f)
	{
		m_TextureBroken->SetPosition(MovePosition[m_BrokenID].x,
			MovePosition[m_BrokenID].y + m_BrokenMove);
		m_TextureBroken->SetRotation(MoveRotation[m_BrokenID]);
		m_TextureBroken->Update(V, P);
		m_TextureBroken->Render();
	}

}

void ChainDaigonal::Reset()
{
	SetActive(false);
	m_bSuccess = false;
}

void ChainDaigonal::SetState(int value)
{
	m_cvDisplay.erase(m_cvDisplay.begin(), m_cvDisplay.end());
	m_cvDisplay.shrink_to_fit();

	for (int i = 0; i < 6; i++)
		Count[i] = 0;
	
	if ((value & 0x100000) == 0x100000)             // 1001000
	{
		m_cvDisplay.push_back(0);
		Count[0] = 6;
		HTMAP->SetValue(0, 1, HTMAPSTATE::daigonal, this);
	}
		
	if ((value & 0x010000) == 0x010000)
	{
		m_cvDisplay.push_back(1);
		Count[1] = 6;
		HTMAP->SetValue(0, 3, HTMAPSTATE::daigonal, this);
	}
	if ((value & 0x001000) == 0x001000)
	{
		Count[2] = 6;
		HTMAP->SetValue(0, 5, HTMAPSTATE::daigonal, this);
		m_cvDisplay.push_back(2);
	}
		
	if ((value & 0x000100) == 0x000100)
	{
		Count[3] = 6;
		HTMAP->SetValue(8, 1, HTMAPSTATE::daigonal, this);
		m_cvDisplay.push_back(3);

	}
		
	if ((value & 0x000010) == 0x000010)
	{
		Count[4] = 6;
		HTMAP->SetValue(8, 3, HTMAPSTATE::daigonal, this);
		m_cvDisplay.push_back(4);

	}
	if ((value & 0x000001) == 0x000001)
	{
		Count[5] = 6;
		HTMAP->SetValue(8, 5, HTMAPSTATE::daigonal, this);
		m_cvDisplay.push_back(5);
	}
		
}

void ChainDaigonal::SetHP(int x, int y)
{
	if (x == 0 && y == 1)
		ResetValue(0, 0, 1);
	if (x == 0 && y == 3)
		ResetValue(1, 0, 3);
	if (x == 0 && y == 5)
		ResetValue(2, 0, 5);
	if (x == 8 && y == 1)
		ResetValue(3, 8, 1);
	if (x == 8 && y == 3)
		ResetValue(4, 8, 3);
	if (x == 8 && y == 5)
		ResetValue(5, 8, 5);
}

void ChainDaigonal::ResetValue(int id, int x, int y)
{
	Count[id]--;
	if (Count[id] > 0)
	{
		m_EffectTime = 0.3f;
		m_EffectID = id;
		m_EffectMove = 0.0f;
		return;
	}
		
		
	for (UINT i = 0; i < m_cvDisplay.size(); i++)
	{
		if (m_cvDisplay[i] != id)
			continue;
		m_cvDisplay.erase(m_cvDisplay.begin() + i, m_cvDisplay.begin() + i + 1);
		m_cvDisplay.shrink_to_fit();
	}
	m_BrokenTime = 0.3f;
	m_BrokenID = id;
	m_BrokenMove = 0.0f;

	HTMAP->ReSetValue(x, y, HTMAPSTATE::daigonal);
}

