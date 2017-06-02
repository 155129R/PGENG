#ifndef __INPUT_HANDLER_H__
#define __INPUT_HANDLER_H__

#include <queue>
#include <list>
#include <vector>

#include "Commands\InputCommandBase.h"
#include "Commands\ActionCommand.h"
#include "Commands\StateCommand.h"
#include "Constants\InputConstant.h"

using std::queue;
using std::list;
using std::vector;

class InputHandler
{
	vector<InputCommandBase*> commands[Input_Game::GAME_INPUT_MAX];
	vector<int> keybinds[Input_Game::GAME_INPUT_MAX];

	queue<int> keyPressed;
	queue<int> keyReleased;

	queue<InputCommandBase*> actionQueue;
	list<InputCommandBase*> stateList;

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

	void RunCommands();
};

#endif // !__INPUT_HANDLER_H__


