#pragma once

class HS10_Chapter05 : public Scene
{
public:
	HS10_Chapter05();
	~HS10_Chapter05();

public:
	void Update() override;
	void Render() override;
	void ChangeScene() override;

private:
	class Texture* texture = nullptr;
};