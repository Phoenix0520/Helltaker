#pragma once

class HS19_MapEditor :public Scene
{
public:
	HS19_MapEditor();
	~HS19_MapEditor();

public:
	void Update() override;
	void Render() override;
	void ChangeScene() override;

public:
	void SetOffset(Vector2 val) { offset = val; }
	void SetOffset(float x, float y) { offset = Vector2(x, y); }

	void ResetAnotherValue(UINT state);
	void ShowGUI();
	void ReadCSVFile(string file);
	void WriteCSVFile(string file);

	void GUISetMap();
	void GUIAddObj();
	void GUISaveMap();

	Vector2 GetOffset() { return offset; }

private:
	class Texture* background	= nullptr;	// ���
	class Texture* mapBG		= nullptr;  // ������ ���� ���

	vector<class Texture*> tempTexture; 	// �̸����� �ؽ���
	vector<class Texture*> mapTile;			// ���� Ÿ��
	vector<class GameObject*> obj;			// �ʿ� ���� ������Ʈ

	vector<string> boxes;
	vector<string> mobs;
	vector<string> traps;
	vector<string> goals;
	vector<string> fires;

	Vector2 offset = Vector2(0.0f, 0.0f);
	vector<vector<UINT>> mapObj;
	vector<vector<int>> data;
	vector<UINT> mapObjX;
	vector<UINT> mapObjY;
	int mapSize[2];

	bool init = false;
	bool inserting = false;
	bool deleting = false;
	bool toggleTrap = false;
	bool drag = false;

	bool nokey = true;
	bool warning = false;
	bool load = false;
	bool save = false;

	int combo = 0;
	int chapter = 0;
	int stageHp = 0;
	int file = 0;
};