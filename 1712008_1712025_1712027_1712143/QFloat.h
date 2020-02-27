#pragma once
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include<conio.h>
#include "Support.h"

using namespace std;

/* Minimum: +/- 1.[112 0s] x 2^(-16382)
Maximum: +/- 1.[112 1s] x 2^(+16383) */
class QFloat
{
private:
	short signExponent;				// sign: 1 bit, exponent: 15 bits
	short fraction[7] = { 0 }; 		// fraction: 112 bits							
									// 128 bits in total

public:
	/*
	Get bit at a specific position in signExponent
	Input:
	bitIndex: the bit position
	Output:
	the bit at the given position
	*/
	int getBitExponent(int bitIndex);

	/*
	Get bit at a specific position in fraction[7]
	Input:
	bitIdx: the bit position
	Output:
	the bit at the given position
	*/
	int getBitFraction(int bitIdx);


	/*
	Turn on/ off one bit in signExponent
	Input:
	bitIndex: the index of the bit
	state:
	0: turn off
	1: otherwise
	*/
	void turnExponentBit(int bitIndex, int state);

	/*
	Turn on/ off one bit in fraction[7]
	Input:
	bitIndex: the index of the bit
	state:
	0: turn off
	1: otherwise
	*/
	void turnFractionBit(int bitIndex, int state);

	/*
	Convert the exponent part of a floating point into base 10
	Output:
	The corresponding base-10 representation
	*/
	int convertExponentBinaryToDecimal();

	/*
	Convert a representation in base 2 into the corresponding base-10 string
	Input:
	input: sequence of bits
	Output:
	A string of digits
	*/
	string binToDec(string input);

	/*
	Take a string containing bits and put them into QFloat, respectively
	Input:
	input: a string of bits
	*/
	void readInputInBinaryFormIntoQFloat(string input);

	/*
	Take a string in base 10, convert it into base 2 and store those bits in QFloat
	Input:
	input: a string of digits
	*/
	void scanQFloat(string input);
	/*
	Print all the bits in both signExponent and fraction[7] to the screen
	*/
	void printQFloat();

	QFloat();
	~QFloat();
};