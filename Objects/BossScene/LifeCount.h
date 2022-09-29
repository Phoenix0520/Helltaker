#pragma once

class LifeCount : public GameObject
{
public:
	LifeCount();
	~LifeCount();

public:
	void Update(Matrix V, Matrix P);
	void Render();
	void Reset();

	void DiscardLife();
	bool IsDead() { return !life[3]; }
	

private:
	vector<class Texture*>		texture;
	Animation*	fire[4];

	bool life[4];
};