#include <iostream>
#include <cmath>
using namespace std;

bool binarySearch(int array[], int Size, int value, int position)
{
    int low = 0, high = Size - 1, midpoint = 0;
    while (low <= high)
    {
        midpoint = low + (high - low)/2;
        if (value == array[midpoint])
        {
            position = midpoint;
            return true;
        }
        else if (value < array[midpoint])
            high = midpoint - 1;
        else
            low = midpoint + 1;
    }
        return false;
}
void FindingNemo(int arrList[], int len)
{
    for (int i=0; i<len || i < 0; i++)
    {
        if(!(binarySearch(arrList, len, arrList[i]+1, -1)))
        {
            cout << arrList[i] + 1;
        }
    }
}

void Swapper(int& num1, int& num2)
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


int main()
{
    int numList[] = {2,7,1,8,4,6};
    int min = 0;
    int max = sizeof(numList) / sizeof(int);
    int N = 4;
    int length = pow(2, (N-1));

    SortItGood(numList, min, max-1);
    FindingNemo(numList, length);
    return 0;
}

//Worst case (n log n)