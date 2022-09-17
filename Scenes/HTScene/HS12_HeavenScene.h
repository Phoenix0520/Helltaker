#pragma once

class HS12_HeavenScene : public Scene
{
public:
	HS12_HeavenScene();
	~HS12_HeavenScene();

public:
	void Update() override;
	void Render() override;
	void ChangeScene() override;

private:
	class Texture*		scene	= nullptr;
	class Booper*		booper	= nullptr;
	class Rect2*		rect	= nullptr;

	int sceneNum = 0;
	wstring script;
};