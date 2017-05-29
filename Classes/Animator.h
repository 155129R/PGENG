#pragma once

#include "cocos2d.h"
using namespace cocos2d;

//Forward declaration for classes since we can't cross include
class Character;

class Animator
{

public:

	enum AnimationType
	{
		NIL = 0,
		PLAYERRUN,
		PLAYERIDLE,
		PLAYERJUMP,
		MAX
	}animType;

	//////////////////////////
	//Plans for optimization//
	//////////////////////////

	//Created it this way because i want it contain all animation
	//and there will be overload of other function.
	//In the future it will be change to Unit base class Instead of Character*

	//Preload all the sprite animation inside a global variable 
	//When animation is being called it will clone from there instead of create.

	void PlayAnimation(AnimationType animType, Character* character);

};