#include "SceneManager.h"
#include "..\scene\HelloWorldScene.h"
#include "..\scene\GameScene.h"

using namespace cocos2d;

//Declaration of singleton
SceneManager* SceneManager::instance = NULL;

SceneManager* SceneManager::getInstance()
{
	if (!instance)
		instance = new SceneManager();
	
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
	case SceneType::TEST:
		sceneToRun = HelloWorld::createScene();
		break;

	case SceneType::GAMEPLAY:
		sceneToRun = GameScene::createScene();
		break;

	default:sceneToRun = GameScene::createScene();
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
		CCDirector::getInstance()->replaceScene(TransitionSlideInT::create(1.5f, sceneToRun));
	}
}

void SceneManager::returnToPrevScene()
{
	this->runSceneWithType(_prevSceneType);
}
