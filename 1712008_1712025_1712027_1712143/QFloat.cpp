#include "QFloat.h"

int QFloat::getBitExponent(int bitIndex) {
	return (signExponent >> bitIndex) & 1;
}

int QFloat::getBitFraction(int bitIdx)
{
	div_t arrIdx = div(bitIdx, 16);

	int shiftRight = fraction[arrIdx.quot] >> arrIdx.rem;
	int andOne = shiftRight & 1;

	return andOne;
}

void QFloat::turnExponentBit(int bitIndex, int state)
{
	int number = signExponent;

	number = (state == 1) ? (number | (1 << bitIndex)) :
		(number & (~(1 << bitIndex)));
	signExponent = number;
}

void QFloat::turnFractionBit(int bitIndex, int state)
{
	div_t arrIndex = div(bitIndex, 16);
	int number = fraction[arrIndex.quot];

	if (state) {
		number = number | (1 << arrIndex.rem);
	}
	else {
		number = number & (~(1 << arrIndex.rem));
	}

	fraction[arrIndex.quot] = number;
}

int QFloat::convertExponentBinaryToDecimal()
{
	int bit;
	int result = 0;
	int i;

	for (i = 1; i <= 15; i++)
	{
		bit = getBitExponent(i);
		result = result + bit * pow(2.0, 15 - i);
	}

	return result;
}

void QFloat::readInputInBinaryFormIntoQFloat(string input)
{
	int i = 0;
	int j = 0;

	if (input[i] == '1') {
		turnExponentBit(i, 1);
	}
	else {
		turnExponentBit(i, 0);
	}

	for (i = 1; i <= 15; i++)
	{
		if (input[i] == '1') {
			turnExponentBit(i, 1);
		}
		else {
			turnExponentBit(i, 0);
		}
	}

	for (j = 0; j <= 111; j++, i++)
	{
		if (input[i] == '1') {
			turnFractionBit(j, 1);
		}
		else {
			turnFractionBit(j, 0);
		}
	}
}

string QFloat::binToDec(string input)
{
	readInputInBinaryFormIntoQFloat(input);

	string result = "";

	int bitIndex = 0;
	char tempChar;
	string tempNum;
	int bit;
	int i = 0;

	// Extract exponent from exponent part of QFloat
	int decimalFormOfExponent = convertExponentBinaryToDecimal();
	//cout << "binaryFormOfExponent: " << decimalFormOfExponent << endl;
	int exponent = decimalFormOfExponent - 16383;
	//cout << "exponent: " << exponent << endl;

	string fraction;
	char t;
	if (exponent < 0)
	{
		exponent = -exponent;
		// The fraction part
		fraction = "1";
		for (i = 1; i < exponent; i++) {
			fraction = '0' + fraction;
		}
		//cout << "fraction: " << fraction << endl;
		// Get all bits in fraction[7]
		for (i = 0; i <= 111; i++)
		{
			bit = getBitFraction(i);
			t = bit + '0';
			fraction = fraction + t;
		}
		//cout << "fraction: " << fraction << endl; 
		fraction = convertBitSequenceInFractionIntoDecimal(fraction);
		//cout << "fraction: " << fraction << endl;

		fraction = '.' + fraction;
		result = '0' + fraction;

		return result;
	}
	else
	{
		string wholeNumber = "1";

		i = 0;
		for (; i < exponent; i++)
		{
			bit = getBitFraction(i);
			t = bit + '0';
			wholeNumber += t;
		}
		//cout << "wholeNumber: " << wholeNumber << endl;
		wholeNumber = convertBitSequenceInWholeNumberIntoDecimal(wholeNumber);
		//cout << "wholeNumber: " <<wholeNumber << endl;

		for (; i <= 111; i++)
		{
			bit = getBitFraction(i);
			t = bit + '0';
			fraction += t;
		}
		//cout << "fraction: " << fraction << endl;
		fraction = convertBitSequenceInFractionIntoDecimal(fraction);
		//cout << "fraction: " << endl;
		if (fraction.length() == 0) {
			result = result + wholeNumber;
		}
		else {
			result = result + wholeNumber + '.' + fraction;
		}
	}

	// Sign
	return (input[0] == '1') ? '-' + result : result;
}

void QFloat::scanQFloat(string input)
{
	string bitSequence = decToBin(input);

	readInputInBinaryFormIntoQFloat(bitSequence);
}

void QFloat::printQFloat()
{
	int i;
	int bit;

	cout << getBitExponent(0) << " ";

	for (i = 1; i <= 15; i++)
	{
		bit = getBitExponent(i);
		cout << bit;
	}
	cout << " ";

	for (i = 0; i <= 111; i++)
	{
		bit = getBitFraction(i);
		cout << bit;
	}

	cout << endl;
}

QFloat::QFloat()
{
}

QFloat::~QFloat()
{
}