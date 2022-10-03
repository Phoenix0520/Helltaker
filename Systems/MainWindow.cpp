 #include "framework.h"
#include "MainWindow.h"
#include "Resource.h"

ID3D11Device*			Device = nullptr;
// CPU 영역 및 자원을 생성하는 영역입니다.
// 직접 할당할수 없으며 해제도 불가능합니다.
// 할당은 Desc 에 요청하여 할당합니다.
// 해제는 Release() 라는 함수를 호출하여 해제합니다.
ID3D11DeviceContext*	DeviceContext = nullptr; // GPU 영역
IDXGISwapChain*			SwapChain = nullptr; // 더블 버퍼링을 위한 것
ID3D11RenderTargetView* rtv = nullptr; // 실제 그려질 영역

bool					visibleMap = false;
bool					visibleCollider = false;
float					bgmSize = 0.15f;
float					sfxSize = 0.15f;

MainWindow::MainWindow()
{
}

MainWindow::~MainWindow()
{
	SAFE_RELEASE(rtv);
	SAFE_RELEASE(SwapChain);
	SAFE_RELEASE(DeviceContext);
	SAFE_RELEASE(Device);
}

void MainWindow::Update()
{
	SCENEMANAGER->Update();
}

///////////////////////////////////////////////////////
// IA -> VS -> PS -> RS -> OM
//
///////////////////////////////////////////////////////
void MainWindow::Render()
{
	D3D11_VIEWPORT viewport;
	{
		ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
		viewport.TopLeftX = 0;	// 시작점
		viewport.TopLeftY = 0;
		viewport.Width = (float)m_nWidth; // 종단점
		viewport.Height = (float)m_nHeight;
	}

	DeviceContext->OMSetRenderTargets(1, &rtv, nullptr);
	// Output Merger 에서 rtv 를 설정해준다.
	DeviceContext->RSSetViewports(1, &viewport);
	// Raster Stage 에서 viewport 를 설정해준다.

	bgColor = Color(2.0f/255.0f, 2.0f/255.0f, 27.0f/255.0f, 1.0f);
	DeviceContext->ClearRenderTargetView(rtv, (float*)bgColor);
	// 바탕을 지울때 사용할 색상을 정해준다.


	SCENEMANAGER->Render();


	SwapChain->Present(1, 0);
	// 향후에 랜더링 할 내용
}

// CALLBACK 이란 누군가에 의해 불려지는 함수 
// 메세지를 처리할때 메세지 처리함수를 통해서 한다.


///////////////////////////////////////////////////////
// DirectX 초기화									 //
// Device, DeviceContext, SwapChain 을 초기화 해준다.	 //
// com interface : description 이 필요하다.			 //
///////////////////////////////////////////////////////
void MainWindow::Init3D()
{
	// COM interface 에서는 함수사용을 요청하기 위해 Desc (Description) 이 필요하다.

	// GPU 에 무언가를 넣기위함
	DXGI_MODE_DESC BufferDesc;
	{
		ZeroMemory(&BufferDesc, sizeof(DXGI_MODE_DESC));
		BufferDesc.Width = m_nWidth;
		BufferDesc.Height = m_nHeight;
		// 실제화면의 너비와 높이를 구할수있다.

		BufferDesc.RefreshRate.Numerator = 60;
		BufferDesc.RefreshRate.Denominator = 1;
		// FPS 를 설정해준다. Denominator 초에 Numerator 만큼 화면을 바꾼다.

		BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		// Alpha 는 색이 곂치는 효과 0 ~ 1 까지로 정규화
		BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		// 주사선 : 밑에서부터 올라오면서 화면을 채운다.
	}

	DXGI_SWAP_CHAIN_DESC swapDesc;
	{
		ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
		swapDesc.BufferDesc = BufferDesc;
		swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		// 버퍼의 종류선택 여기서는 RTV 로 사용하겠다는 뜻이다 
		swapDesc.BufferCount = 1;
		// 버퍼의 갯수

		swapDesc.SampleDesc.Count = 1;
		swapDesc.SampleDesc.Quality = 0;
		// 그림의 확대및 축소에서 사용하기 위한 기본형

		swapDesc.OutputWindow = m_hWnd;
		// 어느 윈도우로 출력할지를 선택한다. 윈도우의 핸들을 준다.

		swapDesc.Windowed = true;
		// 창의 형태로 나타낸다.

		swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		// 스왑을 하고난뒤 이전 데이터를 지워버린다.
	}


	vector<D3D_FEATURE_LEVEL> feature_level =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
	};

	D3D_FEATURE_LEVEL pFeatureLevels;

	// Device, DC, SwapChain 을 모두 생성
	HRESULT hr = D3D11CreateDeviceAndSwapChain
	(
		nullptr, // IDXGIAdapter* pAdapter, 비디오 카드 지정
		D3D_DRIVER_TYPE_HARDWARE, // D3D_DRIVER_TYPE DriverType, 그래픽 드라이브 타입
		nullptr, // HMODULE Software, 소프트웨어 라이브러리 : 서디파티에서 제공되는 라이브러리
		D3D11_CREATE_DEVICE_BGRA_SUPPORT, // UINT Flags, 글자 등을 표시하기위한 옵션 2D+3D 를 혼합사용하게한다.
		feature_level.data(),// D3D_FEATURE_LEVEL* pFeatureLevels, 지원가능한 우선순위를 설정한다.
		feature_level.size(),// UINT FeatureLevels, feature_level 의 크기
		D3D11_SDK_VERSION,// UINT SDKVersion, DX SDK Version 현재 버전
		&swapDesc, // DXGI_SWAP_CHAIN_DESC* pSwapChainDesc, 스왑체인 desc 의 주소
		&SwapChain, // IDXGISwapChain** ppSwapChain, 스왑체인의 주소
		&Device, // ID3D11Device** ppDevice, Device 의주소
		&pFeatureLevels,// D3D_FEATURE_LEVEL* pFeatureLevel, FeatureLevel 의 정보를 받는 변수
		&DeviceContext// ID3D11DeviceContext** ppImmediateContext, DC 의 주소
	);

	assert(SUCCEEDED(hr));

	// Buffer 생성
	// SwapChain 으로부터 BackBuffer 를 얻어와서 RTV 를 생성

	ID3D11Texture2D* BackBuffer;

	hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);
	assert(SUCCEEDED(hr));
	// SwapChain 에서 버퍼를 받아와서

	hr = Device->CreateRenderTargetView(BackBuffer, nullptr, &rtv);
	assert(SUCCEEDED(hr));
	// Device 에 rtv 를 만들어준다.

	SAFE_RELEASE(BackBuffer);
}

void MainWindow::CreateInstance(HINSTANCE hInstance, int width, int height)
{
	m_nWidth = GetSystemMetrics(SM_CXSCREEN);
	m_nHeight = GetSystemMetrics(SM_CYSCREEN);

	m_hInstance = hInstance;

	WNDCLASSEX wndClass;
	ZeroMemory(&wndClass, sizeof(wndClass));

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wndClass.hIconSm = wndClass.hIcon;
	wndClass.hInstance = m_hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = L"D2D";
	wndClass.lpszMenuName = nullptr;
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.cbSize = sizeof(WNDCLASSEX);

	WORD wHr = RegisterClassEx(&wndClass);
	assert(wHr != 0);

	DWORD dwStyle;

	int tempWidth = 0;
	int tempHeight = 0;

	if (width == 0 && height == 0)
	{
		tempWidth = GetSystemMetrics(SM_CXSCREEN);
		tempHeight = GetSystemMetrics(SM_CYSCREEN);

		cout << tempWidth << " , " << tempHeight << endl;

		dwStyle = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_TABSTOP | WS_POPUP;
		SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);
		ShowCursor(false);
	}
	else
	{
		tempWidth = width;
		tempHeight = height;
		dwStyle = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW | WS_TABSTOP;
		SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);
		ShowCursor(true);
	}

	m_hWnd = CreateWindowEx
	(
		WS_EX_APPWINDOW,
		L"D2D",
		L"Helltaker",
		dwStyle,
		0,
		0,
		m_nWidth,
		m_nHeight,
		nullptr,
		(HMENU)nullptr,
		m_hInstance,
		nullptr
	);

	RECT rect = { 0, 0, tempWidth, tempHeight };

	UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - tempWidth) / 2;
	UINT centerY = (GetSystemMetrics(SM_CYSCREEN) - tempHeight) / 2;

	SetWindowPos(m_hWnd, nullptr, centerX, centerY, rect.right - rect.left, rect.bottom - rect.top, 0);

	Init3D();

	UpdateWindow(m_hWnd);
	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);

	SCENEMANAGER->GetInstance();

	//DragAcceptFiles(m_hWnd, TRUE);
}

LRESULT MainWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam);

	HDROP hDrop = NULL;

	if (mouse != NULL)
	{
		mouse->WndProc(message, wParam, lParam);
	}

	// 메세지 처리함수
	switch (message)
	{
	case WM_KEYDOWN:
	{
		Scene* scene = nullptr;

		switch (wParam)
		{
		case VK_TAB:
			if (visibleMap)
				visibleMap = false;
			else
				visibleMap = true;
			break;
		case VK_F1:
			if (visibleCollider)
				visibleCollider = false;
			else
				visibleCollider = true;
			break;
		case 'B':
			scene = SCENEMANAGER->GetScene("HS17_BossScene");
			if (scene)
				SCENEMANAGER->ChangeScene("HS17_BossScene");
			break;
		}

		break;
	}
	case WM_KEYUP:
	{
		KEYBOARD->WindowCallbackKeyUp((int)wParam);
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void MainWindow::SetWindowSize(int width, int height, bool windowedFullScreen)
{
	DWORD dwStyle = GetWindowLong(m_hWnd, GWL_STYLE);

	int tempWidth = 0;
	int tempHeight = 0;

	if (width == 0 && height == 0)
	{
		tempWidth = GetSystemMetrics(SM_CXSCREEN);
		tempHeight = GetSystemMetrics(SM_CYSCREEN);
		dwStyle = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_TABSTOP | WS_POPUP;
		SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);
		ShowCursor(false);
	}
	else if (windowedFullScreen)
	{
		tempWidth = width;
		tempHeight = height;
		dwStyle = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_TABSTOP | WS_POPUP;
		SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);
		ShowCursor(true);
	}
	else
	{
		tempWidth = width;
		tempHeight = height;
		dwStyle = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW | WS_TABSTOP;
		SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);
		ShowCursor(true);
	}

	RECT rect = { 0, 0, tempWidth, tempHeight };

	UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - tempWidth) / 2;
	UINT centerY = (GetSystemMetrics(SM_CYSCREEN) - tempHeight) / 2;

	SetWindowPos(m_hWnd, nullptr, centerX, centerY, rect.right, rect.bottom, 0);

	UpdateWindow(m_hWnd);
	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);
}