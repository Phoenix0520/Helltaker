#include "framework.h"
#include "Bridge.h"

Bridge::Bridge()
{
	wstring imageFile1 = L"./Images/Boss/BridgeAll.png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	texture.push_back(new Texture(imageFile1, shaderFile));
	texture.push_back(new Texture(imageFile1, shaderFile));
	texture.push_back(new Texture(imageFile1, shaderFile));

	float x = texture[0]->GetTextureRealSize().x;

	texture[0]->SetPosition(0.0f, 0.0f);
	texture[0]->SetPosition(0.0f, -x);
	texture[0]->SetPosition(0.0f, -x * 2);
}

Bridge::~Bridge()
{
	for (UINT i = 0; i < texture.size(); i++)
	{
		SAFE_DELETE(texture[i]);
	}
}

void Bridge::Update(Matrix V, Matrix P)
{
	for (UINT i = 0; i < texture.size(); i++)
	{
		if (move)
		{
			float y = texture[i]->GetPosition().y + 3.0f;
			texture[i]->SetPosition(0.0f, y);
		}

		texture[i]->Update(V, P);
	}
}

void Bridge::Render()
{
	for (UINT i = 0; i < texture.size(); i++)
		texture[i]->Render();
}

void Bridge::Reset()
{
}
