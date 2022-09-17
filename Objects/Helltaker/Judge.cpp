#include "framework.h"
#include "Judge.h"
#include "Animation.h"
#include "AnimationClip.h"

/////////////////////////////////////////////////////////
//  1. Bride  Stop 시키는 것
//  2. 헬테이커 움직이고 있을때 ChainDaigonal 보이게 되는 Bug
//  3. A-Star
////////////////////////////////////////////////////////


//////////////////////////////////////////
//
Judge::Judge()
{
	this->SetActive(false);

	wstring ImageFile = L"./Images/Boss/Judgement/Judge_jump (1).png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";


	m_pAnimation = new Animation(ImageFile, shaderFile);

	{
		AnimationClip *pClip = new AnimationClip(AnimationClip::end);
		m_pAnimation->AddClip(pClip);

		for (int i = 1; i <= 8; i++)
		{
			wstring str = L"./Images/Boss/Judgement/Judge_jump (" + to_wstring(i) + L").png";
			pClip->AddFrame(m_pAnimation->GetTexture(), str, 0, 0, 100, 260, 0.1f);
		}
		wstring str = L"./Images/Boss/Judgement/Judge_jump (" + to_wstring(9) + L").png";
		pClip->AddFrame(m_pAnimation->GetTexture(), str, 0, 0, 100, 260, 0.5f);
	}
	
	ImageFile = L"./Images/Effects/Dust.png";	
	shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	m_pDustAnimation = new Animation(ImageFile, shaderFile);

	{
		AnimationClip *pClip = new AnimationClip(AnimationClip::loop);
		m_pDustAnimation->AddClip(pClip);
		float x = 0.0f;
		for (int i = 0; i <= 3; i++)
		{
			pClip->AddFrame(m_pDustAnimation->GetTexture(), ImageFile, x, 0, x + 100, 100, 0.1f);
			x = x + 100.0f;
		}

	}

}

Judge::~Judge()
{
	SAFE_DELETE(m_pAnimation);
}
void Judge::Update(Matrix V, Matrix P)
{
	Vector2 position = GetPosition();

	m_pAnimation->SetPosition(position);
	m_pAnimation->SetScale(scale);
	m_pAnimation->SetRotation(rotation);
	m_pAnimation->Update(V, P);

	Color  color = Color(1.0f, 150.0f / 255.0f, 165.0f / 255.0f, 0.0f);
	m_pDustAnimation->GetTexture()->UpdateColorBuffer(color, 1, 0.0f, 0.0f, 0.0f);
	m_pDustAnimation->SetPosition(position.x, position.y -45.0f);
	m_pDustAnimation->SetScale(1.0f,1.0f);
	m_pDustAnimation->SetRotation(rotation);
	m_pDustAnimation->Update(V, P);


}

void Judge::Render()
{
	if (!IsActive())
		return;
	m_pAnimation->Render();
	if(m_pAnimation->IsPlay())
		m_pDustAnimation->Render();
}

void Judge::Reset()
{
	SetActive(true);
	m_pAnimation->SetStop();
	m_pDustAnimation->SetStop();
	m_pAnimation->SetPlay((UINT)0);
}

bool Judge::IsPlay()
{
	 return m_pAnimation->IsPlay(); 
}

