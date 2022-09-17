#pragma once
class SinPyre : public GameObject
{
public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;
	bool IsPlay();
	void SetState(int nState) { m_nState = nState; }
	

private:
	int   m_nState = 1;     // 0 : Box, 1 : Box+SynPyre(Yellow), 2: Box+SynPyre(White)
	class Animation *m_pAnimation    = nullptr;
	class Texture   *m_Texture       = nullptr;
	class Texture   *m_TextureNoFire = nullptr;
public:
	SinPyre();
	~SinPyre();
};
