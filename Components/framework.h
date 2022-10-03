#pragma once
#define _CRT_SECURE_NO_WARNINGS

// Console Define
#ifdef _DEBUG	// 콘솔을 연결해주는 _DEBUG
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

#endif // _DEBUG

#include "targetver.h"

// Windows 헤더 파일
#include <windows.h>
#include <assert.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// STL
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <bitset> // 비트를 맞춰준다.
#include <functional>
#include <mutex>
#include <io.h>
#include <chrono>
#include <cmath>
#include <bitset>
#include <mmsystem.h>
#include <random>
#pragma comment(lib,"winmm.lib")

// Audio


using namespace std;

// 매크로
#define Check(p) assert(SUCCEEDED(p));
#define SAFE_DELETE(p) {if(p) { delete(p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[](p); p = nullptr; }}
#define SAFE_RELEASE(p) {if(p) { (p)->Release(); (p) = nullptr;}}

#pragma warning (disable : 4099)
#pragma warning (disable : 4244)
#pragma warning (disable : 4996)

// 3D

// header
#include <d3d11.h>
#include <D3DX11.h>
#include <D3DX10.h>
#include <D3DX10math.h>
#include <d3dcompiler.h>
#include <D3DX11async.h>

// library
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

// 2D

//header
#include <d2d1_2.h>
#include <d2d1_1.h>
#include <dwrite.h>
#include <d2d1svg.h>

// library
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

#include "imconfig.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#if _WIN64 
#pragma comment(lib,"./Libraries/imGui64.lib")
#else
#pragma comment(lib,"./Libraries/imGui.lib")
#endif

// 음원
#include "FMOD/fmod.hpp"

#ifdef _WIN64
	#pragma comment(lib, "./Libraries/FMOD/fmodex64_vc.lib")
#else
	#pragma comment(lib, "./Libraries/FMOD/fmodex_vc.lib")

#endif // _WIN64


#pragma comment(lib, "Effects11d.lib")

// Typedef
typedef D3DXVECTOR2 Vector2;
typedef D3DXVECTOR3 Vector3;
typedef D3DXCOLOR	Color;
typedef D3DXMATRIX	Matrix;


// User 정의 디렉토리

// include

// System
#include "MainWindow.h"
#include "GameTime.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Audio.h"
#include "DirectWrite.h"

// Base
#include "Scene.h"
#include "Camera.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "SRVManager.h"
#include "GameObject.h"
#include "Collider.h"
#include "Convert.h"
#include "CSVReader.h"

// Animation
#include "Animation.h"
#include "AnimationClip.h"

// Shader
#include "ColorShader.h"
#include "TextureShader.h"

// define
#define MAIN					MainWindow::GetInstance()
#define SCENEMANAGER			SceneManager::GetInstance()
#define TIMEMANAGER				GameTime::GetInstance()
#define OBJMANAGER				ObjectManager::GetInstance()
#define SRVMANAGER				SRVManager::GetInstance()
#define TRNMANAGER				Terrain::GetInstance()
#define	CAMERA					Camera::GetInstance()
#define KEYBOARD				Keyboard::GetInstance()
#define DOWN(key)				KEYBOARD->Down(key)
#define UP(key)					KEYBOARD->Up(key)
#define PRESS(key)				KEYBOARD->Press(key)
#define HTMAP					HelltakerMap::GetInstance()
#define HTMAPSTATE				HelltakerMap::State
#define DELTA					TIMEMANAGER->Delta()
#define ADDSOUND(str, str2, re)	audio->AddSound(str, str2, re)
#define ISPLAYING(str)			audio->Playing(str)
#define PLAYSOUND(str, vol)		audio->Play(str, vol)
#define STOPSOUND(str)			audio->Stop(str)
#define VOLUME(str, vol)		audio->Volume(str, vol)

#define ISPAUSED(str)			audio->Paused(str)
#define PAUSESOUND(str)			audio->Pause(str)
#define RESUMESOUND(str)		audio->Resume(str)

#define VM						CAMERA->GetViewMatrix()
#define PM						CAMERA->GetProjMatrix()

#define TO_STRING(wstr, str)	str.assign(wstr.begin(), wstr.end())

// Key Define



// extern
extern ID3D11Device*			Device;
extern ID3D11DeviceContext*		DeviceContext;
extern IDXGISwapChain*			SwapChain;
extern ID3D11RenderTargetView*	rtv;
extern CMouse*					mouse;
extern CAudio*					audio;
extern bool						visibleMap;
extern bool						visibleCollider;
extern float					bgmSize;
extern float					sfxSize;