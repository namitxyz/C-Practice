#include <iostream>

void MergeSort(int array[],int length);

int main()
{
	using namespace std;

	const int SIZE = 101;

	int array[SIZE];

	for (int i =0; i< SIZE; i++)
		array[i] = rand() % SIZE; // picks a range between 0 and 100 inclusive

	MergeSort(array, SIZE);

	for (int i=0;i<SIZE;i++)
		cout<<array[i]<< " ";

	return 0;
}

void MergeSort(int array[], const int length)
{
	using namespace std;

	if(length < 2)
		return;

	const int MidLength = length / 2;
	const int SecondHalfLength = length - MidLength;

	int LeftArray[MidLength];
	int RightArray[SecondHalfLength];

	for(int i = 0; i < MidLength; i++)
		LeftArray[i] = array[i];
	
	for(int i = 0, j = MidLength; j < length; j++, i++)
		RightArray[i] = array[j];

	MergeSort(LeftArray, MidLength);
	MergeSort(RightArray, SecondHalfLength);

	int i = 0, j = 0, k =0;

	for (; i < length && j < MidLength && k < SecondHalfLength;)
	{
		if(LeftArray[j] < RightArray[k])
			array[i++] = LeftArray[j++];
		else 
			array[i++] = RightArray[k++];
	}

	while (j< MidLength)
		array[i++] = LeftArray[j++];

	while(k < SecondHalfLength)
		array[i++] = RightArray[k++];
}
