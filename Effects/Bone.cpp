#include "framework.h"
#include "Bone.h"

Bone::Bone(int textureID, int angleID)
{
	state = textureID;
	this->angleID = angleID;
	wstring imageFile1 = L"./Images/Effects/Bone.png";
	wstring shaderFile = L"./Shader/HLSL/Texture.hlsl";

	texture = new Texture(imageFile1, shaderFile);	// 40 24

	SetActive(false);

	state = 0;
}

Bone::~Bone()
{
	SAFE_DELETE(texture);
}

void Bone::Update(Matrix V, Matrix P)
{
	Vector2 position = GetPosition();

	float roll = TIMEMANAGER->GetRunning() * 900.0f;
	SetRotation(0.0f, 0.0f, roll);
	float angle[] = { 0.65f, -0.47f, -0.87f, -0.28f, 0.73f, -0.95f, 0.37f, 0.68f, -0.53f, 0.72f };

	if (IsActive() == false)
		return;

	Vector2 position2 = Vector2(0.0f, (float)MAIN->GetHeight());
	CAMERA->WCToVC(position2);

	position2.y -= 200.0f;

	if (position.y < position2.y)
	{
		gravity = 0.0f;
		SetActive(false);
		return;
	}

	if (angle[angleID] < 0)
		position.x -= cosf(angle[angleID]) * 7.0f;
	else
		position.x += cosf(angle[angleID]) * 7.0f;

	position.y += sinf(0.95f) * 9.0f - gravity;

	gravity += 0.475f;//* TIMEMANAGER->GetRunning();

	SetPosition(position);

	// state 0 0
	// state 1 40
	// state 2 80

	texture->SetOffset(state * 40.0f, 0.0f);
	texture->SetOffsetSize(40.0f, 24.0f);

	texture->SetScale(scale);
	texture->SetPosition(position);
	texture->SetRotation(rotation);

	texture->Update(V, P);
}

void Bone::Render()
{
	if (IsActive())
		texture->Render();
}

void Bone::Reset()
{
	SetRotation(0.0f, 0.0f, 0.0f);
	gravity = 0.0f;
}

void Bone::Random()
{
	/*while (1)
	{
		int id = rand() % 2;
		if (id == state) continue;

		state = id;

		break;
	}*/
	/*while (1)
	{
		int id = rand() % 10;

		angleID = id;

		break;
	}*/
}

bool Bone::IsPlay()
{
	return true; //texture->IsPlay();
}
