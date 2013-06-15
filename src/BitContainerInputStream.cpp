/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#include <climits>
#include "BitContainerInputStream.h"

int BitContainerInputStream::getBegin (const int id) const {
	return this->currentEnd;
}

int BitContainerInputStream::getRow (const int id) const {
	return this->currentRow;
}

BitContainerInputStream::BitContainerInputStream() : BitContainer(0, 0) {
	this->currentEnd = this->currentRow = this->nextId = 0;
	this->size = INT_MAX;
}

BitContainerInputStream::BitContainerInputStream(const vector< uint8_t > data) : BitContainer (0, 0) {
	this->currentEnd = this->currentRow = this->nextId = 0;
	this->container = data;
	this->size = INT_MAX;
}

BitContainerInputStream::BitContainerInputStream (const BitContainer& b) : BitContainer(b) {
	this->currentEnd = this->currentRow = this->nextId = 0;
	this->size = INT_MAX;
}

void BitContainerInputStream::setBitsPerValue(const int bpv) {
	BitContainer::setBitsPerValue(bpv);
}

void BitContainerInputStream::addBits (const uint8_t bits) {
	this->container.push_back(bits);
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

const bool BitContainerInputStream::hasNext() const {
	return this->currentEnd + this->bitsPerValue < this->bitsPerInt ||
		this->currentRow + (this->currentEnd + this->bitsPerValue) / this->bitsPerInt < this->container.size();
}








