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
	void	Update(float  lockFPS);	// �����ð��� Lock�ϰ� Update
	
	void	SetLockFPS(float val) { m_LockFPS = val; }				// LockFPS �� ���Ѵ�.

	float	Delta()			{ return m_TimeElepased; }              // (1 / ������) ��
	float	GetRunning()	{ return m_RunningTime; }				// �� ����ð�
	float	GetFPS()		{ return m_FramePerSecond; }            // Frame�� ����ð�
	float	GetLockFPS()	{ return m_LockFPS;}					// FPS �ִ� ���Ѱ�
	int		GetFrame()		{ return m_FrameCountPerSecond; }		// �ʴ� FrameCount��
	
	void	WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private: // ����
	float	m_TimeElepased = 0.0f;       // ������ �ð�
	float	m_FPStimeElepased = 0.0f;   // ������ �ð�
	float	m_RunningTime = 0.0f;       // Game������ �� run�ð�
	float	m_FramePerSecond = 0.0f;    // Frame Per Second
	float	m_LockFPS = 60.0f;			// �ִ� Frame
	int		m_FrameCount = 0;           // Frame��
	int		m_FrameCountPerSecond = 0;  // �ʴ� frame count
	
	chrono::system_clock::time_point start;

};


