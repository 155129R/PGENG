#ifndef __TEMPLATE_ACTION_COMMAND_H__
#define __TEMPLATE_ACTION_COMMAND_H__

#include "ActionCommand.h"

template <typename T>
class TemplateAction : public ActionCommand
{
protected:
	void(T::*func)();
	T* object;

public:
	TemplateAction(T* _object, void(T::*_func)(), Input_Action _action = Input_Action::PRESSED) : ActionCommand(_action)
	{
		func = _func;
		object = _object;
	}
	~TemplateAction(){}

	virtual void Execute()
	{
		(object->*func)();
	}
};

#endif // !__TEMPLATE_CTION_COMMAND_H__
