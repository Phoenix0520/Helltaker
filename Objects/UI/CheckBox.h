#pragma once

class CheckBox : public GameObject
{
public:
	CheckBox();
	~CheckBox();

public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;

	void SetHover(bool val) { hover = val; }
	void SetCheck(bool val) { check = val; }
	
	bool GetHover() { return hover; }
	bool GetCheck() { return check; }

private:
	class Texture* texture		= nullptr;
	class Texture* checkMark	= nullptr;

	bool hover = false;
	bool check = false;

};