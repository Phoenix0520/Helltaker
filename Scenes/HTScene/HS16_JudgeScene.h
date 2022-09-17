#pragma once
class HS16_JudgeScene : public Scene
{
public:
	HS16_JudgeScene();
	~HS16_JudgeScene();

public:
	void Update() override;
	void Render() override;
	void ChangeScene() override;
	// override

private:
	class Texture*	 background[6];
	class Texture*	 change = nullptr;
	class Texture*	 chain[6];

	class Animation* judgement = nullptr;
	class Animation* glove1 = nullptr;
	class Animation* glove2 = nullptr;

	class Booper*	booper = nullptr;

	float time = 1.0f;
	float timer = 0.0f;
	float ctime = 1.0f;
	float alpha = 0.0f;

	int step = 0;

	bool plus = true;
	bool cplus = true;
};