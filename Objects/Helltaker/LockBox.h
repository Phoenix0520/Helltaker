#pragma once

class LockBox : public GameObject
{
public:
	LockBox();
	~LockBox();

public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;


private:
	class Texture* texture = nullptr;

};