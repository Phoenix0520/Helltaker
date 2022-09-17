#pragma once

class HS15_Chapter09 : public Scene
{
public:
	HS15_Chapter09();
	~HS15_Chapter09();

public:
	void Update() override;
	void Render() override;
	void ChangeScene() override;

private:
	class Texture* texture = nullptr;

	float timer = 0.25f;
};