#pragma once

class Button : public GameObject
{
public:
	Button();
	~Button();
	
public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;

	// override

	void SetCallBack(function<void(int)> cbfunc) { buttonCallBack = cbfunc; }
	void SetHover(bool val) { if (val) PLAYSOUND("HOVER", sfxSize); hover = val; }
	void SetButtonString(wstring val) { buttonName = val; }
	void SetClick(bool val) { click = val; }
	void SetStatus(bool val) { select = val; }
	// Setter

	bool IsPointInRegion(Vector2 position);
	bool IsClick() { return click; }
	bool GetStatus() { return select; }
	bool GetHover() { return hover; }
	// Getter

private:
	class Texture* texture1	= nullptr;
	class Texture* texture2 = nullptr;

	bool	select = false;
	bool	hover  = false;
	bool	click  = false;
	wstring buttonName;

	float time;

	function<void(int)> buttonCallBack = nullptr;
};