#ifndef POWERUP_H
#define POWERUP_H

#include "Classes\Animator.h"
#include "..\BaseEntity.h"
#include "cocos2d.h"

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
	void Update(float _delta, BaseEntity* character);

	BaseEntity::EntityType GetPowerUpType();

};

#endif // POWERUP_H