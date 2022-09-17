#pragma once

class HS02_Prologue : public Scene
{
public:
	HS02_Prologue();
	~HS02_Prologue();

public:
	void Update() override;
	void Render() override;
	void ChangeScene() override;

private:
	class Texture*		scenes[3];
	class Booper*		booper	= nullptr;
	class Rect2*		rect	= nullptr;

	int sceneNum = 0;
	wstring script[3];
};