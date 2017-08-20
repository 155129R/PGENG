#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "Character.h"
#include "Enemy.h"
#include "InputHandler.h"
#include "ParallaxBackground.h"
#include "EnemyManager.h"
#include "cocos2d.h"
#include "ui/UIImageView.h"
#include "ui/UIButton.h"

using namespace cocos2d;

class Projectile;

class GameScene : public cocos2d::Layer
{
public:
	typedef enum GAME_STATE
	{
		RUN,
		PAUSE,
		DEFEAT,
	};

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	static cocos2d::Scene* createScene();
	virtual bool init();
	
	virtual void onKeyPressed(EventKeyboard::KeyCode, Event*);
	virtual void onKeyReleased(EventKeyboard::KeyCode, Event*);

	virtual bool onTouchBegan(Touch* _touch, Event* _event);
	
	virtual void update(float);

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	std::vector<Projectile*> projectileList;
	Character mainChar;
	ParticleExplosion* m_explosionEmitter;
	std::vector<ui::ImageView*> ImageList;
private:

	GLProgram *proPostProcess;
	InputHandler input;
	ParallaxBackground parallaxBackground;
	Label *text;
	Label *loseText;

	EnemyManager* enemyManager;

	GAME_STATE gameState;

	// Weapon should be in character Class
	float spawnTimer;

	//to check if all enemy are on screen
	bool allEnemyALive;

	//for storing number of should spawn random enemy 
	int tempRandom;
	
	//for getting window screen
	Size playingSize;

	Sprite* blackBg;
	Label *finalScore;
	ui::Button* resumeButton;
	ui::Button* quitButton;
	ui::Button* shareButton;

	void InitAndroid();
	void InitButtonsForAndroid();

	void InitIOS();
	void InitButtonsForIOS();

	void InitTouch();

	int GetNumberOfUIHearts();
	void AddUIHeart();
	void RemoveUIHeart();
};


#endif // !__GAME_SCENE_H__
