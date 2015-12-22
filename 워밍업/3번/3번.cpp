// 3번.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	int iInput = 0;
	char cInput;
	int iTemp;
	list<int>*		iNumber = new list<int>();
	srand(unsigned(time(NULL)));

	cout << "리스트의 개수를 입력하세요. : ";
	cin >> iInput;

	for (int i = 0; i < iInput; ++i)
	{
		iNumber->push_back(rand() % iInput + 1);
	}

	cout << "입력된 리스트의 값" << endl;
	for (list<int>::iterator iter = iNumber->begin(); iter != iNumber->end(); ++iter)
	{
		cout << (*iter) << " ";
	}
	cout << endl << endl;

	while (true)
	{
		cout << "M / m : 최대값/최소값을 찾는다." << endl;
		cout << "A / a : 오름차순으로 정렬한다." << endl;
		cout << "D / d : 내림차순으로 정렬한다." << endl;
		cout << "명령어를 입력하세요 : ";
		cin >> cInput;

		if (cInput == 'M')
		{
			list<int>::iterator iter = max_element(iNumber->begin(), iNumber->end());
			cout << *iter << endl;
		}
		else if (cInput == 'm')
		{
			list<int>::iterator iter = min_element(iNumber->begin(), iNumber->end());
			cout << *iter << endl;
		}
		else if (cInput == 'D' || cInput == 'd')
		{
			iNumber->sort(greater<int>());

			for (list<int>::iterator iter = iNumber->begin(); iter != iNumber->end(); ++iter)
			{
				cout << (*iter) << " ";
			}
			cout << endl << endl;
		}
		
		else if (cInput == 'A' || cInput == 'a')
		{
			iNumber->sort();

			for (list<int>::iterator iter = iNumber->begin(); iter != iNumber->end(); ++iter)
			{
				cout << (*iter) << " ";
			}
			cout << endl << endl;
		}
	}
	return 0;
}

