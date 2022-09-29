#include "framework.h"
#include "Bridge.h"

Bridge::Bridge()
{
	wstring imageFile1 = L"./Images/Boss/BridgeAll.png";
	wstring imageFile2 = L"./Images/Boss/Effect.png";
	wstring shaderFile = L"./Shader/HLSL/TextureColor.hlsl";

	texture.push_back(new Texture(imageFile1, shaderFile));
	texture.push_back(new Texture(imageFile1, shaderFile));
	texture.push_back(new Texture(imageFile1, shaderFile));

	float y = texture[0]->GetTextureRealSize().y;

	texture[0]->SetPosition(0.0f, 0.0f);
	texture[1]->SetPosition(0.0f, -y);
	texture[2]->SetPosition(0.0f, -y * 2);

	effect = new Texture(imageFile2, shaderFile);
	effect->SetPosition(0.0f, -20.0f);
	effect->UpdateColorBuffer(Color(0.1f, 0.1f, 0.1f, 0.5f), 13);
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
	if (move)
	{
		if (moveVal < 5.0f)
			moveVal += DELTA * 5.0f;
	}
	else
	{
		if (moveVal > 0.0f)
			moveVal -= DELTA * 2.5f;
		else
			moveVal = 0.0f;
	}

	for (UINT i = 0; i < texture.size(); i++)
	{
		float y = texture[i]->GetPosition().y + moveVal;
		texture[i]->SetPosition(0.0f, y);

		if (texture[i]->GetPosition().y > 540.0f)
		{
			Vector2 size = texture[0]->GetTextureRealSize();
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
		effect->Update(V, P);
	}
}

void Bridge::Render()
{
	for (UINT i = 0; i < texture.size(); i++)
	{
		texture[i]->Render();
	}

	static bool gim = true;

	if (DOWN('Q'))
		gim = true;
	if (DOWN('W'))
		gim = false;

	if (gim)
		effect->Render();
}

void Bridge::Reset()
{
}
