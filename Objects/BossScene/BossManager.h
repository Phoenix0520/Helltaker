#pragma once

class BossManager
{
public:
	BossManager();
	~BossManager();

public:
	static BossManager* GetInstance()
	{
		static BossManager instance;
		return &instance;
	}

public:
	void Update(Matrix V, Matrix P);
	void Render();
	void Reset();

	void PushChain(int type, int value, float time);

private:
	vector<class ChainVH*> chains;
	vector<vector<UINT>>  activated;
	vector<float> times;
	class Helltaker* ht = nullptr;

	UINT end = 0;
	UINT push = 0;
	
	bool reset = false;
	bool attack = false;

	float stime = 0.0f;
	

};