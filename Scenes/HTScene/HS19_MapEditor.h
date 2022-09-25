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

	void ShowGUI();

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

};