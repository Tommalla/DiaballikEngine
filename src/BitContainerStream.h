/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#ifndef BITCONTAINERINPUTSTREAM_H
#define BITCONTAINERINPUTSTREAM_H

#include "BitContainer.h"

class BitContainerStream : protected BitContainer {
	protected:
		int currentRow, currentEnd, nextId;
		
		virtual int getBegin (const int id) const;
		virtual int getRow (const int id) const;
	public:
		BitContainerStream();
		BitContainerStream(const vector<uint8_t> data);
		BitContainerStream(const BitContainer& b);
		
		void addBits(const uint8_t bits);
		void setBitsPerValue(const int bpv);
		vector<uint8_t> getData() const;
		
		const int getNextValue();
		const bool hasNext() const;
		/**
		 * @brief Appends value at the end of [[BitContainerStream]].
		 * 
		 * It's done on assumption that each value starting from the [[nextId]]
		 * is of length [[bitsPerValue]] and that the current container has been 
		 * fully read (eg. "unused" spaces at the end will be a part of the value
		 * appended)/
		 *
		 * @param value The value to be appended.
		 **/
		void append(const int value);
};

#endif // BITCONTAINERINPUTSTREAM_H
