/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#include "BitContainerStream.h"

int BitContainerStream::getBegin (const int id) const {
	return this->currentEnd;
}

int BitContainerStream::getRow (const int id) const {
	return this->currentRow;
}

BitContainerStream::BitContainerStream() : BitContainer(0, 0) {
	this->currentEnd = this->currentRow = this->nextId = 0;
}

BitContainerStream::BitContainerStream(const vector< uint8_t > data) : BitContainer (0, 0) {
	this->currentEnd = this->currentRow = this->nextId = 0;
	this->container = data;
}

BitContainerStream::BitContainerStream (const BitContainer& b) : BitContainer(b) {
	this->currentEnd = this->currentRow = this->nextId = 0;
}

void BitContainerStream::addBits (const uint8_t bits) {
	this->container.push_back(bits);
}

void BitContainerStream::setBitsPerValue (const int bpv) {
	this->bitsPerValue = bpv;
}

vector< uint8_t > BitContainerStream::getData() const {
	return this->container;
}


const int BitContainerStream::getNextValue() {
	int res = this->getValue(this->nextId);
	this->nextId++;
	this->currentEnd += this->bitsPerValue;
	
	if (this->currentEnd > this->bitsPerInt) {
		this->currentRow += this->currentEnd / this->bitsPerInt;
		this->currentEnd %= this->bitsPerInt;
	}
}

const bool BitContainerStream::hasNext() const {
	return this->currentEnd + this->bitsPerValue < this->bitsPerInt ||
		this->currentRow + (this->currentEnd + this->bitsPerValue) / this->bitsPerInt < this->container.size();
}

void BitContainerStream::append (const int value) {
	//calculate the real end of the last row
	int d = ((this->container.size() - this->currentRow) * this->bitsPerValue) + this->bitsPerInt - this->currentEnd;
	int realEnd = this->bitsPerInt -  (d % this->bitsPerValue);
	
	//append as many rows as needed
	int tmp = (this->bitsPerValue - (this->bitsPerInt - realEnd)) / this->bitsPerInt;
	while (tmp--)
		this->container.push_back(0);
	
	this->setValue(this->nextId + d / this->bitsPerValue, value);
}








