/* fib-v0.cpp */

#include <iostream>
using namespace std;

int compute_fib(const int n)
{
	if(n <= 0) return 0;
	if(n ==1) return 1;
	return compute_fib(n-1) + compute_fib(n-2);
}

int main()
{
	int n;
	cout << "Enter n: ";
	cin >> n;

	int Fn = compute_fib(n);
	cout << "F[" << n <<"] is " << Fn << endl;
}
