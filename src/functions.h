#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <string>
#include "enums.h"

using namespace std;

namespace engine {
	inline void printDebug(const string& str) {
		#ifndef NDEBUG
		fputs(("dbg: " + str + "\n").c_str(), stderr);
		#endif
	}
	
	inline int sgn(const int x) {
		return (x == 0) ? 0 : ((x < 0) ? -1 : 1);
	}
	
	//enums-related:
	
	GamePlayer getOppositePlayer (const GamePlayer& player) {
		//engine::printDebug(string("Game::getOppositePlayer(") + string({(char)((char)player + '0')})  + string(")"));
		if (player == NONE)
			return NONE;
		return (player == GAME_PLAYER_A) ? GAME_PLAYER_B : GAME_PLAYER_A;
	}
	
	GamePlayer getPlayerFor (const FieldState& field) {
		//engine::printDebug(string("Game::getPlayerFor(") + string({(char)((char)field + '0')})  + string(")"));
		
		if (field == EMPTY)
			return NONE;
		if (field >= PLAYER_A && field <= BALL_A)
			return GAME_PLAYER_A;
		return GAME_PLAYER_B;
	}
	
}

#endif