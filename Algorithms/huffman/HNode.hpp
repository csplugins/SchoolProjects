#ifndef HNODE_HPP
#define HNODE_HPP

// the nodes used for our encoding trees
// they will be used for both the encoding tree and the minheap
struct HNode {

  HNode* left = 0, * right = 0;

  // set the default value to "*" and change it when you have an actual value
  // this way you dont have to worry about setting it for combined nodes
  char value = '*';
  int weight = 0;

  // create a new node from a string and its value
  // you must implement this function
  HNode(const char&, const int&);

  // create a new node from two existing nodes
  // you must implement this function
  HNode(HNode*, HNode*);

  // this will delete all children when the destructor is called
  // this is ok because we will never call the destructor until we are done with the entire tree
  ~HNode() { delete left; delete right; }

  // overloading comparison operators
  // when comparing two pointers to HNode, make sure to de-reference them first
  // i.e. if (*node_pointer1 < *node_pointer2) ...
  bool operator<(const HNode& h) { return weight < h.weight; }
  bool operator<=(const HNode& h) { return weight <= h.weight; }
};

HNode::HNode(const char& s, const int& t) {
	//The two things being passed are the value and the weight of the node for these two parameters
	//These are the leaves on the tree
	value = s;
	weight = t;
}

HNode::HNode(HNode* l, HNode* r) {
	//The two things being passed are the left and right node pointers
	//These are the inner nodes on the tree
	//Working from the Visual Studios 2015 IDE this output will give me the exact opposite
	//of what it's supposed to be. On Linux, it looks okay though which meets requirements
	left = l;
	right = r;
	//The weight is determined by the sum of the left and right 
	weight = left->weight + right->weight;
}

#endif
