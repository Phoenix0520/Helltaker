#pragma once
class HS01_IntroScene : public Scene
{
public:	// 생성자 소멸자
	HS01_IntroScene();
	~HS01_IntroScene();

public:	// 전역 함수
	void Update() override;
	void Render() override;
	void ChangeScene() override;
	
	void ResetButton();

	void UpdateChapterSelect(Matrix V, Matrix P);
	void RenderChapterSelect();

	void SetClick(int val) { enter = true; click = val; }
	void SetChapter(bool val) { chapter = val; }
	void AddLoadLevel() { if (loadLevel != 1) loadLevel--; else loadLevel = 0, loading = false; loadVal = 0; }
	void AddLoadVal() { loadVal++; }
	void Loading() { if (loading) loading = false; else loading = true; }

private: // 멤버 변수
	class Texture* background[3] = { nullptr, nullptr, nullptr };
	class Texture* beelFly = nullptr;
	class Texture* border = nullptr;

	class Texture* loadingAnim = nullptr;

	class Button*  button1 = nullptr;
	class Button*  button2 = nullptr;
	class Button*  button3 = nullptr;

	class ChapterButton* button[11];

	class Booper*  booper  = nullptr;

	float time = 0.0f;
	float timer = 3.0f;
	float buttonPos = -(MAIN->GetHeight() / 2);

	bool loading = true;
	bool chapter = false;
	bool enter = false;

	int loadLevel = 3;
	int loadVal = 0;
	int click = 0;
};