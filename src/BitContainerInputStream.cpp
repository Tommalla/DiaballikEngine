/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#include <climits>
#include "BitContainerInputStream.h"

int BitContainerInputStream::getBegin (const int id) const {
	return this->currentBegin;
}

int BitContainerInputStream::getRow (const int id) const {
	return this->currentRow;
}

BitContainerInputStream::BitContainerInputStream() : BitContainer(0, 0) {
	this->currentBegin = this->currentRow = 0;
	this->size = INT_MAX;
}

BitContainerInputStream::BitContainerInputStream(const vector< uint8_t > data) : BitContainer (0, 0) {
	this->currentBegin = this->currentRow = 0;
	this->container = data;
	this->size = INT_MAX;
}

BitContainerInputStream::BitContainerInputStream (const BitContainer& b) : BitContainer(b) {
	this->currentBegin = this->currentRow = 0;
	this->size = INT_MAX;
}

void BitContainerInputStream::setBitsPerValue(const int bpv) {
	BitContainer::setBitsPerValue(bpv);
}

void BitContainerInputStream::addBits (const uint8_t bits) {
	this->container.push_back(bits);
}

const int BitContainerInputStream::getNextValue() {
	int res = this->getValue(666);
	this->currentBegin += this->bitsPerValue;
	
	if (this->currentBegin > this->bitsPerInt) {
		this->currentRow += this->currentBegin / this->bitsPerInt;
		this->currentBegin %= this->bitsPerInt;
	}
	return res;
}

const bool BitContainerInputStream::hasNext() const {
	return this->currentBegin + this->bitsPerValue < this->bitsPerInt ||
		this->currentRow + (this->currentBegin + this->bitsPerValue) / this->bitsPerInt < this->container.size();
}









