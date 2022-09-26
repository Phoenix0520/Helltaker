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

	void GUISetMap();
	void GUIAddObj();
	void GUISaveMap();

	Vector2 GetOffset() { return offset; }

private:
	class Texture* background	= nullptr;	// 배경
	class Texture* mapBG		= nullptr;  // 설정할 맵의 배경

	vector<class Texture*> tempTexture; 	// 미리보기 텍스쳐
	vector<class Texture*> mapTile;			// 맵의 타일
	vector<class GameObject*> obj;			// 맵에 넣을 오브젝트

	
	vector<string> boxes;
	vector<string> mobs;
	vector<string> traps;
	vector<string> goals;

	Vector2 offset = Vector2(0.0f, 0.0f);
	vector<vector<UINT>> mapObj;
	vector<UINT> mapObjX;
	vector<UINT> mapObjY;

	bool init = false;
	bool inserting = false;
	bool deleting = false;
	bool toggleTrap = false;
	bool drag = false;

	int combo = 0;
	int chapter = 0;
	int stageHp = 0;

};