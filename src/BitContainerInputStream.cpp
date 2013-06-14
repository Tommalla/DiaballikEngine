/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#include "BitContainerInputStream.h"

int BitContainerInputStream::getBegin (const int id) const {
	return this->currentEnd;
}

int BitContainerInputStream::getRow (const int id) const {
	return this->currentRow;
}

BitContainerInputStream::BitContainerInputStream(const vector< uint8_t > data) : BitContainer (0, 0) {
	this->currentEnd = this->currentRow = this->nextId = 0;
	this->container = data;
}

BitContainerInputStream::BitContainerInputStream (const BitContainer& b) : BitContainer(b) {
	this->currentEnd = this->currentRow = this->nextId = 0;
}

void BitContainerInputStream::setBitsPerValue (const int bpv) {
	this->bitsPerValue = bpv;
}

const int BitContainerInputStream::getNextValue() {
	int res = this->getValue(this->nextId);
	this->nextId++;
	this->currentEnd += this->bitsPerValue;
	
	if (this->currentEnd > this->bitsPerInt) {
		this->currentRow += this->currentEnd / this->bitsPerInt;
		this->currentEnd %= this->bitsPerInt;
	}
}







