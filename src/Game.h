/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Move.h"
//#include "Point.h"
#include "enums.h"
#include "constants.h"

/**
 * @brief The main class of the engine
 * Remembers the current state of game and allows to make valid moves
 **/
class Game {
	private:
		Board board;
		bool gameInProgress;
		/**
		 * @brief Indicates that the game finished after an illegal move
		 **/
		bool illegalEnd;
		/**
		 * @brief The amount of moves left for the current player
		 **/
		uint8_t movesLeft;
		/**
		 * @brief The amount of passes left for the current player
		 **/
		uint8_t passesLeft;
		GamePlayer currentPlayer;
		
		void resetMoves();
		
	public:
		Game();
		void newGame();
		
		bool isMoveValid(const Point& from, const Point& to) const;
		bool isMoveValid(const Move& move) const;
		void makeMove(const Point& from, const Point& to);
		void makeMove(const Move& move);
		
		vector<Point> getDestinationsFor(const Point& pos) const;
		vector<Point> getDestinationsFor(const int x, const int y) const;
		
		vector<Point> getPiecesOf(const GamePlayer player) const;
		
		bool isFinished();
		GamePlayer getWinner() const;
		
		GamePlayer getOppositePlayer(const GamePlayer& player) const;
};

#endif // GAME_H
