/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#include <climits>
#include "BitContainerOutputStream.h"

int BitContainerOutputStream::getBegin (const int id) const {
	return this->currentEnd;
}

int BitContainerOutputStream::getRow (const int id) const {
	return this->currentRow;
}

BitContainerOutputStream::BitContainerOutputStream(): BitContainer(0, 0) {
	this->size = this->maxValue = INT_MAX;
	this->currentEnd = this->currentRow = 0;
}


void BitContainerOutputStream::append (const int value) {
	//append as many rows as needed
	int tmp = (this->currentEnd + this->bitsPerValue) / this->bitsPerInt;
	while (tmp--)
		this->container.push_back(0);
	
	printf("append: currentEnd = %d, bpv = %d, value = %d\n", this->currentEnd, this->bitsPerValue, value);
	
	this->setValue(666, value);
	this->currentRow += (this->currentEnd + this->bitsPerValue) / this->bitsPerInt;
	this->currentEnd += this->bitsPerValue;
	this->currentEnd %= this->bitsPerInt;
}


