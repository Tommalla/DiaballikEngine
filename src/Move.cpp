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

const bool operator== (const Move& a, const Move& b) {
	return a.from == b.from && a.to == b.to;
}


const bool operator!= (const Move& a, const Move& b) {
	return !(a == b);
}



