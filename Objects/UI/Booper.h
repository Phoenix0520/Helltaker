#pragma once

class Booper : public GameObject
{
public:
	Booper();
	~Booper();

public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;

	void SetClick(bool val) { click = val; }

	bool IsClick() { return click; }

private:
	class Animation* animation = nullptr;

	bool click = false;
};