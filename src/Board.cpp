/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */
#include <cassert>
#include <cmath>

#include "Board.h"

void Board::copyToSelf (const Board& b) {
	this->size = b.size;
	this->board = new BitContainer(*b.board);
}

Board::Board() {
	this->size = 7;
	this->board = new BitContainer(7, 5);
	
	//TODO: Board generation.
}

Board::Board (int size) {
	this->size = size;
	this->board = new BitContainer(size * size, size * size);
}

Board::Board (const Board& b) {
	this->copyToSelf(b);
}

void Board::setFieldAt (const int x, const int y, const int field) {
	assert(field < this->size * this->size);
	assert(x < this->size && y < this->size);
	
	this->board->setValue(this->size * y + x, field);
}


void Board::setFieldAt (const Point& pos, const int field) {
	this->setFieldAt(pos.x, pos.y, field);
}

int Board::getFieldAt (const int x, const int y) const {
	assert(x < this->size && y < this->size);
	
	return this->board->getValue(this->size * y + x);
}

int Board::getFieldAt (const Point& pos) const {
	return this->getFieldAt(pos.x, pos.y);
}


Board::~Board() {
	delete this->board;
}

Board& Board::operator= (const Board& b) {
	this->copyToSelf(b);
	return *this;
}

string Board::toString() {
	string res ="";
	
	for (int y = 0; y < this->size; ++y, res += "\n") 
		for (int x = 0; x < this->size; ++x)
			res += this->getFieldAt(x, y) + " ";
		
	return res;
}

