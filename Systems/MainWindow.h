#pragma once
////////////////////////////////////////////////
//  MainWindow는 단한개만 생성하기때문에 싱글톤
//  으로 만든다
////////////////////////////////////////////////

class MainWindow
{
public:
	static MainWindow* GetInstance()
	{
		static MainWindow singleTone;
		return &singleTone;
	}

public:	// Update Render 함수
	void  Update();
	void  Render();

public:	// Getter Setter 함수
	int GetWidth() { return m_nWidth; }
	int GetHeight() { return m_nHeight; }

	void SetWidth(int val) { m_nWidth = val; }
	void SetHeight(int val) { m_nHeight = val; }

public:	// DirectX 3D 초기화
	void   Init3D();
	void   CreateInstance(HINSTANCE hInstance, int width, int height);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	HWND GetWindowHandler() { return m_hWnd; }

	void SetWindowSize(int width, int height, bool windowedFullScreen = false);

private: // 변수	
	HINSTANCE  m_hInstance = nullptr;
	HWND       m_hWnd = nullptr;
	int        m_nWidth = 0;
	int        m_nHeight = 0;
	// 화면의 크기
	Color	   bgColor = Color(0.0f, 0.0f, 0.0f, 1.0f);
	// 화면의 색

private:
	MainWindow();
	~MainWindow();
};
