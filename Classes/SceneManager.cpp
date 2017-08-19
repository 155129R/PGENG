#include "SceneManager.h"

#include "GameScene.h"
#include "MainmenuScene.h"
#include "SettingScene.h"

using namespace cocos2d;

SceneManager& SceneManager::getInstance()
{
	static SceneManager instance;
	return instance;
}

SceneManager::SceneManager():
	_prevSceneType(SceneType::TEST),
	_currSceneType(SceneType::TEST)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::runSceneWithType(const SceneType sceneType)
{
	Scene* sceneToRun = nullptr;

	switch (sceneType)
	{
	case SceneType::GAMEPLAY:
		sceneToRun = GameScene::createScene();
		break;
    case SceneType::MAINMENU:
		sceneToRun = MainmenuScene::createScene();
		break;
	case SceneType::SETTINGS:
		sceneToRun = SettingScene::createScene();
        break;
	default:
        sceneToRun = GameScene::createScene();
		break;
	}

	SceneType oldSceneType = _currSceneType;
	_currSceneType = sceneType;
	sceneToRun->setTag(static_cast<int>(sceneType));

	if (sceneToRun == nullptr)
	{
		_currSceneType = oldSceneType;
		return;
	}

	_prevSceneType = oldSceneType;
	if (CCDirector::getInstance()->getRunningScene() == nullptr)
	{
		CCDirector::getInstance()->runWithScene(sceneToRun);
	}
	else
	{
		CCDirector::getInstance()->replaceScene(TransitionFade::create(1.5f, sceneToRun));
		//CCDirector::getInstance()->replaceScene(TransitionSlideInT::create(1.5f, sceneToRun));
	}
}

void SceneManager::returnToPrevScene()
{
	this->runSceneWithType(_prevSceneType);
}
