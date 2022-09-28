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
	
	if (move)
	{
		if (moveVal < 3.0f)
			moveVal += DELTA * 2.0f;
	}
	else
	{
		if (moveVal > 0.0f)
			moveVal -= DELTA * 2.0f;
	}

	for (UINT i = 0; i < 3; i++)
	{
		float y = texture[i]->GetPosition().y + moveVal;
		texture[i]->SetPosition(x, y);

		if (rotation == Vector3(0.0f, 180.0f, 0.0f))
			texture[i]->SetRotation(0.0f, 0.0f, 0.0f);
		else
			texture[i]->SetRotation(0.0f, 180.0f, 0.0f);

		Vector2 size = texture[0]->GetTextureRealSize();
		if (texture[i]->GetPosition().y > size.y + 540.0f)
		{
			size.y -= 3.0f;
			Vector2 pos;

			switch (i)
			{
			case 0:
				pos = texture[2]->GetPosition();
				texture[i]->SetPosition(pos.x, pos.y - size.y);
				break;
			case 1:
				pos = texture[0]->GetPosition();
				texture[i]->SetPosition(pos.x, pos.y - size.y);
				break;
			case 2:
				pos = texture[1]->GetPosition();
				texture[i]->SetPosition(pos.x, pos.y - size.y);
				break;
			}
		}

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


