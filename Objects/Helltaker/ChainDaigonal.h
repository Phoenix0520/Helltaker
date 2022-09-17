#pragma once
class ChainDaigonal : public GameObject
{
public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;
	void SetState(int nState);
	void SetHP(int x, int y);
	void SetGapY(float y) { m_Gap = y; }
	bool IsScuccess() { return m_bSuccess; }


private:
	int   m_nState = 0;     
	class Texture   *m_Texture       = nullptr;
	class Texture   *m_TextureBroken = nullptr;
	vector<int>   m_cvDisplay;
	Vector2  MovePosition[6];
	Vector3  MoveRotation[6];
	int      Count[6];
	void     ResetValue(int id, int x, int y);
	float    m_BrokenTime = 0.0f;
	int      m_BrokenID = -1;
	float    m_BrokenMove = 0.0f;

	float    m_EffectTime = 0.0f;
	int      m_EffectID = -1;
	float    m_EffectMove = 0.0f;

	float    m_Gap = 0.0f;
	bool     m_bSuccess = false;

public:
	ChainDaigonal();
	~ChainDaigonal();
};
