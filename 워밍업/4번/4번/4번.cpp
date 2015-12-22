#include <iostream>
#include <cmath>
using namespace std;

#define Count 2

typedef struct Info
{
	int iX;
	int iY;
	int iZ;
}Info;

void Sum(Info* One_Info, Info* Two_Info);
void Minus(Info* One_Info, Info* Two_Info);
void VectorInner(Info* One_Info, Info* Two_Info);
void VectorExternal(Info* One_Info, Info* Two_Info);
void VectorSize(Info* One_Info, Info* Two_Info);

int main(void)
{
	Info strNumber[2];
	char iInput;

	for (int i = 0; i < Count; ++i)
	{
		cout << i + 1 << "번째 3차원 벡터 입력 : ";
		cin >> strNumber[i].iX;
		cin >> strNumber[i].iY;
		cin >> strNumber[i].iZ;
	}

	while (true)
	{
		system("cls");
		for (int i = 0; i < Count; ++i)
		{
			cout << "입력한 " << i + 1 << "번째 값은 : ( " << strNumber[i].iX << ", "
				<< strNumber[i].iY << ", " << strNumber[i].iZ << " ) " << endl;
		}

		cout << " + : 두 벡터의 합 " << endl;
		cout << " - : 두 벡터의 차 " << endl;
		cout << " d : 두 벡터의 내적과 두 벡터의 사잇각 " << endl;
		cout << " c : 두 벡터의 외적 " << endl;
		cout << " l : 두 벡터의 각각의 크기 " << endl;
		cout << " q : 종료 " << endl;
		cout << "명령어를 입력하세요. ^_^v : ";
		cin >> iInput;

		if (iInput == '+')
		{
			Sum(&strNumber[0], &strNumber[1]);
			system("pause");
		}

		else if (iInput == '-')
		{
			Minus(&strNumber[0], &strNumber[1]);
			system("pause");
		}

		else if (iInput == 'd')
		{
			VectorInner(&strNumber[0], &strNumber[1]);
			system("pause");
		}

		else if (iInput == 'c')
		{
			VectorExternal(&strNumber[0], &strNumber[1]);
			system("pause");
		}

		else if (iInput == 'l')
		{
			VectorSize(&strNumber[0], &strNumber[1]);
			system("pause");
		}

		else if (iInput == 'q')
			break;
	}

	return 0;
}


void Sum(Info* One_Info, Info* Two_Info)
{
	Info iResult;

	iResult.iX = One_Info->iX + Two_Info->iX;
	iResult.iY = One_Info->iY + Two_Info->iY;
	iResult.iZ = One_Info->iZ + Two_Info->iZ;

	cout << " ( " << One_Info->iX << ", " << One_Info->iY << ", " << One_Info->iZ << " ) + ( "
		<< Two_Info->iX << ", " << Two_Info->iY << ", " << Two_Info->iZ << " ) = ( "
		<< iResult.iX << ", " << iResult.iY << ", " << iResult.iZ << " ) " << endl;

}

void Minus(Info* One_Info, Info* Two_Info)
{
	Info iResult;

	iResult.iX = One_Info->iX - Two_Info->iX;
	iResult.iY = One_Info->iY - Two_Info->iY;
	iResult.iZ = One_Info->iZ - Two_Info->iZ;

	cout << " ( " << One_Info->iX << ", " << One_Info->iY << ", " << One_Info->iZ << " ) - ( "
		<< Two_Info->iX << ", " << Two_Info->iY << ", " << Two_Info->iZ << " ) = ( "
		<< iResult.iX << ", " << iResult.iY << ", " << iResult.iZ << " ) " << endl;
}

void VectorInner(Info* One_Info, Info* Two_Info)
{
	float fFirst_Length, fSecond_Lenght;
	int fInner_Result;
	float fInclude_Angle;
	fInner_Result = (One_Info->iX * Two_Info->iX + One_Info->iY * Two_Info->iY + One_Info->iZ * Two_Info->iZ);
	fFirst_Length = (float)sqrt(One_Info->iX * One_Info->iX + One_Info->iY * One_Info->iY + One_Info->iZ * One_Info->iZ);
	fSecond_Lenght = (float)sqrt(Two_Info->iX * Two_Info->iX + Two_Info->iY * Two_Info->iY + Two_Info->iZ * Two_Info->iZ);
		
	/* 3.141592 * 180.0;*/

	/*if (fResult > 180.0) 
		fResult = (360 - fResult);*/

	fInclude_Angle = (fInner_Result / (fFirst_Length * fSecond_Lenght));
	
	cout << "두벡터의 내적은 " << fInner_Result << endl;
	cout << "두벡터의 사잇각은 " << fInclude_Angle << endl;
}

void VectorExternal(Info* One_Info, Info* Two_Info)
{
	Info iResult;

	iResult.iX = One_Info->iY * Two_Info->iZ - One_Info->iZ * Two_Info->iY;
	iResult.iY = One_Info->iZ * Two_Info->iX - One_Info->iX * Two_Info->iZ;
	iResult.iZ = One_Info->iX * Two_Info->iY - One_Info->iY * Two_Info->iX;

	cout << " ( " << One_Info->iX << ", " << One_Info->iY << ", " << One_Info->iZ << " ) X ( "
		<< Two_Info->iX << ", " << Two_Info->iY << ", " << Two_Info->iZ << " ) = ( "
		<< iResult.iX << ", " << iResult.iY << ", " << iResult.iZ << " ) " << endl;
}


void VectorSize(Info* One_Info, Info* Two_Info)
{
	float fFirst_Size;
	float fSecond_Size;

	fFirst_Size = (float)sqrt(One_Info->iX * One_Info->iX + One_Info->iY * One_Info->iY + One_Info->iZ * One_Info->iZ);
	fSecond_Size = (float)sqrt(Two_Info->iX * Two_Info->iX + Two_Info->iY * Two_Info->iY + Two_Info->iZ * Two_Info->iZ);

	cout << "첫번째 벡터 (" << One_Info->iX << ", " << One_Info->iY << ", " << One_Info->iZ << " )의 크기는 " << fFirst_Size << endl;
	cout << "두번째 벡터 (" << Two_Info->iX << ", " << Two_Info->iY << ", " << Two_Info->iZ << " )의 크기는 " << fSecond_Size << endl;
}