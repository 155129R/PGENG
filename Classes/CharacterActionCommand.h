#ifndef __CHARACTER_ACTION_COMMAND_H__
#define __CHARACTER_ACTION_COMMAND_H__

#include "ActionCommand.h"

class Character;

class CharacterActionCommand : public ActionCommand
{
	void(Character::*func)();
	Character* character;

public:
	CharacterActionCommand(void(Character::*_func)(), Character* _character, Input_Action action)
	{
		actionState = action;
		func = _func;
		character = _character;
	}
	~CharacterActionCommand(){}

	virtual void Execute()
	{
		(character->*func)();
	}
};

#endif // !__CHARACTER_ACTION_COMMAND_H__
