#include <iostream>

void QuickSort(int array[], int start, int end);
int PartitionArray(int array[], int start, int end);
int main()
{
	using namespace std;

	int array[100];

	for (int i =0; i< 100; i++)
		array[i] = rand() %100; // picks a range between 0 and 99 inclusive

	QuickSort(array, 0, 99);

	for (int i=0;i<100;i++)
		cout<<array[i]<< " ";

	return 0;
}

void QuickSort(int array[], int start, int end)
{
	if (start < end) // This condition will stop recursion
	{
		int iPivotIndex = PartitionArray(array, start, end);

		QuickSort(array, start, iPivotIndex-1);
		QuickSort(array, iPivotIndex+1, end);
	}
}

void Swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

int PartitionArray(int array[], int start, int end)
{
	using namespace std;

	int RandomIndex = (rand() % (end-start)) + start; // picks a range between start and end inclusive
	int iPivotIndex = start;

	Swap(array[RandomIndex], array[end]);

	for(int i = start; i<end;i++)
	{
		if(array[i]<=array[end]) //compare the current element with pivot element and if it is smaller, swap it with what is present on the pivot index and increment the pivot index
		{
			Swap(array[i], array[iPivotIndex]);
			iPivotIndex++;
		}
	}

	Swap(array[iPivotIndex], array[end]); // place the pivot element at it rightful position

	return iPivotIndex;
}
