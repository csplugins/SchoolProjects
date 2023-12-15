// making a heap

#ifndef HEAP_HPP
#define HEAP_HPP

#include "HNode.hpp"
#include <vector>
#include<assert.h>

//Basically what we did in class with some minor tweaks here and there
class Heap {
protected:
	// holds the tree
	std::vector<HNode*> tree;

	// index of the last element added
	int position = 0;
public:
	Heap() { tree.resize(2); }
	virtual ~Heap() {}

	//Used for number of nodes in the tree
	int count = 0;
	void clear();

	// add an element to the tree
	void enqueue(HNode*);
	// remove the smallest element
	HNode* dequeue();

	// fix the heap from a specific index up
	void fix_up(const int&);
	// fix the tree after replacing the smallest element
	void fix_down(const int&);

	void swap(const int&, const int&);
};

//This function was not implemented in class so I just took everything out of the queue one at a time until nothing was left
void Heap::clear(){
	while(count != 0)
		dequeue();
}

//Puts a node a the end of the tree
void Heap::enqueue(HNode* t) {
	count++;
	// check to see if we need to expand the vector
	if (position == tree.size() - 1)
		tree.resize(tree.size() * 2);

	// insert at the next position
	tree[++position] = t;

	// fix up to the root (or until we dont need to swap)
	fix_up(position);
	// done
}

//Takes a node out of the top of the tree
HNode* Heap::dequeue() {
	count--;
	assert(position);

	HNode* ret = tree[1];
	swap(1, position--);
	fix_down(1);
	return ret;
}

//Starts at the bottom of the tree and ensures the tree continues to be a min heap fixing when needed
void Heap::fix_up(const int& t) {
	// at the top of the tree
	if (t == 1)
		return;

	// if current is < its parent
	if (tree[t]->weight < tree[t / 2]->weight) {
		swap(t, t / 2);
		fix_up(t / 2);
	}
}

//Starts at the top of the tree and ensures the tree continues to be a min heap fixing when needed
void Heap::fix_down(const int& t) {
	int left_index = t * 2;
	int right_index = (t * 2) + 1;

	// if two children
	if (right_index <= position) {
		// check for the smallest of the children and treat like one child but recurse
		if (tree[left_index]->weight < tree[right_index]->weight) {
			if (tree[left_index]->weight < tree[t]->weight) {
				swap(left_index, t);
				fix_down(left_index);
			}
		}
		else {
			if (tree[right_index]->weight < tree[t]->weight) {
				swap(right_index, t);
				fix_down(right_index);
			}
		}
	}
	// one  child
	else if (left_index <= position) {
		if (tree[left_index]->weight < tree[t]->weight)
			swap(left_index, t);
	}
}

//This will swap two positions of the tree in order to retain min heap
void Heap::swap(const int& a, const int& b) {
	HNode* temp = tree[a];
	tree[a] = tree[b];
	tree[b] = temp;
}

#endif
