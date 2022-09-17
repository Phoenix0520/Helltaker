#pragma once
class Kick : public GameObject
{
public:
	Kick();
	~Kick();

public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;

	void Random();

	bool IsPlay();
	int GetState() { return state; }
	// Getter

private:
	Animation* animation = nullptr;
	int state = 0;

};