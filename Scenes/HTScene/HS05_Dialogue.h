#pragma once
class HS05_Dialogue : public Scene
{
public:
	HS05_Dialogue();
	~HS05_Dialogue();

public:
	void Update() override;
	void Render() override;
	void ChangeScene() override;
	// override

	void UpdateEX();
	void RenderEX();
	// LUCIFER
	
	void UpdateEX2();
	void RenderEX2();
	// JUDGEMENT

	void DrawBanner(wstring str, float cx, float cy, float size, int r, int g, int b);
	// Function

	void SetAttibute(wstring banner, wstring button1, wstring button2); // 모든 설정을 초기화 하는 함수
	void SetSceneID(int id);
	// Setter

	int GetSceneID() { return sceneID; }
	// Getter

private:
	class Texture*		background[2];
	class Texture*		texture[20];

	class Animation*	animation		= nullptr;
	class Animation*	successMotion	= nullptr;
	class Animation*	lucifer			= nullptr;

	class Button*	button1		= nullptr;
	class Button*	button2		= nullptr;

	class Booper*	booper		= nullptr;

	vector<wstring>	script1;
	vector<wstring>	script2;
	vector<wstring>	script3;

	wstring banner;
	wstring strbutton1;
	wstring strbutton2;

	int sceneID		= 0;
	int step		= 0;
	float time		= 0.0f;
	float timer		= 5.0f;


	bool enter			= false;
	bool click			= false;
	bool success		= false;
	bool badRoute		= false;
	bool successRoute	= false;
	bool soundPlay		= false;
};