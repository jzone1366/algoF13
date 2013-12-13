#include <iostream>
#include <cmath>
using namespace std;

bool primalChecker(unsigned int num)
g{
	if (num <= 1)
		return false;
	if (num == 2)
		return true;
	for (unsigned int i = 2; i <= sqrt(num); ++i)
		if (num % i == 0)
			return false;
	return true;
}

int primalLove(int pList[], int len)
{
	int counter = 0;
	int i;
	for(i = 3; i <= len; i++)
	{
		if(primalChecker(i))
		{
			counter++;
			pList[counter-1] = i;
		}
	}
	return counter;
}

int main()
{
	int N = 2000, count;
	int primes[N/2];
	count = primalLove(primes, N);
	for(int j = 0; j < count; j++)
	{
		cout << primes[j] << " ";
	}
	cout << endl << "Counter: " << count << endl;
	return 0;
}

//primalChecker == O(log n)
//primalLove    == O(n)
//total   == O(n log n)