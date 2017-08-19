#pragma once
#include "Animator.h"

class BaseEntity
{
protected:

	Animator animator;
	int m_dir;
	float m_speed;
	Sprite* m_mainSprite;
	bool isAlive;

public:

	enum EntityType 
	{
		NIL = 0,
		CHARACTER,
		ENEMY,
		POWERUP_LIFE,
		MAX
	}entityType;

	virtual int GetDirection();
	virtual float GetSpeed();
	virtual Animator GetAnimator();
	virtual bool GetAlive();

	virtual void SetAlive(bool);
	virtual void SetDirection(int );
	virtual void SetSpeed(float );
	virtual void SetAnimator(Animator );

	virtual Sprite* getSprite(void) { return m_mainSprite; }
	virtual Vec2 getPosition() { return m_mainSprite->getPosition(); }

	inline void SetScale(float scale){ m_mainSprite->setScale(scale); }
};