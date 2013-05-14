/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Move.h"
//#include "Point.h"
#include "enums.h"
#include "constants.h"

using namespace std;

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
		bool areEnemiesBetween (Point from, const Point& to) const;
		
	public:
		Game();
		void newGame();
		
		bool isMoveValid(const Point& from, const Point& to) const;
		bool isMoveValid(const Move& move) const;
		void makeMove(const Point& from, const Point& to);
		void makeMove(const Move& move);
		
		/**
		 * @brief Returns fields that pawn can move to in one move (or pass ball to)
		 * @param pos The position of pawn
		 * @return vector< Point > - the vector of all positions the pawn can move to/pass ball to
		 **/
		vector<Point> getDestinationsFor(const Point& pos) const;
		/**
		 * @brief Returns fields that pawn can move to in one move (or pass ball to)
		 * Same as getDestinationsFor(const Point&)
		 **/
		vector<Point> getDestinationsFor(const int x, const int y) const;
		
		vector<Point> getPawnsOf(const GamePlayer player) const;
		
		bool isFinished();
		GamePlayer getWinner() const;
		
		GamePlayer getOppositePlayer(const GamePlayer& player) const;
};

#endif // GAME_H
