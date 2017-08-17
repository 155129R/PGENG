#ifndef __INPUT_HANDLER_H__
#define __INPUT_HANDLER_H__

#include <queue>
#include <list>
#include <vector>

#include "InputCommandBase.h"
#include "ActionCommand.h"
#include "StateCommand.h"
#include "InputConstant.h"

class InputHandler
{
	std::vector<InputCommandBase*> commands[Input_Game::GAME_INPUT_MAX];
	std::vector<int> keybinds[Input_Game::GAME_INPUT_MAX];

	std::queue<int> keyPressed;
	std::queue<int> keyReleased;

	std::queue<InputCommandBase*> actionQueue;
	std::list<InputCommandBase*> stateList;

	void DecipherKeyPressed();
	void DecipherKeyReleased();
	void RunActions();
	void RunStates();
	bool CheckKeybind();

public:
	InputHandler();
	~InputHandler();

	void BindCommand(Input_Game _gameInput, InputCommandBase *_command);
	void BindKeyToCommand(Input_Game _gameInput, int keyCode);
	void BindCommandAndKey(Input_Game _gameInput, InputCommandBase *_command, int keyCode);

	void EnqueueKeyPressed(int keyCode);
	void EnqueueKeyReleased(int keyCode);

	std::vector<int>::iterator CheckKeyExistInVector(std::vector<int> &binds, int key);

	void RunCommands();
};

#endif // !__INPUT_HANDLER_H__


