#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "SceneManager.h"

#include "TemplateAction.h"
#include "Projectile.h"
#include "BaseWeapon.h"
#include "PowerUp.h"

///////////////////////////CTRL F (Update not running)
USING_NS_CC;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();
	layer->setTag((int)SceneType::GAMEPLAY);

	PhysicsWorld* world = scene->getPhysicsWorld();
	world->setGravity(Vec2(0.f, -1000.f));

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

	gameState = GAME_STATE::RUN;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Screen size
	playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));
	
	// Halved of screen height
	float halvedHeight = playingSize.height * .5f;

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

	mainChar.Init("PlayerIdle/idle1.png", "Player", 80, 160);
	mainChar.SetScale(1.5f);
	playerNode->addChild(mainChar.getSprite(), 1);

	// Input control setup
	input.BindCommandAndKey(Input_Game::USE_WEAPON, new TemplateAction<BaseWeapon>(mainChar.getWeapon(), &BaseWeapon::use, Input_Action::PRESSED), (int)EventKeyboard::KeyCode::KEY_SPACE);

	// Load background
	parallaxBackground.Init(visibleSize.width, visibleSize.height);
	this->addChild(parallaxBackground.node);
	parallaxBackground.SetScrollSpeed(1000.f);
	parallaxBackground.SetFadeTime(0.15f);

	parallaxBackground.AddBackground("hills", 5);
	parallaxBackground.ChangeBackground("hills");

	//Projectile Pool SHOULD BE IN CHARACTER CLASS
	for (int a = 1; a < 4; a++)
	{
		auto projectileNode = Node::create();
		projectileNode->setName("Missile");
		this->addChild(projectileNode, 1);

		Projectile* newMissile = new Projectile("missile.png", 2.0f, Vec2(1.0f, 0.0f), 1.0f);
		projectileNode->addChild(newMissile->getSprite(), 1);
		newMissile->SetAlive(false);
		projectileList.push_back(newMissile);
	}

	enemyManager = new EnemyManager(this);

	spawnTimer = (float)(cocos2d::RandomHelper::random_int(5, 5));
	tempRandom = 0;
	allEnemyALive = false;
	
	m_explosionEmitter = ParticleExplosion::create();
	m_explosionEmitter->setVisible(false);
	this->addChild(m_explosionEmitter, 1);

	//Lives UI
	for (int i = 0; i < mainChar.GetHits(); i++)
	{
		auto imageView = ui::ImageView::create("heart.png");
		imageView->setPosition(Vec2(visibleSize.width * 0.10f + (10.f * i), visibleSize.height * 0.95f));
		this->addChild(imageView);
		ImageList.push_back(imageView);
	}

	//Score UI
	std::stringstream ss;
	ss << mainChar.score;
	text = Label::createWithTTF(ss.str(), "batman.ttf", 100.f);
	text->setColor(Color3B(0.f, 0.f, 0.f));
	text->setPosition(Vec2(visibleSize.width * 0.05f, visibleSize.height * 0.95f));
	this->addChild(text);
	text->setPositionZ(5.f);

	finalScore = Label::createWithTTF(ss.str(), "batman.ttf", 100.f);
	finalScore->setColor(Color3B(255, 255, 255));
	finalScore->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.55f));
	finalScore->setVisible(false);
	this->addChild(finalScore, 3);


	//Lose Text
	loseText = Label::createWithTTF("You Lose", "batman.ttf", 200.f);
	loseText->setColor(Color3B(255, 255, 255));
	loseText->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.8f));
	this->addChild(loseText, 3);
	loseText->setVisible(false);
	loseText->setPositionZ(5.f);

	blackBg = Sprite::create("Background/black.png");
	blackBg->setAnchorPoint(Vec2(0.f, 0.f));
	blackBg->setPosition(Vec2(0.0f, 0.0f));
	blackBg->setOpacity(200);
	this->addChild(blackBg, 2);
	blackBg->setVisible(false);

	m_explosionEmitter->pauseEmissions();

	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("Sounds/MotifLoop.mp3", true);

	InitTouch();
	InitButtons();

	this->scheduleUpdate();
	return true;
}

void GameScene::InitTouch()
{
	auto touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void GameScene::InitButtons()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto button = ui::Button::create("ui/settings-icon.png");
	button->setPosition(Vec2(visibleSize.width * 0.96f, visibleSize.height * 0.94f));
	button->setScale(0.2f);
	button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			gameState = GAME_STATE::PAUSE;
			blackBg->setVisible(true);
			resumeButton->setVisible(true);
			resumeButton->setEnabled(true);
			quitButton->setVisible(true);
			quitButton->setEnabled(true);
		}
	});
	this->addChild(button);

	resumeButton = ui::Button::create("ui/resume-normal.png", "ui/resume-selected.png");
	resumeButton->setPosition(Vec2(visibleSize.width * 0.41f, visibleSize.height * 0.6f));
	resumeButton->setScale(1.5f);
	resumeButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			gameState = GAME_STATE::RUN;
			blackBg->setVisible(false);
			resumeButton->setVisible(false);
			resumeButton->setEnabled(false);
			quitButton->setVisible(false);
			quitButton->setEnabled(false);
		}
	});
	resumeButton->setEnabled(false);
	resumeButton->setVisible(false);
	this->addChild(resumeButton, 4);

	quitButton = ui::Button::create("ui/quit-normal.png", "ui/quit-selected.png");
	quitButton->setPosition(Vec2(visibleSize.width * 0.41f, visibleSize.height * 0.4f));
	quitButton->setScale(1.5f);
	quitButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			SceneManager::getInstance().runSceneWithType(CONSTANTS::SceneType::MAINMENU);
		}
	});
	quitButton->setEnabled(false);
	quitButton->setVisible(false);
	this->addChild(quitButton, 3);

	shareButton = ui::Button::create("ui/share-normal.png", "ui/share-selected.png");
	shareButton->setPosition(Vec2(visibleSize.width * 0.41f, visibleSize.height * 0.35f));
	shareButton->setScale(1.5f);
	shareButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			// TODO: Put your share codes here
		}
	});
	shareButton->setEnabled(false);
	shareButton->setVisible(false);
	this->addChild(shareButton, 3);
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	input.EnqueueKeyPressed((int)keyCode);
	//if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	//{
	//	//CCDirector::getInstance()->replaceScene(TransitionFade::create(1.5, HelloWorld::createScene(), Color3B(0, 255, 255)));
	//	//SceneManager::getInstance()->runSceneWithType(CONSTANTS::SceneType::GAMEPLAY);
	//}
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	input.EnqueueKeyReleased((int)keyCode);
}

bool GameScene::onTouchBegan(Touch* _touch, Event* _event)
{
	mainChar.getWeapon()->use();

	return true;
}

void GameScene::update(float _delta)
{
	if (gameState == GAME_STATE::DEFEAT || gameState == GAME_STATE::PAUSE)
		return;

	if (mainChar.isDead() && gameState != GAME_STATE::DEFEAT)
	{
		gameState = GAME_STATE::DEFEAT;
		loseText->setVisible(true);
		shareButton->setVisible(true);
		shareButton->setEnabled(true);
		blackBg->setVisible(true);

		auto visibleSize = Director::getInstance()->getVisibleSize();
		quitButton->setVisible(true);
		quitButton->setEnabled(true);
		quitButton->setPosition(Vec2(visibleSize.width * 0.41f, visibleSize.height * 0.2f));

		std::stringstream ss;
		ss << "Score: " << mainChar.score;
		finalScore->setString(ss.str());
		finalScore->setVisible(true);
	}
	input.RunCommands();

	std::stringstream ss;
	ss << mainChar.score;
	text->setString(ss.str());
	spawnTimer -= _delta;
	mainChar.Update(_delta);
	parallaxBackground.Update(_delta);
	
	enemyManager->Update(_delta, &mainChar);

	if (GetNumberOfUIHearts() < mainChar.GetHealth())
		AddUIHeart();
	if (GetNumberOfUIHearts() > mainChar.GetHealth())
		RemoveUIHeart();

	//Update for weapon and projectile
	for (auto projectile : projectileList)
		projectile->Update(_delta);
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

int GameScene::GetNumberOfUIHearts()
{
	int returnInt = 0;

	for (int i = 0; i < ImageList.size(); i++)
	{
		if (ImageList[i]->isVisible())
			returnInt++;
	}

	return returnInt;
}

void GameScene::AddUIHeart()
{
	int iter = 0;
	for (iter = 0; iter < ImageList.size(); iter++)
	{
		if (!ImageList[iter]->isVisible())
			break;
	}
	cocos2d::log("GAIN HEART");
	ImageList[iter]->setVisible(true);

}

void GameScene::RemoveUIHeart()
{
	int iter = 0;
	for (iter = ImageList.size() - 1; iter >= 0; --iter)
	{
		if (ImageList[iter]->isVisible())
			break;
	}
	cocos2d::log("REMOVE HEART");
	ImageList[iter]->setVisible(false);
}
