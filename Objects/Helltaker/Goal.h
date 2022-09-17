#pragma once
class Goal : public GameObject
{
public:
	Goal(int id);
	~Goal();

public:
	enum State
	{
		PANDEMONICA = 0,
		MODEUS,
		CERBERUS,
		MALINA,
		ZDRADA,
		AZAZEL,
		JUSTIS,
		LUCIFER
	};

public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;
	
	void SetState	(State state)	{ state = state; }
	void SetGoal	(bool val)		{ goal = val; }

private:
	class Animation* pandemonica = nullptr;
	class Animation* modeus		 = nullptr;
	class Animation* cerberus	 = nullptr;
	class Animation* malina		 = nullptr;
	class Animation* zdrada		 = nullptr;
	class Animation* azazel		 = nullptr;
	class Animation* justis		 = nullptr;
	class Animation* lucifer	 = nullptr;

	class LoveSign*	 loveSign	 = nullptr;
	class Clear*	 clearEffect = nullptr;
	class Star*		 starEffect	 = nullptr;

	State state = PANDEMONICA;
	bool goal	= false;
	bool plus	= true;
	
	int  id		= 0;

	float ctime = 0.0f;
	float rtime = 0.0f;
};