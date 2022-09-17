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

	Vector2 GetOffset() { return offset; }

private:
	class Texture* background	= nullptr;	// ���
	class Texture* tempTexture	= nullptr;	// �̸����� �ؽ���
	class Texture* mapBG		= nullptr;  // ������ ���� ���
	class Texture* mapTile[100];			// ���� Ÿ��

	class GameObject* obj[100];				// �ʿ� ���� ������Ʈ

	Vector2 offset = Vector2(0.0f, 0.0f);
	int size[2] = { 0, 0 };

	bool inserting = false;

};