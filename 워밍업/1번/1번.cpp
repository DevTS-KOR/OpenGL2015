// 1번.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	int iFirst[3][3];
	int iSecond[3][3];
	int iResult[4][4];
	int iResult2[4][4];
	int iDivision;
	char cPlus;
	char cMinus;
	char cMulti;
	char cInput;
	int det(int(*A)[Max], int n);
	srand((unsigned)time(NULL));

	for (int i = 0; i < Weight; ++i)
	{
		for (int j = 0; j < Height; ++j)
		{
			iFirst[i][j] = rand() % 3 ;
			iSecond[i][j] = rand() % 3 ;
		}
	}

	while (true)
	{
		cout << "============첫번째 행렬============" << endl;
		for (int i = 0; i < Weight; ++i)
		{
			for (int j = 0; j < Height; ++j)
			{
				if (j % Height == 0)
					cout << endl;

				cout << iFirst[i][j] << "\t";
				
			}
		}

		cout << endl;
		cout << "============두번째 행렬============" << endl;
		for (int i = 0; i < Weight; ++i)
		{
			for (int j = 0; j < Height; ++j)
			{
				if (j % Height == 0)
					cout << endl;
				cout << iSecond[i][j] << "\t";
				
			}
		}

		cout << endl << endl;
		cout << "A, a : 행렬의 덧셈" << endl;
		cout << "D, d : 행렬의 뺄셈" << endl;
		cout << "M, m : 행렬의 곱셈" << endl;
		cout << "R, r : 행렬식의 값" << endl;
		cout << "H, h : 4x4 행렬 변환" << endl;
		cout << "사용할 명령을 선택하세요. : ";
		cin >> cInput;

		system("cls");
		if (cInput == 'A' || cInput == 'a')
		{
			cout << "=================결과값=============" << endl;
			for (int i = 0; i < Weight; ++i)
			{
				for (int j = 0; j < Height; ++j)
				{
					if (j % Height == 0)
						cout << endl;
					iResult[i][j] = iFirst[i][j] + iSecond[i][j];
					cout << iResult[i][j] << "\t";
					
				}
			}
			cout << "\n===================================" << endl;
			cout << endl;
		}

		else if (cInput == 'D' || cInput == 'd')
		{
			cout << "=================결과값=============" << endl;
			for (int i = 0; i < Weight; ++i)
			{
				for (int j = 0; j < Height; ++j)
				{
					if (j % Height == 0)
						cout << endl;
					iResult[i][j] = iFirst[i][j] - iSecond[i][j];
					cout << iResult[i][j] << "\t";
					
				}
			}
			cout << "\n===================================" << endl;
			cout << endl;
		}

		else if (cInput == 'M' || cInput == 'm')
		{
			cout << "=================결과값=============" << endl;
			for (int j = 0; j < Weight; ++j)
			{
				for (int i= 0; i < Height; ++i)
				{
					iResult[i][j] = 0;
					for (int k = 0; k < Weight; ++k)
					{
						iResult[i][j] += (iFirst[i][j] * iSecond[k][j]);
					}

				}
			}

			for (int i = 0; i < Weight; ++i)
			{
				for (int j = 0; j < Height; ++j)
				{
					if (j % Height == 0)
						cout << endl;
					cout << iResult[i][j] << "\t";
					
				}
			}

			cout << "\n===================================" << endl;
			cout << endl;
		}

		else if (cInput == 'R' || cInput == 'r')
		{
			cout << "첫째행렬의 행렬식 값 : " << det(iFirst, 3) << endl;
			cout << "둘째행렬의 행렬식 값 : " << det(iSecond, 3) << endl;

		}

		else if (cInput == 'H' || cInput == 'h')
		{
			cout << "=================결과값=============" << endl;

			/*for (int i = 0; i < Weight ; ++i)
			{
				for (int j = 0; j < Height; ++j)
				{
					iResult[i][j] = iFirst[i][j];
					iResult2[i][j] = iSecond[i][j];
				}
			}*/

			for (int i = 0; i < (Weight + 1); ++i)
			{
				for (int j = 0; j < (Height + 1); ++j)
				{
					iResult[i][j] = iFirst[i][j];
					iResult2[i][j] = iSecond[i][j];

					if (i == 3 || j == 3)
					{
						iResult[i][j] = 0;
						iResult2[i][j] = 0;
					}

					if (i == 3 && j == 3)
					{
						iResult[i][j] = 1;
						iResult2[i][j] = 1;
					}

				}
			}


			for (int i = 0; i < Weight + 1; ++i)
			{
				for (int j = 0; j < Height + 1; ++j)
				{

					if (j % (Height + 1) == 0)
						cout << endl;
					cout << iResult[i][j] << "\t";

				}
			}

			cout << "\n\n===================================" << endl;

			for (int i = 0; i < Weight + 1; ++i)
			{
				for (int j = 0; j < Height + 1; ++j)
				{

					if (j % (Height + 1) == 0)
						cout << endl;
					cout << iResult2[i][j] << "\t";

				}
			}


			cout << "\n===================================" << endl;
			cout << endl;
		}

	}

	return 0;
}


int det(int(*A)[Max], int n)
{
	int i, j, k, y; //루프를 수행하기 위한 변수 선언
	int det_a = 0;        //결과 값 저장 변수
	int temp[Max][Max];     //행렬식 값 임시 저장 배열
	//알고리즘
	if (n != 1)
	{
		for (i = 0; i < n; i++)
		{
			for (j = 1; j < n; j++)
			{
				y = 0;
				for (k = 0; k < n; k++)
				{
					if (k != i)
					{
						temp[j - 1][y++] = *(A[0] + j*Max + k);
						//소행렬식을 구하기 위해 각 행렬의 원소들을 재배치한다.
					}
				}
			}
			det_a = det_a + *(A[0] + i) * (pow(-1.0, i)) * det(temp, n - 1);
			//소행렬식들의 전체 합을 구한다.
		}
		return det_a;
	}
	else
	{
		return *A[0];
	}
}