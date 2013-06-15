/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved 
v 0.1					*/
#ifndef GAME_H
#define GAME_H

#include <unordered_set>

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
//IMPORTANT: The class assumes that player A starts at top and B starts at bottom!
class Game {
	private:
		Board board;
		bool gameInProgress;
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
		void callWinner(const GamePlayer &player);
		void callDraw();
		/**
		 * @brief Checks if 'unfair game' condition is met
		 * @return bool
		 **/
		bool checkForBlocks();
		bool innerIsFinished();
		
	public:
		Game(const GamePlayer player = NONE);
		void newGame();
		/**
		 * @brief Creates a new game from a predefined board
		 *
		 * @param black The coordinates of the black pawns
		 * @param white The coordinates of the white pawns
		 * @param ball The cooridnates of the balls (black then white)
		 * @return bool False if the board is invalid. Otherwise true.
		 **/
		bool newGame(const vector<Point> black, const vector<Point> white, const vector<Point> ball);
		
		const bool isMoveValid(const Point& from, const Point& to) const;
		const bool isMoveValid(const Move& move) const;
		/**
		 * @brief Returns true if the move is possible - performs the whole validation
		 * unaware of the player and his/her moves/passes left. Otherwise, returns false
		 **/
		const bool isMovePossible(const Point& from, const Point& to) const;
		/**
		 * @brief Equals [[isMovePossible(const Point&, const Point&)]]
		 **/
		const bool isMovePossible(const Move& move) const;
		void makeMove(const Point& from, const Point& to, const bool undo = false);
		void makeMove(const Move& move, const bool undo = false);
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
		
		const FieldState getFieldAt(const int8_t x, const int8_t y);
		const FieldState getFieldAt(const Point& pos) const;
		
		GamePlayer getWinner() const;
		
		GamePlayer getCurrentPlayer() const;
		/**
		 * @brief Sets current player to player
		 **/
		void setCurrentPlayer(const GamePlayer &player, const uint8_t movesLeft = 2, const uint8_t passesLeft = 1);
		
		MoveType getMoveTypeFor (const Move& move);
		
		const bool isFinished() const;
		/**
		 * @brief Switches to the next player
		 **/
		void finishMove();
		
		const string getHash() const;
		const int getPassessLeft() const;
		const int getMovesLeft() const;
		
		//debug
		const string toString() const;
		const string toInvertedString() const;
};

#endif // GAME_H
