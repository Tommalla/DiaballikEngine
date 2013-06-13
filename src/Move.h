/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#ifndef MOVE_H
#define MOVE_H
#include "Point.h"

//It's a class because in future I might want to add some extra features to it
class Move {
	public:
		Point from, to;
		
		Move(){}
		Move(const Point &from, const Point &to);
		
		/**
		 * @brief Reverts the move (swaps from and to)
		 **/
		void revert();
};

const bool operator== (const Move& a, const Move& b);
const bool operator!= (const Move& a, const Move& b);

#endif // MOVE_H
