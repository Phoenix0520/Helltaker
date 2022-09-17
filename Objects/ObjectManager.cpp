#include "framework.h"
#include "ObjectManager.h"
#include "HS01_IntroScene.h"
#include "Mob.h"
#include "Box.h"
#include "Trap.h"
#include "Slate.h"
#include "LockBox.h"
#include "Key.h"
#include "Goal.h"
#include "Fire.h"


ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
	for (auto a : objects)
		SAFE_DELETE(a.second);
	ClearObjectStrings();
}

void ObjectManager::Update(string name, Matrix V, Matrix P)
{
	GameObject* obj = FindObject(name);
	
	if (obj == nullptr)
		return;
	else
		obj->Update(V, P);
}

void ObjectManager::Render(string name)
{
	GameObject* obj = FindObject(name);
	if (obj == nullptr)
		return;

	obj->Render();
}

void ObjectManager::UpdateAll(Matrix V, Matrix P)
{
	for (auto a : objectStrings)
	{
		Update(a, V, P);
	}
}

void ObjectManager::RenderAll()
{
	for (auto a : objectStrings)
	{
		if (a != "NoDisplay")
			Render(a);
	}
}

void ObjectManager::AddObject(string name, GameObject * obj)
{
	objects.insert(make_pair(name, obj));
}

void ObjectManager::SetPosition(string name, Vector2 pos)
{
	GameObject* object = FindObject(name);

	if (!object) return;

	object->SetPosition(pos);
}

void ObjectManager::SetPosition(string name, float x, float y)
{
	GameObject* object = FindObject(name);

	if (!object) return;

	object->SetPosition(x, y);
}

GameObject* ObjectManager::FindObject(string name)
{
	GameObject* obj = nullptr;

	if (objects.count(name))
		obj = objects[name];

	return obj;
}
