// 2번.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

void InputPlus(list<Pos> &_list_Pos);
void InputE(list<Pos> &_list_Pos);
void InputMinus(list<Pos> &_list_Pos);
void InputD(list<Pos> &_list_Pos);
void InputL(list<Pos> &_list_Pos);
void InputC(list<Pos> &_list_Pos);
void InputM(list<Pos> &_list_Pos);
void InputN(list<Pos> &_list_Pos);

int _tmain(int argc, _TCHAR* argv[])
{
	list<Pos>	list_Pos;
	Pos m_Pos;
	
	char cInput;

	while (true)
	{
		cout << "===========================================================" << endl;
		cout << "+ : 리스트의 맨 위에 입력" << endl;//
		cout << "- : 리스트의 맨 아래에서 출력" << endl;//
		cout << "e : 리스트의 맨 아래에 입력" << endl;//
		cout << "d : 리스트의 맨 위에서 출력" << endl;//
		cout << "l : 리스트의 길이를 출력" << endl;//
		cout << "c : 리스트를 비운다." << endl;//
		cout << "m : 원점에서 가장 먼 거리에 있는 점의 좌표값을 출력한다." << endl;
		cout << "n : 원점에서 가장 가까운 거리에 있는 점의 좌표값을 출력한다. " << endl;
		cout << "q : 프로그램을 종료한다." << endl;
		cout << "===========================================================" << endl;
		cout << "명령어를 입력하세요 : ";
		cin >> cInput;

		cout << endl;

		if (cInput == '+')
		{
			if (list_Pos.size() > 7)
			{
				cout << "================================" << endl;
				cout << "경고! 더이상 입력할 수 없습니다." << endl;
				cout << "================================" << endl;
				system("pause");
				system("cls");
				continue;
			}
			InputPlus(list_Pos);
			system("pause");
			system("cls");
			
		}

		else if (cInput == '-')
		{
			InputMinus(list_Pos);
			system("pause");
			system("cls");
		}

		else if (cInput == 'e')
		{
			if (list_Pos.size() > 7)
			{
				cout << "================================" << endl;
				cout << "경고! 더이상 입력할 수 없습니다." << endl;
				cout << "================================" << endl;
				system("pause");
				system("cls");
				continue;
			}

			InputE(list_Pos);
			system("pause");
			system("cls");
		}

		else if (cInput == 'd')
		{
			InputD(list_Pos);
			system("pause");
			system("cls");
		}

		else if (cInput == 'l')
		{
			InputL(list_Pos);
			system("pause");
			system("cls");
		}

		else if (cInput == 'c')
		{
			InputC(list_Pos);
			system("pause");
			system("cls");
		}

		else if (cInput == 'm')
		{
			InputM(list_Pos);
			system("pause");
			system("cls");
		}

		else if (cInput == 'n')
		{
			InputN(list_Pos);
			system("pause");
			system("cls");
		}

		else if (cInput == 'q')
			break;

		
	}
	return 0;
}


void InputPlus(list<Pos> &_list_Pos)
{
	int iInputX, iInputY, iInputZ;

	cout << "숫자를 입력하세요." << endl;
	cout << "X : ";
	cin >> iInputX;
	cout << "Y : ";
	cin >> iInputY;
	cout << "Z : ";
	cin >> iInputZ;

	_list_Pos.push_front(Pos(iInputX, iInputY, iInputZ));

	cout << "===========================================================" << endl;

	for (list<Pos>::iterator iter = _list_Pos.begin(); iter != _list_Pos.end(); ++iter)
		cout << (*iter).iX << " " << (*iter).iY << " " << (*iter).iZ << endl;

	cout << "===========================================================" << endl;
}

void InputMinus(list<Pos> &_list_Pos)
{

	for (list<Pos>::iterator iter = _list_Pos.begin(); iter != _list_Pos.end(); ++iter)
		cout << (*iter).iX << " " << (*iter).iY << " " << (*iter).iZ << endl << endl;

	list<Pos>::iterator iter = _list_Pos.begin();

	_list_Pos.erase(iter);
	iter = _list_Pos.begin();
	

	cout << "===========================================================" << endl;

	for (list<Pos>::iterator iter = _list_Pos.begin(); iter != _list_Pos.end(); ++iter)
		cout << (*iter).iX << " " << (*iter).iY << " " << (*iter).iZ << endl;

	cout << "===========================================================" << endl;
}

void InputE(list<Pos> &_list_Pos)
{
	int iInputX, iInputY, iInputZ;

	cout << "숫자를 입력하세요." << endl;
	cout << "X : ";
	cin >> iInputX;
	cout << "Y : ";
	cin >> iInputY;
	cout << "Z : ";
	cin >> iInputZ;

	_list_Pos.push_back(Pos(iInputX, iInputY, iInputZ));

	cout << "===========================================================" << endl;

	for (list<Pos>::iterator iter = _list_Pos.begin(); iter != _list_Pos.end(); ++iter)
		cout << (*iter).iX << " " << (*iter).iY << " " << (*iter).iZ << endl;

	cout << "===========================================================" << endl;
}

void InputD(list<Pos> &_list_Pos)
{


	for (list<Pos>::iterator iter = _list_Pos.begin(); iter != _list_Pos.end(); ++iter)
		cout << (*iter).iX << " " << (*iter).iY << " " << (*iter).iZ << endl << endl;

	_list_Pos.reverse();
	list<Pos>::iterator iter = _list_Pos.begin();

	_list_Pos.erase(iter);
	iter = _list_Pos.begin();



	_list_Pos.reverse();

	cout << "===========================================================" << endl;

	for (list<Pos>::iterator iter = _list_Pos.begin(); iter != _list_Pos.end(); ++iter)
		cout << (*iter).iX << " " << (*iter).iY << " " << (*iter).iZ << endl;

	cout << "===========================================================" << endl;
}

void InputL(list<Pos> &_list_Pos)
{
	cout << "===========================================================" << endl;
	cout << "리스트의 길이는 " << _list_Pos.size() << "입니다." << endl;
	cout << "===========================================================" << endl;
}

void InputC(list<Pos> &_list_Pos)
{
	_list_Pos.clear();
	cout << "===========================================================" << endl;
	cout << "리스트를 비웠습니다." << endl;
	cout << "리스트의 길이는 " << _list_Pos.size() << "입니다." << endl;
	cout << "===========================================================" << endl;
}

void InputM(list<Pos> &_list_Pos)
{
	int iInputX, iInputY, iInputZ;
	Pos	str_Pos[7];
	float iCount[7];
	int iNumber = 0;
	int iPlus = 0;
	int iTemp;
	iInputX = 0;
	iInputY = 0;
	iInputZ = 0;
	Pos str_Temp;

	for (list<Pos>::iterator iter = _list_Pos.begin(); iter != _list_Pos.end(); ++iter)
	{
		iCount[iNumber] = sqrt((((float)(*iter).iX - iInputX)*((float)(*iter).iX - iInputX) +
			((float)(*iter).iY - iInputY)*((float)(*iter).iY - iInputY) +
			((float)(*iter).iZ - iInputZ)*((float)(*iter).iZ - iInputZ)));
	
		str_Pos[iPlus] = { (*iter).iX, (*iter).iY, (*iter).iZ };

		iNumber++;
		iPlus++;
	}

	for (int i = 0; i < iNumber; ++i)
	{
		for (int j = 0; j < iNumber - 1; ++j)
		{
			if (iCount[j] < iCount[j + 1])
			{
				iTemp = iCount[j];
				iCount[j] = iCount[j + 1];
				iCount[j + 1] = iTemp;

				str_Temp = str_Pos[j];
				str_Pos[j] = str_Pos[j + 1];
				str_Pos[j + 1] = str_Temp;
			}
		}
	}

	cout << "===========================================================" << endl;
	cout << "원점과 가장 멀리있는 좌표는 " << str_Pos[0].iX << " " << str_Pos[0].iY << " " << str_Pos[0].iZ << " 입니다." << endl;
	cout << "===========================================================" << endl;
}

void InputN(list<Pos> &_list_Pos)
{
	int iInputX, iInputY, iInputZ;
	Pos	str_Pos[7];
	float iCount[7];
	int iNumber = 0;
	int iPlus = 0;
	float iTemp;
	Pos str_Temp;
	iInputX = 0;
	iInputY = 0;
	iInputZ = 0;

	for (list<Pos>::iterator iter = _list_Pos.begin(); iter != _list_Pos.end(); ++iter)
	{
		iCount[iNumber] = sqrt(((float)(*iter).iX - iInputX)*((float)(*iter).iX - iInputX) +
			((float)(*iter).iY - iInputY)*((float)(*iter).iY - iInputY) +
			((float)(*iter).iZ - iInputZ)*((float)(*iter).iZ - iInputZ));

		str_Pos[iPlus] = { (*iter).iX, (*iter).iY, (*iter).iZ };

		iNumber++;
		iPlus++;
	}

	for (int i = 0; i < iNumber; ++i)
	{
		for (int j = 0; j < iNumber - 1; ++j)
		{
			if (iCount[j] > iCount[j + 1])
			{
				iTemp = iCount[j];
				iCount[j] = iCount[j + 1];
				iCount[j + 1] = iTemp;

				str_Temp = str_Pos[j];
				str_Pos[j] = str_Pos[j + 1];
				str_Pos[j + 1] = str_Temp;
			}
		}
	}

	cout << "===========================================================" << endl;
	cout << "원점과 가장 가까운 좌표는 " << str_Pos[0].iX << " " 
		<< str_Pos[0].iY << " " << str_Pos[0].iZ << " 입니다." << endl;
	cout << "===========================================================" << endl;
}