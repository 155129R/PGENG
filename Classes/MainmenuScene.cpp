#include "MainmenuScene.h"
#include "SimpleAudioEngine.h"
#include "SceneManager.h"
#include "ui/UIButton.h"

///////////////////////////CTRL F (Update not running)
USING_NS_CC;

Scene* MainmenuScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainmenuScene::create();
	layer->setTag((int)SceneType::MAINMENU);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainmenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	// Screen size
	playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

	auto title = Sprite::create();
	title->initWithFile("ui/Title.png");
	title->setPosition(Vec2(playingSize.width * 0.5f, playingSize.height * 0.75f));
	title->setScale(1.5f);
	this->addChild(title);
	
	InitButtons();

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/MotifLoop.mp3", true);
	return true;
}

void MainmenuScene::InitButtons()
{
	// Game Start Button
	auto button = ui::Button::create("ui/start-normal.png", "ui/start-selected.png");
	button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			SceneManager::getInstance().runSceneWithType(CONSTANTS::SceneType::GAMEPLAY);
		}
	});
	button->setPosition(Vec2(playingSize.width * 0.44f, playingSize.height * 0.35f));
	button->setScale(2.5f);
	this->addChild(button);

	// Options Button
	button = ui::Button::create("ui/settings-normal.png", "ui/settings-selected.png");
	button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			SceneManager::getInstance().runSceneWithType(CONSTANTS::SceneType::SETTINGS);
		}
	});
	button->setPosition(Vec2(playingSize.width * 0.43f, playingSize.height * 0.2f));
	button->setScale(2.5f);
	this->addChild(button);
}

void MainmenuScene::menuCloseCallback(Ref* pSender)
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