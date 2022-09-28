#pragma once
class ChainVH : public GameObject
{
public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;
	void SetValue(int value, int hoiz);
	void SetState(int value) { m_nState = value; }
private:
	class Texture   *m_Texture                = nullptr;
	float  m_Time = 0.0f;
	vector<int>     m_cvDisplay;
	vector<int>     m_cvAngle;
	int   m_nState = 0;
	float  m_Angle;

public:
	ChainVH();
	~ChainVH();
};
