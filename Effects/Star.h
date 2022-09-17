#pragma once

class Star : public GameObject
{
public:
	Star();
	~Star();

public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;

	int  GetState() { return state; }

private:
	class Texture*	 star[12];

	int state = 0;

	Vector2 sPos[12];
	float sc[10];
	float val = 1.0f;
};