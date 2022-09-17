#pragma once

class HS06_Chapter02 : public Scene
{
public:
	HS06_Chapter02();
	~HS06_Chapter02();

public:
	void Update() override;
	void Render() override;
	void ChangeScene() override;

private:
	class Texture* texture = nullptr;
};