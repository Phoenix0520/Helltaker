 #pragma once

class HS04_Chapter01 : public Scene
{
public:
	HS04_Chapter01();
	~HS04_Chapter01();

public:
	void Update() override;
	void Render() override;
	void ChangeScene() override;

private:
	class Texture*	texture	= nullptr;
	class Clear*	test	= nullptr;
	class Booper*	booper	= nullptr;

	bool soundPlaying = false;
};