#pragma once

#include "cocos2d.h"
using namespace cocos2d;

//Forward declaration for classes since we can't cross include
class BaseEntity;

class Animator
{
	Animate* animate;
	Animation* animation;
public:

	enum AnimationType
	{
		NIL = 0,
		PLAYERRUN,
		PLAYERIDLE,
		PLAYERJUMP,
		ENEMYRUN,
		PLAYERHEAL,
		PLAYERTAKEDAMAGE,
		MAX
	}animType;

	//////////////////////////
	//Plans for optimization//
	//////////////////////////

	//Preload all the sprite animation inside a global variable 
	//When animation is being called it will clone from there instead of create.

	void Init();

	void SetAnimType(AnimationType);
	AnimationType GetAnimType();

	void PowerUpAnimationFinish(BaseEntity*);

	void PlayAnimation(AnimationType animType, BaseEntity* entity);
	void PlayFeedBackAnimation(AnimationType animType, BaseEntity*);

};