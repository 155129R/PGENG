#ifndef __ACTION_COMMAND_H__
#define __ACTION_COMMAND_H__

#include "InputCommandBase.h"

class ActionCommand : public InputCommandBase
{
protected:
	Input_Action actionState;

public:
	ActionCommand(Input_Action _action = Input_Action::PRESSED)
	{
		inputType = Input_Type::ACTION;
		actionState = _action;
	}
	~ActionCommand(){}

	Input_Action GetActionState()
	{
		return actionState;
	}

	virtual void Execute()
	{
	}
};

#endif // !__ACTION_COMMAND_H__
