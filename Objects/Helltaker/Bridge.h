#pragma once
class Bridge : public GameObject
{
public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;
	void SetMove(bool value); 
	void SetMoveSpeed(int value) { m_MoveSpeed = value; }
	bool IsMoveable()        { return m_bMove; }
	void SetCallback(function<void()> cbFunction) { m_fpCallback = cbFunction; }
	float  Gap();
private:
	float m_Time = 0.0f;
	class Texture *m_pTexture[3];  // 시우학생
	bool  m_bMove = false;
	float m_MoveSpeed = 1.5f;
	function<void()>   m_fpCallback = nullptr;

public:
	Bridge();
	~Bridge();
};
