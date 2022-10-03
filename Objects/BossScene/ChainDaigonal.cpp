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

	wstring imageFile1 = L"./Images/Boss/ChainVH.png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	texture = new Texture(imageFile1, shaderFile);

	collider = new Collider();
}

ChainDaigonal::~ChainDaigonal()
{
	SAFE_DELETE(texture);
}

void ChainDaigonal::Update(Matrix V, Matrix P)
{
	
}

void ChainDaigonal::Render()
{
	
}

void ChainDaigonal::Reset()
{
	
}
