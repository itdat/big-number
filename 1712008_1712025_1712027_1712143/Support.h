#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "QInt.h"
#include "QFloat.h"

using namespace std;

//QINT

/*
Read input from input file, execute each line, then print the output
into outpt file
Input:
*inputFile: input file name
*outputFile: output file name
*/
void executeQInt(char *inputFile, char *outputFile);

/*
Perform addition between two strings of digits
Input:
A: array of one-byte integers
B: (the same)
Format of A, B:
A[0]: the number of digits in A
A[1..n]: 0 -> 9
Output:
an array of one-byte integers with the same format as A/B
*/
string add2Dec(string &A, string &B);

/*
Perform multiplication between two strings of digits
Input:
A: array of one-byte integers
B: (the same)
Format of A, B:
A[0]: the number of digits in A
A[1..n]: 0 -> 9
Output:
an array of one-byte integers with the same format as A/B
*/

/*
Fill a given string to {0}
Input:
str: a string to fill
Output:
A filled string

*/
void fillZero(string &str);
string multiply2Dec(string &A, string &B);

/*
Reverse a given string
Input:
str: a string to reverse
Output:
A reversed string
*/
void reverseStr(string &str);

/*
Convert lowercase characters in a given string into uppercase ones
Input:
str: a given string
Output
A string with uppercase characters
*/
void uppercaseStr(string &str);


//QFLOAT

//Read input from file and executeQInt
void executeQFloat(char *inputFile, char *outputFile);


/*
Convert a sequence of bits into the relevant sequence of digits of the whole number
Input:
bitSeqInWholeNumber: a sequence of bits of the whole number part
Output:
The corresponding representation in base 10
*/
string convertBitSequenceInWholeNumberIntoDecimal(string bitSeqInWholeNumber);

/*
Convert a sequence of bits behind the '.' into a corresponding digit sequence
Input:
bitSeqInFraction: bit sequence behind the '.'
Output:
A corresponding sequence of digits
*/
string convertBitSequenceInFractionIntoDecimal(string bitSeqInFraction);

/*
Perform div between a string of digits and "2"
Input:
bigDecimal: digit string
Output:
A whole number of bigDecimal div 2
*/
string divBigDecimalByTwo(string bigDecimal);

/*
Perform addition between two strings of digits
Input:
aBigDecimal: a string of digits
otherBigDecimal: another string of digits
Output:
A result after adding two input
*/
string addBigDecimal(string aBigDecimal, string otherBigDecimal);

/*
Perform multiplication between a digit string and "2"
Input:
bigDecimal: a string of digits
Output:
A result after multiplying the input with "2"
*/
string multiplyBigDecimalByTwo(string bigDecimal);

bool isZero(string input);

/*
Convert input in base 10 into base 2
Input:
input: a string of digits
Output:
A string of corresponding bits
*/
string decToBin(string input);

string returnSmallestNormalInDecimal();

void executeQFloat(char *inputFile, char *outputFile);