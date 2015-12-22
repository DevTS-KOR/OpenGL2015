#pragma once

typedef struct Info
{
	int iX;
	int iY;
	int iZ;

	Info(void)
	{
		iX = 0; iY = 0; iZ = 0;
	}

	Info(int _iX, int _iY, int _iZ)
		: iX(_iX), iY(_iY), iZ(_iZ)
	{

	}

	void GetInfo(void)
	{
		//cout << iX << "\t" << iY << "\t" << iZ << endl;
	}

}Pos;
