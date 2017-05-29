#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "..\Constants\Constants.h"

class SceneManager
{
public:
	static SceneManager* getInstance();
	~SceneManager();
	void runSceneWithType(const SceneType sceneType);
	void returnToPrevScene();

private:
	SceneType _prevSceneType;
	SceneType _currSceneType;
	static SceneManager* instance;
	SceneManager();

};

#endif // SCENEMANAGER_H