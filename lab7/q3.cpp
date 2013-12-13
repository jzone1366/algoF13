#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

void changeItUp(int n, vector<int> & coins)
{
	int i, j, iter = 0;
	vector<int> used;
	vector<int>::iterator itr = coins.begin();
	if(n == 0)
	{
		printf("There are: %d coins", n);
		cout << endl;
	}
	else if(n == 1)
	{
		printf("There is: %d coin", n);
		cout << endl;
	}
	else
	{
		while(itr != coins.end())
		{
			while(*itr <= n)
			{
				used.push_back(*itr);
				iter++;
				n = n - *itr;
			}
			itr++;
		}

		printf("Takes a minimum of %d coins!\n", iter);
		for(j = 0; j < iter; j++)
		{
			cout << used.at(j) << " ";
		}
		cout << endl;
	}
}

int main()
{
	int n, c[] = {25, 10, 5, 1};
	vector<int> cList (c, c + sizeof(c)/sizeof(int) );
	cout << "Enter coin amount: ";
	cin >> n;
	changeItUp(n, cList);
}