#pragma once

class HS17_BossScene : public Scene
{
public:
	HS17_BossScene();
	~HS17_BossScene();

public:
	void Update();
	void Render();
	void ChangeScene();

	void MoveingTrap();
	void SetPhase();

	void DiscardLife();
	void AttackChain(int index);

private:
	class Texture* background	= nullptr;
	class Texture* rect			= nullptr;
	class Texture* uprBorder	= nullptr;
	class Texture* uprBorder2	= nullptr;
	class Texture* udrBorder	= nullptr;
	class Animation* gear[2];

	class Piston*		piston[2];
	class Bridge*		bridge		= nullptr;
	class LifeCount*	lifeCount	= nullptr;
	class Helltaker*	helltaker	= nullptr;
	
	vector<class Trap*> traps;

	class ChainDaigonal* chain = nullptr;
	//vector<bool> chainWork;
	//vector<bool> timeRemain;
	
	bool working = false;
	bool attacked = false;

	float time = 0.0f;
	float ctime = 0.0f;
	float endTime = 29.5f;
	float moveVal = 0.0f;

	UINT push = 0;
};