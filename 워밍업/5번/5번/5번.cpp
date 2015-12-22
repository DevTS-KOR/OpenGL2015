#include <iostream>
using namespace std;

#define Count 4

typedef struct Info
{
	int iX;
	int iY;
	int iZ;
}Info;

void ThreeDimensionPlane(Info* One_Info, Info* Two_Info, Info* Three_Info);
void Vertex_to_Vertex_distance(Info* One_Info, Info* Two_Info);

int main(void)
{
	Info strNumber[4];

	cout << "3차원의 꼭짓점 4개를 입력하세요." << endl;

	for (int i = 0; i < Count; ++i)
	{
		cout << i + 1 << "번째 : ";
		cin >> strNumber[i].iX;
		cin >> strNumber[i].iY;
		cin >> strNumber[i].iZ;
	}
	cout << endl;


	cout << "입력한 4개의 꼭짓점의 좌표값은 " << endl;

	for (int i = 0; i < Count; ++i)
	{
		cout << i + 1 << "번째 : " << "( " << strNumber[i].iX << ", " << strNumber[i].iY << ", " << strNumber[i].iZ << " )" << endl;
	}
	cout << endl;

	cout << "평면의 방정식의 값은 : ";
	ThreeDimensionPlane(&strNumber[0], &strNumber[1], &strNumber[2]);
	cout << endl;

	cout << "선의 좌표와 길이는 : " << endl;
	Vertex_to_Vertex_distance(&strNumber[0], &strNumber[1]);
	Vertex_to_Vertex_distance(&strNumber[1], &strNumber[2]);
	Vertex_to_Vertex_distance(&strNumber[2], &strNumber[3]);
	Vertex_to_Vertex_distance(&strNumber[3], &strNumber[0]);

	return 0;
}

void ThreeDimensionPlane(Info* One_Info, Info* Two_Info, Info* Three_Info)
{
	int iResult[4];

	iResult[0] = One_Info->iY*(Two_Info->iZ - Three_Info->iZ) + Two_Info->iY *(Three_Info->iZ - One_Info->iZ)
		+ Three_Info->iY * (One_Info->iZ - Two_Info->iZ);

	iResult[1] = One_Info->iZ * (Two_Info->iX - Three_Info->iX) + Two_Info->iZ * (Three_Info->iX - One_Info->iX)
		+ Three_Info->iZ * (One_Info->iX - Two_Info->iX);

	iResult[2] = One_Info->iX * (Two_Info->iY - Three_Info->iY) + Two_Info->iX * (Two_Info->iY - One_Info->iY)
		+ Three_Info->iX * (One_Info->iY - Two_Info->iY);

	iResult[3] = -(One_Info->iX * (Two_Info->iY * Three_Info->iZ - Three_Info->iY * Two_Info->iZ) + Two_Info->iX 
		* (Three_Info->iY * One_Info->iZ - One_Info->iY * Three_Info->iZ) + Three_Info->iX *
		(One_Info->iY * Two_Info->iZ - Two_Info->iY * One_Info->iZ));

	cout << "A = " << iResult[0] << ", B = " << iResult[1] << ", C = " << iResult[2] << ", D = " << iResult[3] << endl;
}

void Vertex_to_Vertex_distance(Info* One_Info, Info* Two_Info)
{
	int iResult;

	iResult = sqrt(((Two_Info->iX - One_Info->iX) * (Two_Info->iX - One_Info->iX)
		+ (Two_Info->iZ - One_Info->iY) * (Two_Info->iY - One_Info->iY)
		+ (Two_Info->iZ - One_Info->iZ) * (Two_Info->iZ - One_Info->iZ)));

	cout << "( " << One_Info->iX << ", " << One_Info->iY << ", " << One_Info->iZ << " ) - ( "
		<< Two_Info->iX << ", " << Two_Info->iY << ", " << Two_Info->iZ << " ) : " << iResult << endl;
}