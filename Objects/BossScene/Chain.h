#pragma once

class Chain : public GameObject
{
public:
	Chain(float x);
	~Chain();

public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;
	
	void SetMove(bool val) { move = val; }
	void SetMoveVal(float val) { moveVal = val; }

	bool GetMove() { return move; }
	float GetMoveVal() { return moveVal; }

private:
	vector<class Texture*> texture;

	bool move = false;

	float moveVal = 0.0f;
	float x = 0.0f;
};
