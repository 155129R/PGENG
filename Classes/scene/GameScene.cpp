#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "SceneManager.h"

#include "Commands\CharacterActionCommand.h"
#include "Commands\CharacterStateCommand.h"

///////////////////////////CTRL F (Update not running)
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
	playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));
	
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

	mainChar.Init("Blue_Front1.png", "Player", 80, 60);
	playerNode->addChild(mainChar.getSprite(), 1);

	// Input control setup
	input.BindCommandAndKey(Input_Game::MOVE_RIGHT, new CharacterActionCommand(&Character::MoveRight, &mainChar, Input_Action::PRESSED), (int)EventKeyboard::KeyCode::KEY_D);
	input.BindCommandAndKey(Input_Game::MOVE_LEFT, new CharacterActionCommand(&Character::MoveLeft, &mainChar, Input_Action::PRESSED), (int)EventKeyboard::KeyCode::KEY_A);
	input.BindCommandAndKey(Input_Game::STOP_ACTION, new CharacterActionCommand(&Character::Stop, &mainChar, Input_Action::RELEASED), (int)EventKeyboard::KeyCode::KEY_D);
	input.BindCommandAndKey(Input_Game::STOP_ACTION, new CharacterActionCommand(&Character::Stop, &mainChar, Input_Action::RELEASED), (int)EventKeyboard::KeyCode::KEY_A);

	// Load background
	auto backgroundNode1 = Node::create();
	auto backgroundNode2 = Node::create();
	this->addChild(backgroundNode1, 0);
	this->addChild(backgroundNode2, 0);

	backgroundNode1->setName("backgroundNode1");
	backgroundNode2->setName("backgroundNode2");
	backgroundNode1->setPosition(0, 0);
	backgroundNode2->setPosition(0, 0);

	background.Init(visibleSize.width, visibleSize.height, 3.f);
	background.AddImage("day", "Background/city_day.png");
	background.AddImage("noon", "Background/city_noon.png");
	background.AddImage("night", "Background/city_night.png");
	background.SetStartingBackground("day");
	background.QueueNextBackground("noon");
	background.QueueNextBackground("night");

	backgroundNode1->addChild(background.buffers[0], 0);
	backgroundNode2->addChild(background.buffers[1], 0);

	for (int i = 0; i < 8; i++)
	{
		auto enemyNode = Node::create();
		enemyNode->setName("enemyNode");
		enemyNode->setPosition(10, 0);
		this->addChild(enemyNode, 1);

		Enemy* newEnemy = new Enemy();
		newEnemy->Init("Blue_Front1.png", "Player", 300, i * 100, mainChar.getPosition().x);
		enemyNode->addChild(newEnemy->getSprite(), 1);
		newEnemy->SetAlive(false);
		
		enemyList.push_back(newEnemy);
	}

	spawnTimer = (float)(cocos2d::RandomHelper::random_int(5, 5));
	tempRandom = 0;
	allEnemyALive = false;

	this->scheduleUpdate();
	return true;
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	input.EnqueueKeyPressed((int)keyCode);
	//if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	//{
	//	//CCDirector::getInstance()->replaceScene(TransitionFade::create(1.5, HelloWorld::createScene(), Color3B(0, 255, 255)));
	//	SceneManager::getInstance()->runSceneWithType(CONSTANTS::SceneType::GAMEPLAY);
	//}
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	input.EnqueueKeyReleased((int)keyCode);
}

void GameScene::SpawnEnemy(int numberOfEnemy)
{
	for (int i = 0; i < numberOfEnemy; i++)
	{
		int tempEnemyPosition = cocos2d::RandomHelper::random_int(0, 7);
		if (!enemyList[tempEnemyPosition]->GetAlive())
		{
			allEnemyALive = false;
			enemyList[tempEnemyPosition]->SetAlive(true);
			enemyList[tempEnemyPosition]->getSprite()->setPosition(playingSize.width, enemyList[i]->getPosition().y);
		}
	}
}
void GameScene::update(float _delta)
{
	spawnTimer -= _delta;
	background.Update(_delta);
	if (spawnTimer <= 0.0f && !allEnemyALive)
	{
		//For Debug
		spawnTimer = 0.2f;

		//For Playtest
		//spawnTimer = (float)(cocos2d::RandomHelper::random_int(1, 5));

		tempRandom = cocos2d::RandomHelper::random_int(1, 7);
		SpawnEnemy(tempRandom);
	}
	for (auto enemy : enemyList)
		enemy->Update(_delta, mainChar);

	input.RunCommands();
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
