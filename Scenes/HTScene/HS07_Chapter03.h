#pragma once

class HS07_Chapter03 : public Scene
{
public:
	HS07_Chapter03();
	~HS07_Chapter03();

public:
	void Update() override;
	void Render() override;
	void ChangeScene() override;

private:
	class Texture* texture = nullptr;
};