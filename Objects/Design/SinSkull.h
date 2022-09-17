#pragma once
class SinSkull : public GameObject
{
public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;
	void SetMaxMin(float max, float min)
	{
		m_MaxHeight = max;
		m_MinHeight = min;
	}
	void SetState(int state) { m_nState = state; }
	void SetStep(int step) { m_nStep = step; }
private:
	float m_Time = 0.0f;
	class Texture *m_pTexture[3];
	float m_MaxHeight = 0.0f;
	float m_MinHeight = 0.0f;
	int   m_nState = 0;
	int   m_nStep = 0;

public:
	SinSkull();
	~SinSkull();
};
