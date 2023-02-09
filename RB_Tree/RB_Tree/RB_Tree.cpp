// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

//#include <bits/stdc++.h>

//**************** RBtree Rules ******************************************

//	Every Node is red or black
//
//	Root is always black
//
//	New insertions are always red
//
//	Every path from root-leaf has the same number of BLACK nodes
//
//	No path can have two consecutive RED nodes
//
//	Nulls are black
// true = Red , false = Black


//>> If Black Uncle then Rotate :
		//After rotation		black
		//						/	\
		//					 red	red 

//>> If Red Uncle then color flip :
		//After color flip		 red
		//						/	\
		//					black   black
//*************************************************************************


enum color { RED = 1, BLACK = 0 };

class RBtree
{
	struct Node
	{
		bool color = RED;
		int value = 0;

		Node(int val) : value(val)
		{
		}

		Node* father = nullptr;
		Node* leftChild = nullptr;
		Node* rightChild = nullptr;

	};

	Node* m_root = nullptr;

	//void leftRotation(Node* uncl)
	//{

	//}

	//void rightRotation(Node* uncl)
	//{

	//}

	//void left_right_Rotation(Node* uncl)
	//{

	//}

	//void right_left_Rotation(Node* uncl)
	//{

	//}

public:

	RBtree()
	{}

	RBtree(int val)
	{
		m_root = new Node(val);
		m_root->color = BLACK;
	}

	void insert(int val)
	{
		Node* temp = new Node(val);
		temp->color = RED;
		Node* p = m_root;

		while (p != nullptr) // adding node according to BST rule
		{
			if (val < p->value)
			{
				if (p->leftChild == nullptr)
				{
					temp->father = p;
					p->leftChild = temp;
				}
				else
					p = p->leftChild;
			}
			else if (val > p->value)
			{
				if (p->rightChild == nullptr)
				{
					temp->father = p;
					p->rightChild = temp;
				}
				else
					p = p->rightChild;
			}
			else
				break;
		}

		if (p->father->color == RED)   //To-Do While() instead of if ()
		{
			Node* uncle = nullptr;
			// finding the uncle
			if (p->father == p->father->father->leftChild)
			{
				uncle = p->father->father->rightChild;
			}
			else if (p->father == p->father->father->rightChild)
			{
				uncle = p->father->father->leftChild;
			}

			if (uncle == nullptr )  // Rotate 
			{
				if (p == p->father->rightChild && p->father == p->father->father->rightChild) // Left rotation
				{
					if (p->father->leftChild != nullptr)
					{
						Node* temp = p->father->leftChild;
						p->father->leftChild = nullptr;
						//left rotation
						p->father->leftChild = p->father->father;
						p->father->father = p->father->father->father;
						p->father->father->rightChild = p->father;
						p->father->leftChild->father = p->father;
						p->father->leftChild->rightChild = nullptr;

						// adding 'temp' according to BST rule
						Node* ptr = m_root;
						while (ptr != nullptr)
						{
							if (temp->value < ptr->leftChild->value)
							{
								ptr = ptr->leftChild;
							}
							else if (temp->value > ptr->rightChild->value)
							{
								ptr = ptr->rightChild;
							}
							else
								return;
						}

						ptr = temp;  // if ptr->father->color == RED && ptr->color == RED then continue;

					}

					else if (p->father->leftChild == nullptr)
					{
						//left rotation
						p->father->leftChild = p->father->father;
						p->father->father = p->father->father->father;
						p->father->father->rightChild = p->father;
						p->father->leftChild->father = p->father;
						p->father->leftChild->rightChild = nullptr;
					}
					// remember after rotation change the color of parent to black and all its children to red (L)
					p->father->color = BLACK;
					p->father->leftChild->color = RED;
					p->father->rightChild->color = RED;

				}
				//  *************************************************************************************************************************************************************
				if (p == p->father->leftChild && p->father == p->father->father->leftChild)  // Right rotation
				{
					if (p->father->rightChild != nullptr)
					{
						Node* temp = p->father->rightChild;
						//right rotation
						p->father->rightChild = p->father->father;
						p->father->father = p->father->father->father;
						p->father->father->leftChild = p->father;
						p->father->rightChild->father = p->father;
						p->father->rightChild->leftChild = nullptr;

						// adding 'temp' according to BST rule
						Node* ptr = m_root;
						while (ptr != nullptr)
						{
							if (temp->value < ptr->leftChild->value)
							{
								ptr = ptr->leftChild;
							}
							else if (temp->value > ptr->rightChild->value)
							{
								ptr = ptr->rightChild;
							}
							else
								return;
						}
						ptr = temp;  // if ptr->father->color == RED && ptr->color == RED then continue;  
					}

					else if (p->father->rightChild == nullptr)
					{
						//right rotation
						p->father->rightChild = p->father->father;
						p->father->father = p->father->father->father;
						p->father->father->leftChild = p->father;
						p->father->rightChild->father = p->father;
						p->father->rightChild->leftChild = nullptr;
					}
				}
				//  *************************************************************************************************************************************************************
				if (p == p->father->rightChild && p->father == p->father->father->leftChild) // Left-Right rotation
				{
					//Left Rotation
					if (p->leftChild != nullptr)
					{
						Node* temp = p->leftChild;
						p->leftChild = nullptr;
						//left rotation 
						p->leftChild = p->father;
						p->father = p->father->father;
						p->father->leftChild = p;
						p->leftChild->father = p;
						p->leftChild->rightChild = nullptr;

						// adding 'temp' according to BST rule
						Node* ptr = m_root;
						while (ptr != nullptr)
						{
							if (temp->value < ptr->leftChild->value)
							{
								ptr = ptr->leftChild;
							}
							else if (temp->value > ptr->rightChild->value)
							{
								ptr = ptr->rightChild;
							}
							else
								return;
						}

						ptr = temp;  // if ptr->father->color == RED && ptr->color == RED then continue;  
					}
					else if (p->leftChild == nullptr)
					{
						// left rotataion 
						p->leftChild = p->father;
						p->father = p->father->father;
						p->father->leftChild = p;
						p->leftChild->father = p;
						p->leftChild->rightChild = nullptr;

					}

					//Right Rotation
					if (p->rightChild != nullptr)
					{
						Node* temp = p->rightChild;
						// right rotation
						p->rightChild = p->father;
						p->father = p->father->father;
						p->father->leftChild = p;
						p->rightChild->father = p;
						p->rightChild->leftChild = nullptr;

						// adding 'temp' according to BST rule
						Node* ptr = m_root;
						while (ptr != nullptr)
						{
							if (temp->value < ptr->leftChild->value)
							{
								ptr = ptr->leftChild;
							}
							else if (temp->value > ptr->rightChild->value)
							{
								ptr = ptr->rightChild;
							}
							else
								return;
						}

						ptr = temp;  // if ptr->father->color == RED && ptr->color == RED then continue;  
					}

					else if (p->rightChild == nullptr)
					{
						// right rotation
						p->rightChild = p->father;
						p->father = p->father->father;
						p->father->leftChild = p;
						p->rightChild->father = p;
						p->rightChild->leftChild = nullptr;
					}

					// remember after rotation change the color of parent to black and all its children to red (L-R)
					p->color = BLACK;
					p->leftChild->color = RED;
					p->rightChild->color = RED;
				}
				//  *************************************************************************************************************************************************************
				if (p == p->father->leftChild && p->father == p->father->father->rightChild) // Right-Left rotation
				{
					//Right Rotation
					if (p->rightChild != nullptr)
					{
						Node* temp = p->rightChild;
						p->rightChild = nullptr;
						//right rotation 
						p->rightChild = p->father;
						p->father = p->father->father;
						p->father->rightChild = p;
						p->rightChild->father = p;
						p->rightChild->leftChild = nullptr;

						// adding 'temp' according to BST rule
						Node* ptr = m_root;
						while (ptr != nullptr)
						{
							if (temp->value < ptr->leftChild->value)
							{
								ptr = ptr->leftChild;
							}
							else if (temp->value > ptr->rightChild->value)
							{
								ptr = ptr->rightChild;
							}
							else
								return;
						}

						ptr = temp;  // if ptr->father->color == RED && ptr->color == RED then continue;  
					}
					else if (p->rightChild == nullptr)
					{
						//right rotation 
						p->rightChild = p->father;
						p->father = p->father->father;
						p->father->rightChild = p;
						p->rightChild->father = p;
						p->rightChild->leftChild = nullptr;
					}

					//Left Rotation
					if (p->leftChild != nullptr)
					{
						Node* temp = p->leftChild;
						p->leftChild = nullptr;
						// left rotation
						p->leftChild = p->father;
						p->father = p->father->father;
						p->father->rightChild = p;
						p->leftChild->father = p;
						p->leftChild->rightChild = nullptr;

						// adding 'temp' according to BST rule
						Node* ptr = m_root;
						while (ptr != nullptr)
						{
							if (temp->value < ptr->leftChild->value)
							{
								ptr = ptr->leftChild;
							}
							else if (temp->value > ptr->rightChild->value)
							{
								ptr = ptr->rightChild;
							}
							else
								return;
						}

						ptr = temp;  // if ptr->father->color == RED && ptr->color == RED then continue;  
					}

					else if (p->leftChild == nullptr)
					{
						// left rotation
						p->leftChild = p->father;
						p->father = p->father->father;
						p->father->rightChild = p;
						p->leftChild->father = p;
						p->leftChild->rightChild = nullptr;

					}
					// remember after rotation change the color of parent to black and all its children to red (R-L)
					p->color = BLACK;
					p->leftChild->color = RED;
					p->rightChild->color = RED;
				}

			}

			//Color Flip
			else if (uncle->color == RED) 
			{
				p->father->father->color = RED;
				p->father->father->leftChild->color = BLACK;
				p->father->father->rightChild->color = BLACK;
				if (p->father->father == m_root)
					m_root->color = BLACK;
			}
		}

	}

};

int main()
{
	int rootval = 3;

	RBtree rbtree(rootval);
	rbtree.insert(1);
	rbtree.insert(5);
	rbtree.insert(7);
	rbtree.insert(6);
	rbtree.insert(8);
	rbtree.insert(9);
	rbtree.insert(10);

}