/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#ifndef BITCONTAINER_H
#define BITCONTAINER_H
#include <vector>
#include <string>
#include <cstdint>

using namespace std;

/**
 * @brief Klasa służaca jako skompresowany kontener na inty
 **/
class BitContainer {
	private:
		
		uint8_t getMask(const int begin, const int end, const uint8_t value) const;
		/**
		 * @brief Returns a mask with zeros on positions from begin to end
		 **/
		uint8_t getClearMask(const int begin, const int end) const;
		
		void setBits(const int row, const int begin, const int end, const uint8_t value);
		int getBits(const int row, const int begin, const int end) const;
	protected:
		const int bitsPerInt = 8;
		int bitsPerValue, maxValue, size;
		vector<uint8_t> container;
		
		virtual int getBegin(const int id) const;
		virtual int getRow(const int id) const;
	public:
		/**
		 * @brief Konstruktor
		 *
		 * @param size rozmiar pożądanej tablicy
		 * @param maxValue maksymalna wartość do przechowywania
		 **/
		BitContainer(int size, int maxValue);
		
		void setValue(const int id, const int value);
		int getValue(const int id) const;
		
		void setBitsPerValue (const int bpv);
		vector< uint8_t > getData() const;
		
		const string getHash() const;
		BitContainer& operator=(const BitContainer& b);
};

#endif // BITCONTAINER_H
