 #include "framework.h"
#include "MainWindow.h"
#include "Resource.h"

ID3D11Device*			Device = nullptr;
// CPU ���� �� �ڿ��� �����ϴ� �����Դϴ�.
// ���� �Ҵ��Ҽ� ������ ������ �Ұ����մϴ�.
// �Ҵ��� Desc �� ��û�Ͽ� �Ҵ��մϴ�.
// ������ Release() ��� �Լ��� ȣ���Ͽ� �����մϴ�.
ID3D11DeviceContext*	DeviceContext = nullptr; // GPU ����
IDXGISwapChain*			SwapChain = nullptr; // ���� ���۸��� ���� ��
ID3D11RenderTargetView* rtv = nullptr; // ���� �׷��� ����

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
		viewport.TopLeftX = 0;	// ������
		viewport.TopLeftY = 0;
		viewport.Width = (float)m_nWidth; // ������
		viewport.Height = (float)m_nHeight;
	}

	DeviceContext->OMSetRenderTargets(1, &rtv, nullptr);
	// Output Merger ���� rtv �� �������ش�.
	DeviceContext->RSSetViewports(1, &viewport);
	// Raster Stage ���� viewport �� �������ش�.

	bgColor = Color(2.0f/255.0f, 2.0f/255.0f, 27.0f/255.0f, 1.0f);
	DeviceContext->ClearRenderTargetView(rtv, (float*)bgColor);
	// ������ ���ﶧ ����� ������ �����ش�.


	SCENEMANAGER->Render();


	SwapChain->Present(1, 0);
	// ���Ŀ� ������ �� ����
}

// CALLBACK �̶� �������� ���� �ҷ����� �Լ� 
// �޼����� ó���Ҷ� �޼��� ó���Լ��� ���ؼ� �Ѵ�.


///////////////////////////////////////////////////////
// DirectX �ʱ�ȭ									 //
// Device, DeviceContext, SwapChain �� �ʱ�ȭ ���ش�.	 //
// com interface : description �� �ʿ��ϴ�.			 //
///////////////////////////////////////////////////////
void MainWindow::Init3D()
{
	// COM interface ������ �Լ������ ��û�ϱ� ���� Desc (Description) �� �ʿ��ϴ�.

	// GPU �� ���𰡸� �ֱ�����
	DXGI_MODE_DESC BufferDesc;
	{
		ZeroMemory(&BufferDesc, sizeof(DXGI_MODE_DESC));
		BufferDesc.Width = m_nWidth;
		BufferDesc.Height = m_nHeight;
		// ����ȭ���� �ʺ�� ���̸� ���Ҽ��ִ�.

		BufferDesc.RefreshRate.Numerator = 60;
		BufferDesc.RefreshRate.Denominator = 1;
		// FPS �� �������ش�. Denominator �ʿ� Numerator ��ŭ ȭ���� �ٲ۴�.

		BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		// Alpha �� ���� ��ġ�� ȿ�� 0 ~ 1 ������ ����ȭ
		BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		// �ֻ缱 : �ؿ������� �ö���鼭 ȭ���� ä���.
	}

	DXGI_SWAP_CHAIN_DESC swapDesc;
	{
		ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
		swapDesc.BufferDesc = BufferDesc;
		swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		// ������ �������� ���⼭�� RTV �� ����ϰڴٴ� ���̴� 
		swapDesc.BufferCount = 1;
		// ������ ����

		swapDesc.SampleDesc.Count = 1;
		swapDesc.SampleDesc.Quality = 0;
		// �׸��� Ȯ��� ��ҿ��� ����ϱ� ���� �⺻��

		swapDesc.OutputWindow = m_hWnd;
		// ��� ������� ��������� �����Ѵ�. �������� �ڵ��� �ش�.

		swapDesc.Windowed = true;
		// â�� ���·� ��Ÿ����.

		swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		// ������ �ϰ��� ���� �����͸� ����������.
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

	// Device, DC, SwapChain �� ��� ����
	HRESULT hr = D3D11CreateDeviceAndSwapChain
	(
		nullptr, // IDXGIAdapter* pAdapter, ���� ī�� ����
		D3D_DRIVER_TYPE_HARDWARE, // D3D_DRIVER_TYPE DriverType, �׷��� ����̺� Ÿ��
		nullptr, // HMODULE Software, ����Ʈ���� ���̺귯�� : ������Ƽ���� �����Ǵ� ���̺귯��
		D3D11_CREATE_DEVICE_BGRA_SUPPORT, // UINT Flags, ���� ���� ǥ���ϱ����� �ɼ� 2D+3D �� ȥ�ջ���ϰ��Ѵ�.
		feature_level.data(),// D3D_FEATURE_LEVEL* pFeatureLevels, ���������� �켱������ �����Ѵ�.
		feature_level.size(),// UINT FeatureLevels, feature_level �� ũ��
		D3D11_SDK_VERSION,// UINT SDKVersion, DX SDK Version ���� ����
		&swapDesc, // DXGI_SWAP_CHAIN_DESC* pSwapChainDesc, ����ü�� desc �� �ּ�
		&SwapChain, // IDXGISwapChain** ppSwapChain, ����ü���� �ּ�
		&Device, // ID3D11Device** ppDevice, Device ���ּ�
		&pFeatureLevels,// D3D_FEATURE_LEVEL* pFeatureLevel, FeatureLevel �� ������ �޴� ����
		&DeviceContext// ID3D11DeviceContext** ppImmediateContext, DC �� �ּ�
	);

	assert(SUCCEEDED(hr));

	// Buffer ����
	// SwapChain ���κ��� BackBuffer �� ���ͼ� RTV �� ����

	ID3D11Texture2D* BackBuffer;

	hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);
	assert(SUCCEEDED(hr));
	// SwapChain ���� ���۸� �޾ƿͼ�

	hr = Device->CreateRenderTargetView(BackBuffer, nullptr, &rtv);
	assert(SUCCEEDED(hr));
	// Device �� rtv �� ������ش�.

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

	// �޼��� ó���Լ�
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