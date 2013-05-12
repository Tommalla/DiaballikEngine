#ifndef ENUMS_H
#define ENUMS_H
#include "constants.h"

enum FieldState {
	EMPTY = _EMPTY,
	PLAYER_A = _PLAYER_A,
	PLAYER_B = _PLAYER_B,
	BALL_A = _BALL_A,
	BALL_B = _BALL_B
};

enum GamePlayer {
	NONE = _EMPTY,
	GAME_PLAYER_A = _PLAYER_A,
	GAME_PLAYER_B = _PLAYER_B
};

#endif