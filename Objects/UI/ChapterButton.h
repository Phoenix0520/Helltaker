#pragma once

class ChapterButton : public GameObject
{
public:
	ChapterButton(UINT num);
	~ChapterButton();

public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;

	void SetHover(bool val) { hover = val; if (val) PLAYSOUND("Hover", sfxSize); }
	void SetClick(bool val)	{ click = val; }

	bool GetHover() { return hover; }
	bool GetClick() { return click; }

private:
	class Texture* texture = nullptr;

	bool hover = false;
	bool click = true;

	wstring script = L"";
	UINT sceneNum = 0;

};