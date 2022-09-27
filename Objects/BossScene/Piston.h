#pragma once

class Piston : public GameObject
{
public:
	Piston(float time);
	~Piston();

public:
	void Update(Matrix V, Matrix P);
	void Render();
	void Reset();

private:
	class Animation* uprPiston[2];
	class Animation* udrPiston[2];

	float time = 0.0f;
	float endTime = 0.0f;

};