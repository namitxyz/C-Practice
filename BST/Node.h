#ifndef NODE_H
#define NODE_H
#include <iostream>
class Node{
public:
	Node *left;
	Node *right;
	int value;
	Node(int val)
	{
		value = val;
		left  = NULL;
		right = NULL;
	}
};
#endif