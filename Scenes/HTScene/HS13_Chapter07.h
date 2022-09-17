#pragma once

class HS13_Chapter07 : public Scene
{
public:
	HS13_Chapter07();
	~HS13_Chapter07();

public:
	void Update() override;
	void Render() override;
	void ChangeScene() override;

private:
	class Texture* texture = nullptr;
};