#pragma once

class Trap : public GameObject
{
public:
	Trap();
	~Trap();

	enum State
	{
		UP = 0,
		DOWN,
		UP_DOWN,
		DOWN_UP,
		DUMMY,
		KILL_UP,
		KILL_DOWN
	};

public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;

	void MoveObject(Direction direction, Vector2& position);

	void SetState(int val) { state = (State)val; }
	void Toggle();

	int GetState() { return state; }
	bool IsKillState() { if (state == KILL_UP) return true; else return false; }

	bool IsUp();

private:
	class Animation* trap = nullptr;

	State state = UP;
	int test = 0;
};