#pragma once

class HS17_BossScene : public Scene
{
public:
	HS17_BossScene();
	~HS17_BossScene();

public:
	void Update();
	void Render();
	void ChangeScene();

private:
	class Texture* background = nullptr;
	class Texture* rect = nullptr;
	class Texture* uprBorder = nullptr;
	class Texture* udrBorder = nullptr;

	class Animation* gear[2];

	class Piston* piston[2];
};