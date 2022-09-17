#pragma once
class Chain : public GameObject
{
public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;
	void SetMove(bool value) { m_bMove = value; m_Time = 0.0f; }
private:
	float m_Time = 0.0f;
	bool  m_bMove = false;
	class Texture *m_pTexture[3];

public:
	Chain();
	~Chain();
};
