#pragma once

class BossTrap : public GameObject
{
public:
	BossTrap();
	~BossTrap();

public:
	enum State
	{
		UP,
		DOWN
	};

public:
	void Update(Matrix V, Matrix P);
	void Render();
	void Reset();

private:
	class Animation* animation = nullptr;
	
	State state = UP;
	

};