#include "framework.h"
#include "SceneManager.h"
#include "SceneList.h"
#include "Booper.h"
#include "Helltaker.h"
#include "HelltakerMap.h"
#include "Mob.h"
#include "Box.h"
#include "Trap.h"
#include "Goal.h"
#include "Slate.h"
#include "Fire.h"
#include "Key.h"
#include "LockBox.h"
#include "OptionMenu.h"
#include "Star.h"
#include "Clear.h"
#include "LoveSign.h"
#include "ChainVH.h"

long start;

////////////////////////////////////////////////////////
// 생성자, 소멸자
////////////////////////////////////////////////////////

SceneManager::SceneManager()
{
	start = GetTickCount();

	optionMenu = new OptionMenu();

	scenes.push_back(new HS01_IntroScene());

	//CreateObject();
	//ThreadStart2();

	thread t0(bind(&SceneManager::CreateObject, this));
	t0.detach();
	//t0.join();

	thread t1(bind(&SceneManager::ThreadStart1, this));
	t1.detach();
	//t1.join();

	//thread t2(bind(&SceneManager::ThreadStart2, this));
	//t2.detach();
	//t2.join();
}

SceneManager::~SceneManager()
{
	// 주소만 배열로 되어있기 때문에 오브젝트를 Delete 해주어야한다.
	for (UINT i = 0; i < scenes.size(); i++)
	{
		SAFE_DELETE(scenes.at(i));
	}

	// 모든 데이터주소값도 지워준다.
	scenes.erase(scenes.begin(), scenes.end());
}

void SceneManager::Update()
{
	//if (!threadStart)
	//{
	//	ThreadStart1();
	//	threadStart = true;
	//}

	if (DOWN(VK_F11))
		MAIN->SetWindowSize(1600, 900);
	if (DOWN(VK_F12))
		MAIN->SetWindowSize(0, 0);

	for (UINT i = 0; i < scenes.size(); i++)
	{
		if (scenes[i]->IsActive())
		{
			if (pause)
			{
				optionMenu->Update(VM, PM);
				return;
			}

			if (scenes[i]->GetDisplay())
			{
				if (DOWN(VK_ESCAPE))
				{
					if (pause)
						pause = false;
					else
						pause = true;
				}
			}

			scenes[i]->Update();

			curScene = scenes[i];
			curSceneNum = i;

			if (curSceneNum != 15)
				CAMERA->SetPosition(0.0f, 0.0f);
		}
		// Scene 이 Active 되어있을때만 Update 해준다.
	}

}

void SceneManager::Render()
{
	for (UINT i = 0; i < scenes.size(); i++)
	{
		if (scenes[i]->IsActive())
		{
			scenes[i]->Render();

			if (scenes[i]->GetDisplay())
				RenderChapterDisplay();
			
			if (pause)
				optionMenu->Render();
		}
		// Scene 이 Active 되어있을때만 Rendering 해준다.
	}
}

void SceneManager::ThreadStart1()
{
	HS01_IntroScene* scene = (HS01_IntroScene*)SCENEMANAGER->GetScene("HS01_IntroScene");

	//CreateObject();

	scenes.push_back(new HS00_DeadScene());
	scene->AddLoadVal();
	
	scenes.push_back(new HS02_Prologue());
	scene->AddLoadVal();
	
	scenes.push_back(new HS03_ChangeScene());
	scene->AddLoadVal(); 
	
	scenes.push_back(new HS04_Chapter01());
	scene->AddLoadVal();
	
	scenes.push_back(new HS05_Dialogue());
	scene->AddLoadVal(); 


	scenes.push_back(new HS06_Chapter02());
	scene->AddLoadVal();
	
	scenes.push_back(new HS07_Chapter03());
	scene->AddLoadVal();
	
	scenes.push_back(new HS08_Chapter04());
	scene->AddLoadVal(); 
	
	scenes.push_back(new HS09_SlateScene());
	scene->AddLoadVal(); 
	
	scenes.push_back(new HS10_Chapter05());
	scene->AddLoadVal();
	
	scenes.push_back(new HS11_Chapter06());
	scene->AddLoadVal();
	

	scenes.push_back(new HS12_HeavenScene());
	scene->AddLoadVal();
	
	scenes.push_back(new HS13_Chapter07());
	scene->AddLoadVal();
	
	scenes.push_back(new HS14_Chapter08());
	scene->AddLoadVal();
	
	scenes.push_back(new HS15_Chapter09());
	scene->AddLoadVal();
	
	scenes.push_back(new HS16_JudgeScene());
	scene->AddLoadVal();
	
	scenes.push_back(new HS17_BossScene());
	scene->AddLoadVal();
	
	scenes.push_back(new HS19_MapEditor());
	scene->AddLoadVal();

	scene->AddLoadLevel();
	scene->AddLoadLevel();
}

void SceneManager::ThreadStart2()
{
	{
		Helltaker* helltaker = new Helltaker();
		OBJMANAGER->AddObject("Helltaker", helltaker);
	}
	
	for (int i = 1; i < 32; i++)
	{
		string str = "Trap" + to_string(i);
		if (!OBJMANAGER->FindObject(str))
		{
			Trap* trap = new Trap();
			OBJMANAGER->AddObject(str, trap);
		}
	}
	
	for (int i = 0; i < 12; i++)
	{
		string str = "ChainVH" + to_string(i);
		if (!OBJMANAGER->FindObject(str))
		{
			ChainVH* ch = new ChainVH();
			OBJMANAGER->AddObject(str, ch);
		}
	}
	
	scenes.push_back(new HS00_DeadScene());
	scenes.push_back(new HS03_ChangeScene());
	scenes.push_back(new HS17_BossScene());
}

///////////////////////////////////////////////////////////////////
//
//	Game 관련 Object 생성
//
///////////////////////////////////////////////////////////////////


void SceneManager::CreateObject()
{
	HS01_IntroScene* scene = (HS01_IntroScene*)SCENEMANAGER->GetScene("HS01_IntroScene");

	// SFX
	ADDSOUND("Change", "./Sound/ChangeScene.wav", false);
	ADDSOUND("HOVER", "./Sound/ButtonHover.wav", false);
	ADDSOUND("CONFIRM", "./Sound/ButtonConfirm.wav", false);

	ADDSOUND("Move", "./Sound/Move.wav", false);
	ADDSOUND("CLEAR", "./Sound/Clear.wav", false);
	ADDSOUND("DEATH", "./Sound/DEATH.wav", false);

	ADDSOUND("KEY", "./Sound/Key.wav", false);
	ADDSOUND("LOCKBOXKICK", "./Sound/LockBoxKick.wav", false);
	ADDSOUND("LOCKBOXOPEN", "./Sound/LockBoxOpen.wav", false);

	ADDSOUND("MOBDIE1", "./Sound/MobDie1.wav", false);
	ADDSOUND("MOBDIE2", "./Sound/MobDie2.wav", false);
	ADDSOUND("MOBDIE3", "./Sound/MobDie3.wav", false);
	ADDSOUND("MOBKICK1", "./Sound/MobKick1.wav", false);
	ADDSOUND("MOBKICK2", "./Sound/MobKick2.wav", false);
	ADDSOUND("MOBKICK3", "./Sound/MobKick3.wav", false);

	ADDSOUND("BOXMOVE1", "./Sound/BoxMove1.wav", false);
	ADDSOUND("BOXMOVE2", "./Sound/BoxMove2.wav", false);
	ADDSOUND("BOXMOVE3", "./Sound/BoxMove3.wav", false);
	ADDSOUND("BOXKICK1", "./Sound/BoxKick1.wav", false);
	ADDSOUND("BOXKICK2", "./Sound/BoxKick2.wav", false);
	ADDSOUND("BOXKICK3", "./Sound/BoxKick3.wav", false);

	ADDSOUND("TRAP", "./Sound/Trap1.wav", false);

	ADDSOUND("CHAINBREAK", "./Sound/ChainBreak.wav", false);
	ADDSOUND("CHAINKICK_L", "./Sound/ChainKickLeft.wav", false);
	ADDSOUND("CHAINKICK_R", "./Sound/ChainKickRight.wav", false);
	ADDSOUND("CHAINBLINK1", "./Sound/ChainBlink1.wav", false);
	ADDSOUND("CHAINBLINK2", "./Sound/ChainBlink2.wav", false);
	ADDSOUND("CHAINBLINK3", "./Sound/ChainBlink3.wav", false);
	ADDSOUND("CHAINBLINK4", "./Sound/ChainBlink4.wav", false);
	
	ADDSOUND("DSTART", "./Sound/Dialogue Start.wav", false);
	ADDSOUND("DSUCCESS", "./Sound/Dialogue Success.wav", false);
	ADDSOUND("BADEND", "./Sound/BADEND.wav", false);

	ADDSOUND("Slate1", "./Sound/Slate1.wav", false);
	ADDSOUND("Slate2", "./Sound/Slate2.wav", false);
	ADDSOUND("Slate3", "./Sound/Slate3.wav", false);

	// BGM
	ADDSOUND("INTRO", "./Sound/IntroBGM.wav", true);
	ADDSOUND("MAINBGM", "./Sound/HTBGM.wav", true);

	{
		Helltaker* helltaker = new Helltaker();
		OBJMANAGER->AddObject("Helltaker", helltaker);
	}

	// Booper
	{
		Booper* obj = new Booper();
		OBJMANAGER->AddObject("Booper", obj);
	}

	scene->AddLoadLevel();

	for (int i = 0; i < 12; i++)
	{
		string str = "ChainVH" + to_string(i);
		if (!OBJMANAGER->FindObject(str))
		{
			ChainVH* ch = new ChainVH();
			OBJMANAGER->AddObject(str, ch);
		}
	}

	for (int i = 1; i < 32; i++)
	{
		string str = "Trap" + to_string(i);
		if (!OBJMANAGER->FindObject(str))
		{
			Trap* trap = new Trap();
			OBJMANAGER->AddObject(str, trap);
		}
	}



	// Helltaker
	{
		Helltaker* helltaker = new Helltaker();
		OBJMANAGER->AddObject("Helltaker", helltaker);
		scene->AddLoadVal();
	}

	// LoveSign
	{
		LoveSign* sign = new LoveSign();
		OBJMANAGER->AddObject("LoveSign", sign);
		scene->AddLoadVal();
	}

	// StarEffect
	{
		Star* star = new Star();
		OBJMANAGER->AddObject("Star", star);
		scene->AddLoadVal();
	}

	// ClearEffect
	{
		Clear* clear = new Clear();
		OBJMANAGER->AddObject("Clear", clear);
		scene->AddLoadVal();
	}

	for (int i = 1; i <= 12; i++)
	{
		string str = "Mob" + to_string(i);
		if (!OBJMANAGER->FindObject(str))
		{
			Mob* mob = new Mob();
			OBJMANAGER->AddObject(str, mob);
			scene->AddLoadVal();
		}
	}


	for (int i = 1; i <= 15; i++)
	{
		string str = "Box" + to_string(i);
		if (!OBJMANAGER->FindObject(str))
		{
			Box* box = new Box();
			OBJMANAGER->AddObject(str, box);
			scene->AddLoadVal();
		}
	}

	for (int i = 1; i <= 10; i++)
	{
		string str = "Goal" + to_string(i);
		if (!OBJMANAGER->FindObject(str))
		{
			Goal* goal = new Goal(i);
			OBJMANAGER->AddObject(str, goal);
			scene->AddLoadVal();
		}
	}

	for (int i = 1; i <= 8; i++)
	{
		string str = "Fire" + to_string(i);
		if (!OBJMANAGER->FindObject(str))
		{
			Fire* fire = new Fire();
			OBJMANAGER->AddObject(str, fire);
			scene->AddLoadVal();
		}
	}

	for (int i = 1; i < 32; i++)
	{
		string str = "Trap" + to_string(i);
		if (!OBJMANAGER->FindObject(str))
		{
			Trap* trap = new Trap();
			OBJMANAGER->AddObject(str, trap);
			scene->AddLoadVal();
		}
	}

	// Key
	{
		string str = "Key";
		if (!OBJMANAGER->FindObject(str))
		{
			Key* key = new Key();
			OBJMANAGER->AddObject(str, key);
			scene->AddLoadVal();
		}
	}

	// LockBox
	{
		string str = "LockBox";
		if (!OBJMANAGER->FindObject(str))
		{
			LockBox* lbox = new LockBox();
			OBJMANAGER->AddObject(str, lbox);
			scene->AddLoadVal();
		}
	}

	//
	{
		string str = "Slate";
		if (!OBJMANAGER->FindObject(str))
		{
			Slate* obj = new Slate();
			OBJMANAGER->AddObject(str, obj);
			scene->AddLoadVal();
		}
	}
}

Scene* SceneManager::GetScene(string name)
{
	Scene* value = nullptr;
	for (UINT i = 0; i < scenes.size(); i++)
	{
		if (scenes[i]->GetSceneName() != name)
			continue;

		if (scenes[i])
			value = scenes[i];
		else
			value = nullptr;

		break;
	}

	return value;
}


void SceneManager::RenderChapterDisplay()
{
	DirectWrite::GetDC()->BeginDraw();
	{
		// HP drawing
		{
			Helltaker* helltaker = (Helltaker*)OBJMANAGER->FindObject("Helltaker");
			wstring str = to_wstring(helltaker->GetHP());
			static wstring old = L"";
			if (helltaker->GetHP() <= 0)
				str = L"X";

			Vector2 position;
			if (helltaker->GetHP() >= 10)
				position = Vector2(80.0f, 730.0f);
			else
				position = Vector2(140.0f, 730.0f);

			DirectWrite::ChangeTextType
			(
				L"Amiri",
				DWRITE_FONT_WEIGHT_REGULAR,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_CONDENSED
			);

			DirectWrite::RenderText(str, position, 255, 255, 255, 125.0f);

			DirectWrite::ChangeTextType
			(
				L"Amiri",
				DWRITE_FONT_WEIGHT_MEDIUM,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_CONDENSED
			);

			// stage drawing
			switch (curSceneNum)
			{
			case 4:
				str = L"I";
				break;
			case 6:
				str = L"II";
				break;
			case 7:
				str = L"III";
				break;
			case 8:
				str = L"IV";
				break;
			case 10:
				str = L"V";
				break;
			case 11:
				str = L"VI";
				break;
			case 13:
				str = L"VII";
				break;
			case 14:
				str = L"VIII";
				break;
			case 15:
				str = L"IX";
				break;
			case 16:
				str = L"X";
				break;
			default:
				str = L"";
				break;
			}

			if (!pause)
			{
				position = Vector2(1715.0f, 730.0f);
				position.x -= str.length() * 65.0f;
				DirectWrite::RenderText(str, position, 255, 255, 255, 130.0f);

				DirectWrite::ChangeTextType
				(
					L"맑은고딕체",
					DWRITE_FONT_WEIGHT_BOLD,
					DWRITE_FONT_STYLE_NORMAL,
					DWRITE_FONT_STRETCH_CONDENSED
				);

				// menual drawing

				if (curSceneNum != 15)
				{
					str = L"• 인생 조언 [L키] •";
					position = Vector2(495.5f, 1005.0f);
					DirectWrite::RenderText(str, position, 255, 255, 255, 35.0f);

					str = L"• 재시작 [R키] •";
					position = Vector2(970.5f, 1005.0f);
					DirectWrite::RenderText(str, position, 255, 255, 255, 35.0f);

				}
				DirectWrite::ChangeTextType
				(
					L"맑은고딕체",
					DWRITE_FONT_WEIGHT_MEDIUM,
					DWRITE_FONT_STYLE_NORMAL,
					DWRITE_FONT_STRETCH_CONDENSED
				);
			}
		}

		if (visibleMap)
		{
			// Mouse Position
			RECT rect = { 5, 5, 505, 505 };
			wstring str = L"FPS : " + to_wstring(TIMEMANAGER->GetFrame());
			DirectWrite::RenderText(str, rect);

			rect.top += 20;
			rect.bottom += 20;

			str = L"CameraPos(" + to_wstring(CAMERA->GetPosition().x) + L" , " + to_wstring(CAMERA->GetPosition().y) + L")";
			DirectWrite::RenderText(str, rect);

			rect.top += 20;
			rect.bottom += 20;

			Vector2 pos = mouse->GetPosition();
			CAMERA->WCToVC(pos);

			str = L"MousePos(" + to_wstring(pos.x) + L" , " + to_wstring(pos.y) + L")";
			DirectWrite::RenderText(str, rect);

			rect.top += 20;
			rect.bottom += 20;

			str = L"SoundSize(" + to_wstring(bgmSize) + L" , " + to_wstring(sfxSize) + L")";
			DirectWrite::RenderText(str, rect);

			// Map visible
			for (int y = 0; y < HTMAP->GetSizeY(); y++)
			{
				for (int x = 0; x < HTMAP->GetSizeX(); x++)
				{
					Vector2 position = HTMAP->GetPosition(x, y);
					position.x -= 10.0f;
					int state = HTMAP->GetValue(x, y);
					CAMERA->VCToWC(position);

					wstring str = to_wstring(state);

					Vector2 sndpos = position;
					sndpos.x -= 10.0f;

					Vector2 trdpos = position;
					trdpos.x -= 20.0f;

					Vector3 color = Vector3(255.0f, 255.0f, 255.0f);

					switch (state)
					{
					case 0:
						color.y = 0.0f;
						break;
					case 9:
						color.x = 0.0f;
						color.z = 0.0f;
						break;
					case 33:
						position = sndpos;
						color.y = 0.0f;
						color.z = 0.0f;
						break;
					case 65:
						position = sndpos;
						color.y = 122.5f;
						color.z = 0.0f;
						break;
					case 129:
						position = trdpos;
						color.y = 122.5f;
						color.z = 0.0f;
						break;
					case 261:
						position = trdpos;
						color.z = 0.0f;
						break;
					default:
						if (state >= 10)
							position = sndpos;
						break;
					}

					// 각 오브젝트 번호
					DirectWrite::RenderText(str, position, color.x, color.y, color.z, 20.0f);

					wstring str2 = to_wstring(x) + to_wstring(y);
					position.x += 25.0f;
					position.y += 25.0f;

					DirectWrite::RenderText(str2, position, 0.0f, 255.0f, 255.0f, 12.5f);
				}
			}

			if (curScene == GetScene("HS19_MapEditor"))
			{
				for (int y = 0; y <= HTMAP->GetSizeY(); y++)
				{
					for (int x = 0; x <= HTMAP->GetSizeX(); x++)
					{
						if (x == HTMAP->GetSizeX())
						{

						}
						else if (y == HTMAP->GetSizeY())
						{
							Vector2 position = HTMAP->GetPosition(x - 1, y - 1);
							position -= Vector2(-10.0f, 10.0f);
						}
						else if (x == HTMAP->GetSizeX() && y == HTMAP->GetSizeY())
						{
							Vector2 position = HTMAP->GetPosition(x - 1, y - 1);
							position -= Vector2(-10.0f, 10.0f);
						}
						else
						{
							Vector2 position = HTMAP->GetPosition(x, y);
							position -= Vector2(10.0f, 10.0f);
						}
						
					}
				}
			}
		}
	}
	DirectWrite::GetDC()->EndDraw();
}


void SceneManager::ChangeScene(string name)
{
	CAMERA->SetPosition(0.0f, 0.0f);

	for (UINT i = 0; i < scenes.size(); i++)
	{
		scenes[i]->SetActive(false);

		if (scenes[i] == curScene)
		{
			latScene = scenes[i];
			latSceneNum = i;
		}

		if (scenes[i]->GetSceneName() == name)
			scenes[i]->ChangeScene();
	}
}