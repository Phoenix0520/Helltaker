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
	wstring imageFile1 = L"./Images/Boss/ChainVH.png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	texture = new Texture(imageFile1, shaderFile);

	collider = new Collider();

	SetScale(0.4f, 0.4f);
	SetActive(false);
}

ChainVH::~ChainVH()
{
	SAFE_DELETE(texture);
}

void ChainVH::Update(Matrix V, Matrix P)
{
	time += DELTA;

	cout << time << endl;

	if (time >= 0.0f && time < 0.5f)
	{
		texture->UpdateColorBuffer(Color(1, 1, 1, 0.5f), 4);

		switch (angle)
		{
		case ChainVH::VERTICAL:
			if (time < 0.3f)
				scale.x += DELTA * 1.0f;
			else
				scale.x -= DELTA * 1.0f;
			break;
		case ChainVH::HORIZONTAL:
			if (time < 0.3f)
				scale.y += DELTA * 1.0f;
			else
				scale.y -= DELTA * 1.0f;
			break;
		}
	}
	else if (time >= 0.5f && time < 1.0f)
	{
		texture->UpdateColorBuffer(Color(1, 1, 1, 1.0f), 4);

		switch (angle)
		{
		case ChainVH::VERTICAL:
			if (time < 0.3f)
				scale.x += DELTA * 1.0f;
			else
				scale.x -= DELTA * 1.0f;
			break;
		case ChainVH::HORIZONTAL:
			if (time < 0.3f)
				scale.y += DELTA * 1.0f;
			else
				scale.y -= DELTA * 1.0f;
			break;
		}

		attacking = true;
	}
	else
		SetActive(false);

	texture->SetPosition(pos);
	texture->SetScale(scale);
	texture->Update(V, P);

	collider->SetPosition(pos);
	collider->SetScale(texture->GetTextureRealSize());
	collider->Update(V, P);
}

void ChainVH::Render()
{
	if (!IsActive())
		return;

	texture->Render();
	collider->Render();
}

void ChainVH::Reset()
{
	SetScale(0.4f, 0.4f);
	time = 0.0f;
	attacking = false;

	SetActive(true);
}

//void ChainVH::SetValue(int value, int horiz)
//{
//	m_cvDisplay.erase(m_cvDisplay.begin(), m_cvDisplay.end());
//	m_cvDisplay.shrink_to_fit();
//	m_cvAngle.erase(m_cvAngle.begin(), m_cvAngle.end());
//	m_cvAngle.shrink_to_fit();
//
//
//	if ((value & 0x1000000) == 0x1000000)
//	{// 1001000
//		m_cvDisplay.push_back(0);
//		m_cvAngle.push_back(0);
//
//	}
//	if ((value & 0x0100000) == 0x0100000)
//	{
//		m_cvDisplay.push_back(1);
//		m_cvAngle.push_back(0);
//
//	}
//
//	if ((value & 0x0010000) == 0x0010000)
//	{
//		m_cvDisplay.push_back(2);
//		m_cvAngle.push_back(0);
//	}
//
//	if ((value & 0x0001000) == 0x0001000)
//	{
//		m_cvDisplay.push_back(3);
//		m_cvAngle.push_back(0);
//	}
//	
//	if ((value & 0x0000100) == 0x0000100)
//	{
//		m_cvDisplay.push_back(4);
//		m_cvAngle.push_back(0);
//	}
//	
//	if ((value & 0x0000010) == 0x0000010)
//	{
//		m_cvDisplay.push_back(5);
//		m_cvAngle.push_back(0);
//	}
//	
//	if ((value & 0x0000001) == 0x0000001)
//	{
//		m_cvDisplay.push_back(6);
//		m_cvAngle.push_back(0);
//	}
//
//	///////////////////////////////////////////////////
//
//
//	if ((horiz & 0x10000) == 0x10000)
//	{
//		m_cvDisplay.push_back(7);
//		m_cvAngle.push_back(1);
//	}
//
//	if ((horiz & 0x01000) == 0x01000)
//	{
//		m_cvDisplay.push_back(8);
//		m_cvAngle.push_back(1);
//	}
//	if ((horiz & 0x00100) == 0x00100)
//	{
//		m_cvDisplay.push_back(9);
//		m_cvAngle.push_back(1);
//	}
//
//	if ((horiz & 0x00010) == 0x00010)
//	{
//		m_cvDisplay.push_back(10);
//		m_cvAngle.push_back(1);
//	}
//	if ((horiz & 0x00001) == 0x00001)
//	{
//		m_cvDisplay.push_back(11);
//		m_cvAngle.push_back(1);
//	}
//
//}





