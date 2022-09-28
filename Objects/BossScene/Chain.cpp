#include "framework.h"
#include "Chain.h"
#include "Animation.h"
#include "AnimationClip.h"

//////////////////////////////////////////
//
Chain::Chain(float x)
{
	wstring imageFile1 = L"./Images/Boss/ChainAll.png";
	wstring shaderFile = L"./Shader/HLSL/Texture.hlsl";

	texture.push_back(new Texture(imageFile1, shaderFile));
	texture.push_back(new Texture(imageFile1, shaderFile));
	texture.push_back(new Texture(imageFile1, shaderFile));

	this->x = x;


	for (UINT i = 0; i < 3; i++)
		texture[i]->SetScale(0.75f, 0.75f);

	float y = texture[0]->GetTextureRealSize().y;

	texture[0]->SetPosition(x, 0.0f);
	texture[1]->SetPosition(x, -y);
	texture[2]->SetPosition(x, -y * 2);
}

Chain::~Chain()
{
	for (UINT i = 0; i < 3; i++)
		SAFE_DELETE(texture[i]);
}

void Chain::Update(Matrix V, Matrix P)
{
	float y[3];
	
	for (UINT i = 0; i < 3; i++)
	{
		if (move)
		{
			float y = texture[i]->GetPosition().y + 3.0f;
			texture[i]->SetPosition(x, y);
		}

		if (rotation == Vector3(0.0f, 180.0f, 0.0f))
			texture[i]->SetRotation(0.0f, 0.0f, 0.0f);
		else
			texture[i]->SetRotation(0.0f, 180.0f, 0.0f);

		texture[i]->Update(V, P);
	}
}

void Chain::Render()
{
	for (UINT i = 0; i < 3; i++)
		texture[i]->Render();
}

void Chain::Reset()
{

}


