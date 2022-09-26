#include "framework.h"
#include "HelltakerMap.h"
#include "Helltaker.h"
#include "Mob.h"
#include "Box.h"
#include "Trap.h"
#include "Slate.h"
#include "LockBox.h"
#include "Key.h"
#include "Goal.h"
#include "Fire.h"

void HelltakerMap::Clear()
{
	for (UINT i = 0; i < maps.size(); i++)
		SAFE_DELETE(maps[i]);
	maps.erase(maps.begin(), maps.end());

	sizeX = sizeY = 0;

	CAMERA->SetObject(nullptr);
}

//////////////////////////////////////////////////////////////////////////////
//
//	x = row, y = column 을 넣으면 실제 x, y 좌표를 반환해준다.
//
//////////////////////////////////////////////////////////////////////////////

Vector2 HelltakerMap::GetPosition(int x, int y)
{
	Vector2 position = Vector2();

	position.x = offset.x + x * offsetSize.x;
	position.y = offset.y - y * offsetSize.y;

	return position;
}
///////////////////////////////////////////////////////
//	Debugging
//
///////////////////////////////////////////////////////
int HelltakerMap::GetValue(int x, int y)
{
	int id = sizeX * y + x;
	// 2차원을 1차원으로 계산한것이다.

	State oldState = maps[id]->state;
	return (int)oldState;
}

bool HelltakerMap::IsWall(int x, int y)
{
	// 이상처리
	if (y < 0 || x < 0 || sizeX < 0 || sizeY < 0)
		return true;

	int id = sizeX * y + x;
	State oldState = maps[id]->state;

	if (oldState == 0)
		return true;
	else
		return false;
}

bool HelltakerMap::IsMob(int x, int y)
{
	int id = sizeX * y + x;
	State oldState = maps[id]->state;

	if (oldState & State::mob)
		return true;
	else
		return false;
}

bool HelltakerMap::IsBox(int x, int y)
{
	int id = sizeX * y + x;
	State oldState = maps[id]->state;

	if (oldState & State::box)
		return true;
	else
		return false;
}

bool HelltakerMap::IsGoal(int x, int y)
{
	int id = sizeX * y + x;
	State oldState = maps[id]->state;

	if (oldState & State::goal)
		return true;
	else
		return false;
}

bool HelltakerMap::IsTrap(int x, int y)
{
	int id = sizeX * y + x;
	State oldState = maps[id]->state;

	if (oldState & State::trap)
		return true;
	else
		return false;
}

bool HelltakerMap::IsKey(int x, int y)
{
	int id = sizeX * y + x;
	State oldState = maps[id]->state;

	if (oldState & State::key)
		return true;
	else
		return false;
}

bool HelltakerMap::IsLockBox(int x, int y)
{
	int id = sizeX * y + x;
	State oldState = maps[id]->state;

	if (oldState & State::lockBox)
		return true;
	else
		return false;
}

bool HelltakerMap::IsSlate(int x, int y)
{
	int id = sizeX * y + x;
	State oldState = maps[id]->state;

	if (oldState & State::slate)
		return true;
	else
		return false;
}

bool HelltakerMap::IsAnotherObject(int x, int y)
{
	int id = sizeX * y + x;

	if (maps[id]->secondObject)
		return true;
	else
		return false;
}

/////////////////////////////////////////////////////////
//	실제 좌표를 넣으면 Map 의 X Y 를 계산하는 함수
/////////////////////////////////////////////////////////

POINT HelltakerMap::GetMapXY(Vector2 position)
{
	position.x = fabs(position.x - offset.x);
	position.y = fabs(position.y - offset.y);

	POINT val = POINT{ 0, 0 };
	
	val.x = (int)(position.x / offsetSize.x);
	val.y = (int)(position.y / offsetSize.y);

	return val;
}

GameObject* HelltakerMap::GetGameObject(int x, int y)
{
	int id = sizeX * y + x;
	return maps[id]->gameObject;
}

GameObject* HelltakerMap::GetSecondObject(int x, int y)
{
	int id = sizeX * y + x;
	return maps[id]->secondObject;
}


void HelltakerMap::SetSize(int x, int y, bool reset)
{
	Clear();
	for (int i = 0; i < (x * y); i++)
	{
		if (reset)
		{
			HTMap* map = new HTMap;
			map->state = wall;
			map->gameObject = nullptr;
			map->secondObject = nullptr;

			maps.push_back(map);
			names.push_back("");
		}
	}


	sizeX = x;
	sizeY = y;
}

/////////////////////////////////////////////////////
// Map 에 Object 를 Assign 한다.
////////////////////////////////////////////////////
void HelltakerMap::SetValue(int x, int y, State state, GameObject* object)
{
	int id = sizeX * y + x;
	// 2차원을 1차원으로 계산한것이다.

	State oldState = maps[id]->state;

	maps[id]->state = (State)((int)oldState | (int)state);
	
	// 집어넣은 state 로 바꿔준다.

	if (state == State::trap)
	{
		maps[id]->secondObject = object;

		if (maps[id]->gameObject)
			return;
	}
	
	if (state == State::key)
	{
		maps[id]->secondObject = object;

		if (maps[id]->gameObject)
			return;
	}

	if (state == State::slate)
	{
		maps[id]->secondObject = object;

		if (maps[id]->gameObject)
			return;
	}

	maps[id]->gameObject = object;
}

void HelltakerMap::ReSetValue(int x, int y)
{
	int id = sizeX * y + x;

	State oldState = maps[id]->state;
	maps[id]->state = wall;

	maps[id]->gameObject = nullptr;
}

void HelltakerMap::ReSetValue(int x, int y, State state)
{
	int id = sizeX * y + x;

	State oldState = maps[id]->state;
	maps[id]->state = (State)((int)oldState ^ (int)state);

	maps[id]->gameObject = nullptr;
}

void HelltakerMap::ReSetAnotherValue(State state)
{
	for (UINT x = 0; x < sizeX; x++)
	{
		for (UINT y = 0; y < sizeY; y++)
		{
			int id = sizeX * y + x;
			
			State oldState = maps[id]->state;
			
			if (maps[id]->state == state + move)
			{
				maps[id]->state = move;
				maps[id]->gameObject = nullptr;
			}
		}
	}
}

string HelltakerMap::GetName(int x, int y)
{
	int id = sizeX * y + x;

	cout << names[id] << endl;

	return names[id];
}

void HelltakerMap::SetMapValue(int y, int startX, int endX)
{
	for (int i = startX; i <= endX; i++)
	{
		SetValue(i, y, State::move, nullptr);
	}
}

void HelltakerMap::UpdatePosition(float x, float y)
{
	for (UINT i = 0; i < maps.size(); i++)
	{
		GameObject* obj = maps[i]->gameObject;

		if (!obj) 
			continue;

		State oldState = maps[i]->state;
		if (oldState & State::helltaker)
		{
			if (y == -100.0f)
				continue;
		}

		Vector2 pos = obj->GetPosition();
		obj->SetPosition(pos.x + x, pos.y + y);
	}

	SetOffset(GetOffset().x + x, GetOffset().y + y);
}

void HelltakerMap::AssignHelltaker(int x, int y, int hp)
{
	Helltaker* obj1 = dynamic_cast<Helltaker*>(OBJMANAGER->FindObject("Helltaker"));

	if (obj1 != nullptr)
	{
		Vector2 pos = GetPosition(x, y);
		obj1->SetPosition(pos);
		SetValue(x, y, State::helltaker, obj1);

		// casting
		Helltaker* obj2 = obj1;
		obj2->SetHP(hp);
		obj2->Reset();

		int id = sizeX * y + x;

		names[id] = "Helltaker";

		OBJMANAGER->AddObjectStrings("Helltaker");
	}
}

void HelltakerMap::AssignMob(string name, int x, int y)
{
	// Mob
	{
		OBJMANAGER->FindObject(name)->SetPosition(GetPosition(x, y));
		SetValue(x, y, State::mob, OBJMANAGER->FindObject(name));

		Vector2 pos = GetPosition(x, y);
		OBJMANAGER->FindObject(name)->SetPosition(pos);
		OBJMANAGER->FindObject(name)->SetActive(true);
		Mob* object = dynamic_cast<Mob*>(OBJMANAGER->FindObject(name));
		if (object)
			object->Reset();
		else
			MessageBoxA(nullptr, name.c_str(), "Object Missing", MB_OK);

		int id = sizeX * y + x;
		names[id] = name;

		OBJMANAGER->AddObjectStrings(name);
	}
}

void HelltakerMap::AssignBox(string name, int x, int y)
{
	// Box
	{
		OBJMANAGER->FindObject(name)->SetPosition(GetPosition(x, y));
		SetValue(x, y, State::box, OBJMANAGER->FindObject(name));

		Vector2 pos = GetPosition(x, y);
		OBJMANAGER->FindObject(name)->SetPosition(pos);
		OBJMANAGER->FindObject(name)->SetActive(true);
		Box* object = dynamic_cast<Box*>(OBJMANAGER->FindObject(name));
		if (object)
		{
			object->Reset();
		}
		else
			MessageBoxA(nullptr, name.c_str(), "Object Missing", MB_OK);

		int id = sizeX * y + x;
		names[id] = name;

		OBJMANAGER->AddObjectStrings(name);
	}
}

void HelltakerMap::AssignGoal(string name, int x, int y)
{
	// Goal
	{
		OBJMANAGER->FindObject(name)->SetPosition(GetPosition(x, y));
		SetValue(x, y, State::goal, OBJMANAGER->FindObject(name));

		Vector2 pos = GetPosition(x, y);
		OBJMANAGER->FindObject(name)->SetPosition(pos);
		OBJMANAGER->FindObject(name)->SetActive(true);
		Goal* object = dynamic_cast<Goal*>(OBJMANAGER->FindObject(name));
		if (object)
			object->Reset();
		else
			MessageBoxA(nullptr, name.c_str(), "Object Missing", MB_OK);

		int id = sizeX * y + x;
		names[id] = name;

		OBJMANAGER->AddObjectStrings(name);
	}
}

void HelltakerMap::AssignTrap(string name, int x, int y)
{
	// Trap
	{
		OBJMANAGER->FindObject(name)->SetPosition(GetPosition(x, y));
		SetValue(x, y, State::trap, OBJMANAGER->FindObject(name));

		Vector2 pos = GetPosition(x, y);
		OBJMANAGER->FindObject(name)->SetPosition(pos);
		OBJMANAGER->FindObject(name)->SetActive(true);

		int id = sizeX * y + x;
		names[id] = name;

		OBJMANAGER->AddObjectStrings(name);
		
		Trap* object = dynamic_cast<Trap*>(OBJMANAGER->FindObject(name));
		if (object)
		{
			object->Reset();
			object->SetState(0);
		}
		else
			MessageBoxA(nullptr, name.c_str(), "Object Missing", MB_OK);
	}
}

void HelltakerMap::AssignTrap(string name, int x, int y, int state)
{
	// Trap
	{
		OBJMANAGER->FindObject(name)->SetPosition(GetPosition(x, y));
		SetValue(x, y, State::trap, OBJMANAGER->FindObject(name));

		Vector2 pos = GetPosition(x, y);
		OBJMANAGER->FindObject(name)->SetPosition(pos);
		OBJMANAGER->FindObject(name)->SetActive(true);
		Trap* object = dynamic_cast<Trap*>(OBJMANAGER->FindObject(name));
		if (object)
		{
			object->Reset();
			object->SetState(state);
		}
		else
			MessageBoxA(nullptr, name.c_str(), "Object Missing", MB_OK);

		int id = sizeX * y + x;
		names[id] = name;
		OBJMANAGER->AddObjectStrings(name);
	}
}

void HelltakerMap::AssignKey(string name, int x, int y)
{
	// Key
	{
		OBJMANAGER->FindObject(name)->SetPosition(GetPosition(x, y));
		SetValue(x, y, State::key, OBJMANAGER->FindObject(name));

		Vector2 pos = GetPosition(x, y);
		OBJMANAGER->FindObject(name)->SetPosition(pos);
		OBJMANAGER->FindObject(name)->SetActive(true);
		Key* object = dynamic_cast<Key*>(OBJMANAGER->FindObject(name));
		if (object)
			object->Reset();
		else
			MessageBoxA(nullptr, name.c_str(), "Object Missing", MB_OK);

		int id = sizeX * y + x;
		names[id] = name;
		OBJMANAGER->AddObjectStrings(name);
	}
}

void HelltakerMap::AssignLockBox(string name, int x, int y)
{
	// LockBox
	{
		OBJMANAGER->FindObject(name)->SetPosition(GetPosition(x, y));
		SetValue(x, y, State::lockBox, OBJMANAGER->FindObject(name));

		Vector2 pos = GetPosition(x, y);
		OBJMANAGER->FindObject(name)->SetPosition(pos);
		OBJMANAGER->FindObject(name)->SetActive(true);
		LockBox* object = dynamic_cast<LockBox*>(OBJMANAGER->FindObject(name));
		if (object)
			object->Reset();
		else
			MessageBoxA(nullptr, name.c_str(), "Object Missing", MB_OK);

		int id = sizeX * y + x;
		names[id] = name;
		OBJMANAGER->AddObjectStrings(name);
	}
}

void HelltakerMap::AssignFire(string name, float x, float y, int aniID)
{
	// Fire
	{
		OBJMANAGER->FindObject(name)->SetPosition(x, y);
		OBJMANAGER->FindObject(name)->SetActive(true);
		
		Fire* object = dynamic_cast<Fire*>(OBJMANAGER->FindObject(name));

		if (object)
		{
			object->SetState(aniID);
			object->Reset();
		}
		else
			MessageBoxA(nullptr, name.c_str(), "Object Missing", MB_OK);

		int id = sizeX * y + x;
		names[id] = name;
		OBJMANAGER->AddObjectStrings(name);
	}
}

void HelltakerMap::AssignSlate(string name, int x, int y)
{
	// Slate
	{
		OBJMANAGER->FindObject(name)->SetPosition(GetPosition(x, y));
		SetValue(x, y, State::slate, OBJMANAGER->FindObject(name));

		Vector2 pos = GetPosition(x, y);
		OBJMANAGER->FindObject(name)->SetPosition(pos);
		OBJMANAGER->FindObject(name)->SetActive(true);
		Slate* object = dynamic_cast<Slate*>(OBJMANAGER->FindObject(name));
		if (object)
			object->Reset();
		else
			MessageBoxA(nullptr, name.c_str(), "Object Missing", MB_OK);

		int id = sizeX * y + x;
		names[id] = name;

		OBJMANAGER->AddObjectStrings(name);
	}
}

void HelltakerMap::AssignObject(string name, int type, int x, int y)
{
	OBJMANAGER->FindObject(name)->SetPosition(GetPosition(x, y));
	SetValue(x, y, (State)type, OBJMANAGER->FindObject(name));

	Vector2 pos = GetPosition(x, y);
	OBJMANAGER->FindObject(name)->SetPosition(pos);
	OBJMANAGER->FindObject(name)->SetActive(true);
	Slate* object = dynamic_cast<Slate*>(OBJMANAGER->FindObject(name));
	if (object)
		object->Reset();
	else
		MessageBoxA(nullptr, name.c_str(), "Object Missing", MB_OK);

	int id = sizeX * y + x;
	names[id] = name;

	OBJMANAGER->AddObjectStrings(name);
}
