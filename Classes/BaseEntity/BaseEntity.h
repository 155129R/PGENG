#pragma once
#include "Classes\Animator.h"
class BaseEntity
{
protected:

	Animator animator;
	int m_dir;
	float m_speed;
	Sprite* m_mainSprite;

public:

	enum EntityType 
	{
		NIL = 0,
		CHARACTER,
		ENEMY,
		MAX
	}entityType;

	virtual int GetDirection();
	virtual float GetSpeed();
	virtual Animator GetAnimator();

	virtual void SetDirection(int );
	virtual void SetSpeed(float );
	virtual void SetAnimator(Animator );

	virtual Sprite* getSprite(void) { return m_mainSprite; }
	virtual Vec2 getPosition() { return m_mainSprite->getPosition(); }
};