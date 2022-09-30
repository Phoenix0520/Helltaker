#pragma once

class ChainVH : public GameObject
{
public:
	ChainVH();
	~ChainVH();

public:
	enum Angle
	{
		VERTICAL = 0,
		HORIZONTAL
	};

public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;

	void SetPosByXY(int x, int y) { pos = Vector2(0.0f, 0.0f); }
	void SetVertical() { angle = VERTICAL; }
	void SetHorizontal() { angle = HORIZONTAL; }

	UINT GetAngle() { return (UINT)angle; }
	bool IsAttacking() { return attacking; }

private:
	class Texture* texture = nullptr;

	Vector2 pos = Vector2(0.0f, 0.0f);

	Angle angle = VERTICAL;
	
	bool attacking = false;
	float time = 0.0f;

};
