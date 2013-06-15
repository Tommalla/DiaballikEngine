/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#ifndef BITCONTAINERINPUTSTREAM_H
#define BITCONTAINERINPUTSTREAM_H

#include "BitContainer.h"

class BitContainerInputStream : protected BitContainer {
	protected:
		int currentRow, currentEnd, nextId;
		
		virtual int getBegin (const int id) const;
		virtual int getRow (const int id) const;
	public:
		BitContainerInputStream();
		BitContainerInputStream(const vector<uint8_t> data);
		BitContainerInputStream(const BitContainer& b);
		
		void addBits(const uint8_t bits);
		
		const int getNextValue();
		const bool hasNext() const;
};

#endif // BITCONTAINERINPUTSTREAM_H
