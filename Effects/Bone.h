#pragma once

class Bone : public GameObject
{
public:
	Bone(int textureID, int angleID);
	~Bone();

public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;

	void Random();

	bool IsPlay();
	int GetState() { return state; }
	// Getter

private:
	Texture* texture = nullptr;
	int state = 0;
	int	angleID = 0;
	float gravity = 0.0f;
};