#include "BST.h"
#include <iostream>

int main()
{
	using namespace std;
	Bst bst;
	bst.AddElement(&bst.root, 50,0);
	bst.AddElement(&bst.root, 25,0);
	bst.AddElement(&bst.root, 47,0);
	bst.AddElement(&bst.root, 60,0);
	bst.AddElement(&bst.root, 42,0);
	bst.AddElement(&bst.root, 100,0);
	bst.AddElement(&bst.root, 55,0);

	cout<<"InOrderTraversal"<<endl;
	bst.InOrderTraversal(bst.root);
	cout<<endl<<"PreOrderTraversal"<<endl;
	bst.PreOrderTraversal(bst.root);
	cout<<endl<<"PreOrderTraversal"<<endl;
	bst.PostOrderTraversal(bst.root);
	cout<<endl<<"LevelOrderTraversal"<<endl;
	bst.LevelOrderTraversal(bst.root);
	cout<<endl<<"Deleting All:"<<endl;
	bst.DeleteAll(&bst.root);


	return 0;
}