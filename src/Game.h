/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Move.h"
//#include "Point.h"
#include "enums.h"

/**
 * @brief The main class of the engine
 * Remembers the current state of game and allows to make valid moves
 **/
class Game {
	private:
		Board board;
		bool gameInProgress;
		/**
		 * @brief The amount of moves left for the current player
		 **/
		int movesLeft;
		GamePlayer currentPlayer;
		
	public:
		void newGame();
		
		bool isMoveValid(const Move& move) const;
		void makeMove(const Move& move);
		
		bool isFinished();
		GamePlayer getWinner() const;
		
		vector<Point> getDestinationsFor(const Point& pos) const;
		vector<Point> getDestinationsFor(const int x, const int y) const;
		
		vector<Point> getPiecesOf(const GamePlayer player) const;
};

#endif // GAME_H
