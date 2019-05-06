#include <iostream>

using namespace std;

class Node {
	public:
		Node *left;
		int value;
		Node *right;

		Node() {
			left = nullptr;
			right = nullptr;
		}

		Node(int value): Node() {
			this->value = value;
		}

};


bool ancestorFound = false;

bool isAncestor(Node *tree, int value) {
	if(tree == nullptr) {
		return false;
	}
	if(tree->value == value) {
		return true;
	}

	if(isAncestor(tree->left, value)) {
		return true;
	} else {
		return isAncestor(tree->right, value);
	}
}


void lcaRecursion(Node *tree, int a, int b, Node *&aPtr, Node *&bPtr, Node *&ancestor) {

	if(ancestor == nullptr) {
		ancestor = tree;
	}

	if(tree == nullptr) {
		return;
	}

	if(tree->value == a) {
		aPtr = tree;
		if(aPtr and bPtr){
			return;
		}
	}
	else if(tree->value == b) {
		bPtr = tree;
		if(aPtr and bPtr) {
			return;
		}
	}

	
	lcaRecursion(tree->left, a, b, aPtr, bPtr, ancestor);
	lcaRecursion(tree->right, a, b, aPtr, bPtr, ancestor);

	if((aPtr and bPtr) and !ancestorFound and (tree->value != a and tree->value != b)) {
		if(isAncestor(tree, aPtr->value) and isAncestor(tree, bPtr->value)) {
			ancestor = tree;
			ancestorFound = true;
		}
	}

}

int lca(Node *tree, int a, int b) {

	if(tree->value == a or tree->value == b)
		return tree->value;

	Node *ancestor = nullptr;
	Node *aPtr= nullptr;
	Node *bPtr= nullptr;
	ancestorFound = false;

	lcaRecursion(tree, a, b, aPtr, bPtr, ancestor);

	return ancestor->value;

}

int main() {

	Node *root = new Node(1);

	root->left = new Node(2);
	root->left->left = new Node(4);
	root->left->right = new Node(5);

	root->right = new Node(3);
	root->right->left = new Node(6);
	root->right->right = new Node(7);



	cout << 4 << ", " << 5 << ": " << lca(root, 4, 5) << endl;
	cout << 1 << ", " << 5 << ": " << lca(root, 1, 5) << endl;
	cout << 4 << ", " << 7 << ": " << lca(root, 4, 7) << endl;
	cout << 3 << ", " << 6 << ": " << lca(root, 3, 6) << endl;
	cout << 6 << ", " << 7 << ": " << lca(root, 6, 7) << endl;
	cout << 2 << ", " << 4 << ": " << lca(root, 2, 4) << endl;


	return 0;
}

