#pragma once
class Fire : public GameObject
{
public:
	Fire();
	~Fire();

public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;

	bool IsPlay();
	void SetState(int val) { state = val; }

private:
	int state = 0;	// 0 : box , 1 : box + fire , 2: box + white;
	float time = 0.0f;

	class Animation* animation = nullptr;
	class Texture* texture[2];

};