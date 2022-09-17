#pragma once

class OptionButton : public GameObject
{
public:
	OptionButton();
	~OptionButton();

public:
	enum Level
	{
		DISABLE = -1,
		MUTE,
		LOW,
		MIDDLE,
		HIGH
	};

public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;

	void SetHover(bool val) { if (val) PLAYSOUND("HOVER", sfxSize); hover = val; }
	void SetClick(bool val) { click = val; }
	void SetCombo(bool val) { combo = val; }
	void SetDisable(bool val) { disable = val; }
	void SetScript(wstring val) { script = val; }
	void SetLevel(Level val) { level = val; }
	void SetLevel(UINT val) { level = (Level)val; }
	void SetComboHover(UINT val) { comboHover = val; }
	void SetComboScript(vector<wstring> val) { comboScripts = val; }

	bool GetHover() { return hover; }
	bool GetClick() { return click; }
	bool GetCombo() { return combo; }
	bool GetDisable() { return disable; }
	wstring GetScript() { return script; }
	UINT GetComboHover() { return comboHover; }
	UINT GetLevel() { return level; }

private:
	class Texture* texture		= nullptr;
	class Texture* comboList	= nullptr;
	class Texture* cHover		= nullptr;

	wstring script = L"";

	bool hover = false;
	bool click = false;
	bool combo = false;
	bool disable = false;

	UINT comboHover = 0;
	UINT begin = 0;
	UINT end = 9;

	float scale = 0.0f;

	vector<wstring> comboScripts;

	Level level = DISABLE;
};