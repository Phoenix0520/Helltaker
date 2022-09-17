#pragma once
class SinPistone : public GameObject
{
public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;
	void SetState(UINT state); 
	void SetMove(bool value) { m_bMove = value; m_Time = 0.0f; }

public:
	void SetMaxMin(float max, float min)
	{
		m_MaxHeight = max;
		m_MinHeight = min;
	}

private:
	class Animation *m_pAnimation = nullptr;
	float m_MaxHeight = 0.0f;
	float m_MinHeight = 0.0f;
	UINT  m_nState = 0;
	bool  m_bMove = false;
	float m_Time = 0.0f;
	int   m_nStep = 0;
public:
	SinPistone();
	~SinPistone();
};
