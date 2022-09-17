#pragma once

class LoveSign : public GameObject
{
public:
	LoveSign();
	~LoveSign();

public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;

private:
	class Texture* loveSign = nullptr;

	bool plus = true;

	float val = 35.0f;
};