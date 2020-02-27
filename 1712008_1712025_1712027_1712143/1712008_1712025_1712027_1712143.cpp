// 1712008_1712025_1712027_1712143.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Support.h"
int main(int argc, char* argv[])
{
	if (argc == 4)
	{
		if (strcmp(argv[3], "0") == 0)
		{
			executeQInt(argv[1], argv[2]);
		}
		else
		{
			executeQFloat(argv[1], argv[2]);
		}
	}
	else
	{
		cout << "BigNumberOOP <input file name> <output file name> <O: QInt; otherwise: QFloat>" << endl;
	}

	//executeQInt("input.txt", "output.txt");
	//executeQFloat("inputQFloat.txt", "outputQFloat.txt");

	return 0;
}

