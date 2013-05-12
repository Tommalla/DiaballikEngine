/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#ifndef POINT_H
#define POINT_H
#include <cstdint>

class Point {
	public:
		int8_t x, y;
		Point(int8_t x, int8_t y);
		Point(){}
};

Point operator+(const Point &a, const Point &b);
Point operator-(const Point &a, const Point &b);
const bool operator==(const Point &a, const Point &b);
const bool operator!=(const Point &a, const Point &b);

#endif // POINT_H
