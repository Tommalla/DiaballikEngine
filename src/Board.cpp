/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */
#include <cassert>
#include <cmath>

#include "Board.h"
#include "functions.h"

void Board::copyToSelf (const Board& b) {
	this->size = b.size;
	this->board = b.board;
}

Board::Board (int size) : board(size * size, MAX_FIELD_STATE) {
	this->size = size;
	//this->board = new BitContainer(size * size, MAX_FIELD_STATE);
	
	for (int x = 0; x < this->size; ++x) {
		this->setFieldAt(x, 0, PLAYER_A);
		this->setFieldAt(x, this->size - 1, PLAYER_B);
	}
	
	for (int y = 1; y < this->size - 1; ++y)
		for (int x = 0; x < this->size; ++x)
			this->setFieldAt(x, y, EMPTY);
		
		this->setFieldAt(this->size / 2, 0, BALL_A);
	this->setFieldAt(this->size / 2, this->size - 1, BALL_B);
}

Board::Board (const Board& b) : board(b.board) {
	this->copyToSelf(b);
}

void Board::setFieldAt (const uint8_t x, const uint8_t y, const FieldState field) {
	assert(field < this->size * this->size);
	assert(x < this->size && y < this->size);
	
	this->board.setValue(this->size * y + x, field);
}


void Board::setFieldAt (const Point& pos, const FieldState field) {
	this->setFieldAt(pos.x, pos.y, field);
}

FieldState Board::getFieldAt (const uint8_t x, const uint8_t y) const {
	engine::printDebug("Board::getFieldAt(" + string({char(x + '0')}) + ", " + string({char(y + '0')}) +")");
	assert(x < this->size && y < this->size);
	
	return (FieldState)this->board.getValue(this->size * y + x);
}

FieldState Board::getFieldAt (const Point& pos) const {
	return this->getFieldAt(pos.x, pos.y);
}

Board& Board::operator= (const Board& b) {
	this->copyToSelf(b);
	return *this;
}

const string Board::getHash() const {
	return this->board.getHash();
}

const int Board::getSize() const {
	return this->size;
}

const string Board::toString() const {
	string res = "";
	
	for (int y = 0; y < this->size; ++y, res += "\n") 
		for (int x = 0; x < this->size; ++x) {
			string tmp = "";	//ugly hack
			tmp.push_back(this->getFieldAt(x, y) + '0');
			res += tmp + string(" ");
		}
		
		return res;
}

