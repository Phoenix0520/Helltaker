#pragma once
class HS17_BossScene : public Scene
{
public:
	struct  Scenario
	{
		int   State;          // Ready,Attack
		int   horizontal;     // Veritical, HoriZontal
		int   vertical;       // 수직(7), 수평(4-5)
		float Time;           // 
	};


public:
	void Update() override;
	void Render() override;
	void ChangeScene() override;
	void OnDialog(); //Goal이 됬을때 클리어 이펙트 뿌릴때 이용
	void IncrementStage() { m_Stage++; }

private:
	void Sample();
	void ShowMap(float x, float y);
	void SetScenario1();
	//void SetScenario2();
	//void SetScenario3();
	//void SetScenario4();
	void UpdateChain();
	void UpdateBridge();
	void StartBridge();

	 
private: 
	void DrawBanner(wstring strBanner, float cx, float cy, float size, int r, int g, int b);
	class Texture* m_pBackground = nullptr;
	class Texture* m_pBackground2 = nullptr;
	class Texture* m_pBackground3 = nullptr;

	class Texture* m_pBlock = nullptr;
	class Texture* m_pBlock2 = nullptr;      // 추가
	class Texture* m_pSinPanel = nullptr;


	class Texture* m_pSinWheel = nullptr;

	class Texture* m_pSinCoreL = nullptr;
	class Texture* m_pSinCoreR = nullptr;
	class SinPyre* m_pSinPyre1 = nullptr;
	class SinPyre* m_pSinPyre2 = nullptr;
	class SinPyre* m_pSinPyre3 = nullptr;
	class SinPyre* m_pSinPyre4 = nullptr;

	class ChainVH*		 m_pChainVH = nullptr;
    class ChainDaigonal* m_pChainDaigonal = nullptr;

	class Judge*         m_pJudge = nullptr;
	class Line*          m_cvGrid;        // Grid Line

	int   m_nStep = 0;
	int   m_Stage = 1;
	float m_Time = 0.0f;
	int   m_nScenarioCount = 0;

	vector<Scenario> m_cvScenario;
public:
	HS17_BossScene();
	~HS17_BossScene();
};
