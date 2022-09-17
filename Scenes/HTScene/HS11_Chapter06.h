#pragma once

class HS11_Chapter06 : public Scene
{
public:
	HS11_Chapter06();
	~HS11_Chapter06();

public:
	void Update() override;
	void Render() override;
	void ChangeScene() override;

private:
	class Texture* texture = nullptr;
};