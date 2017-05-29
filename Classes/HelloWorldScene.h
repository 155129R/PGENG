#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Character.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
private:
	Character* player;
	GLProgram* proPostProcess;
	RenderTexture* rendtex;
	Sprite* rendtexSprite;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	virtual void update(float );
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	virtual void onKeyPressed(EventKeyboard::KeyCode, Event*);
	virtual void onKeyReleased(EventKeyboard::KeyCode, Event*);
	virtual void onMousePressed(Event*);
	Character* getChar() { return player; }

    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
