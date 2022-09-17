#pragma once

class Huge : public GameObject
{
public:
	Huge();
	~Huge();

public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;

	void Random();

	bool IsPlay();

	void SetState(int val) { state = val; }

	int GetState() { return state; }
	// Getter

private:
	Animation* animation = nullptr;
	int state = 0;

};