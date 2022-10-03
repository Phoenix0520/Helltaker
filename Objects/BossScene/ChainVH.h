#pragma once

class ChainVH : public GameObject
{
public:
	ChainVH();
	~ChainVH();

public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;

	void SetPosByID(int id);

	//void PushChain(int index, int type, int val);

	bool IsAttacking() { return attacking; }

private:
	class Texture* texture = nullptr; 
	//UINT activated;
	bool attacking = false;
	
	//int actIndex = 0;

	float time = 0.0f;


};
