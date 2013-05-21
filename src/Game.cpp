/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#include <cassert>
#include <cmath>
#include "Game.h"
#include "functions.h"

using namespace std;

Game::Game() {
	this->gameInProgress = false;
	this->currentPlayer = NONE;
}

bool Game::areEnemiesBetween (Point from, const Point& to) const {
	engine::printDebug("Game::areEnemiesBetween(" + string({char(from.x + '0')}) + ", " + string({char(from.y + '0')}) + "; " +
	string({char(to.x + '0')}) + ", " + string({char(to.y + '0')}) + ")");
	FieldState orig = this->board.getFieldAt(from);
	
	Point diff = to - from;
	diff.x = engine::sgn(diff.x);
	diff.y = engine::sgn(diff.y);
	
	do {
		from = from + diff;
		if (this->board.getFieldAt(from) != EMPTY &&  
			this->getPlayerFor(this->board.getFieldAt(from)) != this->getPlayerFor(orig))
			return true;
	} while (from != to);
	
	return false;
}

void Game::callWinner (const GamePlayer& player) {
	engine::printDebug(string("Game::callWinner(") + string({(char)((char)player + '0')})  + string(")"));
	this->gameInProgress = false;
	this->currentPlayer = player;
}

void Game::callDraw() {
	engine::printDebug("Game::callDraw()");
	this->gameInProgress = false;
	this->currentPlayer = NONE;
}

void Game::resetMoves() {
	engine::printDebug("Game::resetMoves()");
	this->movesLeft = 2;
	this->passesLeft = 1;
}

bool Game::checkForBlocks() {
	engine::printDebug("Game::checkForBlocks()");
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
					abs(lastA.y - y) <= 1 ) )
						lastA = Point(x,y);
					else
						lineA = false;
				}
				
				if ((field == PLAYER_B || field == BALL_B) && lineB) {
					if (lastB == Point(-1, -1) || (lastB.x + 1 == x && 
					abs(lastB.y - y) <= 1 ) )
						lastB = Point(x,y);
					else
						lineB = false;
				}
			}
			
			if (lineA == false && lineB == false)
				return false;
		}
	
	if ((lineA || lineB) && contacts >= 3) {
		if (lineA && lineB)
			this->callDraw();
		else
			this->callWinner((lineA) ? GAME_PLAYER_B : GAME_PLAYER_A);
		return true;
	}
}

void Game::newGame() {
	engine::printDebug("Game::newGame()");
	this->board = Board();
	this->currentPlayer = NONE;
	
	this->resetMoves();
	
	this->gameInProgress = true;
}

bool Game::isMoveValid (const Point& from, const Point& to) const {
	engine::printDebug("Game::isMoveValid(" + string({char(from.x + '0')}) + ", " + string({char(from.y + '0')}) + "; " +
	string({char(to.x + '0')}) + ", " + string({char(to.y + '0')}) + ")");
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
	engine::printDebug("Game::isMoveValid(" + string({char(move.from.x + '0')}) + ", " + string({char(move.from.y + '0')}) + "; " +
	string({char(move.to.x + '0')}) + ", " + string({char(move.to.y + '0')}) + ")");
	return this->isMoveValid(move.from, move.to);
}

void Game::makeMove (const Point& from, const Point& to) {
	engine::printDebug("Game::makeMove(" + string({char(from.x + '0')}) + ", " + string({char(from.y + '0')}) + "; " +
	string({char(to.x + '0')}) + ", " + string({char(to.y + '0')}) + ")");
	assert(this->isMoveValid(from, to));
	
	FieldState srcFieldState = this->board.getFieldAt(from);
	FieldState dstFieldState = this->board.getFieldAt(to);
	
	if (this->currentPlayer != this->getPlayerFor(srcFieldState)) {	//player not yet known or a new player
		this->currentPlayer = this->getPlayerFor(srcFieldState);
		this->resetMoves();
	}
	
	if (dstFieldState == EMPTY) {	//MOVE
		assert(this->movesLeft > 0);
		
		this->board.setFieldAt(to, srcFieldState);
		this->board.setFieldAt(from, EMPTY);
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
	engine::printDebug("Game::makeMove(" + string({char(move.from.x + '0')}) + ", " + string({char(move.from.y + '0')}) + "; " +
	string({char(move.to.x + '0')}) + ", " + string({char(move.to.y + '0')}) + ")");
	this->makeMove(move.from, move.to);
}

vector< Point > Game::getDestinationsFor (const int x, const int y) const {
	engine::printDebug("Game::getDestinationsFor(" + string({char(x + '0')}) + ", " + string({char(y + '0')}) +")");
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
				Point(-1, 1), Point(1, -1), Point(0, -1), Point(0, 1)};
		
		Point iter[8];
		for (int i = 0; i < 8; ++i)
			iter[i] = Point(x, y);
		
		while (size > 0) {
			for (int i = 0; i < size; ++i) {
				iter[i] = iter[i] + t[i];
				if (iter[i].x < 0 || iter[i].x >= this->board.getSize() ||
					iter[i].y < 0 || iter[i].y >= this->board.getSize() ||	//if the iterator is no longer valid
					(srcFieldState == BALL_A && 
						(this->board.getFieldAt(iter[i]) == PLAYER_B || 
						this->board.getFieldAt(iter[i]) == BALL_B)) ||
					(srcFieldState == BALL_B &&
						(this->board.getFieldAt(iter[i]) == PLAYER_A || 
						this->board.getFieldAt(iter[i]) == BALL_A)) ) {
							swap(iter[i], iter[size - 1]);
							swap(t[i], t[size - 1]);
							--size;
				} else if (board.getFieldAt(iter[i]) != EMPTY)
					res.push_back(iter[i]);
			}
		}
	}
	return res;
}

vector< Point > Game::getDestinationsFor (const Point& pos) const {
	engine::printDebug("Game::getDestinationsFor(" + string({char(pos.x + '0')}) + ", " + string({char(pos.y + '0')}) +")");
	return this->getDestinationsFor(pos.x, pos.y);
}

vector< Point > Game::getPawnsOf (const GamePlayer player) const {
	engine::printDebug(string("Game::getPawnsOf(") + string({(char)((char)player + '0')})  + string(")"));
	assert(this->gameInProgress);
	
	vector<Point> res;
	
	for (int x = 0; x < BOARD_SIZE; ++x)
		for (int y = 0; y < BOARD_SIZE; ++y)
			if (this->getPlayerFor(this->board.getFieldAt(x, y)) == player)
				res.push_back(Point(x, y));
			
	return res;
}

const FieldState Game::getFieldAt (const int8_t x, const int8_t y) {
	engine::printDebug("Game::getFieldAt(" + string({char(x + '0')}) + ", " + string({char(y + '0')}) +")");
	return this->board.getFieldAt(x, y);
}

const FieldState Game::getFieldAt (const Point& pos) const {
	engine::printDebug("Game::getFieldAt(" + string({char(pos.x + '0')}) + ", " + string({char(pos.y + '0')}) +")");
	return this->board.getFieldAt(pos);
}

bool Game::isFinished() {
	engine::printDebug("Game::isFinished()");
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
	engine::printDebug("Game::getWinner()");
	if (this->gameInProgress)
		return NONE;
	
	return this->currentPlayer;
}

GamePlayer Game::getCurrentPlayer() const {
	engine::printDebug("Game::getCurrentPlayer()");
	return this->currentPlayer;
}


GamePlayer Game::getOppositePlayer (const GamePlayer& player) const {
	engine::printDebug(string("Game::getOppositePlayer(") + string({(char)((char)player + '0')})  + string(")"));
	if (player == NONE)
		return NONE;
	return (player == GAME_PLAYER_A) ? GAME_PLAYER_B : GAME_PLAYER_A;
}

GamePlayer Game::getPlayerFor (const FieldState& field) const {
	engine::printDebug(string("Game::getPlayerFor(") + string({(char)((char)field + '0')})  + string(")"));
	
	if (field == EMPTY)
		return NONE;
	if (field >= PLAYER_A && field <= BALL_A)
		return GAME_PLAYER_A;
	return GAME_PLAYER_B;
}

MoveType Game::getMoveTypeFor (const Move& move) {
	if (this->isMoveValid(move) == false)
		return INVALID;
	return (this->board.getFieldAt(move.to) != EMPTY) ? BALL_PASS : MOVE;
}


const string Game::getHash() const {
	engine::printDebug("Game::getHash()");
	return char(this->currentPlayer) + this->board.getHash();
}

const string Game::toString() const {
	return string((this->currentPlayer == GAME_PLAYER_A) ? "PlayerA" : ((this->currentPlayer == GAME_PLAYER_B) ? "PlayerB" : "NONE")) +
	"\n" + this->board.toString();
}

const string Game::toInvertedString() const {
	return string((this->currentPlayer == GAME_PLAYER_A) ? "PlayerA" : ((this->currentPlayer == GAME_PLAYER_B) ? "PlayerB" : "NONE")) +
	"\n" + this->board.toInvertedString();
}







