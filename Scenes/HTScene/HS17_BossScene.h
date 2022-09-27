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

};