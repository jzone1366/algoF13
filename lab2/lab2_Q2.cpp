#include <iostream>
#include <cmath>
using namespace std;

int gcDizzle(int num1, int num2)
{
	if(num2 == 0)
		return num1;
	else
		return gcDizzle(num2, num1 % num2);
}

int lcMizzle(int n1, int n2)
{
	return abs((n1 * n2) / gcDizzle(n1, n2));
}

int main()
{
	int num1 = 240;
	int num2 = 100;
	int lcm;
	lcm = lcMizzle(num1, num2);
	cout << "LCM: " << lcm << endl;
}

// gcDizzle == O(n)
// lcMizzle == O(n)
// Total == O(n)