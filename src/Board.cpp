/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */
#include <cassert>
#include <cmath>

#include "Board.h"

void Board::copyToSelf (const Board& b) {
	this->size = b.size;
	this->board = new BitContainer(*b.board);
}


void Board::setFieldAt (const Point& pos, const int field) {
	assert(field < this->size * this->size);
	assert(pos.x < this->size && pos.y < this->size);
	
	this->board->setValue(this->size * pos.y + pos.x, field);
}

Board::Board (int size) {
	this->size = size;
	this->board = new BitContainer(size * size, size * size);
}

Board::Board (const Board& b) {
	this->copyToSelf(b);
}

Board::~Board() {
	delete this->board;
}

Board& Board::operator= (const Board& b) {
	this->copyToSelf(b);
	return *this;
}


int Board::getFieldAt (const int x, const int y) const {
	assert(x < this->size && y < this->size);
	
	return this->board->getValue(this->size * y + x);
}

const Point Board::getFreeFieldAround (const Point& pos) {
	assert(pos.x < this->size && pos.y < this->size);
	
	Point t[4] = {Point(-1, 0), Point(1, 0), Point(0, -1), Point(0, 1)};
	for (int i = 0; i < 4; ++i)
		if (pos.x + t[i].x >= 0 && pos.x + t[i].x < this->size &&
			pos.y + t[i].y >= 0 && pos.y + t[i].y < this->size &&
			this->getFieldAt(pos.x + t[i].x, pos.y + t[i].y) == 0 )
			return t[i];
			
	return Point(0, 0);
}

const vector< Point > Board::getMoves() {
	vector<Point> res;
	for (int x = 0; x < this->size; ++x)
		for (int y = 0; y < this->size; ++y)
			if (this->getFreeFieldAround(Point(x, y)) != Point(0, 0))
				res.push_back(Point(x,y));
	return res;
}


const int Board::countInversions() const {
	//napałowo, bo mało
	int res = 0;
	for (int i = 0; i < this->size * this->size; ++i) {
		int elem = this->board->getValue(i);
		if (elem != 0)
			for (int j = 0; j < i; ++j)
				if (this->board->getValue(j) > elem)
					++res;
	}
	return res;
}

//TODO to też uzależnić od wierszy?
const int Board::getManhattanMetricValue(const int row) const {
	int res = 0;
	for (int x = 0; x < this->size; ++x)
		for (int y = 0; y < this->size; ++y) {
			int elem = this->getFieldAt(x, y);
			if (elem != 0 && elem <= (row + 1) * this->size) {
				elem--;
				res += abs(x - (elem % this->size));
				res += abs(y - (elem / this->size));
			}
		}
		
	return res;
}

const Point Board::getPos (const int number) {
	for (int x = 0; x < this->size; ++x)
		for (int y = 0; y < this->size; ++y)
			if (this->getFieldAt(x, y) == number)
				return Point(x, y);
			
	return Point(-1, -1);
}



bool Board::isSolved(const int rows, const int col) const {
	for (int i = 0; i < rows * this->size; ++i)
		if (i != this->size * this->size - 1 && (rows != this->size || i / this->size < rows - 2 || i % this->size < col) &&
			this->getFieldAt(i % this->size, i / this->size) != i + 1)
			return false;
	
	return true;
}

string Board::toString() {
	string res ="";
	
	for (int y = 0; y < this->size; ++y, res += "\n") 
		for (int x = 0; x < this->size; ++x)
			res += this->getFieldAt(x, y) + " ";
		
	return res;
}

