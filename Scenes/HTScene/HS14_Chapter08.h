#pragma once

class HS14_Chapter08 : public Scene
{
public:
	HS14_Chapter08();
	~HS14_Chapter08();

public:
	void Update() override;
	void Render() override;
	void ChangeScene() override;

private:
	class Texture* texture = nullptr;
	class Texture* UI = nullptr;

	int moveCount = 0;
	float movePos = 0.0f;
	float time = 0.0f;

};