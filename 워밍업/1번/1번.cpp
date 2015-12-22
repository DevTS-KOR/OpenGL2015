// 1��.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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
		cout << "============ù��° ���============" << endl;
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
		cout << "============�ι�° ���============" << endl;
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
		cout << "A, a : ����� ����" << endl;
		cout << "D, d : ����� ����" << endl;
		cout << "M, m : ����� ����" << endl;
		cout << "R, r : ��Ľ��� ��" << endl;
		cout << "H, h : 4x4 ��� ��ȯ" << endl;
		cout << "����� ����� �����ϼ���. : ";
		cin >> cInput;

		system("cls");
		if (cInput == 'A' || cInput == 'a')
		{
			cout << "=================�����=============" << endl;
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
			cout << "=================�����=============" << endl;
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
			cout << "=================�����=============" << endl;
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
			cout << "ù°����� ��Ľ� �� : " << det(iFirst, 3) << endl;
			cout << "��°����� ��Ľ� �� : " << det(iSecond, 3) << endl;

		}

		else if (cInput == 'H' || cInput == 'h')
		{
			cout << "=================�����=============" << endl;

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
	int i, j, k, y; //������ �����ϱ� ���� ���� ����
	int det_a = 0;        //��� �� ���� ����
	int temp[Max][Max];     //��Ľ� �� �ӽ� ���� �迭
	//�˰���
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
						//����Ľ��� ���ϱ� ���� �� ����� ���ҵ��� ���ġ�Ѵ�.
					}
				}
			}
			det_a = det_a + *(A[0] + i) * (pow(-1.0, i)) * det(temp, n - 1);
			//����Ľĵ��� ��ü ���� ���Ѵ�.
		}
		return det_a;
	}
	else
	{
		return *A[0];
	}
}