//#pragma warning(suppress : 4996)
#pragma warning(disable : 4996)
#include <stdio.h>

#include<iostream>
#include<numeric>

using namespace std;

typedef long long int type;
type maxSemLen = INT64_MIN;
struct Node {
	Node(type key) : key(key) {}
	type key;
	type h = 0;
	type b = 0;
	type l = 0;
	type msl = 0;
	type c = 0;
	type a = 0;
	Node* left = nullptr;
	Node *right = nullptr;
};
class Tree {
public:
	Tree() :Root(0) {}
	~Tree() {
		destroyNode(Root);
	}
	void Insert(type el);
	void deleteNode(type el) {
		Root = deleteNode(Root, el);
	}
	Node* deleteNode(Node* root, type el);
	
	void start() {
		start(Root);

		setA(Root);
		printTree(Root);
	}
private:
	void destroyNode(Node* node) {
		if (node) {
			destroyNode(node->left);
			destroyNode(node->right);
			delete node;
		}
	}
	
	void setA(Node* node)
	{
		if (node != nullptr) {
		
			if (node->msl == maxSemLen) {
				if (node->right != NULL&&node->left != NULL)
				{
					node->b = node->left->l*node->right->l;
					
				}
				else if(node->right == NULL && node->left == NULL)
				{
					node->b = 1;
				}
				else if(node->right == NULL)
				{
					if (node->left != NULL) 
					{
						node->b = node->left->l;
					}
					
				}
				else if (node->left == NULL)
				{
					node->b = node->right->l;
				}
			}
			

			if (node->left == NULL && node->right != NULL)
			{
				node->right->a = node->a + node->b;
			}
			else if (node->right == NULL&& node->left != NULL)
			{
				node->left->a = node->a + node->b;
			}
			else if (node->left != NULL && node->right != NULL)
			{
				
				if (node == Root)
				{
					node->a = 0;
				}
				
					if ((node->right->h )> (node->left->h))
					{
						node->right->a = node->a + node->b;
						node->left->a = node->b;
					}
					else if ((node->right->h) < (node->left->h))
					{
						node->left->a = node->a + node->b;
						node->right->a = node->b;
					}
					else
					{
						
						node->right->a = node->b + (node->right->l)*(node->a / node->l);
						node->left->a = node->b + node->left->l*node->a / node->l;
					}
				
			}
			cout << node->key << " h= " << node->h << " " << " msl= " << node->msl << " b= " << node->b << " a = " << node->a << " l = " << node->l << endl;

			setA(node->left);
			setA(node->right);

		}
	}
	void start(Node* node) {
	

		if (node != nullptr) {
			start(node->left);
			start(node->right);

			if (node->left == NULL && node->right == NULL)
			{
				node->h = 0;
				node->msl = 0;
				node->l = 1;

			}
			else if (node->left == NULL)
			{
				node->h = node->right->h + 1;
				node->msl = node->right->h + 1;
				node->l = node->right->l;
			}
			else if (node->right == NULL)
			{
				node->h = node->left->h + 1;
				node->msl = node->left->h + 1;
				node->l = node->left->l;
			}
			else
			{
				if ((node->right->h) > (node->left->h))
				{
					node->h = node->right->h + 1;
				}
				else
				{
					node->h = node->left->h + 1;
				}
				node->msl = node->right->h + node->left->h + 2;
				if (node->right->h == node->left->h)
				{
					node->l = node->right->l + node->left->l;
				}
				else if (node->right->h > node->left->h)
				{
					node->l = node->right->l;
				}
				else
				{
					node->l = node->left->l;
				}
			}
			if (maxSemLen < node->msl)
			{
				maxSemLen = node->msl;
			}
		

		}

	}
	void printTree(Node* node);

private:
	Node * Root;

};
	
void Tree::printTree(Node*node) {

	if (node != nullptr) {
		cout <<node->key<< " " << (node->a + node->b) << endl;
	
		printTree(node->left);
		printTree(node->right);
	}
}
Node* FindMin(Node* root)
{
	while (root->left != NULL) root = root->left;
	return root;
}
Node* Tree::deleteNode(Node *root, type el) {

	if (root == nullptr)
	{
		return nullptr;
	}
	if (el < root->key)
	{
		root->left = deleteNode(root->left, el);
	}
	else if (el > root->key)
	{
		root->right = deleteNode(root->right, el);
	}
	else {
		if (root->left == NULL && root->right == NULL) {
			delete root;
			root = nullptr;
		}
		else if (root->left == NULL) {
			Node* temp = root;
			root = root->right;
			delete temp;
		}
		else if (root->right == NULL) {
			Node* temp = root;
			root = root->left;
			delete temp;
		}
		else
		{
			struct Node *temp = FindMin(root->right);
			root->key = temp->key;
			root->right = deleteNode(root->right, temp->key);

		}

	}
	return root;
}

void Tree::Insert(type el) {
	Node** current = &Root;
	while (*current) {
		Node& node = **current;
		if (el < node.key) {
			current = &node.left;
		}
		else if (el > node.key) {
			current = &node.right;
		}
		else {
			return;
		}

	}
	*current = new Node(el);

}
int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	type a, num;
	Tree* tree = new Tree();
	cin >> num;
	tree->Insert(num);
	while (!cin.eof()) {
		cin >> a;
		tree->Insert(a);
	}

	tree->deleteNode(num);


	tree->start();

	delete tree;
	return 0;
}