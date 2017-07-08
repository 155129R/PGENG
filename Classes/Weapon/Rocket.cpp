#include "Rocket.h"
#include "../BaseEntity/Character.h"

Rocket::Rocket(BaseEntity* _character)
{
	setWielder(_character);
}

Rocket::~Rocket()
{

}

void Rocket::setWielder(BaseEntity* _wielder)
{
	wielder = _wielder;
	character = dynamic_cast<Character*>(_wielder);
}

void Rocket::use()
{
	if (character->getCharacterState() == CHARACTER_STATE::RUNNING)
		character->Jump();
	else
	{
		// FIRE THE MISSILE!!!
	}
}