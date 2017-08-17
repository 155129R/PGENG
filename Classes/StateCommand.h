#ifndef __STATE_COMMAND_H__
#define __STATE_COMMAND_H__

#include "InputCommandBase.h"

class StateCommand : public InputCommandBase
{
protected:
	Input_State state;

public:
	StateCommand(Input_State _state = Input_State::STOP)
	{
		inputType = Input_Type::STATE;
		state = _state;
	}
	~StateCommand(){}

	Input_State GetState()
	{
		return state;
	}

	virtual void Execute(){}
};

#endif // !__STATE_COMMAND_H__
