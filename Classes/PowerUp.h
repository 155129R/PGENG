#ifndef POWERUP_H
#define POWERUP_H

#include "Animator.h"
#include "BaseEntity.h"
#include "cocos2d.h"
#include "FeedBack.h"

using namespace cocos2d;

class PowerUp : public BaseEntity
{
private:
	cocos2d::Node* node;
	float groundHeight;
	bool visible;

public:

	PowerUp();
	virtual ~PowerUp();

	void Init(const char* _srcImg, const char* _name, float _x, float _y);
	void Update(float _delta, BaseEntity* character, FeedBack* feedback);

	BaseEntity::EntityType GetPowerUpType();
};

#endif // POWERUP_H