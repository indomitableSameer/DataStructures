// LearnTrees.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<list>

class BTreeNode
{
	public:

	int data;
	BTreeNode* leftBranch;
	BTreeNode* rightBranch;

	BTreeNode(int val)
	{
		data = val;
		leftBranch = NULL;
		rightBranch = NULL;
	}
};

class BTree
{

	BTreeNode *bTRoot;
	void preorderTriversal(BTreeNode* node);
	void postOrderTriversal(BTreeNode* node);
	void inorderTriversal(BTreeNode* node);
	void levelOrderTriversal(BTreeNode* node);
	int findLargestNode(BTreeNode* node);
	int findSmallestNode(BTreeNode* node);
	void Destroy(BTreeNode* node);
public:
	BTree()
	{
		bTRoot = NULL;
	}

	bool isEmtry()
	{
		return bTRoot == NULL;
	}

	// inserting node
	bool insert(int data);

	// deleting a node
	bool remove(int data);

	// Depth first triversal -> inorder(left, node, right) , preorder(node, left, right), postorder(l, r, n)
	void inorderTriversal() { inorderTriversal(bTRoot); }
	void preorderTriversal() { preorderTriversal(bTRoot); }
	void postOrderTriversal(){ postOrderTriversal(bTRoot); }

	// breadth first triversal or level order triversal
	void levelOrderTriversal() { levelOrderTriversal(bTRoot); }

	// searching 
	void search(int data);
	int findSmallestNode() { return findSmallestNode(bTRoot);}
	int findLargestNode() { return findLargestNode(bTRoot);}

	// destrying tree
	void DestroyTree() { Destroy(bTRoot); }

	// destructor
	~BTree()
	{
		DestroyTree();
	} 
};

// 3 cases; 1- node is terminal node, 2- node has one child, 3- node has 2 child
bool BTree::remove(int val)
{
	return false;
}

int BTree::findLargestNode(BTreeNode* node)
{
	if(node == NULL || node->rightBranch == NULL)
		return node->data;
	else
		findLargestNode(node->rightBranch);
}

int BTree::findSmallestNode(BTreeNode* node)
{
	if(node == NULL || node->leftBranch == NULL)
		return node->data;
	else
		findSmallestNode(node->leftBranch);
}

// O(n)
void BTree::Destroy(BTreeNode* node)
{
	if(node != NULL) 
	{
		Destroy(node->leftBranch);
		Destroy(node->rightBranch);
		std::cout<< "\n Destrying -> "<< node->data << "\n";
		delete(node);
		node = NULL;
	}
}

// O(n)
void BTree::preorderTriversal(BTreeNode* node)
{
	if (node!=NULL)
	{
		std::cout<< node->data << " ";
		preorderTriversal(node->leftBranch);
		preorderTriversal(node->rightBranch);
	}
}

// O(n)
void BTree::postOrderTriversal(BTreeNode* node)
{
	if (node!=NULL)
	{
		preorderTriversal(node->leftBranch);
		preorderTriversal(node->rightBranch);
		std::cout<< node->data << " ";
	}
}

// O(n)
void BTree::levelOrderTriversal(BTreeNode* root)
{
	std::list<BTreeNode*> queue;
	queue.push_back(root);

	while (!queue.empty())
	{
		BTreeNode* current = queue.front();
		queue.pop_front();

		std::cout<<current->data << " ";

		if(current->leftBranch != NULL)
			queue.push_back(current->leftBranch);

		if(current->rightBranch != NULL)
			queue.push_back(current->rightBranch);
	}
	
}

void BTree::inorderTriversal(BTreeNode* node)
{
	if (node!=NULL)
	{
		preorderTriversal(node->leftBranch);
		std::cout<< node->data << " ";
		preorderTriversal(node->rightBranch);
	}
}

// O(log2 n)
void BTree::search(int val)
{
	if(bTRoot == NULL) { std::cout<<"No Elements!\n"; return; };

	BTreeNode* node = bTRoot;
	while(node != NULL)
	{
		if(val == node->data)
		{
			std::cout<<"Found!\n";
			break;
		}

		if(val < node->data)
		{
			node = node->leftBranch;
		}
		else if(val > node->data)
		{
			node = node->rightBranch;
		}
	}
}

bool BTree::insert(int data)
{
	BTreeNode* node = new BTreeNode(data);
	
	if(bTRoot == NULL)
	{
		bTRoot = new BTreeNode(data);
		return true;
	}

	BTreeNode* parentPtr = NULL;
	BTreeNode* nodePrt = bTRoot;

	while (nodePrt != NULL)
	{
		parentPtr = nodePrt;
		if(data < nodePrt->data)
		{
			nodePrt = nodePrt->leftBranch;
		}
		else if(data > nodePrt->data)
		{
			nodePrt = nodePrt->rightBranch;
		}
	}
	std::cout<< "inserting " << data <<"\n";
	if(data < parentPtr->data)
	{
		parentPtr->leftBranch = node;
		return true;
	}
	else
	{
		parentPtr->rightBranch = node;
		return true;
	}

	return false;
}

int _tmain(int argc, _TCHAR* argv[])
{
	BTree b;
	b.insert(5);
	b.insert(1);
	b.insert(15);
	b.insert(2);
	b.insert(10);

	b.search(5);
	b.search(1);
	b.search(15);
	b.search(2);
	b.search(10);

	std::cout<< "\n Preorder - ";
	b.preorderTriversal();
	std::cout<< "\n inorder - ";
	b.inorderTriversal();
	std::cout<< "\n postorder - ";
	b.postOrderTriversal();
	std::cout<< "\n Levelorder - ";
	b.levelOrderTriversal();


	std::cout<<"\n\n";
	std::cout<< "Largest =" << b.findLargestNode() << "\n"; 
	std::cout<< "Smallest =" << b.findSmallestNode() << "\n"; 
	//b.DestroyTree();

	getchar();

	return 0;
}

