#pragma once

class Clear : public GameObject
{
public:
	Clear();
	~Clear();

public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;

	void Random();

	bool IsPlay();
	int  GetState() { return state; }

private:
	class Animation* animation = nullptr;
	class Texture*	 heart[10];
	class Texture*	 star[10];

	int state = 0;

	Vector2 hPos[10];
	Vector2 sPos[10];

	float sc[10];
	float val = 0.0f;
};