/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#include "Move.h"

Move::Move (const Point& from, const Point& to) {
	this->from = from;
	this->to = to;
}

void Move::revert() {
	Point tmp = this->from;
	this->from = this->to;
	this->to = tmp;
}


