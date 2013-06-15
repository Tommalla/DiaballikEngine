/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#ifndef BITCONTAINEROUTPUTSTREAM_H
#define BITCONTAINEROUTPUTSTREAM_H

#include "BitContainer.h"


class BitContainerOutputStream : protected BitContainer {
	protected:
		virtual int getBegin (const int id) const;
		virtual int getRow (const int id) const;

		int currentRow, currentEnd;
	public:
		BitContainerOutputStream();
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

#endif // BITCONTAINEROUTPUTSTREAM_H
