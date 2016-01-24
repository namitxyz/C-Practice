// Implementation of Binary heap tree - used for Priority queues. O(NlogN) insertion and deletion. Highest element stored at array index 1.
#include <iostream>
#include <vector>

using namespace std;

void InsertData(std::vector<int> &BinaryHeap, int value);
void PrintHeap(std::vector<int> &BinaryHeap);
void RemoveData(std::vector<int> &BinaryHeap);
void StartIterating(std::vector<int> &BinaryHeap, int &current_location);

void Swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

int main()
{
	vector<int> BinaryHeap;

	BinaryHeap.push_back(-1);

	InsertData(BinaryHeap, 15);
	InsertData(BinaryHeap, 18);
	InsertData(BinaryHeap, 40);
	InsertData(BinaryHeap, 33);
	InsertData(BinaryHeap, 27);
	InsertData(BinaryHeap, 43);
	InsertData(BinaryHeap, 5);

	PrintHeap(BinaryHeap);

	RemoveData(BinaryHeap);

	PrintHeap(BinaryHeap);
}

void InsertData(std::vector<int> &BinaryHeap, int value)
{
	int current_location = BinaryHeap.size();

	BinaryHeap.push_back(value);

	while(current_location != 0 && current_location != 1)
		StartIterating(BinaryHeap, current_location);
}

void StartIterating(std::vector<int> &BinaryHeap, int &current_location)
{
	if (current_location % 2 == 0) // at 2*i --> stored at the left node of the binary tree
	{
		current_location = current_location/2;
		
		if(BinaryHeap[current_location] < BinaryHeap[2*current_location])
			Swap(BinaryHeap[current_location], BinaryHeap[2*current_location]);
	}
	else // at 2*i + 1 ---> Stored at the right node of the binary tree
	{
		current_location = (current_location-1)/2;

		if(BinaryHeap[current_location] < BinaryHeap[2*current_location + 1])
			Swap(BinaryHeap[current_location], BinaryHeap[2*current_location + 1]);
	}
}
void PrintHeap(std::vector<int> &BinaryHeap)
{
	for(int i =0; i< BinaryHeap.size(); i++)
		cout<<BinaryHeap[i]<<" ";
}

void RemoveData(std::vector<int> &BinaryHeap)
{
	int current_location = BinaryHeap.size();

}