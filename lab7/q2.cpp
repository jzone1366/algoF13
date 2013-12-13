#include <iostream>
#include <stdio.h>
using namespace std;

void sqrt(int x, int decP)
{
	double y, z(1.0);

	while(int(y)-int(z))
	{
		y=z;
		z=double(x)/2/y+y/2;
	}
	printf("sqrt: %.*f", decP, y);
	cout << endl;
}
//sqrt(n)
int main()
{
	sqrt(9999999, 10);
}