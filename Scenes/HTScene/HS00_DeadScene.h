#pragma once
class HS00_DeadScene : public Scene
{
public:
	HS00_DeadScene();
	~HS00_DeadScene();

public:
	void Update() override;
	void Render() override;
	void ChangeScene() override;

	void SetState(int val) { state = val; }
	void SetScript(wstring str, int row) { script[row] = str; }

private:
	class Animation* animation	= nullptr;
	class Animation* animation2 = nullptr;
	class Rect2*		 rect		= nullptr;
	
	int state = 0;
	float bloodTime = 0.0f;
	float alpha = 1.0f;
	bool soundPlay = false;


	wstring script[4];
	
};