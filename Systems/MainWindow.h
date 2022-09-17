#pragma once
////////////////////////////////////////////////
//  MainWindow�� ���Ѱ��� �����ϱ⶧���� �̱���
//  ���� �����
////////////////////////////////////////////////

class MainWindow
{
public:
	static MainWindow* GetInstance()
	{
		static MainWindow singleTone;
		return &singleTone;
	}

public:	// Update Render �Լ�
	void  Update();
	void  Render();

public:	// Getter Setter �Լ�
	int GetWidth() { return m_nWidth; }
	int GetHeight() { return m_nHeight; }

	void SetWidth(int val) { m_nWidth = val; }
	void SetHeight(int val) { m_nHeight = val; }

public:	// DirectX 3D �ʱ�ȭ
	void   Init3D();
	void   CreateInstance(HINSTANCE hInstance, int width, int height);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	HWND GetWindowHandler() { return m_hWnd; }

	void SetWindowSize(int width, int height, bool windowedFullScreen = false);

private: // ����	
	HINSTANCE  m_hInstance = nullptr;
	HWND       m_hWnd = nullptr;
	int        m_nWidth = 0;
	int        m_nHeight = 0;
	// ȭ���� ũ��
	Color	   bgColor = Color(0.0f, 0.0f, 0.0f, 1.0f);
	// ȭ���� ��

private:
	MainWindow();
	~MainWindow();
};
