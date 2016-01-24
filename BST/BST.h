#ifndef BST
#define BST
#include <iostream>
#include "Node.h"
#include <queue>

class Bst{

public:
	Node *root;
	
	Bst()
	{
		root = NULL;
	}

	int AddElement(Node **node, int val, int CurrDepth)
	{
		using namespace std;

		if(*node == NULL)
		{
			cout<<"Adding Element :"<<val<<endl;
			*node = new Node(val);
			(*node)->depth = CurrDepth;
			(*node)->height = 0;
		}
		else
		{
			int ChildHeight = 0;

			if(val < (*node)->value)
				ChildHeight = AddElement(&((*node)->left), val, CurrDepth+1);
			else
				ChildHeight = AddElement(&((*node)->right), val, CurrDepth+1);

			if(ChildHeight + 1 > (*node)->height)
				(*node)->height = ChildHeight + 1;
		}

		return (*node)->height;

	}
	void InOrderTraversal(Node *node)
	{
		using namespace std;
		if(node==NULL)
			return;

		InOrderTraversal(node->left);

		cout<<node->value<< " "<<","<<node->depth<<" , "<<node->height<<" | ";


		InOrderTraversal(node->right);
	}

	void PreOrderTraversal(Node *node)
	{
		using namespace std;

		if(node ==NULL)
			return;

		cout<<node->value<<" ";

		PreOrderTraversal(node->left);
		PreOrderTraversal(node->right);
	}

	void PostOrderTraversal(Node *node)
	{
		using namespace std;

		if(node ==NULL)
			return;

		PostOrderTraversal(node->left);
		PostOrderTraversal(node->right);
		cout<<node->value<<" ";
	}

	void LevelOrderTraversal(Node *node) //BFS algorithm
	{
		using namespace std;
		if(node == NULL)
			return;

		std::queue<Node>  BFSNodeQueue;
		BFSNodeQueue.push(*node);

		while(!BFSNodeQueue.empty())
		{
			Node tempNode = BFSNodeQueue.front();
			BFSNodeQueue.pop();
			cout<<tempNode.value<<" ";

			if(tempNode.left != NULL)
				BFSNodeQueue.push(*tempNode.left);

			if(tempNode.right !=NULL)
				BFSNodeQueue.push(*tempNode.right);
				
			
		}
	}

	void DeleteAll(Node **node)
	{
		using namespace std;
		if(*node == NULL)
			return;

		DeleteAll(&((*node)->left));
		DeleteAll(&((*node)->right));
		cout<<((*node)->value)<<" ";
		delete *node;

	}
};

#endif