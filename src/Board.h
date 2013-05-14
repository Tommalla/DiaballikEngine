/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */
#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <string>

#include "Point.h"
#include "BitContainer.h"
#include "constants.h"
#include "enums.h"

using namespace std;

class Board {
	private:
		int size;
		BitContainer board;
		
		void copyToSelf(const Board &b);
	public:
		/**
		 * @brief Creates a new square board of specified width
		 * @param size Board width. The default is 7.
		 **/
		Board(int size = BOARD_SIZE);
		Board(const Board &b);
		
		void setFieldAt(const uint8_t x, const uint8_t y, const FieldState field);
		void setFieldAt(const Point& pos, const FieldState field);
		FieldState getFieldAt(const uint8_t x, const uint8_t y) const;
		FieldState getFieldAt(const Point& pos) const;

		Board& operator=(const Board &b);
		//debug:
		string toString();
		string getHash();
};

#endif // BOARD_H
