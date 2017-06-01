#pragma once

#include "cocos2d.h"
using namespace cocos2d;

//Forward declaration for classes since we can't cross include
class BaseEntity;

class Animator
{

public:

	enum AnimationType
	{
		NIL = 0,
		PLAYERRUN,
		PLAYERIDLE,
		PLAYERJUMP,
		ENEMYRUN,
		MAX
	}animType;

	//////////////////////////
	//Plans for optimization//
	//////////////////////////

	//Preload all the sprite animation inside a global variable 
	//When animation is being called it will clone from there instead of create.

	void PlayAnimation(AnimationType animType, BaseEntity* entity);

};