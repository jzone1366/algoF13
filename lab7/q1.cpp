#include <iostream>
using namespace std;

void sqrt1(int x)
{
	double y, z(1.0);
	unsigned int iter = 0;
	while(int(y)-int(z))
	{
		y=z;
		z=double(x)/2/y+y/2;
		iter++;
	}
	cout << "sqrt1: " << int(y) << endl;
	cout << "iter1: " << iter << endl;
}
//sqrt(n) time

void sqrt2(int x)
{
	int first = 0, last = x, mid, iter = 1;
	if(x==0)
	{
		cout << 0;
		cout << "No iterations" << endl;
	}
	if(x==1)
	{
		cout << 1 << endl;
		cout << "No iterations" << endl;
	}
	while(first+1 < last)
	{
		mid = (last+first)/2;
		if(mid == x/mid)
		{
			cout << mid;
			cout << iter;
		}
		if(mid < x/mid)
		{
			first = mid;
		}
		else
		{
			last = mid;
		}
		iter++;
	}
	cout << "sqrt2: " << first << endl;
	cout << "iter2: " << iter << endl;
}
//sqrt(n)
int main()
{
	sqrt1(999999999);
	sqrt2(999999999);

	return 0;
}