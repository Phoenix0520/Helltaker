#pragma once

class Helltaker : public GameObject
{
public:
	Helltaker();
	~Helltaker();

public:
	enum State
	{
		IDLE = 0,
		WALK,
		ATTACK,
		GOAL
	};

public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;

	void BossUpdate(Matrix V, Matrix P);
	void BossMove(char val);
	void BossRender();
	void BossReset();
	// Update Render

	void CheckTrap(int x, int y);

	int  GetHP() { return hp; }
	bool IsGoal() { if (state == State::GOAL) return true; else return false; }
	// Getter
	
	void SetHP(int val) { hp = val; }
	void SetState(State val) { state = val; }
	void SetGoal(bool val) { goal = val; }
	// Setter
	
	void ExternMoveObject(int vert, int horiz);
	void SetHuge();
	void SetBoss(bool val) { boss = val; }
	bool IsAttacted();
	void Attacked();

	void SetImmune(bool value) { immortal = value; }
	bool GetImmune() { return immortal; }
	bool IsBoss() { return boss; }

private:
	void MoveObject(Direction direction, Vector2& position);

private:
	class Animation*	animation	= nullptr;
	class Huge*			hugeEffect	= nullptr;
	
	State				state		= State::IDLE; //현재 플레이어가 기본으로 가지는 동작의 상태를 의미한다.
	
	float				time		= 0.0f;
	float				bloodTime	= 0.0f;
	float				goalTime	= 0.0f;
	
	int					moveCount	= 0;
	Vector2				movePos		= Vector2(0.0f, 0.0f);

	vector<Scene*>		scenes;

	// normal

	int hp			= 0;
	bool goal		= false;
	bool haveKey	= false;
	bool boss		= false;
	bool immortal	= false;
	// status

	class Kick*	kickEffect = nullptr;
	class Dust* dustEffect = nullptr;
	// effect
};