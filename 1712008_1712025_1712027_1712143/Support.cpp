#include "Support.h"
//QInt
void executeQInt(char *inputFile, char *outputFile)
{
	string line;
	ifstream inpFile(inputFile);
	if (inpFile.is_open())
	{
		freopen(outputFile, "wt", stdout);
		while (getline(inpFile, line))
		{
			uppercaseStr(line);
			vector<string> listParameters;
			string parameter;
			istringstream iss(line);	//use sstream library
			while (iss >> parameter)
			{
				listParameters.push_back(parameter);
			}

			CQInt temp;
			//Case line has 3 parameters
			if (listParameters.size() == 3)
			{
				//Operator not
				if (listParameters[1] == "~")
				{
					CQInt A;
					A.scanQInt(listParameters[2], stoi(listParameters[0]));
					CQInt res = ~A;
					res.printQInt(stoi(listParameters[0]));
				}
				else
				{
					//Convert
					temp.scanQInt(listParameters[2], stoi(listParameters[0]));
					temp.printQInt(stoi(listParameters[1]));
				}
			}

			//Case line has 4 parameters
			if (listParameters.size() == 4)
			{
				if (listParameters[2] == ">>" || listParameters[2] == "<<" || listParameters[2] == "ROR" || listParameters[2] == "ROL")
				{
					CQInt A, res;
					A.scanQInt(listParameters[1], stoi(listParameters[0]));
					int B = stoi(listParameters[3]);

					if (listParameters[2] == ">>")
					{
						res = A >> B;
					}
					else if (listParameters[2] == "<<")
					{
						res = A << B;
					}
					else if (listParameters[2] == "ROR")
					{
						res = A.ror(B);
					}
					else
					{
						res = A.rol(B);
					}
					res.printQInt(stoi(listParameters[0]));
				}
				else
				{
					CQInt A, B, res;
					A.scanQInt(listParameters[1], stoi(listParameters[0]));
					B.scanQInt(listParameters[3], stoi(listParameters[0]));

					if (listParameters[2] == ">" || listParameters[2] == "<" || listParameters[2] == "==" || listParameters[2] == "!=" || listParameters[2] == ">=" || listParameters[2] == "<=")
					{
						int boo;
						if (listParameters[2] == ">")
						{
							boo = A > B;
						}
						if (listParameters[2] == "<")
						{
							boo = A < B;
						}
						if (listParameters[2] == "==")
						{
							boo = A == B;
						}
						if (listParameters[2] == "!=")
						{
							boo = A != B;
						}
						if (listParameters[2] == ">=")
						{
							boo = A >= B;
						}
						if (listParameters[2] == "<=")
						{
							boo = A <= B;
						}
						if (boo == 1)
						{
							cout << "true\n";
						}
						else
						{
							cout << "false\n";
						}

					}
					else
					{
						if (listParameters[2] == "+")
						{
							res = A + B;
						}
						if (listParameters[2] == "-")
						{
							res = A - B;
						}
						if (listParameters[2] == "*")
						{
							res = A * B;
						}
						if (listParameters[2] == "/")
						{
							res = A / B;
						}
						if (listParameters[2] == "&")
						{
							res = A&B;
						}
						if (listParameters[2] == "|")
						{
							res = A | B;
						}
						if (listParameters[2] == "^")
						{
							res = A^B;
						}
						res.printQInt(stoi(listParameters[0]));
					}
				}
			}
		}
		inpFile.close();
	}
}

void fillZero(string &str)
{
	for (int i = 0; i < str.length(); i++)
	{
		str[i] = 0;
	}
}

string add2Dec(string &A, string &B)
{
	string res;
	res.resize(50);
	fillZero(res);

	int remain = 0;

	res[0] = A[0] > B[0] ? A[0] : B[0];

	for (int i = 1; i <= res[0]; i++)
	{
		remain = remain + A[i] + B[i];
		res[i] = remain % 10;
		remain /= 10;
	}

	if (remain != 0)
	{
		res[0]++;
		res[res[0]] = remain;
	}
	return res;
}

string multiply2Dec(string &A, string &B)
{
	string res;
	res.resize(50);
	fillZero(res);

	for (int i = 1; i <= A[0]; i++)
	{
		int remain = 0;
		for (int j = 1; j <= B[0]; j++)
		{
			remain = A[i] * B[j] + remain + res[i + j - 1];
			res[i + j - 1] = remain % 10;
			remain /= 10;
		}

		int j = i + B[0] - 1;

		while (remain != 0)
		{
			j++;
			remain = remain + res[j];
			res[j] = remain % 10;
			remain /= 10;
		}
	}
	res[0] = A[0] + B[0] + 2;
	while ((res[res[0]] == 0) && (res[0] > 1)) res[0]--;
	return res;
}

void reverseStr(string &str)
{
	for (int i = 0; i < str.length() / 2; i++)
	{
		char temp = str[i];
		str[i] = str[str.length() - 1 - i];
		str[str.length() - 1 - i] = temp;
	}
}

void uppercaseStr(string &str)
{
	for (int i = 0; i < str.length(); i++)
	{
		str[i] = toupper(str[i]);
	}
}

//QFloat
void executeQFloat(char *inputFile, char *outputFile)
{
	string line;
	ifstream inpFile(inputFile);
	if (inpFile.is_open())
	{
		freopen(outputFile, "wt", stdout);
		while (getline(inpFile, line))
		{
			vector<string> listParameters;
			string parameter;
			istringstream iss(line);	//use sstream library
			while (iss >> parameter)
			{
				listParameters.push_back(parameter);
			}

			CQInt temp;
			//Case line has 2 parameters
			if (listParameters.size() == 2)
			{
				if (listParameters[0] == "2")
				{
					QFloat flpoint;
					cout << flpoint.binToDec(listParameters[1]) << endl;
				}
				else
				{
					cout << decToBin(listParameters[1]) << endl;
				}
			}

		}
		inpFile.close();
	}
}

string divBigDecimalByTwo(string bigDecimal)
{
	string result = "";
	string temp = "";
	string quot = bigDecimal;

	int i = 0;
	int recNum = 0;

	div_t res;

	char t;
	char rem;

	if ((quot[i] - '0') < 2)
	{
		if ((i + 1) != quot.size())
		{
			recNum = (quot[i] - '0') * 10 + (quot[i + 1] - '0');

			res = div(recNum, 2);

			t = res.quot + '0';
			temp += t;

			t = res.rem + '0';
			rem = t;

			result = result + temp;

			i = i + 2;
		}
		else
		{
			result = "0";
			return result;
		}
	}
	else
	{
		recNum = (quot[i] - '0');

		res = div(recNum, 2);

		t = res.quot + '0';
		temp += t;

		t = res.rem + '0';
		rem = t;

		result = result + temp;

		i = i + 1;
	}

	temp = "";

	while (i < quot.size())
	{
		recNum = (rem - '0') * 10 + (quot[i] - '0');

		if ((recNum < 2))
		{
			temp = '0';

			t = recNum + '0';
			rem = t;

			result = result + temp;

			i++;
		}
		else
		{
			res = div(recNum, 2);

			t = res.quot + '0';
			temp = t;

			t = res.rem + '0';
			rem = t;

			result = result + temp;

			i = i + 1;
		}
	}

	return result;
}

string addBigDecimal(string aBigDecimal, string otherBigDecimal)
{
	int i = 0;
	int remainder = 0;
	int temp = 0;

	// Check if the big decimals hace different size
	int difBetweenTwoSizes;
	if (aBigDecimal.size() < otherBigDecimal.size())
	{
		difBetweenTwoSizes = otherBigDecimal.size() - aBigDecimal.size();
		while (difBetweenTwoSizes)
		{
			aBigDecimal = '0' + aBigDecimal;
			difBetweenTwoSizes--;
		}
	}
	else
	{
		difBetweenTwoSizes = aBigDecimal.size() - otherBigDecimal.size();
		while (difBetweenTwoSizes)
		{
			otherBigDecimal = '0' + otherBigDecimal;
			difBetweenTwoSizes--;
		}
	}
	//cout << aBigDecimal << " " << otherBigDecimal << endl;
	char c;
	string result = "";

	for (i = aBigDecimal.size() - 1; i >= 0; i--)
	{
		temp = (aBigDecimal[i] - '0') + (otherBigDecimal[i] - '0');

		if (temp >= 10)
		{
			if (remainder)
			{
				c = ((temp - 10 + 1) + '0');
				result = c + result;

				if (i == 0)
				{
					result = "1" + result;
					remainder = 0;
					remainder = 0;
				}
				else {
					remainder = 1;
				}
			}
			else
			{
				c = ((temp - 10) + '0');
				result = c + result;

				if (i == 0)
				{
					result = "1" + result;
					remainder = 0;
					return result;
				}
				else {
					remainder = 1;
				}
			}
		}
		else
		{
			temp = (remainder == 1) ? temp + 1 : temp;

			if (temp >= 10)
			{
				c = ((temp - 10) + '0');
				result = c + result;
				remainder = 1;
			}
			else
			{
				c = (temp + '0');
				result = c + result;
				remainder = 0;
			}
		}
	}

	return result;
}

string multiplyBigDecimalByTwo(string bigDecimal)
{
	int i = 0;
	int remainder = 0;
	int temp = 0;

	char c;
	string result = "";

	for (i = bigDecimal.size() - 1; i >= 0; i--)
	{
		temp = (bigDecimal[i] - '0') * 2;

		if (temp >= 10)
		{
			if (remainder)
			{
				c = ((temp - 10 + 1) + '0');
				result = c + result;

				if (i == 0)
				{
					result = "1" + result;
					remainder = 0;
					remainder = 0;
				}
				else {
					remainder = 1;
				}
			}
			else
			{
				c = ((temp - 10) + '0');
				result = c + result;

				if (i == 0)
				{
					result = "1" + result;
					remainder = 0;
					return result;
				}
				else {
					remainder = 1;
				}
			}
		}
		else
		{
			temp = (remainder == 1) ? temp + 1 : temp;

			if (temp >= 10)
			{
				c = ((temp - 10) + '0');
				result = c + result;
				remainder = 1;
			}
			else
			{
				c = (temp + '0');
				result = c + result;
				remainder = 0;
			}
		}
	}

	return result;
}

string convertBitSequenceInWholeNumberIntoDecimal(string bitSeqInWholeNumber)
{
	string result = "0";

	int j = 0;

	int maxExponentOfTwo = bitSeqInWholeNumber.size() - 1;

	string resultOfMul;
	for (; j < bitSeqInWholeNumber.size(); j++)
	{
		if (bitSeqInWholeNumber[j] == '1')
		{
			resultOfMul = "1";
			for (int i = 0; i < (maxExponentOfTwo - j); i++) {
				resultOfMul = multiplyBigDecimalByTwo(resultOfMul);
				//cout << "resultOfMul: " << resultOfMul << endl;
			}

			result = addBigDecimal(result, resultOfMul);
			//cout << "result: " << result << endl;
		}
	}

	return result;
}

string convertBitSequenceInFractionIntoDecimal(string bitSeqInFraction)
{
	int numBits = bitSeqInFraction.size();
	int i;

	// Create a 10^numBits, string type
	string powTen = "1";
	while (powTen.size() <= numBits) {
		powTen.push_back('0');
	}

	// Initialize result
	string result;
	while (result.size() < numBits) {
		result.push_back('0');
	}

	int j;
	string resultOfDiv;
	for (i = 0; i < bitSeqInFraction.size(); i++)
	{
		if (bitSeqInFraction[i] == '1')
		{
			//cout << "i: " << i << endl;
			resultOfDiv = powTen;
			for (j = 0; j <= i; ++j) {
				resultOfDiv = divBigDecimalByTwo(resultOfDiv);
			}
			//cout << "resultOfDiv: " << resultOfDiv << endl;
			result = addBigDecimal(resultOfDiv, result);
			//cout << "result: " << result << endl;
		}
	}

	return result;
}

bool Find(string s)
{
	int i = 0;
	while (i < s.length() && s[i] != '.')
	{
		i++;
	}
	if (i == s.length())
		return false;
	return true;
}

string convertFractionPartFromDecimalToBinary(string fraction, int usedBits)
{
	string result = "";
	int remainder = 0;
	int end = 0, start = fraction.size() - 1;
	int i, temp;
	int numBitsCoveredBySignificand = usedBits - 1;	// Number of bits taken by the significant part
	int maxBits;
	int isGreaterThanOne = 0;

	maxBits = (numBitsCoveredBySignificand < 0) ? 112 :
		maxBits = 112 - numBitsCoveredBySignificand;
	//cout << "maxBits: "<< maxBits << endl;

	while (maxBits > 0)
	{
		// Multiply by 2
		for (i = start; i >= end; i--)
		{
			//cout << "i: "<<i<<" ";
			temp = (fraction[i] - '0') * 2;

			if (temp >= 10)
			{
				if (remainder)
				{
					fraction[i] = (temp - 10 + 1) + '0';

					if (i == 0)
					{
						remainder = 0;
						isGreaterThanOne = 1;
					}
					else {
						remainder = 1;
					}
				}
				else
				{
					fraction[i] = (temp - 10) + '0';

					if (i == end)
					{
						remainder = 0;
						isGreaterThanOne = 1;
					}
					else {
						remainder = 1;
					}
				}
			}
			else
			{
				temp = (remainder == 1) ? temp + 1 : temp;

				if (temp >= 10)
				{
					fraction[i] = (temp - 10) + '0';
					remainder = 1;
				}
				else
				{
					fraction[i] = temp + '0';
					remainder = 0;
				}
			}
		}
		//cout << fraction << " isGreaterThanOne: "<< isGreaterThanOne<<endl;
		// If result is greater than 1
		if (isGreaterThanOne) {
			result = result + '1';
		}
		else {
			result = result + '0';
		}

		// If result is equal to 1
		int j;
		int numZeros = 0;
		for (j = 0; j < fraction.size(); j++)
		{
			if (fraction[j] == '0') {
				numZeros++;
			}
		}
		if ((numZeros == fraction.size()) && (isGreaterThanOne == 1))
		{
			while (result.size() < maxBits)
			{
				result.push_back('0');
				i--;
			}

			return result;
		}

		isGreaterThanOne = 0;

		maxBits--;
	}

	return result;
}

string convertWholeNumberPartFromDecimalToBinary(string wholeNumber)
{
	string result = "";

	int i;
	int recNum = 0; // temporary number to perform division
	div_t res;
	char t;

	char rem;
	string quot = wholeNumber;
	string temp = "";

	// Check for zero
	int numOlds = 0;
	for (i = 0; i <= wholeNumber.size() - 1; i++)
	{
		if (wholeNumber[i] == '0') {
			numOlds++;
		}
	}
	if (numOlds == wholeNumber.size())
	{
		result = "0";
		return result;
	}

	int count = 0;
	while (quot != "0")
	{
		i = 0;

		if ((quot[i] - '0') < 2)
		{

			if ((i + 1) != quot.size())
			{
				recNum = (quot[i] - '0') * 10 + (quot[i + 1] - '0');
				//cout << recNum<<endl;
				res = div(recNum, 2);

				t = res.quot + '0';
				temp += t;

				t = res.rem + '0';
				rem = t;

				i = i + 2;

				//cout << "temp: "<<temp<<" rem: "<<rem<<endl;
			}
			else
			{
				result = '1' + result;
				return result;
			}
		}
		else
		{
			recNum = (quot[i] - '0');

			res = div(recNum, 2);

			t = res.quot + '0';
			temp += t;

			t = res.rem + '0';
			rem = t;

			i = i + 1;
			//cout << "temp: "<<temp<<" rem: "<<rem<<endl;
		}

		while (i < quot.size())
		{
			//cout << "Here.\n";
			//cout<<"quot[i]: "<<quot[i]<<endl;
			recNum = (rem - '0') * 10 + (quot[i] - '0');
			//cout << "recNum: "<<recNum<<endl;
			if ((recNum < 2))
			{
				temp += '0';

				t = recNum + '0';
				rem = t;
				i++;
				//cout << "temp: "<<temp<<" rem: "<<rem<<endl;
			}
			else
			{
				res = div(recNum, 2);

				t = res.quot + '0';
				temp += t;

				t = res.rem + '0';
				rem = t;

				i = i + 1;
				//cout << "temp: "<<temp<<" rem: "<<rem<<endl;
			}
		}

		// Update result
		result = rem + result;
		//cout << "result: "<<result<<endl;
		quot = temp;
		//cout <<"quot: "<<quot<<endl;
		temp = "";
	}

	return result;
}

string convertExponentFromDecimalToBinary(int usedBitsFromWholeNumber)
{
	int decimalNumber = (usedBitsFromWholeNumber > 0) ?
		usedBitsFromWholeNumber - 1 + 16383 :
		usedBitsFromWholeNumber + 16383;
	//cout << "decimalNumber: " << decimalNumber << endl;
	string resultBinary = "000000000000000";
	int index = 14;
	int remainder;

	if (decimalNumber >= 0)
	{
		while (decimalNumber != 0)
		{
			remainder = decimalNumber % 2;

			resultBinary[index] = (remainder == 0) ? '0' : '1';
			index--;

			decimalNumber /= 2;
		}
	}

	return resultBinary;
}

bool isZero(string input)
{
	int numOlds = 0;
	for (int i = 0; i <= input.size() - 1; i++) {
		numOlds = (input[i] == '0') ? numOlds + 1 : numOlds;
	}
	return numOlds == input.size() - 1 ? true : false;
}

string decToBin(string input)
{
	/*
	Some special floating points:
	0: 			E = 0; F = 0
	0.F*2E: 	E = 0; F = binary representation of the fraction
	Infinity & NaN only occurs in arithmetic
	*/
	string result = "";
	string temp = "";

	int i;
	int usedBits = 0;

	// Check for zero

	if (isZero(input)) // Is zero
	{
		// result is all 0s
		for (i = 0; i <= 127; i++) {
			result = result + '0';
		}
		return result;
	}

	// Check the sign
	if (input[0] == '-')
	{
		result += '1';
		i = 1;
	}
	else
	{
		result += '0';
		i = 0;
	}

	// Convert input into base 2 \\

	// The whole-number part
	string wholeNumber = "";

	for (; input[i] != '.'; i++)
	{
		wholeNumber += input[i];
		if (i >= input.size()) {
			break;
		}
	}
	//cout << "wholeNumber before converting: " << wholeNumber << endl;

	wholeNumber = convertWholeNumberPartFromDecimalToBinary(wholeNumber);
	usedBits = wholeNumber.size();
	//cout << "usedBits: "<< usedBits <<endl; 
	//cout << "wholeNumber: " << wholeNumber << " " << wholeNumber.size() << endl;

	// The fraction part
	string fraction = "";
	i = i + 1;
	for (; i < input.size(); i++) {
		fraction += input[i];
	}
	//cout << "fraction size: "<< fraction.size() << endl;
	fraction = convertFractionPartFromDecimalToBinary(fraction, usedBits);
	//cout << "fraction: " << fraction << " " << fraction.size() << endl;

	// The exponent part
	string exponent;
	int e;
	if (wholeNumber == "0")
	{
		e = -1; i = 0;
		while (fraction[i] == '0')
		{
			e = e - 1;
			i++;
		}
		//cout << "e: " << e << endl;
		exponent = convertExponentFromDecimalToBinary(e);
	}
	else {
		exponent = convertExponentFromDecimalToBinary(usedBits);
	}
	//cout << "usedBits: " << usedBits << " exponent: " << exponent << endl;

	// Combine wholeNumber, fraction and exponent for the final result \\


	if (wholeNumber != "0")		//  If the whole number is not zero
	{
		i = 1;
		usedBits = usedBits - 1;
		// Find bits behind 1. (Ex: 1.11 -> 2 bits behind!)
		if (usedBits <= 112)
		{
			while (usedBits)
			{
				temp.push_back(wholeNumber[i]);
				usedBits--;

				i++;
			}
			//cout << "temp: " << temp << endl;
			result = result + exponent + temp + fraction;
			while (result.size() != 128) {
				result.push_back('0');
			}
		}
		else
		{
			int count = 0;
			while (count <= 111)
			{
				temp.push_back(wholeNumber[i]);
				i++;
				count++;
			}

			result = result + exponent + temp + fraction;
		}
	}
	else
	{
		i = -e;
		for (; i < fraction.size(); i++) {
			temp.push_back(fraction[i]);
		}

		result = result + exponent + temp;
		//cout << "result before printing: " << result << endl;
		while (result.size() != 128) {
			result.push_back('0');
		}
		//cout << "result: " << result << endl;
	}
	//cout << "temp: "<<temp<<endl;

	return result;
}

string returnSmallestNormalInDecimal()
{
	string result = "11897314953572317650857593266280070162";
	int i = 0;

	for (; i <= 1000; i++) {
		result = result + '0';
	}

	//result = '.' + result;
	//result = '0' + result;

	return result;
}