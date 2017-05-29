#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "SceneManager.h"


USING_NS_CC;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Screen size
	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));
	// Halved of screen height
	float halvedHeight = playingSize.height * .5f;

	//Temporary Code
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// Node for items
	auto nodeItems = Node::create();
	nodeItems->setName("nodeItems");
	nodeItems->setPosition(0, halvedHeight);
	this->addChild(nodeItems, 1);

	auto playerNode = Node::create();
	playerNode->setName("playerNode");
	playerNode->setPosition(0, 0);
	this->addChild(playerNode, 1);


	mainChar.Init("Blue_Front1.png", "Player", 100, 500);
	playerNode->addChild(mainChar.getSprite(), 1);

	return true;
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		mainChar.MoveChar(1);
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		mainChar.MoveChar(-1);
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		//CCDirector::getInstance()->replaceScene(TransitionFade::create(1.5, HelloWorld::createScene(), Color3B(0, 255, 255)));
		SceneManager::getInstance()->runSceneWithType(CONSTANTS::SceneType::GAMEPLAY);
	}
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		mainChar.Stop();
	}
}

void GameScene::update(float _delta)
{
	
}

void GameScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);

}
