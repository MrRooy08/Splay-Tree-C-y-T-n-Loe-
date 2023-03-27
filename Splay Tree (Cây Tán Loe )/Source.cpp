#include <iostream>
using namespace std;

struct Node
{
	int data;
	Node* left;
	Node* right;
};

Node* newNode(int x)
{
	Node* p = new Node();
	p->data = x;
	p->left = NULL;
	p->right = NULL;
	return (p);
}

Node* rightRotate(Node* x)
{
	Node* y = x->left;

	x->left = y->right;
	y->right = x;

	return y;
	
}

Node* leftRotate(Node* y)
{
	Node* x = y->right;

	y->right = x->left;
	x->left = y;

	return x;

}

Node* Splay(Node* node, int x)
{
	// base cases: node is NULL or x is present at node 
	if (node == NULL || node->data == x) return node;

	if (x < node->data)
	{
		// X is not in tree and done
		if (node->left == NULL) return node;

		//Left - Left

		if (x < node->left->data)
		{
			node->left->left = Splay(node->left->left, x);

			node = rightRotate(node);
		}
		else if (x > node->left->data) // Left - Right
		{
			node->left->right = Splay(node->left->right, x);

			if (node->left->right != NULL)
				node->left = leftRotate(node->left);

		}

		return (node->left == NULL) ? node : rightRotate(node);

	}
	else
	{
		// X is not in tree and done
		if (node->right == NULL) return node;

		//Right Right
		if (x < node->right->data)
		{
			node->right->left = Splay(node->right->left, x);

			if (node->right->left != NULL)
				node->right = rightRotate(node->right);
		}
		else if (x > node->right->data) // Right Left 
		{
			node->right->right = Splay(node->right->right, x);
			node = leftRotate(node);
		}

		return (node->right == NULL) ? node : leftRotate(node);

	}
}

Node* insertNode(Node* node, int x)
{

	if (node == NULL) return newNode(x);

	node = Splay(node, x);

	if (node->data == x) return node;

	Node* p = newNode(x);

	if (x < node->data)
	{
		p->right = node;

		p->left = node->left;

		node->left = NULL;
	}
	else
	{
		p->left = node;

		p->right = node->right;

		node->right = NULL;
	}

	return p;
}

void nhap(Node*& node)
{
	int x;
	do
	{
		cout << "\n Nhap Gia Tri: "; cin >> x;
		if (x == -99) break;
		node = insertNode(node, x);
	} while (1);

}

void preOrder(Node* node)
{
	if (node != NULL)
	{
		cout << " " << node->data;
		preOrder(node->left);
		preOrder(node->right);
	}
}

void displayMenu()
{
	cout << "\n\n\t\t===================================" << endl;
	cout << "\n\n\t\t1. Nhap Node. ";
	cout << "\n\n\t\t2. Xuat Node.";
	cout << "\n\n\t\t0. Dung Lai. ";
	cout << "\n\n\t\t===================================" << endl;
}


int main()
{
	Node* node = NULL;
	int choice;
	bool isRunning = true;
	cout << "\n Chon 1 so nguyen de thuc thi: ";
	while (isRunning)
	{
		displayMenu();
		cin >> choice;
		switch (choice)
		{
		case 1:
			system("cls");
			nhap(node);
			break;
		case 2:
			system("cls");
			preOrder(node);
			break;
		case 0:
			isRunning = false;
			break;
		default:
			cout << "\n Ban Nhap Khong Hop Le Vui Long Nhap Lai";
			break;
		}
	}
	return 0;
}