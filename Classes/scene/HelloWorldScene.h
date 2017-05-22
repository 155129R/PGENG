#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Character.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	virtual void onKeyPressed(EventKeyboard::KeyCode, Event*);
	virtual void onKeyReleased(EventKeyboard::KeyCode, Event*);
	virtual void onMouseDown(Event*);

	virtual void update(float);

	Character* getChar() { return &mainChar; }

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
	GLProgram *proPostProcess;
	RenderTexture *rendtex;
	Sprite* rendtexSprite;

	Character mainChar;
};

#endif // __HELLOWORLD_SCENE_H__
