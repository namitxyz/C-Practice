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

	void AddElement(Node **node, int val)
	{
		using namespace std;

		if(*node == NULL)
		{
			cout<<"Adding Element :"<<val<<endl;
			*node = new Node(val);
		}
		else
		{
			if(val < (*node)->value)
				AddElement(&((*node)->left), val);
			else
				AddElement(&((*node)->right), val);
		}
	}
	void InOrderTraversal(Node *node)
	{
		using namespace std;
		if(node==NULL)
			return;

		InOrderTraversal(node->left);

		cout<<node->value<< " ";

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