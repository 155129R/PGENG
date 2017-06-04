#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "BaseEntity\Character.h"
#include "BaseEntity\Enemy.h"
#include "Input\InputHandler.h"
#include "Background\ScrollingBackground.h"
#include "cocos2d.h"

using namespace cocos2d;

class GameScene : public cocos2d::Layer
{
public:
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	static cocos2d::Scene* createScene();
	virtual bool init();
	
	//Temporary until Input for touch is in
	virtual void onKeyPressed(EventKeyboard::KeyCode, Event*);
	virtual void onKeyReleased(EventKeyboard::KeyCode, Event*);
	
	virtual void update(float);

	void SpawnEnemy(int);

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	GLProgram *proPostProcess;
	InputHandler input;
	ScrollingBackground background;

	Character mainChar;

	std::vector<Enemy*> enemyList;
	float spawnTimer;

	//to check if all enemy are on screen
	bool allEnemyALive;

	//for storing number of should spawn random enemy 
	int tempRandom;
	
	//for getting window screen
	Size playingSize;
	
};


#endif // !__GAME_SCENE_H__
