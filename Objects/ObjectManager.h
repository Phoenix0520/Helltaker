#pragma once

class ObjectManager // �̱��� ������ ����
{
private:
	ObjectManager();
	~ObjectManager();
	// ���������� �ܺ� ���� �� �Ҹ� �Ұ�
public:	
	static ObjectManager* GetInstance()
	{
		static ObjectManager instance;
		return &instance;
	}
	// Singleton Instance ��ȯ

	void Update(string name, Matrix V, Matrix P);
	void Render(string name);
	// Ư�� ������Ʈ�� ����, ����մϴ�.
	void UpdateAll(Matrix V, Matrix P);
	void RenderAll();
	// ��� ������Ʈ�� ����, ����մϴ�.
		 
	void AddObject(string name, GameObject* obj);
	// ������Ʈ�� �߰��մϴ�.
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