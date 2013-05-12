/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#include <cassert>
#include "Game.h"

Game::Game() {
	this->gameInProgress = false;
	this->currentPlayer = NONE;
}

void Game::resetMoves() {
	this->movesLeft = 2;
	this->passesLeft = 1;
}


void Game::newGame() {
	this->board = Board();
	this->currentPlayer = NONE;
	
	this->resetMoves();
	
	this->gameInProgress = true;
}

bool Game::isMoveValid (const Point& from, const Point& to) const {
	//TODO check if move is valid
}

bool Game::isMoveValid (const Move& move) const {
	return this->isMoveValid(move.from, move.to);
}

void Game::makeMove (const Point& from, const Point& to) {
	//TODO make move
}

void Game::makeMove (const Move& move) {
	this->makeMove(move.from, move.to);
}

vector< Point > Game::getDestinationsFor (const int x, const int y) const {
	//TODO get 'em!
}

vector< Point > Game::getDestinationsFor (const Point& pos) const {
	return this->getDestinationsFor(pos.x, pos.y);
}

vector< Point > Game::getPiecesOf (const GamePlayer player) const {
	assert(this->gameInProgress);
	
	vector<Point> res;
	
	for (int x = 0; x < BOARD_SIZE; ++x)
		for (int y = 0; y < BOARD_SIZE; ++y)
			if ((int)this->board.getFieldAt(x, y) == (int)player)
				res.push_back(Point(x, y));
			
	return res;
}

bool Game::isFinished() {

}

GamePlayer Game::getWinner() const {
	if (this->gameInProgress)
		return NONE;
	
	if (this->illegalEnd)
		return this->getOppositePlayer(this->currentPlayer);
	
	return this->currentPlayer;
}

GamePlayer Game::getOppositePlayer (const GamePlayer& player) const {
	if (player == NONE)
		return NONE;
	return (player == GAME_PLAYER_A) ? GAME_PLAYER_B : GAME_PLAYER_A;
}





