#pragma once

class Key : public GameObject
{
public:
	Key();
	~Key();

public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;

private:
	class Animation* animation = nullptr;
	
};