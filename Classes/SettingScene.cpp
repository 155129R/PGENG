#include "SettingScene.h"
#include "SceneManager.h"
#include "ui/UIButton.h"
#include "SimpleAudioEngine.h"

///////////////////////////CTRL F (Update not running)
USING_NS_CC;

Scene* SettingScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SettingScene::create();
	layer->setTag((int)SceneType::SETTINGS);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool SettingScene::init()
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
	title->initWithFile("ui/settings-title.png");
	title->setPosition(Vec2(playingSize.width * 0.5f, playingSize.height * 0.75f));
	title->setScale(1.5f);
	this->addChild(title);
	
	InitButtons();

	return true;
}

void SettingScene::InitButtons()
{
	// Background Volume Slider
	auto backgroundVolumeImage = Sprite::create();
	backgroundVolumeImage->initWithFile("ui/background-volume.png");
	backgroundVolumeImage->setPosition(Vec2(playingSize.width * 0.38f, playingSize.height * 0.4f));
	backgroundVolumeImage->setScale(2.5f);
	this->addChild(backgroundVolumeImage);

	backgroundSlider = ui::Slider::create();
	backgroundSlider->loadBarTexture("ui/Slider_Back.png");
	backgroundSlider->loadSlidBallTextures("ui/SliderNode_Normal.png", "ui/SliderNode_Press.png", "ui/SliderNode_Disable.png");
	backgroundSlider->loadProgressBarTexture("ui/Slider_PressBar.png");
	backgroundSlider->setPercent(CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume() * 100);
	backgroundSlider->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			float volume = (float)backgroundSlider->getPercent() / 100.0f;
			CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);
		}
	});
	backgroundSlider->setPosition(Vec2(playingSize.width * 0.6f, playingSize.height * 0.4f));
	backgroundSlider->setScale(2.f);
	this->addChild(backgroundSlider);

	// Effects Volume Slider
	auto effectVolumeImage = Sprite::create();
	effectVolumeImage->initWithFile("ui/effects-volume.png");
	effectVolumeImage->setPosition(Vec2(playingSize.width * 0.38f, playingSize.height * 0.3f));
	effectVolumeImage->setScale(2.5f);
	this->addChild(effectVolumeImage);

	effectSlider = ui::Slider::create();
	effectSlider->loadBarTexture("ui/Slider_Back.png");
	effectSlider->loadSlidBallTextures("ui/SliderNode_Normal.png", "ui/SliderNode_Press.png", "ui/SliderNode_Disable.png");
	effectSlider->loadProgressBarTexture("ui/Slider_PressBar.png");
	effectSlider->setPercent(CocosDenshion::SimpleAudioEngine::getInstance()->getEffectsVolume() * 100);
	effectSlider->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::MOVED)
		{
			CCLOG("I HAVED MOVED\n");
			float volume = (float)effectSlider->getPercent() / 100.0f;
			CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(volume);
		}
	});
	effectSlider->setPosition(Vec2(playingSize.width * 0.6f, playingSize.height * 0.3f));
	effectSlider->setScale(2.f);
	this->addChild(effectSlider);

	// Return
	auto button = ui::Button::create("ui/return-normal.png", "ui/return-selected.png");
	button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			SceneManager::getInstance().runSceneWithType(CONSTANTS::SceneType::MAINMENU);
		}
	});
	button->setPosition(Vec2(playingSize.width * 0.47f, playingSize.height * 0.2f));
	button->setScale(2.f);
	this->addChild(button);
}

void SettingScene::menuCloseCallback(Ref* pSender)
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