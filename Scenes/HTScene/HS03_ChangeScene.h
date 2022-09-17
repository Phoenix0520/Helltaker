#pragma once

class HS03_ChangeScene : public Scene
{
public:
	HS03_ChangeScene();
	~HS03_ChangeScene();

public:
	void Update() override;
	void Render() override;
	void ChangeScene() override;

private:
	class Animation* animation = nullptr;

};