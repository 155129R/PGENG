#include "InputHandler.h"

InputHandler::InputHandler()
{
	
}

InputHandler::~InputHandler()
{
	for (int i = 0; i < Input_Game::GAME_INPUT_MAX; ++i)
	{
		keybinds[i].clear();

		if (!commands[i].empty())
		{
			std::vector<InputCommandBase*>::iterator it = commands[i].begin();
			std::vector<InputCommandBase*>::iterator end = commands[i].end();

			while (it != end)
			{
				delete *it;
				it++;
			}

			commands[i].clear();
		}
	}
}

void InputHandler::BindCommand(Input_Game _gameInput, InputCommandBase *_command)
{
	commands[_gameInput].push_back(_command);
}

void InputHandler::BindKeyToCommand(Input_Game _gameInput, int keyCode)
{
	keybinds[_gameInput].push_back(keyCode);
}

void InputHandler::BindCommandAndKey(Input_Game _gameInput, InputCommandBase *_command, int keyCode)
{
	BindCommand(_gameInput, _command);
	BindKeyToCommand(_gameInput, keyCode);
}

void InputHandler::EnqueueKeyPressed(int keyCode)
{
	keyPressed.push(keyCode);
}

void InputHandler::EnqueueKeyReleased(int keyCode)
{
	keyReleased.push(keyCode);
}

void InputHandler::RunCommands()
{
	DecipherKeyPressed();
	DecipherKeyReleased();
	RunActions();
	RunStates();
}

void InputHandler::DecipherKeyPressed()
{
	// Checks key pressed, and push appointed commands
	while (!keyPressed.empty())
	{
		int key = keyPressed.front();
		for (int i = 0; i < Input_Game::GAME_INPUT_MAX; ++i)
		{
			// Checks if key exist in keybinds
			std::vector<int>::iterator it = CheckKeyExistInVector(keybinds[i], key);
 
			if (it != keybinds[i].end())
			{
				std::vector<InputCommandBase*>::iterator commIt = commands[i].begin();
				std::vector<InputCommandBase*>::iterator commEnd = commands[i].end();

				// Cycle through commands that are tied to this keybind
				while (commIt != commEnd)
				{
					// Check input type
					switch ((*commIt)->GetInputType())
					{
					case Input_Type::ACTION:
						{
							ActionCommand *action = (ActionCommand*)(*commIt);
							if (action->GetActionState() == Input_Action::PRESSED)
								actionQueue.push(action);
						}
						break;
					case Input_Type::STATE:
						stateList.push_back((*commIt));
						break;
					case Input_Type::RANGE:
						break;
					default:
						break;
					}
					
					commIt++;
				}
			}
		}
		keyPressed.pop();
	}
}

void InputHandler::DecipherKeyReleased()
{
	// Checks key released, and push appointed commands
	while (!keyReleased.empty())
	{
		int key = keyReleased.front();
		for (int i = 0; i < Input_Game::GAME_INPUT_MAX; ++i)
		{
			// Checks if key exist in keybinds
			std::vector<int>::iterator it = CheckKeyExistInVector(keybinds[i], key);
			if (it != keybinds[i].end())
			{
				std::vector<InputCommandBase*>::iterator commIt = commands[i].begin();
				std::vector<InputCommandBase*>::iterator commEnd = commands[i].end();

				// Cycle through commands that are tied to this keybind
				while (commIt != commEnd)
				{
					// Check input type
					switch ((*commIt)->GetInputType())
					{
					case Input_Type::ACTION:
						{
							ActionCommand *action = (ActionCommand*)(*commIt);
							if (action->GetActionState() == Input_Action::RELEASED)
								actionQueue.push(action);
						}
						break;
					case Input_Type::STATE:
						stateList.push_back((*commIt));
						break;
					case Input_Type::RANGE:
						break;
					default: 
						break;
					}
					commIt++;
				}
			}
		}
		keyReleased.pop();
	}
}

void InputHandler::RunActions()
{
	while (!actionQueue.empty())
	{
		InputCommandBase* command = actionQueue.front();
		command->Execute();
		actionQueue.pop();
	}
}

void InputHandler::RunStates()
{
	std::list<InputCommandBase*>::iterator it = stateList.begin();
	std::list<InputCommandBase*>::iterator end = stateList.end();
	while (it != end)
	{
		(*it)->Execute();
		it++;
	}
}

std::vector<int>::iterator InputHandler::CheckKeyExistInVector(std::vector<int> &binds, int key)
{
	std::vector<int>::iterator it = binds.begin();
	while (it != binds.end())
	{
		if (*it == key)
			return it;
		it++;
	}
	return binds.end();
}