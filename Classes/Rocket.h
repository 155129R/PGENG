#ifndef __ROCKET_H__
#define __ROCKET_H__

#include "BaseWeapon.h"
#include "cocos2d.h"

class Character;

using namespace cocos2d;

class Rocket : public BaseWeapon
{
	Character* character;
	PhysicsBody* physics;
	bool fired;

public:
	Rocket(BaseEntity* _character = nullptr);
	virtual ~Rocket();
	virtual void setWielder(BaseEntity* _wielder);
	virtual void use();
};

#endif // !__ROCKET_H__
