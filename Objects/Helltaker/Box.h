#pragma once

class Box : public GameObject
{
public:
	Box();
	~Box();

public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;

	void MoveObject(Direction direction, Vector2& position);

	void SetID(int id) { textureID = id; }
	int  GetID() { return textureID; }

private:
	class Texture* texture = nullptr;
	int textureID = 0;
	int soundID = 0;

};