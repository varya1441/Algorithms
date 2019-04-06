#include <iostream>
#include <vector>
#include <set>
#include <fstream>


class BinaryTree {
private:
	struct Node {
	public:
		long long key;
		Node* left;
		Node* right;

		int height;
		int depth;
		std::set<int> pathes;

		Node() {
			this->left = nullptr;
			this->right = nullptr;
		}

		Node(long long key) : key(key) {
			left = nullptr;
			right = nullptr;
		}

		Node(const Node& node) {
			this->key = node.key;
			this->left = node.left;
			this->right = node.right;

			this->height = node.height;
			this->depth = node.depth;
			this->pathes = node.pathes;
		}

		void setKey(long long value) {
			this->key = value;
		}

		void findDepth(int currentLevel) {
			this->depth = currentLevel + 1;
		}

		void findHeightAndPathes() {
			if (this->left == nullptr && this->right == nullptr) {
				this->height = 0;
			}
			else if (this->left != nullptr && this->right != nullptr) {
				if (left->height >= right->height) {
					this->height = left->height + 1;
				}
				else {
					this->height = right->height + 1;
				}
			}
			else if (this->left != nullptr) {
				this->height = left->height + 1;
			}
			else {
				this->height = right->height + 1;
			}
		}
	};

	Node* root;
	int height;
	int currentDepth;
public:
	BinaryTree() {
		root = nullptr;
	}

	void add(long long value) {
		if (root == nullptr) {
			root = new Node(value);
			return;
		}
		else {
			Node* node = root;
			this->add(value, node);
		}
	}

	Node* find(long long value) {
		Node* temp = root;
		while (temp != nullptr) {
			if (temp->key == value) {
				return temp;
			}
			else if (temp->key > value) {
				temp = temp->left;
			}
			else if (temp->key < value) {
				temp = temp->right;
			}
		}
		return nullptr;
	}

	void erase(long long value) {
		Node* node = root;
		Node* parent = nullptr;

		while (true) {
			if (node == nullptr) {
				return;
			}
			if (node->key == value) {
				break;
			}
			else if (node->key > value) {
				parent = node;
				node = node->left;
			}
			else if (node->key < value) {
				parent = node;
				node = node->right;
			}
		}

		Node* left = node->left;
		Node* right = node->right;
		Node* minNodeParent = node;
		Node* minNode = node;
		Node* newNode = nullptr;

		if (node != nullptr) {
			if (right != nullptr && left != nullptr) {
				minNode = minNode->right;
				while (minNode->left != nullptr) {
					minNodeParent = minNode;
					minNode = minNode->left;
				}
				node->key = minNode->key;
				replaceNode(minNodeParent, minNode, minNode->right);
				return;
			}
			else if (right != nullptr) {
				newNode = right;
			}
			else if (left != nullptr) {
				newNode = left;
			}
			replaceNode(parent, node, newNode);
		}
	}

	void task() {
		lre(root);
		height = root->height;
		getPathes(root);
		int currentLevel = -1;
		elr(currentLevel);

		//test();

		findAndDelete();
	}

	void elr(int currentLevel) {
		elr(root, currentLevel);
	}

	void test() {
		test(root);
	}

	void findAndDelete() {
		currentDepth = 0;
		std::set<long long> keys;
		lre(root, keys);
		if (keys.size() != 0 && (keys.size() % 2) != 0) {
			std::set<long long>::iterator iter = keys.begin();
			for (int i = 0; i < keys.size() / 2; i++) {
				++iter;
			}
			erase(*iter);
		}
	}

	std::set<int> getPathes(Node* node) {
		if (node->left != nullptr && node->right != nullptr) {
			std::set<int> setL = this->getPathes(node->left);
			std::set<int> setR = this->getPathes(node->right);
			std::set<int> setE;
			for (std::set<int>::iterator iterL = setL.begin(); iterL != setL.end(); ++iterL) {
				for (std::set<int>::iterator iterR = setR.begin(); iterR != setR.end(); ++iterR) {
					node->pathes.insert(*iterL + *iterR + 2);
				}
			}
			for (std::set<int>::iterator iter = setL.begin(); iter != setL.end(); ++iter) {
				setE.insert(*iter + 1);
			}
			for (std::set<int>::iterator iter = setR.begin(); iter != setR.end(); ++iter) {
				setE.insert(*iter + 1);
			}
			return setE;
		}
		else if (node->left != nullptr) {
			std::set<int> setL = this->getPathes(node->left);
			for (std::set<int>::iterator iter = setL.begin(); iter != setL.end(); ++iter) {
				node->pathes.insert(*iter + 1);
			}
			return node->pathes;
		}
		else if (node->right != nullptr) {
			std::set<int> setR = this->getPathes(node->right);
			for (std::set<int>::iterator iter = setR.begin(); iter != setR.end(); ++iter) {
				node->pathes.insert(*iter + 1);
			}
			return node->pathes;
		}
		else {
			node->pathes.insert(0);
			return node->pathes;
		}
	}

	std::vector<long long> ler() {
		std::vector<long long> treeElements;
		ler(root, treeElements);
		return treeElements;
	}

	std::vector<long long> elr() {
		std::vector<long long> treeElements;
		elr(root, treeElements);
		return treeElements;
	}

	long long sumOfElements() {
		std::vector<long long> treeElements(ler());
		long long sum = 0;
		for (std::vector<long long>::iterator iter = treeElements.begin(); iter != treeElements.end(); ++iter) {
			sum += *iter;
		}
		return sum;
	}
private:
	void ler(Node* node, std::vector<long long>& vec) {
		if (node != nullptr) {
			ler(node->left, vec);
			vec.push_back(node->key);
			ler(node->right, vec);
		}
	}

	void elr(Node* node, std::vector<long long>& vec) {
		if (node != nullptr) {
			vec.push_back(node->key);
			elr(node->left, vec);
			elr(node->right, vec);
		}
	}

	void elr(Node* node, int currentLevel) {
		if (node != nullptr) {
			node->findDepth(currentLevel);
			elr(node->left, currentLevel + 1);
			elr(node->right, currentLevel + 1);
		}
	}

	void lre(Node* node) {
		if (node != nullptr) {
			lre(node->left);
			lre(node->right);
			node->findHeightAndPathes();
		}
	}

	void lre(Node* node, std::set<long long>& set) {
		if (node != nullptr) {
			lre(node->left, set);
			lre(node->right, set);
			checkPathes(node, set);
		}
	}

	void checkPathes(Node* node, std::set<long long>& set) {
		if (node == root || (node->left != nullptr && node->right != nullptr)) {
			std::set<int>::reverse_iterator riter = node->pathes.rbegin();
			std::set<int>::iterator iter = node->pathes.begin();
			if (*riter >= height && *iter <= height) {
				for (iter; iter != node->pathes.end(); ++iter) {
					if (*iter == height) {
						if (node->depth > currentDepth) {
							set.clear();
							set.insert(node->key);
							currentDepth = node->depth;
						}
						else if (node->depth == currentDepth) {
							set.insert(node->key);
						}
					}
				}
			}
		}
	}

	void test(Node* node) {
		if (node != nullptr) {
			std::cout << node->key << " H:" << node->height << " D:" << node->depth << " P:";
			for (std::set<int>::iterator iter = node->pathes.begin(); iter != node->pathes.end(); ++iter) {
				std::cout << *iter << ",";
			}
			std::cout << std::endl;
			test(node->left);
			test(node->right);
		}
	}

	void add(long long value, Node* &node) {
		if (node != nullptr) {
			if (node->key > value) {
				this->add(value, node->left);
			}
			if (node->key < value) {
				this->add(value, node->right);
			}
		}
		else {
			node = new Node(value);
		}
	}

	void replaceNode(Node* parent, Node* oldNode, Node* newNode) {
		if (parent == nullptr) {
			root = newNode;
		}
		else if (parent->left == oldNode) {
			parent->left = newNode;
		}
		else if (parent->right == oldNode) {
			parent->right = newNode;
		}
		//delete[] oldNode;
	}
};



int main() {
	BinaryTree tree1;
	std::ifstream fin;
	long long value;
	fin.open("tst.in");
	if (fin.is_open()) {
		while (fin >> value) {
			tree1.add(value);
		}
		fin.close();
	}
	else {
		std::cout << "Error during file opening!" << std::endl;
	}
	tree1.task();
	std::ofstream fout;
	fout.open("tst.out");
	std::vector<long long> elr(tree1.elr());
	for (std::vector<long long>::iterator iter = elr.begin(); iter != elr.end(); ++iter) {
		fout << *iter << std::endl;
	}
	fout.close();

	system("pause");
	return 0;
}