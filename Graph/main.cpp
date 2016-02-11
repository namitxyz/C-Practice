#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <set>

using namespace std;

const int NumberOfVertices = 5;

set<int> PerformBFS(int StartingVertex, map<int, vector<int> > &AdjacencyList);
set<int> PerformDFS(int StartingVertex, map<int, vector<int> > &AdjacencyList);

int main()
{
	int AdjacencyMatrix[NumberOfVertices][NumberOfVertices];

	for(int i=0;i<NumberOfVertices;i++)
	{
		for(int j = 0; j< NumberOfVertices; j++)
			if(i==j)
				AdjacencyMatrix[i][j] = 1;
			else
				AdjacencyMatrix[i][j] = 0;

	}

	//AdjacencyMatrix[1][2] = 1;
	//AdjacencyMatrix[2][1] = 1;

	map<int, vector<int> > AdjacencyList;

	for(int i = 0; i< NumberOfVertices;i++)
	{
		vector<int> emptyVector;

		AdjacencyList[i] = emptyVector;
	}

	for(int i=0;i<NumberOfVertices;i++)
	{
		for(int j = 0; j< NumberOfVertices; j++)
			if(AdjacencyMatrix[i][j] == 1)
				AdjacencyList[i].push_back(j);

	}

	set<set<int> > AllSets;
	for(map<int, vector<int> >::iterator it = AdjacencyList.begin(); it != AdjacencyList.end(); ++it)
	{
		set<int> Path_BFS = PerformBFS(it->first, AdjacencyList);

		set<int> Path_DFS = PerformDFS(it->first, AdjacencyList);

		AllSets.insert(Path_BFS);

		cout<<"Unique number of groups :"<<AllSets.size()<<endl;

		/*cout<<endl<<"BFS path for starting at vertex :"<<it->first<<endl;
		for(int i =0; i< Path_BFS.size(); i++)
			cout<<Path_BFS[i]<<" , ";

		cout<<endl<<"DFS path for starting at vertex :"<<it->first<<endl;
		for(int i =0; i<Path_DFS.size(); i++)
			cout<<Path_DFS[i]<<" ,";*/
	}
}

set<int> PerformBFS(int StartingVertex, map<int, vector<int> > &AdjacencyList)
{
	queue<int>  BFSQueue;
	set<int>    VisitedVertices;
	set<int>    Path;

	BFSQueue.push(StartingVertex);
	VisitedVertices.insert(StartingVertex);

	while(!BFSQueue.empty())
	{
		int current = BFSQueue.front();
		BFSQueue.pop();
		Path.insert(current);
		vector<int> neighbors = AdjacencyList[current];

		for(int i =0; i < neighbors.size(); i++)
		{
			int neighbor = neighbors[i];
			if(VisitedVertices.find(neighbor) == VisitedVertices.end())
			{
				VisitedVertices.insert(neighbor);
				BFSQueue.push(neighbor);
			}
		}
	}

	return Path;
}

set<int> PerformDFS(int StartingVertex, map<int, vector<int> > &AdjacencyList)
{

	stack<int> DFSStack;
	set<int> VisitedVertices;
	set<int> Path;

	DFSStack.push(StartingVertex);
	VisitedVertices.insert(StartingVertex);

	while(!DFSStack.empty())
	{
		int current = DFSStack.top();
		DFSStack.pop();

		Path.insert(current);

		vector<int> neighbors = AdjacencyList[current];

		for(int i =0; i< neighbors.size(); i++)
		{
			int neighbor = neighbors[i];

			if(VisitedVertices.find(neighbor) == VisitedVertices.end())
			{
				VisitedVertices.insert(neighbor);
				DFSStack.push(neighbor);
			}
		}
	}

	return Path;
}