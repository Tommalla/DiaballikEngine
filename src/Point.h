/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#ifndef POINT_H
#define POINT_H
#include <cstdint>

class Point {
	public:
		uint8_t x, y;
		Point(uint8_t x, uint8_t y);
		Point(){}
};

Point operator+(const Point &a, const Point &b);
const bool operator==(const Point &a, const Point &b);
const bool operator!=(const Point &a, const Point &b);

#endif // POINT_H
