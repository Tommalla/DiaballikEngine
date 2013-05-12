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
	uint8_t clearMask = UINT8_T_MAX - uint8_t(1 << (this->bitsPerInt - begin) - 1);
	clearMask += uint8_t(1 << (this->bitsPerInt - end) - 1);
	return clearMask;
}

int BitContainer::getBits (const int row, const int begin, const int end) const {
	uint8_t mask = ~this->getClearMask(begin, end);
// 	printf("\tgetBits(row = %d, begin = %d, end = %d)\n", row, begin, end);
// 	printf("mask = %s\n", bitset<64>(mask).to_string<char,char_traits<char>,allocator<char> >().c_str());
	mask &= container[row];
// 	printf("mask = %s\n", bitset<64>(mask).to_string<char,char_traits<char>,allocator<char> >().c_str());
// 	puts("Done(getBits)");
	return mask / uint8_t(2 << (this->bitsPerInt - end));
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
	
	this->bitsPerValue = ceil(log2(maxValue));
	this->container.resize(ceil((double)(size * this->bitsPerValue) / (double)this->bitsPerInt), 0);
}

void BitContainer::setValue (const int id, int value) {
	assert(value <= maxValue);
	assert(id < size);
	
	int row = this->getRow(id);
	int begin = this->getBegin(id);
	int end = min(begin + this->bitsPerValue, this->bitsPerInt);
	
	//TODO: While
	
// 	QDebug() << "setValue(" << id << ", " << value <<"):\n\trow = " << row << "; begin = " << begin << "; end = " << end <<
// 	 "; mask = " << mask << "; clearMask = " << clearMask << "\n";
	this->setBits(row, begin, end, value >> (this->bitsPerValue - end + begin));
	
	//printf("DBG %d\n", this->bitsPerValue - end + begin);
	
	if (end - begin == this->bitsPerValue)
		return;
	
	value -= value - value / pow(2, this->bitsPerValue - end + begin);
	row++;
	end = this->bitsPerValue - end + begin;
	begin = 0;
	
	this->setBits(row, begin, end, value);
}

int BitContainer::getValue (const int id) const {
	assert(id < size);
	
	int row = this->getRow(id);
	int begin = this->getBegin(id);
	int end = min(begin + this->bitsPerValue, this->bitsPerInt);
	
	//TODO: while
	
	int result = this->getBits(row, begin, end);
// 	printf("result = %s\n", bitset<64>(result).to_string<char,char_traits<char>,allocator<char> >().c_str());
	
	if (end - begin == this->bitsPerValue)
		return result;
	
	result <<= this->bitsPerValue - (end - begin);
// 	printf("result = %s\n", bitset<64>(result).to_string<char,char_traits<char>,allocator<char> >().c_str());
	row++;
	end = this->bitsPerValue - end + begin;
	begin = 0;
	
	return result + this->getBits(row, begin, end);
}

const string BitContainer::getHash() {
	string res = "";
	for (int i = 0; i < this->container.size() - 1; ++i)
		res += this->container[i] + ";";
	res.push_back(container.back());
	return res;
}
