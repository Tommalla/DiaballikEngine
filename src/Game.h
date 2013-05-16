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
		
		unordered_set<string> prevStates;
		
		void resetMoves();
		bool areEnemiesBetween (Point from, const Point& to) const;
		void callDraw();
		void callWinner(const GamePlayer &player);
		/**
		 * @brief Checks if 'unfair game' condition is met
		 * @return bool
		 **/
		bool checkForBlocks();
		
	public:
		Game();
		void newGame();
		//TODO for further versions
		//void newGame(const Board &b);
		//begins a new game on a given Board.
		
		bool isMoveValid(const Point& from, const Point& to) const;
		bool isMoveValid(const Move& move) const;
		void makeMove(const Point& from, const Point& to);
		void makeMove(const Move& move);
		//TODO for further versions used for gui-based games with undo option
		//void undoMove(const Point& from, const Point &to);
		//void undoMove(const Move& move);
		//works pretty much the same as makeMove BUT removes states from prevStates so that going back with
		//moves and then doing them again doesn't induce draws
		
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
		
		bool isFinished();
		GamePlayer getWinner() const;
		
		GamePlayer getCurrentPlayer() const;
		GamePlayer getOppositePlayer(const GamePlayer& player) const;
		
		GamePlayer getPlayerFor(const FieldState& field) const;
		
		const string getHash() const;
		
		//debug
		const string toString() const;
};

#endif // GAME_H
