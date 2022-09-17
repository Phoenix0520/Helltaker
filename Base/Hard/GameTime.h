#pragma once
#define TIMEMANAGER GameTime::GetInstance()

class GameTime
{
private:
	GameTime();
	~GameTime();

public:
	static GameTime* GetInstance()
	{
		static GameTime singletoneInstane; 
		return &singletoneInstane;
	}

	void	Update();
	void	Update(float  lockFPS);	// 일정시간을 Lock하고 Update
	
	void	SetLockFPS(float val) { m_LockFPS = val; }				// LockFPS 를 정한다.

	float	Delta()			{ return m_TimeElepased; }              // (1 / 프레임) 초
	float	GetRunning()	{ return m_RunningTime; }				// 총 경과시간
	float	GetFPS()		{ return m_FramePerSecond; }            // Frame당 경과시간
	float	GetLockFPS()	{ return m_LockFPS;}					// FPS 최대 제한값
	int		GetFrame()		{ return m_FrameCountPerSecond; }		// 초당 FrameCount수
	
	void	WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private: // 변수
	float	m_TimeElepased = 0.0f;       // 현재경과 시간
	float	m_FPStimeElepased = 0.0f;   // 현재경과 시간
	float	m_RunningTime = 0.0f;       // Game에서의 총 run시간
	float	m_FramePerSecond = 0.0f;    // Frame Per Second
	float	m_LockFPS = 60.0f;			// 최대 Frame
	int		m_FrameCount = 0;           // Frame수
	int		m_FrameCountPerSecond = 0;  // 초당 frame count
	
	chrono::system_clock::time_point start;

};


