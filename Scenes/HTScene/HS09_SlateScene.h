#pragma once
class HS09_SlateScene : public Scene
{
public:
	HS09_SlateScene();
	~HS09_SlateScene();

public:
	void Update() override;
	void Render() override;
	void ChangeScene() override;
	// override

	void SetSceneID(int id) { sceneID = id; }
	// Setter

	int GetSceneID() { return sceneID; }
	// Getter

private:
	class Texture*	background	= nullptr;
	class Texture*	texture[3];

	class Booper*	booper		= nullptr;

	float time = 0.0f;
	float ctime = 0.0f;
	int sceneID = 0;
	bool soundPlay = false;

};