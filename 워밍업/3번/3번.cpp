// 3��.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	int iInput = 0;
	char cInput;
	int iTemp;
	list<int>*		iNumber = new list<int>();
	srand(unsigned(time(NULL)));

	cout << "����Ʈ�� ������ �Է��ϼ���. : ";
	cin >> iInput;

	for (int i = 0; i < iInput; ++i)
	{
		iNumber->push_back(rand() % iInput + 1);
	}

	cout << "�Էµ� ����Ʈ�� ��" << endl;
	for (list<int>::iterator iter = iNumber->begin(); iter != iNumber->end(); ++iter)
	{
		cout << (*iter) << " ";
	}
	cout << endl << endl;

	while (true)
	{
		cout << "M / m : �ִ밪/�ּҰ��� ã�´�." << endl;
		cout << "A / a : ������������ �����Ѵ�." << endl;
		cout << "D / d : ������������ �����Ѵ�." << endl;
		cout << "��ɾ �Է��ϼ��� : ";
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

