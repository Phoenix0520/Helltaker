#pragma once
class Judge : public GameObject
{
public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;
	bool IsPlay();

private:
	int   m_nState = 0;
	class Animation *m_pAnimation    = nullptr;
	class Animation *m_pDustAnimation = nullptr;
public:
	Judge();
	~Judge();
};
