#pragma once

class OptionMenu : public GameObject
{
public:
	OptionMenu();
	~OptionMenu();

public:
	enum WinType
	{
		FULLSCREEN = 0,
		WINDOWEDFULLSCREEN,
		WINDOWED,
	};

public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;

	void WinSetUpdate();
	void WinSetRender();

	void EnumerateAdapterOutputResolution();

private:
	class Texture* background = nullptr;
	class Texture* border = nullptr;

	class OptionButton* button[5];
	class CheckBox* checkBox = nullptr;

	WinType type = FULLSCREEN;

	vector<pair<UINT, UINT>> resList;

	bool windowSetting = false;


};