#include <iostream>
#include <stdio.h>
using namespace std;

int changeItUp(int n, int coins[], int len, int cNum)
{
	int i, j, iter = 0;
	if(n == 0)
	{
		return 0;
	}
	else if(n == 1)
	{
		return 1;
	}
	else
	{
		for(i = cNum; i < len;)
		{
			while(coins[i] <= n)
			{
				iter++;
				n = n - coins[i];
			}
			i++;
		}
		return iter;
	}
}
void optimalCoins(int n, int coins[], int len)
{
	int lowest = 655, run = 0, i;
	for(i = 0; i < len; i++)
	{
		run = changeItUp(n, coins, len, i);
		if (run == 1)
			lowest = run;
		if (run < lowest)
			lowest = run;
	}
	printf("Takes a min of %d coins", lowest);
	cout << endl;

}

int main()
{
	int n, cList[] = {25, 10, 1};
	int length = sizeof(cList)/sizeof(int);
	cout << "Enter coin amount: ";
	cin >> n;
	optimalCoins(n, cList, length);
}