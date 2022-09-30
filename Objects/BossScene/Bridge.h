#pragma once

class Bridge : public GameObject
{
public:
	Bridge();
	~Bridge();

public:
	void Update(Matrix V, Matrix P);
	void Render();
	void Reset();

	void SetMove(bool val) { move = val; }
	float GetMoveVal() { return moveVal; }

private:
	vector<class Texture*> texture;
	class Texture* effect = nullptr;

	bool move = false;

	float moveVal = 0.0f;
	float time = 0.0f;
};