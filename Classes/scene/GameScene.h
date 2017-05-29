#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "Character.h"
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

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	GLProgram *proPostProcess;

	Character mainChar;
};


#endif // !__GAME_SCENE_H__
