#ifndef __INPUT_CONSTANTS_H__
#define __INPUT_CONSTANTS_H__

typedef enum Input_Type
{
	ACTION,
	STATE,
	RANGE,
};

typedef enum Input_Action
{
	PRESSED,
	RELEASED,
};

typedef enum Input_State
{
	RUN,
	STOP,
};

typedef enum Input_Game
{
	MOVE_RIGHT,
	MOVE_LEFT,
	STOP_ACTION,
	JUMP,
	GAME_INPUT_MAX,
};

#endif // !__INPUT_CONSTANTS_H__