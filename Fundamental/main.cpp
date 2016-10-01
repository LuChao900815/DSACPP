#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
using namespace std;
#include "Max2.h"



void printArray(int* A,int n)
{
	for(int i = 0; i < n; ++i)
	{
		cout << A[i] << endl;
	}
}

int main(int argc,char** argv)
{
	srand((unsigned int)time(NULL));
	
	const int SIZE = 10;

	int A[SIZE] = {0};

	for(int i = 0; i < SIZE; ++i)
	{
		A[i] = rand();
	}

	printArray(A,SIZE);

	int x1 = 0, x2 = 0;

	//循环版
	max2(A,0,SIZE,x1,x2);

	cout << "x1 = " << x1 << ", x2 = " << x2 << endl;

	//改进版
	max2I(A,0,SIZE,x1,x2);

	cout << "x1 = " << x1 << ", x2 = " << x2 << endl;

	//递归版
	max2R(A,0,SIZE,x1,x2);

	cout << "x1 = " << x1 << ", x2 = " << x2 << endl;
	return 0;
}