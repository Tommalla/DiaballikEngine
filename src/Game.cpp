/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#include <cassert>
#include <cmath>
#include "Game.h"

Game::Game() {
	this->gameInProgress = false;
	this->currentPlayer = NONE;
}

bool Game::areEnemiesBetween (Point from, const Point& to) const {
	FieldState orig = this->board.getFieldAt(from);
	Point diff(((from - to).x > 0) ? 1 : -1, ((from - to).y > 0) ? 1 : -1);
	
	do {
		from = from + diff;
		if (this->board.getFieldAt(from) != orig)
			return true;
	} while (from != to);
	
	return false;
}

void Game::callDraw() {
	this->gameInProgress = false;	//a draw
	this->currentPlayer = NONE;
}

void Game::callWinner (const GamePlayer& player) {
	this->gameInProgress = false;
	this->currentPlayer = player;
}


void Game::resetMoves() {
	this->movesLeft = 2;
	this->passesLeft = 1;
}

bool Game::checkForBlocks() {
	int contacts = 0;
	bool lineA, lineB;
	lineA = lineB = true;
	
	Point lastA, lastB;
	lastA = lastB = Point(-1, -1);
	
	FieldState field;
	
	for (int x = 0; x < this->board.getSize(); ++x) 
		for (int y = 0; y < this->board.getSize(); ++y) {
			field = this->board.getFieldAt(x, y);
			
			if ((field == PLAYER_A || field == BALL_A) && y < this->board.getSize() - 1 &&
				(this->board.getFieldAt(x, y + 1) == PLAYER_B || this->board.getFieldAt(x, y + 1) == BALL_B) )
				++contacts;	//two players facing each other
			
			if (field != EMPTY) {
				if ((field == PLAYER_A || field == BALL_A) && lineA) {
					if (lastA == Point(-1, -1) || (lastA.x + 1 == x && 
					(lastA.y == y || lastA.y + 1 == y || lastA.y == y + 1 )) )
						lastA = Point(x,y);
					else
						lineA = false;
				}
				
				if ((field == PLAYER_B || field == BALL_B) && lineB) {
					if (lastB == Point(-1, -1) || (lastB.x + 1 == x && 
						(lastB.y == y || lastB.y + 1 == y || lastB.y == y + 1 )) )
						lastB = Point(x,y);
					else
						lineB = false;
				}
			}
			
			if (lineA == false && lineB == false)
				return false;
		}
	
	if ((lineA || lineB) && contacts >= 3) {
		this->callWinner(this->getOppositePlayer(this->currentPlayer));
		return true;
	}
	//check for lines and contacts with lines
}

void Game::newGame() {
	this->board = Board();
	this->currentPlayer = NONE;
	
	this->resetMoves();
	
	this->prevStates.clear();
	this->gameInProgress = true;
}

bool Game::isMoveValid (const Point& from, const Point& to) const {
	if (from.x != to.x && from.y != to.y && (to-from).x != (to-from).y)
		return false;
	
	
	if (board.getFieldAt(to) == EMPTY) {
		return (from.x == to.x || from.y == to.y) &&
			(abs((to - from).x) + abs((to - from).y) == 1) &&	/* Not more than one field */
			this->board.getFieldAt(from) != BALL_A &&
			this->board.getFieldAt(from) != BALL_B;
	} else {
		return ((this->board.getFieldAt(to) == PLAYER_A && this->board.getFieldAt(from) == BALL_A) ||
		(this->board.getFieldAt(to) == PLAYER_B && this->board.getFieldAt(from) == BALL_B)) &&
		!this->areEnemiesBetween(from, to);
	}
}

bool Game::isMoveValid (const Move& move) const {
	return this->isMoveValid(move.from, move.to);
}

void Game::makeMove (const Point& from, const Point& to) {
	assert(this->isMoveValid(from, to));
	
	FieldState srcFieldState = this->board.getFieldAt(from);
	FieldState dstFieldState = this->board.getFieldAt(to);
	
	if (this->currentPlayer != (GamePlayer)srcFieldState) {	//player not yet known or a new player
		this->currentPlayer = (GamePlayer)srcFieldState;
		this->resetMoves();
	}
	
	{
		string hash = this->getHash();
		if (prevStates.count(hash) > 0) {	//repetition!
			this->callDraw();
			return;
		}
		
		prevStates.insert(hash);
	}
	
	if (dstFieldState == EMPTY) {	//MOVE
		assert(this->movesLeft > 0);
		
		this->board.setFieldAt(to, srcFieldState);
		this->board.setFieldAt(to, EMPTY);
		this->movesLeft--;
	} else {	//PASS
		assert(this->passesLeft > 0);
		
		this->board.setFieldAt(to, srcFieldState);
		this->board.setFieldAt(from, dstFieldState);
		this->passesLeft--;
	}
	
	if (this->checkForBlocks() == false)
		this->isFinished();
}

void Game::makeMove (const Move& move) {
	this->makeMove(move.from, move.to);
}

vector< Point > Game::getDestinationsFor (const int x, const int y) const {
	FieldState srcFieldState = this->board.getFieldAt(x, y);
	vector<Point> res;
	
	if (srcFieldState == PLAYER_A || srcFieldState == PLAYER_B) {
		Point t[4] = { Point(-1, 0), Point(1, 0), Point(0, -1), Point(0, 1) };
		
		for (int i = 0; i < 4; ++i) {
			Point tmp = Point(x, y) + t[i];
			if (tmp.x >= 0 && tmp.x < this->board.getSize() &&
				tmp.y >= 0 && tmp.y < this->board.getSize() &&
				this->board.getFieldAt(tmp) == EMPTY)
				res.push_back(tmp);
		}
	} else if (srcFieldState == BALL_A || srcFieldState == BALL_B) {
		int size = 8;
		Point t[8] = { Point(-1, -1), Point(-1, 0), Point(1, 1), Point(1, 0),
				Point(-1, 1), Point(1, -1), Point(0, -1), Point(-1, 0)};
		
		Point iter[8];
		for (int i = 0; i < 8; ++i)
			iter[i] = Point(x, y) + t[i];
		
		while (size > 0) {
			for (int i = 0; i < size; ++i) {
				if (iter[i].x < 0 || iter[i].x >= this->board.getSize() ||
					iter[i].y < 0 || iter[i].y >= this->board.getSize() ||	//if the iterator is no longer valid
					(srcFieldState == BALL_A && 
						(this->board.getFieldAt(iter[i]) == PLAYER_B || 
						this->board.getFieldAt(iter[i]) == BALL_B)) ||
					(srcFieldState == BALL_B &&
						(this->board.getFieldAt(iter[i]) == PLAYER_A || 
						this->board.getFieldAt(iter[i]) == BALL_A)) ) {
							swap(iter[i], iter[size - 1]);
							--size;
				} else if (board.getFieldAt(iter[i]) != EMPTY)
					res.push_back(iter[i]);
			}
		}
	}
}

vector< Point > Game::getDestinationsFor (const Point& pos) const {
	return this->getDestinationsFor(pos.x, pos.y);
}

vector< Point > Game::getPawnsOf (const GamePlayer player) const {
	assert(this->gameInProgress);
	
	vector<Point> res;
	
	for (int x = 0; x < BOARD_SIZE; ++x)
		for (int y = 0; y < BOARD_SIZE; ++y)
			if ((int)this->board.getFieldAt(x, y) == (int)player)
				res.push_back(Point(x, y));
			
	return res;
}

bool Game::isFinished() {
	if (!this->gameInProgress)
		return true;
	
	for (int x = 0; x < this->board.getSize(); ++x) {
		if (this->board.getFieldAt(x, 0) == BALL_B) {
			this->callWinner(GAME_PLAYER_B);
			return true;
		}
		
		if (this->board.getFieldAt(x, this->board.getSize() - 1) == BALL_A) {
			this->callWinner(GAME_PLAYER_A);
			return true;
		}
	}
		
	return false;
}

GamePlayer Game::getWinner() const {
	if (this->gameInProgress)
		return NONE;
	
	return this->currentPlayer;
}

GamePlayer Game::getOppositePlayer (const GamePlayer& player) const {
	if (player == NONE)
		return NONE;
	return (player == GAME_PLAYER_A) ? GAME_PLAYER_B : GAME_PLAYER_A;
}

const string Game::getHash() const {
	return char(this->currentPlayer) + this->board.getHash();
}






