#pragma once

class SceneManager
{
private: // ���� �Ҹ���
	SceneManager(); 
	~SceneManager();
	SceneManager(const SceneManager* other) {};

public:	// �Լ�
	void Update();
	void Render();
	// MainWindow ���� Call �̵ȴ�.

	void ThreadStart1();
	void ThreadStart2();
	void RenderChapterDisplay();
	// Thread �� �������� �Լ�

	void ChangeScene(string name);

	static SceneManager* GetInstance()
	{
		static SceneManager instance;
		return &instance;
	}
	// �̱��� �ν��Ͻ� �Լ�

	class Scene*	GetScene(string name);
	class Scene*	GetCurScene() { return curScene; }
	class Scene*	GetLatScene() { return latScene; }
	int				GetCurSceneNum() { return curScene->GetSceneNum(); }
	// Getter �Լ�

	void Pause() { if (pause) pause = false; else pause = true; }

private: // ����� �Լ�
	void CreateObject();

private: // private �Լ�
	vector<class Scene*> scenes;	// Scene�� ���� �����͸� �����Ѵ�.
	// �̷���� �ּ��� �迭�� vector �� ���°��̴�.
	
	class Scene* curScene = nullptr;
	class Scene* latScene = nullptr;

	class OptionMenu* optionMenu = nullptr;

	bool threadStart = false;
	bool pause = false;

	int curSceneNum = 0;
	int latSceneNum = 0;
};