#include "QInt.h"
#include "Support.h"

void CQInt::turnBit(int bitIdx, int state)
{
	if (bitIdx <= 127)
	{
		div_t arrIdx = div(bitIdx, 32); // Tra ve arrIdx.quot la phan nguyen, arrIdx.rem la phan du
		int number = qint[arrIdx.quot];

		if (state != 0)
		{
			number = number | (1 << arrIdx.rem);	//turn bit on
		}
		else
		{
			number = number & (~(1 << arrIdx.rem));	//turn bit off
		}

		qint[arrIdx.quot] = number;
	}
}

int CQInt::getBit(int bitIdx)
{
	div_t arrIdx = div(bitIdx, 32);
	int shiftRight = qint[arrIdx.quot] >> arrIdx.rem;
	int andOne = shiftRight & 1;
	return andOne;
}

int CQInt::getUsedBits()
{
	int usedBits = 0;
	int i = 3;	//start from the last element of array qint[], run back to the first one
	while ((this->qint[i] == 0) && (i >= 0)) i--;	//ignore element equals 0 (32 bits is 0)
	if (i >= 0)	//stop at element unequals 0
	{
		int bitIdx = (i + 1) * 32 - 1;	//start from the last bit of element unequals 0, run back to the first one
		while ((this->getBit(bitIdx) == 0) && (bitIdx >= 0)) bitIdx--;	//ignore bit equals 0
		usedBits = bitIdx + 1;	//update used bits
	}
	else
	{
		usedBits = 0;
	}
	return usedBits;
}

void CQInt::reset()
{
	for (int i = 0; i < 4; i++)
	{
		this->qint[i] = 0;
	}
}

void CQInt::pushDecimal(int decDigit)
{
	//Varible val10 = 10
	CQInt val10;
	val10.qint[0] = 10;

	//Varible digit = decDigit
	CQInt digit;
	digit.qint[0] = decDigit;

	*this = (*this)*val10 + digit;
}

void CQInt::convertTwoComplement()
{
	*this = ~(*this);

	CQInt temp;
	temp.qint[0] = 1;

	*this = (*this) + temp;
}

void CQInt::setDecStr(string decStr)
{
	this->reset();	//reset to 0

	int start = 0;
	if (decStr[0] == '-')
	{
		start = 1;
	}

	for (int i = start; i < decStr.length(); i++)
	{
		this->pushDecimal(decStr[i] - 48);
	}

	if (decStr[0] == '-')
	{
		this->convertTwoComplement();
	}
}

void CQInt::setBinStr(string binStr)
{
	reverseStr(binStr);

	for (int i = 0; i < binStr.length(); i++)
	{
		turnBit(i, binStr[i] - 48);
	}
}

void CQInt::setHexStr(string hexStr)
{
	reverseStr(hexStr);

	for (int i = 0; i < hexStr.length(); i++)
	{
		CQInt temp;
		temp.qint[0] = (hexStr[i] >= '0' && hexStr[i] <= '9') ? hexStr[i] - 48 : hexStr[i] - 55;

		for (int j = 0; j < 4; j++)
		{
			turnBit(i * 4 + j, temp.getBit(j));
		}
	}
}

string CQInt::convertToDec()
{
	string str;

	//Init P = 1 (in calculated format string)
	string P;
	P.resize(50);
	fillZero(P);
	P[0] = P[1] = 1;

	//Init S = 0 (in calculated format string)
	string S;
	fillZero(S);
	S.resize(50);
	S[0] = 1;

	if (this->getBit(127) == 1)	//is positive number
	{
		str.push_back('-');

		CQInt temp = *this;
		temp.convertTwoComplement();

		if (temp == *this)	//minimum value
		{
			string minimumVal = MIN_INT_128;
			return minimumVal;
		}

		str += temp.convertToDec();
		return str;
	}
	else
	{
		//If 0th bit is zero then init S = 1 (in calculated format string)
		if (this->getBit(0) == 1)
		{
			S[1] = 1;
		}

		//two = 2 (in calculated format string)
		string two;
		fillZero(two);
		two.resize(50);
		two[0] = 1;
		two[1] = 2;

		for (int i = 1; i < this->getUsedBits(); i++)
		{
			//Calculate 2^i
			P = multiply2Dec(P, two);

			//If bit i equals 1 then add 2^i to S
			if (this->getBit(i) == 1)
			{
				S = add2Dec(S, P);
			}
		}

		//Convert 'calculated format string' to string for displaying
		for (int i = S[0]; i >= 1; i--)
		{
			str.push_back(S[i] + 48);
		}
		return str;
	}
}

string CQInt::convertToBin()
{
	string str;
	for (int i = this->getUsedBits() - 1; i >= 0; i--)
	{
		str.push_back(this->getBit(i) + 48);
	}
	if (str.length() == 0)
		str.push_back('0');
	return str;
}

string CQInt::convertToHex()
{
	string str;
	CQInt temp;
	int lastBit = this->getUsedBits();
	while (lastBit < 128 && lastBit % 4 != 0) lastBit++;

	for (int i = 0; i < lastBit; i++)
	{
		temp.turnBit(i % 4, this->getBit(i));
		if ((i + 1) % 4 == 0)
		{
			string temp2 = temp.convertToDec();
			if (temp2.length() == 2)
			{
				str.push_back(temp2[1] + 17);
			}
			else
				str.push_back(temp2[0]);
		}
	}
	reverseStr(str);
	if (str.length() == 0)
		str.push_back('0');
	return str;
}

CQInt CQInt::operator=(const CQInt & srcQInt)
{
	for (int i = 0; i < 4; i++)
	{
		this->qint[i] = srcQInt.qint[i];
	}
	return *this;
}

CQInt CQInt::operator+(CQInt B)
{
	CQInt A = *this;
	CQInt res;

	int remain = 0;
	int max = A.getUsedBits() > B.getUsedBits() ? A.getUsedBits() : B.getUsedBits();
	for (int i = 0; i < max; i++)
	{
		remain = remain + A.getBit(i) + B.getBit(i);
		res.turnBit(i, remain % 2);
		remain /= 2;
	}
	if (remain != 0)
	{
		res.turnBit(max, 1);
		remain = 0;
	}
	return res;
}

CQInt CQInt::operator-(CQInt aQInt)
{
	aQInt.convertTwoComplement();
	CQInt res = *this + aQInt;
	return res;
}

CQInt CQInt::operator*(CQInt aQInt)
{
	CQInt A = *this;
	CQInt res;

	for (int i = 0; i < A.getUsedBits(); i++)
	{
		int bitA = A.getBit(i);
		int remain = 0;

		for (int j = 0; j < aQInt.getUsedBits(); j++)
		{
			int bitB = aQInt.getBit(j);

			remain = bitA * bitB + remain + res.getBit(i + j);
			res.turnBit(i + j, remain % 2);
			remain /= 2;
		}

		int j = aQInt.getUsedBits() + i - 1;

		while (remain != 0)
		{
			j++;
			remain += res.getBit(j);
			res.turnBit(j, remain % 2);
			remain /= 2;
		}
	}
	return res;
}

CQInt CQInt::operator/(CQInt aQInt)
{
	CQInt A = *this;
	CQInt res;
	string str;
	CQInt zero;

	bool isNegative = false;
	if (A < zero)
	{
		isNegative = !isNegative;
		A.convertTwoComplement();
	}
	if (aQInt < zero)
	{
		isNegative = !isNegative;
		aQInt.convertTwoComplement();
	}

	CQInt temp;
	int pos = A.getUsedBits() - aQInt.getUsedBits();

	while (pos >= 0)
	{
		temp = aQInt << pos;
		if (A >= temp)
		{
			str.push_back('1');
			A = A - temp;
		}
		else
		{
			str.push_back('0');
		}
		pos--;
	}
	res.setBinStr(str);
	if (isNegative)
		res.convertTwoComplement();
	return res;
}

bool CQInt::operator>(CQInt aQInt)
{
	CQInt A = *this;
	if ((A.getBit(127) == 0) && (aQInt.getBit(127) == 1))
	{
		return true;
	}
	else
		if ((A.getBit(127) == 1) && (aQInt.getBit(127) == 0))
		{
			return false;
		}
		else
			if ((A.getBit(127) == 0) && (aQInt.getBit(127) == 0))
			{
				if (A.getUsedBits() != aQInt.getUsedBits())
				{
					return (A.getUsedBits() > aQInt.getUsedBits());
				}
				else
				{
					int i = A.getUsedBits() - 1;
					while ((i >= 0) && (A.getBit(i) == aQInt.getBit(i))) i--;
					return (A.getBit(i) > aQInt.getBit(i));
				}
			}
			else
			{
				A.convertTwoComplement();
				aQInt.convertTwoComplement();
				return aQInt > A;
			}
}

bool CQInt::operator>=(CQInt aQInt)
{
	return (*this > aQInt) || (*this == aQInt);
}

bool CQInt::operator<(CQInt aQInt)
{
	return !(*this >= aQInt);
}

bool CQInt::operator<=(CQInt aQInt)
{
	return !(*this > aQInt);
}

bool CQInt::operator==(CQInt aQInt)
{
	for (int i = 0; i < 128; i++)
	{
		if (this->getBit(i) != aQInt.getBit(i))
		{
			return false;
		}
	}
	return true;
}

bool CQInt::operator!=(CQInt aQInt)
{
	return !(*this == aQInt);
}

CQInt CQInt::operator&(CQInt aQInt)
{
	CQInt A = *this;
	CQInt res;

	for (int i = 0; i < 128; i++)
	{
		res.turnBit(i, A.getBit(i) && aQInt.getBit(i));
	}
	return res;
}

CQInt CQInt::operator|(CQInt aQInt)
{
	CQInt A = *this;
	CQInt res;

	for (int i = 0; i < 128; i++)
	{
		res.turnBit(i, A.getBit(i) || aQInt.getBit(i));
	}
	return res;
}

CQInt CQInt::operator^(CQInt aQInt)
{
	CQInt A = *this;
	CQInt res;

	for (int i = 0; i < 128; i++)
	{
		res.turnBit(i, A.getBit(i) - aQInt.getBit(i));
	}
	return res;
}

CQInt CQInt::operator~()
{
	CQInt A = *this;
	CQInt res;

	for (int i = 0; i < 128; i++)
	{
		res.turnBit(i, A.getBit(i) - 1);
	}
	return res;
}

CQInt CQInt::operator >> (int number)
{
	CQInt res;
	if (number >= 128)
	{
		return res;
	}
	else
	{
		for (int i = 0; i <= 127; i++)
		{
			if (i + number <= 127)
			{
				res.turnBit(i, this->getBit(i + number));
			}
			else
			{
				res.turnBit(i, 0);
			}
		}
	}
	return res;
}

CQInt CQInt::operator << (int number)
{
	CQInt res;
	if (number >= 128)
	{
		return res;
	}
	else
	{
		for (int i = 127; i >= 0; i--)
		{
			if (i - number >= 0)
			{
				res.turnBit(i, this->getBit(i - number));
			}
			else
			{
				res.turnBit(i, 0);
			}
		}
	}
	return res;
}

CQInt CQInt::rol(int number)
{
	return ((*this << number) | (*this >> (128 - number)));
}

CQInt CQInt::ror(int number)
{
	return this->rol(128 - number);
}

void CQInt::scanQInt(string str, int base)
{
	switch (base)
	{
	case 2:
		this->setBinStr(str);
		break;
	case 10:
		this->setDecStr(str);
		break;
	case 16:
		this->setHexStr(str);
		break;
	default:
		break;
	}
}

void CQInt::printQInt(int base)
{
	switch (base)
	{
	case 2:
		cout << this->convertToBin() << endl;
		break;
	case 10:
		cout << this->convertToDec() << endl;
		break;
	case 16:
		cout << this->convertToHex() << endl;
		break;
	default:
		break;
	}
}

CQInt::CQInt()
{
}

CQInt::~CQInt()
{
}
