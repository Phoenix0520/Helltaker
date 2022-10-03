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

private:
	vector<UINT> hp;

	class Texture* texture = nullptr;

};
