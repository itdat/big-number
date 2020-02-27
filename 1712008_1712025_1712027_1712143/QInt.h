#pragma once
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

#define MAX_INT_128 "170141183460469231731687303715884105727"
#define MIN_INT_128 "-170141183460469231731687303715884105728"

class CQInt
{
private:
	int qint[4] = { 0 };

public:
	/*
	Turn on/off bit at position i of sequence of 128 bits (0: turn off, otherwise: turn on)
	Input:
	bitIdx: index of bit in the sequence
	state: turn on or off
	*/
	void turnBit(int bitIdx, int state);

	/*
	Get bit at position i of a 128-bit sequence
	Input:
	bitIdx: index of bit in the sequence
	Output: the required bit
	*/
	int getBit(int bitIdx);


	/**/
	int getUsedBits();

	//Set all bits in QInt to zero
	void reset();

	/*
	Append a digit into the units of the QInt's value
	Input:
	decDigit: a digit appended
	*/
	void pushDecimal(int decDigit);

	//Perform two's complement convertion  
	void convertTwoComplement();

	/*
	Set a string of digits into QInt
	Input:
	decStr: a string of digits
	*/
	void setDecStr(string decStr);

	/*
	Set a string of bits into QInt
	Input:
	binStr: a bit string
	*/
	void setBinStr(string binStr);

	/*
	Set a string of hexes into QInt
	Input:
	hexStr: a string of hexes
	*/
	void setHexStr(string hexStr);

	/*
	Convert QInt into a decimal string
	Output:
	a string of ditgits
	*/
	string convertToDec();

	/*
	Convert QInt into a binary string
	Output:
	a string of bits
	*/
	string convertToBin();

	/*
	Convert QInt number to hexadecimal string
	Output:
	a string of hexes
	*/
	string convertToHex();


	/*
	Assign a QInt to another QInt
	Input:
	srcQInt: a QInt to assign from
	Output:
	former QInt with the bit sequence of srcQInt
	*/
	CQInt operator=(const CQInt & srcQInt);


	//ARITHMETIC OPERATOR

	/*
	Perform addition between two QInt(s)
	Input:
	aQInt to add
	Output:
	result from an addition between *this and aQInt
	*/
	CQInt operator+(CQInt aQInt);

	/*
	Perform substraction between two QInt(s)
	Input:
	aQInt to substract
	Output:
	result from an substract between *this and aQInt
	*/
	CQInt operator-(CQInt aQInt);

	/*
	Perform multiplication between two QInt(s)
	Input:
	aQInt to multiply
	Output:
	result from an multiply between *this and aQInt
	*/
	CQInt operator*(CQInt aQInt);

	/*
	Perform division between two QInt(s)
	Input:
	aQInt to divide
	Output:
	result from an division between *this and aQInt
	*/
	CQInt operator/(CQInt aQInt);


	//RELATIONAL OPERATOR

	/*
	Greater comparison between *this and another QInt aQInt
	Input:
	a number QInt type to compare with *this
	Output:
	true if *this is greater than B and false otherwise
	*/
	bool operator>(CQInt aQInt);

	/*
	Greater or equal comparison between *this and another QInt aQInt
	Input:
	a number in QInt type
	Output:
	true if *this >= aQInt and false otherwise
	*/
	bool operator>=(CQInt aQInt);

	/*
	Less than comparison
	Input:
	a number in QInt type
	Output:
	true if *this < aQInt and false otherwise
	*/
	bool operator<(CQInt aQInt);

	/*
	Les than or equal comparison
	Input:
	a number QInt type
	Output:
	true if *this <= aQInt and false otherwise
	*/
	bool operator<=(CQInt aQInt);

	/*
	Equal to comparison
	Input:
	a number in QInt type
	Output:
	true if *this == aQInt and false otherwise
	*/
	bool operator==(CQInt aQInt);

	/*
	Not equal comparison
	Input:
	a number in QInt type
	Output:
	true if *this != aQInt and false otherwise
	*/
	bool operator!=(CQInt aQInt);


	//BITWISE OPERATOR

	/*
	AND operator
	Input:
	a QInt type number to perform AND
	Output:
	CQInt type result
	*/
	CQInt operator&(CQInt aQInt);

	/*
	OR operator
	Input:
	a QInt type number to perform OR
	Output:
	CQInt type result
	*/
	CQInt operator|(CQInt aQInt);

	/*
	XOR operator
	Input:
	a QInt type number to perform XOR
	Output:
	CQInt type result
	*/
	CQInt operator^(CQInt aQInt);

	/*
	NOT operator
	Input:
	a QInt type number to perform NOT
	Output:
	CQInt type result
	*/
	CQInt operator~();

	/*
	Logical shift right
	Input:
	number: the number of bits to shift
	Output:
	right shifted QInt
	*/
	CQInt operator >> (int number);

	/*
	Shift left
	Input :
	number: the number of bits to shift
	Output :
	left shifted QInt
	*/
	CQInt operator << (int number);

	/*
	Right rotate
	Input:
	number: the number of bits to rotate
	Output:
	rotated QInt
	*/
	CQInt ror(int number);

	/*
	Left circular rotate
	Input:
	number: the number of bits to rotate
	Output:
	rotated QInt
	*/
	CQInt rol(int number);


	/*
	Get input into QInt
	Input:
	str: sequence of bits/digits/hexes
	base: base 2/10/16
	Output:

	*/
	void scanQInt(string str, int base);

	/*
	Print output to screen in base 2/10/16
	Input:
	base: base 2/10/16
	Output:
	output in the desired base
	*/
	void printQInt(int base);

	CQInt();

	~CQInt();
};

