/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */
#include <cmath>
#include <climits>
#include <cassert>
#include <cstdio>
#include <bitset>
#include <string>

#include "BitContainer.h"

const uint8_t UINT8_T_MAX = ~uint8_t(0);

int BitContainer::getBegin (const int id) const {
	return (this->bitsPerValue * id) % this->bitsPerInt;
}

int BitContainer::getRow (const int id) const {
	return (this->bitsPerValue * id) / this->bitsPerInt;
}

uint8_t BitContainer::getMask (const int begin, const int end, const uint8_t value) const {
	uint8_t mask = value;
	mask <<= this->bitsPerInt - end;
	return mask;
}

uint8_t BitContainer::getClearMask (const int begin, const int end) const {
	uint8_t clearMask = UINT8_T_MAX - uint8_t((1 << (this->bitsPerInt - begin)) - 1);
	clearMask += uint8_t((1 << (this->bitsPerInt - end)) - 1);
	return clearMask;
}

int BitContainer::getBits (const int row, const int begin, const int end) const {
	uint8_t mask = ~this->getClearMask(begin, end);
	//printf("\tgetBits(row = %d, begin = %d, end = %d)\n", row, begin, end);
	//printf("mask = %s\n", bitset<8>(mask).to_string<char,char_traits<char>,allocator<char> >().c_str());
	mask &= container[row];
// 	printf("mask = %s\n", bitset<64>(mask).to_string<char,char_traits<char>,allocator<char> >().c_str());
// 	puts("Done(getBits)");
	return mask / uint8_t(1 << (this->bitsPerInt - end));
}

void BitContainer::setBits (const int row, const int begin, const int end, const uint8_t value) {
	
	uint8_t clearMask = this->getClearMask(begin, end);
	uint8_t mask = this->getMask(begin, end, value);
	
	container[row] &= clearMask;
	container[row] |= mask;
}


BitContainer::BitContainer (int size, int maxValue) {
	this->size = size;
	this->maxValue = maxValue;
	
	this->bitsPerValue = ceil(log2(maxValue)) + ((1 << (int)log2(maxValue)) == maxValue) ;
	this->container.resize(ceil((double)(size * this->bitsPerValue) / (double)this->bitsPerInt), 0);
}

void BitContainer::setValue (const int id, int value) {
	assert(value <= maxValue);
	assert(id < size);
	
	printf("DEBUG: setValue(%d, %d)\n", id, value);
	
	int row = this->getRow(id);
	int begin = this->getBegin(id);
	int end = min(begin + this->bitsPerValue, this->bitsPerInt);
	int bitsWritten = 0;
	int offset;
	
	for (; bitsWritten < this->bitsPerValue; ) {
		offset = this->bitsPerValue - bitsWritten - end + begin;
		//printf("DEBUG: writing: row %d: [%d, %d], %d, diff = %d\n", row, begin, end, value >> offset, offset);
		this->setBits(row, begin, end, value >> offset);
		//printf("row = %s\n", bitset<8>(container[row]).to_string<char,char_traits<char>,allocator<char> >().c_str());
		
		bitsWritten += end - begin;
		value -= (value >> offset) << offset;	//we remove all the bits other than the last offset
		row += end >= this->bitsPerInt;
		begin = end % this->bitsPerInt;
		end = (begin + this->bitsPerValue - bitsWritten) % this->bitsPerInt;
	}
}

int BitContainer::getValue (const int id) const {
	assert(id < size);
	printf("DEBUG: getValue(%d)\n", id);
	
	int row = this->getRow(id);
	int begin = this->getBegin(id);
	int end = min(begin + this->bitsPerValue, this->bitsPerInt);
	int bitsRead = 0;
	int result = 0;
	int offset;
	
	for(; bitsRead < this->bitsPerValue;) {
		printf("DEBUG: reading row %d: [%d, %d], val = %d\n", row, begin, end, this->getBits(row, begin, end));
		result = (result << (end - begin)) + this->getBits(row, begin, end);
		
		bitsRead += end - begin;
		row += end >= this->bitsPerInt;
		begin = end % this->bitsPerInt;
		end = (begin + this->bitsPerValue - bitsRead) % this->bitsPerInt;
	}

	return result;
}

const string BitContainer::getHash() {
	string res = "";
	for (int i = 0; i < this->container.size() - 1; ++i)
		res += this->container[i] + ";";
	res.push_back(container.back());
	return res;
}
