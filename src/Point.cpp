/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#include "Point.h"

Point::Point(int8_t x, int8_t y) {
	this->x = x;
	this->y = y;
}

Point operator+ (const Point& a, const Point& b) {
	return Point(a.x + b.x, a.y + b.y);
}

Point operator- (const Point& a, const Point& b) {
	return a + Point(-b.x, -b.y);
}

const bool operator== (const Point& a, const Point& b) {
	return a.x == b.x && a.y == b.y;
}

const bool operator!= (const Point& a, const Point& b) {
	return !(a == b);
}



