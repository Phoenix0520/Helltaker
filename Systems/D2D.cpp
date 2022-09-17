#include "framework.h"
#include "D2D.h"
#include <fstream>

CMouse* mouse = nullptr;
CAudio* audio = nullptr;

////////////////////////////////////////////////////
// 프로그램의 진입점
////////////////////////////////////////////////////

void LoadFont();

int APIENTRY wWinMain
(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow
)
{	// Window 생성, Direct X11 세팅

	srand(time(NULL)); // 난수 생성시 사용할 srand
	audio = new CAudio(); // Audio 작업시 사용할 CAudio
	MAIN->CreateInstance(hInstance, 0, 0);
	// width, height 를 각각 0 으로 해주면 전체화면이 됩니다.
	mouse = new CMouse(MAIN->GetWindowHandler()); // 마우스

	// ImGUI Setting
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplWin32_Init(MAIN->GetWindowHandler());
	ImGui_ImplDX11_Init(Device, DeviceContext);
	ImGui::StyleColorsDark();
	LoadFont();

	DirectWrite::Create(); // 텍스트를 그릴 Direct2DWrite

	MSG msg; // 메세지

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			TIMEMANAGER->Update(60.0f);
			mouse->Update();
			audio->Update();
			MAIN->Update();
			MAIN->Render();
		}
	}

	DirectWrite::Delete();
	SAFE_DELETE(mouse);
	//SAFE_DELETE(audio);

	return (int)msg.wParam;
}

void LoadFont()
{
	ImGuiIO& io = ImGui::GetIO();
	ImFont* font = nullptr;
	string fontfile = "./Font/malgunbd.ttf";

	ifstream ifile;
	ifile.open(fontfile);

	if (ifile)
	{
		io.Fonts->AddFontFromFileTTF
		(
			fontfile.c_str(),
			20.0f,
			NULL,
			io.Fonts->GetGlyphRangesKorean()
		);
	}
}