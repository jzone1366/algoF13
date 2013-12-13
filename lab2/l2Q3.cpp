#include <iostream>
#include <cmath>
using namespace std;

void Swapper(int& num1n int& num2)
{
	int temp = num1;
	num1 = num2;
	num2 = temp;
}
void SortItGood(int myArray[], int min, int max)
{
    int pivot = myArray[(min + max) / 2];

    int left = min, right = max;

    while (left < right) {
        while (myArray[left] < pivot) {
            left++;
        }
        while (myArray[right] > pivot) {
            right--;
        }

        if (left <= right) {
            Swapper(myArray[left], myArray[right]);
            left++;
            right--;
        }
    }

    if (min < right) {
        SortItGood(myArray, min, right);
    }
    if (left < max) {
        SortItGood(myArray, left, max);
    }
}
void Splitter()
{
	
}

int main()
{
	int numList[] = {20, 13, 42, 20, 593, 43, 33, 2, 100, 220};
	int min = 0;
    int max = sizeof(numList) / sizeof(int);
    int N = 4;
    int length = pow(2, (N-1));

    SortItGood(numList, min, max-1);
    FindingNemo(numList, length);
    return 0;
}