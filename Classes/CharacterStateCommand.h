#ifndef __CHARACTER_STATE_COMMAND_H__
#define __CHARACTER_STATE_COMMAND_H__

#include "StateCommand.h"

class Character;

class CharacterStateCommand : public StateCommand
{
	void(Character::*func)();
	Character* character;

public:
	CharacterStateCommand(void(Character::*_func)(), Character* _character)
	{
		func = _func;
		character = _character;
	}
	~CharacterStateCommand(){}

	virtual void Execute()
	{
		(character->*func)();
	}
};

#endif // !__CHARACTER_STATE_COMMAND_H__
