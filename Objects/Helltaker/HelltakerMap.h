#pragma once

class HelltakerMap
{
private: // ������, �Ҹ���
	HelltakerMap() {}
	~HelltakerMap() {}

public:	// ������
	enum State
	{
		wall		= 0,	// �̵� �Ұ� ����
		move		= 1,	// �̵� ���� ����
		helltaker	= 2,	// ĳ���Ͱ� ��ġ�� ��
		box			= 4,	// �����ϼ� �ִ� �ڽ�
		mob			= 8,	// ����
		trap		= 16,	// ����
		goal		= 32,	// ���� ����
		key			= 64,	// Ű
		lockBox		= 128,	// Ű�� ���� �ڽ�
		slate		= 256,	// ����
		daigonal	= 512
	};

public: // �����Լ�
	static HelltakerMap* GetInstance()
	{
		static HelltakerMap instance;

		return &instance;
	}
	// Singleton Instance
	
	void Clear();
	// 


	void SetMapValue(int y, int startX, int endX);
	void UpdatePosition(float x, float y);

	void AssignHelltaker(int x, int y, int hp);
	void AssignMob(string name, int x, int y);
	void AssignBox(string name, int x, int y);
	void AssignGoal(string name, int x, int y);
	void AssignTrap(string name, int x, int y);
	void AssignTrap(string name, int x, int y, int state);
	void AssignKey(string name, int x, int y);
	void AssignLockBox(string name, int x, int y);
	void AssignFire(string name, float x, float y, int aniID);
	void AssignSlate(string name, int x, int y);
	void AssignObject(string name, int type, int x, int y);

	// Assign
			
	Vector2		GetPosition(int x, int y);		// x, y ���� ������ ����ǥ��
	int			GetSizeX() { return sizeX; }
	int			GetSizeY() { return sizeY; }
	int			GetValue(int x, int y);
	bool		IsWall(int x, int y);
	bool		IsMob(int x, int y);
	bool		IsBox(int x, int y);
	bool		IsGoal(int x, int y);
	bool		IsTrap(int x, int y);
	bool		IsKey(int x, int y);
	bool		IsLockBox(int x, int y);
	bool		IsSlate(int x, int y);
	bool		IsAnotherObject(int x, int y);

	POINT		GetMapXY(Vector2 position);
	GameObject* GetGameObject(int x, int y);
	GameObject* GetSecondObject(int x, int y);
	// Getter

	void SetSize(int x, int y, bool reset = true);
	void SetValue(int x, int y, State state, GameObject* object);
	void ReSetValue(int x, int y);
	void ReSetValue(int x, int y, State state);
	void ReSetAnotherValue(State state);
	void SetOffset(float x, float y) { this->offset = Vector2(x, y); }
	void SetOffset(Vector2 offset) { this->offset = offset; }
	void AddOffset(float x, float y) { this->offset += Vector2(x, y); }
	void AddOffset(Vector2 val) { this->offset += offset; }
	Vector2 GetOffset() { return this->offset; }
	string GetName(int x, int y);
	// Setter


private: // �������
	struct HTMap
	{
		State state;
		class GameObject* gameObject = nullptr;
		class GameObject* secondObject = nullptr;
	};

	vector<HTMap*> maps;
	vector<string> names;
	// map ���� ��� vector

	int sizeX = 0;
	int sizeY = 0;
	// map �� ũ��

	Vector2 offset		= Vector2(0.0f, 0.0f); // �»���� ��ǥ
	Vector2 offsetSize	= Vector2(100.0f, 100.0f);	// �� ĭ�� ũ��
	// offset

	Vector2 position	= Vector2(0.0f, 0.0f);
};