#ifndef __ROCKET_H__
#define __ROCKET_H__

#include "BaseWeapon.h"
class Character;

class Rocket : public BaseWeapon
{
	Character* character;
	bool fired;

public:
	Rocket(BaseEntity* _character = nullptr);
	virtual ~Rocket();
	virtual void setWielder(BaseEntity* _wielder);
	virtual void use();
};

#endif // !__ROCKET_H__
