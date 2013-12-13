#include <iostream>
using namespace std;

int main()
{
	const int SIZE = 6;
	unsigned long F[SIZE];
	F[0] = 0;
	F[1] = 1;
	F[2] = 1;

	for (int i = 3 ; i < SIZE; i++)
	{
		F[i] = F[i-1] + F[i-2];
	}

	for (int i = 0; i < SIZE; i++)
	{
		cout << "F[" << i << "] is " << F[i] << endl;
	}

	return 0;
}
