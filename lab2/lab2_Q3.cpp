#include <iostream>
#include <cmath>
using namespace std;

void Swapper(int& num1, int& num2)
{
	int temp = num1;
	num1 = num2;
	num2 = temp;
}

void Splitter(int* array, const int arr_size)
{
int temp = 0;   //Temporary integer to store (if necessary) the current element
int end = 0;    //Run time condition

while(end++ != arr_size){ // Will loop max. 10 times
	for(int i = 0; i < arr_size; i++)
	{
    if(array[i] > array[i + 1])
    {    //If the current element 
      temp = array[i];    //is bigger than the next
      array[i] = array[i + 1];//Change the positions
      array[i + 1] = temp;    
     }
  }
}
int main()
{
	int numArr[] = {13, 42, 593, 20, 20, 43, 33, 2, 100, 220};
	int len = sizeof(numArr) / sizeof(int);
	int v = 20;
	Splitter(numArr, len, v);
	for(int i = 0; i < len; i++)
	{
		cout << numArr[i] << " ";
	}
	cout << endl;
	return 0;
}