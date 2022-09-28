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

private:
	vector<class Texture*> texture;
	
	float time = 0.0f;

	bool move = false;
};