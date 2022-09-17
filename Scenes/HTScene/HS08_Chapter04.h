#pragma once

class HS08_Chapter04 : public Scene
{
public:
	HS08_Chapter04();
	~HS08_Chapter04();

public:
	void Update() override;
	void Render() override;
	void ChangeScene() override;

private:
	class Texture* texture = nullptr;
};