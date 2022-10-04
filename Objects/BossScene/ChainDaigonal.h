#pragma once
class ChainDaigonal : public GameObject
{
public:
	ChainDaigonal();
	~ChainDaigonal();

public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;

	void Attack(int index);

private:
	vector<class Texture*> texture;
	vector<UINT> hp;
	class Texture* broken = nullptr;
	class Texture* hpBorder = nullptr;
	class Texture* hpBar = nullptr;

	float time = 0.0f;
	float ctime = 0.0f;


};
