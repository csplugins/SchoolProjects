#ifndef AVL_HPP
#define AVL_HPP

#include <string>

template <class T>
struct ALVN {
	T data;
	ALVN* left = 0, *right = 0, *parent = 0;
	int height, balanceFactor;
	ALVN(const T& t) {
		data = t;
		height = 0;
		balanceFactor = 0;
	}
	~ALVN();
};

template <class T>
ALVN<T>::~ALVN() {
	if (left)
		delete left;
	if (right)
		delete right;
}

template <class T>
class AVL {
private:
	// put your private functions here (you will probably have quite a few)
	ALVN<T>* root = 0;
	void insert(const T&, ALVN<T>*);
	void remove(const T&, ALVN<T>*);
	void findPredecessorAndRemove(ALVN<T>*, ALVN<T>*);
	void serialize(ALVN<int>*, std::vector<std::string>&);
	void serialize(ALVN<std::string>*, std::vector<std::string>&);
	void updateHeightAndBF(ALVN<T>*);
	void doubleRight(ALVN<T>*);
	void doubleLeft(ALVN<T>*);
	void right(ALVN<T>*);
	void left(ALVN<T>*);
public:
	AVL() {}
	~AVL();

	// Insert a node into the AVL with a given data value
	// The tree must be balanced after every insert
	void insert(const T& t){
		if (root)
			insert(t, root);
		else root = new ALVN<T>(t);
	}

	// remove a node from the AVL with a specific data value
	// you MUST use the in order predecessor to replace the removed node
	void remove(const T& t) {
		if (!root)
			return;
		remove(t, root);
	}

	// return a std::vector<std::string> of the serialized AVL tree
	// you WILL need to have template specialization for AVL<int> and AVL<std::string>
	// std::to_string(int) can be used to convert an integer to a string
	std::vector<std::string> serialize(){
		std::vector<std::string> v;
		if (root)
			serialize((ALVN<T>*) root, v);
		return v;
	}
};

//The deconstructor handles the memory leaks appropriately
template <class T>
AVL<T>::~AVL(){
  delete root;
}

//This inserts a node according to the current tree structure and height/balance factor recalcualted
template <class T>
void AVL<T>::insert(const T& t, ALVN<T>* node){
	if (t <= node->data) {
		if (node->left)
			insert(t, node->left);
		else{
			node->left = new ALVN<T>(t);
			node->left->parent = node;
		}
	}
	else {
		if (node->right)
			insert(t, node->right);
		else{
			node->right = new ALVN<T>(t);
			node->right->parent = node;
		}
	}
	updateHeightAndBF(root);
}

//This removes a node handling all cases accordingly depending on the situation
template <class T>
void AVL<T>::remove(const T& t, ALVN<T>* node){
	if (t == node->data){
		if (!node->left && !node->right){
			if (!node->parent){
				root = 0;
				return;
			}
			else if (node->data > node->parent->data)
				node->parent->right = 0;
			else node->parent->left = 0;
			delete node;
		}
		else if (!node->left){
			node->right->parent = node->parent;
			if (!node->parent)
				root = node->right;
			else if (node->data > node->parent->data)
				node->parent->right = node->right;
			else node->parent->left = node->right;
			node->right = 0;
			delete node;
		}
		else if (!node->right){
			node->left->parent = node->parent;
			if (!node->parent)
				root = node->left;
			else if (node->data > node->parent->data)
				node->parent->right = node->left;
			else node->parent->left = node->left;
			node->left = 0;
			delete node;
		}
		else
			findPredecessorAndRemove(node->left, node); 
		updateHeightAndBF(root);
	}
	else if (t <= node->data) {
		if (!node->left)
			return;
		remove(t, node->left);
	}
	else {
		if (!node->right)
			return;
		remove(t, node->right);
	}
}

//This will make the nodeToBeDeleted value equal to its predecessor and simply delete the predecessor
template <class T>
void AVL<T>::findPredecessorAndRemove(ALVN<T>* node, ALVN<T>*nodeToBeDeleted){
	if (node->right){
		findPredecessorAndRemove(node->right, nodeToBeDeleted);
		return;
	}
	T temp = node->data;
	remove(node->data, root);
	nodeToBeDeleted->data = temp;
}

//This is how the vector of ints is returned for usage in text_avl.cpp
template <class T>
void AVL<T>::serialize(ALVN<int>* node, std::vector<std::string>& v) {
	if (node)
		v.push_back(std::to_string(node->data));
	else {
		v.push_back("/");
		return;
	}
	serialize(node->left, v);
	serialize(node->right, v);
}

//This is how the vector of strings is returned for usage in text_avl.cpp
template <class T>
void AVL<T>::serialize(ALVN<std::string>* node, std::vector<std::string>& v) {
	if (node)
		v.push_back(node->data);
	else {
		v.push_back("/");
		return;
	}
	serialize(node->left, v);
	serialize(node->right, v);
}

//This determines height and balance factor for each node then rotates if necessary
template <class T>
void AVL<T>::updateHeightAndBF(ALVN<T>* node){
	if (!node->left && !node->right){
		node->balanceFactor = 0;
		node->height = 0;
	}
	else if (node->left && node->right){
		updateHeightAndBF(node->left);
		updateHeightAndBF(node->right);
		node->balanceFactor = node->left->height - node->right->height;
		node->height = (node->left->height > node->right->height) ? node->left->height + 1 : node->right->height + 1;
	}
	else if (node->left){
		updateHeightAndBF(node->left);
		node->balanceFactor = node->left->height + 1;
		node->height = node->left->height + 1;
	}
	else if (node->right){
		updateHeightAndBF(node->right);
		node->height = node->right->height + 1;
		node->balanceFactor = (-1) - node->right->height;
	}

	if (node->balanceFactor > 1){
		if (node->left->balanceFactor < 0)
			doubleRight(node);
		else right(node);
	}
	else if (node->balanceFactor < -1){
		if (node->right->balanceFactor > 0)
			doubleLeft(node);
		else left(node);
	}
}

//This double rotates right on a specific node
template <class T>
void AVL<T>::doubleRight(ALVN<T>* node){
	left(node->left);
	right(node);
}

//This double rotates left on a specific node
template <class T>
void AVL<T>::doubleLeft(ALVN<T>* node){
	right(node->right);
	left(node);
}

//This rotates right on a specific node
template <class T>
void AVL<T>::right(ALVN<T>* node){
	node->left->parent = node->parent;
	node->parent = node->left;
	if (node->left->right){
		node->left->right->parent = node;
		node->left = node->left->right;
	}
	else node->left = 0;
	node->parent->right = node;
	if (!node->parent->parent)
		root = node->parent;
	else if (node->parent->data > node->parent->parent->data)
			node->parent->parent->right = node->parent;
	else node->parent->parent->left = node->parent;
}

//This rotates left on a specific node
template <class T>
void AVL<T>::left(ALVN<T>* node){
	node->right->parent = node->parent;
	node->parent = node->right;
	if (node->right->left){
		node->right->left->parent = node;
		node->right = node->right->left;
	}
	else node->right = 0;
	node->parent->left = node;
	if (!node->parent->parent)
		root = node->parent;
	else if (node->parent->data > node->parent->parent->data)
		node->parent->parent->right = node->parent;
	else node->parent->parent->left = node->parent;
}
#endif