#pragma once

class GameObject;

class ObjectManager	// 추상클래스
{
private:	// 생성자, 소멸자
	ObjectManager();
	~ObjectManager();

public:
	static ObjectManager* GetInstance()
	{
		static ObjectManager instance;

		return &instance;
	}

public:	// 순수 가상함수
	void		Update(string name, Matrix V, Matrix P);
	void		Render(string name);

	void		UpdateAll(Matrix V, Matrix P);
	void		RenderAll();

	void		AddObject(string name, GameObject* obj);
	void		AddObjectStrings(string name) { objectStrings.push_back(name); DeleteOverlapedObjectString(); }
	void		DeleteObjectString(string name);
	void		DeleteOverlapedObjectString();
	void		ClearObjectStrings()						{ objectStrings.clear(); }

	void SetPosition(string name, Vector2 pos);
	void SetPosition(string name, float x, float y);

	GameObject* FindObject(string name);

private:
	class HS01_IntroScene* scene = nullptr;

	map<string, GameObject*> objects;
	vector<string> objectStrings;
};