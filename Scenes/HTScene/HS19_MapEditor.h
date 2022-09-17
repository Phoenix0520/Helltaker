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
	class Texture* background	= nullptr;	// 배경
	class Texture* tempTexture	= nullptr;	// 미리보기 텍스쳐
	class Texture* mapBG		= nullptr;  // 설정할 맵의 배경
	class Texture* mapTile[100];			// 맵의 타일

	class GameObject* obj[100];				// 맵에 넣을 오브젝트

	Vector2 offset = Vector2(0.0f, 0.0f);
	int size[2] = { 0, 0 };

	bool inserting = false;

};