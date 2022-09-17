#pragma once

class Mob : public GameObject
{
public:
	Mob();
	~Mob();

public:
	enum State
	{
		IDLE = 0,
		ATTACKED,
		DEAD
	};

public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;
	void MoveObject(Direction direction, Vector2& position);

private:
	class Animation* animation  = nullptr;
	class Bone*		 bone		= nullptr;

	int		soundID = 0;
	float	time = 0.0f;
	bool	destroy = false;
	State	state	= State::IDLE;

	vector<Bone*> effect;
};