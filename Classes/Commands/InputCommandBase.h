#ifndef __INPUT_COMMAND_BASE_H__
#define __INPUT_COMMAND_BASE_H__

#include "Command.h"
#include "Constants\InputConstant.h"

class InputCommandBase : public Command
{
protected:
	Input_Type inputType;

public:
	InputCommandBase(Input_Type _inputType = Input_Type::ACTION) 
	{
		inputType = _inputType; 
	}
	~InputCommandBase(){}

	Input_Type GetInputType()
	{
		return inputType;
	}

	virtual void Execute(){}
};

#endif // !__INPUT_COMMAND_BASE_H__
