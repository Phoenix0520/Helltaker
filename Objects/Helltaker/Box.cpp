#include "framework.h"
#include "HelltakerMap.h"
#include "Box.h"

Box::Box()
{
	textureID = rand() % 8;

	mt19937 engine((unsigned int)time(NULL));
	uniform_int_distribution<int> distribution(0, 2);
	auto generator = bind(distribution, engine);

	soundID = generator();


	wstring imageFile1 = L"./Images/Box.png";
	wstring shaderFile = L"./Shader/HLSL/Texture.hlsl";
	
	texture = new Texture(imageFile1, shaderFile);
}

Box::~Box()
{
	SAFE_DELETE(texture);
}

void Box::Update(Matrix V, Matrix P)
{
	Vector2 offset = Vector2(textureID * 100.0f, 10.0f);
	Vector2 offsetSize = Vector2(100.0f, 100.0f);

	Vector2 position = GetPosition();
	position.y -= 19.5f;

	texture->SetOffset(offset);
	texture->SetOffsetSize(offsetSize);
	texture->SetPosition(position);
	texture->Update(V, P);
}

void Box::Render()
{
	texture->Render();
}

void Box::Reset()
{
	if (textureID >= 8)
		textureID = rand() % 8;

}

void Box::MoveObject(Direction direction, Vector2 & position)
{
	POINT pt = HTMAP->GetMapXY(position);
	POINT oldpt = pt;

	switch (direction)
	{
	case GameObject::right:
		pt.x += 1;
		break;
	case GameObject::left:
		pt.x -= 1;
		break;
	case GameObject::up:
		pt.y -= 1;
		break;
	case GameObject::down:
		pt.y += 1;
		break;
	}

	mt19937 engine((unsigned int)time(NULL));
	uniform_int_distribution<int> distribution(1, 3);
	auto generator = bind(distribution, engine);

	soundID = generator();

	string str = "BOXKICK" + to_string(soundID);

	if (!ISPLAYING(str))
		PLAYSOUND(str, sfxSize);

	if (HTMAP->IsWall(pt.x, pt.y))
		return;
	else if (HTMAP->IsMob(pt.x, pt.y))
		return;
	else if (HTMAP->IsBox(pt.x, pt.y))
		return;
	else if (HTMAP->IsGoal(pt.x, pt.y))
		return;
	else
	{
		soundID = generator();

		string str = "BOXMOVE" + to_string(soundID);

		if (!ISPLAYING(str))
			PLAYSOUND(str, sfxSize);
	
		// 움직일수 있는 경우
		HTMAP->ReSetValue(oldpt.x, oldpt.y, HTMAP->box);
		HTMAP->SetValue(pt.x, pt.y, HTMAP->box, this);

		Vector2 pos = HTMAP->GetPosition(pt.x, pt.y);
		SetPosition(pos);

		return;
	}
}
