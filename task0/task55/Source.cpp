//#pragma warning(suppress : 4996)
#pragma warning(disable : 4996)
#include <stdio.h>

#include<iostream>
#include<numeric>

using namespace std;

typedef long long int type;

struct Node {
	Node(type key) : key(key) {}
	type key;
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
	void goRootLeftRight() {
		goRootLeftRight(Root);
	}
private:
	void destroyNode(Node* node) {
		if (node) {
			destroyNode(node->left);
			destroyNode(node->right);
			delete node;
		}
	}
	void goRootLeftRight(Node* node)
	{
		if (node != nullptr) {
			cout << node->key << endl;
			goRootLeftRight(node->left);
			goRootLeftRight(node->right);
		}
	}

private:
	Node * Root;

};
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

	 tree->goRootLeftRight();
	delete tree;
	return 0;
}