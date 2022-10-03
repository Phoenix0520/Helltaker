#pragma once

class ObjectManager // 싱글톤 디자인 패턴
{
private:
	ObjectManager();
	~ObjectManager();
	// 마찬가지로 외부 생성 및 소멸 불가
public:	
	static ObjectManager* GetInstance()
	{
		static ObjectManager instance;
		return &instance;
	}
	// Singleton Instance 반환

	void Update(string name, Matrix V, Matrix P);
	void Render(string name);
	// 특정 오브젝트를 구성, 출력합니다.
	void UpdateAll(Matrix V, Matrix P);
	void RenderAll();
	// 모든 오브젝트를 구성, 출력합니다.
		 
	void AddObject(string name, GameObject* obj);
	// 오브젝트를 추가합니다.
	void AddObjectStrings(string name) { objectStrings.push_back(name); DeleteOverlapedObjectString(); }
	void DeleteObjectString(string name);
	void DeleteOverlapedObjectString();
	void ClearObjectStrings() { objectStrings.clear(); }

	void SetPosition(string name, Vector2 pos);
	void SetPosition(string name, float x, float y);

	class GameObject* FindObject(string name);

private:
	class HS01_IntroScene* scene = nullptr;

	map<string, class GameObject*> objects;
	vector<string> objectStrings;
};