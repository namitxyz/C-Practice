#ifndef NODE_H
#define NODE_H
#include <iostream>
class Node{
public:
	Node *left;
	Node *right;
	int value;
	int height;
	int depth;
	Node(int val)
	{
		value = val;
		left  = NULL;
		right = NULL;
		depth = 0;
	}
};
#endif