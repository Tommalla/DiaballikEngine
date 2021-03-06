/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#include <climits>
//#include <bitset>
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
	this->container.push_back(0);
}

void BitContainerOutputStream::setBitsPerValue (const int bpv) {
	BitContainer::setBitsPerValue(bpv);
}

vector< uint8_t > BitContainerOutputStream::getData() const {
	return BitContainer::getData();
}


void BitContainerOutputStream::append (const int value) {
	//append as many rows as needed
	int tmp = (this->currentEnd + this->bitsPerValue) / this->bitsPerInt;
	while (tmp--)
		this->container.push_back(0);
	
	//printf("append: currentEnd = %d, bpv = %d, value = %d\n", this->currentEnd, this->bitsPerValue, value);
	
	this->setValue(666, value);
	this->currentRow += (this->currentEnd + this->bitsPerValue) / this->bitsPerInt;
	this->currentEnd += this->bitsPerValue;
	this->currentEnd %= this->bitsPerInt;
	
	
	//printf("row = %s\n", bitset<8>(container[this->currentRow]).to_string<char,char_traits<char>,allocator<char> >().c_str());
}


