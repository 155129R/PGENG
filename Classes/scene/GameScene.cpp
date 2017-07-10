#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "SceneManager.h"

#include "Commands\TemplateAction.h"
#include "Projectile\Projectile.h"
#include "Weapon\BaseWeapon.h"

///////////////////////////CTRL F (Update not running)
USING_NS_CC;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();
	layer->setTag((int)SceneType::GAMEPLAY);

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

	mainChar.Init("Blue_Front1.png", "Player", 80, 150);
	playerNode->addChild(mainChar.getSprite(), 1);

	// Input control setup
	input.BindCommandAndKey(Input_Game::USE_WEAPON, new TemplateAction<BaseWeapon>(mainChar.getWeapon(), &BaseWeapon::use, Input_Action::PRESSED), (int)EventKeyboard::KeyCode::KEY_SPACE);

	// Load background
	parallaxBackground.Init(visibleSize.width, visibleSize.height);
	this->addChild(parallaxBackground.node);
	parallaxBackground.AddBackground("hills", "Background/");
	parallaxBackground.SetStartingBackground("hills");
	parallaxBackground.SetScrollSpeedByTime(30.f);

	//Projectile Pool SHOULD BE IN CHARACTER CLASS
	for (int a = 1; a < 4; a++)
	{
		auto projectileNode = Node::create();
		projectileNode->setName("Missile");
		this->addChild(projectileNode, 1);

		Projectile* newMissile = new Projectile("Blue_Front1.png", 2.0f, Vec2(1.0f, 0.0f), 1.0f);
		projectileNode->addChild(newMissile->getSprite(), 1);
		newMissile->SetAlive(false);
		projectileList.push_back(newMissile);
	}

	enemyManager = new EnemyManager(this);
	
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
	//	//SceneManager::getInstance()->runSceneWithType(CONSTANTS::SceneType::GAMEPLAY);
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
	input.RunCommands();

	spawnTimer -= _delta;
	mainChar.Update(_delta);
	parallaxBackground.Update(_delta);
	
	enemyManager->Update(_delta, mainChar);

	for (auto enemy : enemyList)
		enemy->Update(_delta, mainChar);

	//Update for weapon and projectile
	for (auto projectile : projectileList)
		projectile->Update(_delta);

	for (auto enemy : enemyList)
		enemy->Update(_delta, mainChar);

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
