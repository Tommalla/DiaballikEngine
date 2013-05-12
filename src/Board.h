/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */
#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <string>

#include "Point.h"
#include "BitContainer.h"

using namespace std;

class Board {
	private:
		int size;
		BitContainer* board;
		
		void copyToSelf(const Board &b);
	public:
		/**
		 * @brief An empty constructor
		 * Creates a default board: 7 x 7 with opponents lined up on both sides
		 **/
		Board();
		/**
		 * @brief Creates a new square board of specified width
		 * @param size Board width. The default is 7.
		 **/
		Board(int size = 7);
		Board(const Board &b);
		
		void setFieldAt(const int x, const int y, const int field);
		void setFieldAt(const Point& pos, const int field);
		int getFieldAt(const int x, const int y) const;
		int getFieldAt(const Point& pos) const;

		
		
		~Board();
		Board& operator=(const Board &b);
		//debug:
		string toString();
};

#endif // BOARD_H
