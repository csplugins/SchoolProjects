#include "Palindrome.hpp"
//This is the creation of the Linked List Stack
struct StackNode
{
	int data;
	StackNode* next;
	StackNode(const int& num): data(num), next(0) {}
};

class LLStack
{
public:
	StackNode* top;
	int size;

	LLStack();
	~LLStack();
	void push(const int&);
	bool pop(int&);
	bool isEmpty();
};
//The constructor makes the Stack empty
LLStack::LLStack()
{
	top = 0;
	size = 0;
}
//The destructor will empty out the stack
LLStack::~LLStack()
{
	int temp;
	while (!isEmpty())
	{
		pop(temp);
	}
}
//Push will put an item at the top making it the new first item to be pushed
void LLStack::push(const int& num)
{
	StackNode* newNode = new StackNode(num);
	newNode->next = top;
	top = newNode;
}
//Pop will pop from the Stack popping the last one that was added (first in, last out)
bool LLStack::pop(int& num)
{
	if (isEmpty())
		return false;

	num = top->data;
	StackNode* temp = top;
	top = top->next;
	delete temp;
	return true;
}
//Check to see if the Stack contains any nodes
bool LLStack::isEmpty()
{
	return top == 0;
}
//This is the creation of the Array Queue
class ArrayQueue
{
public:
	int front, rear, capacity, size;
	int* data;

	ArrayQueue(const int&);
	~ArrayQueue();

	bool enqueue(const int&);
	bool dequeue(int& num);
	bool isEmpty();
};
//The contructor initializes the Array Queue and has it start off empty
ArrayQueue::ArrayQueue(const int& capacity)
{
	data = new int[capacity];
	front = rear = size = 0;
	this->capacity = capacity;
}
//The destructor safely destroys the items in the queue
ArrayQueue::~ArrayQueue()
{
	delete data;
}
//Enqueue adds an item to the end of the queue
bool ArrayQueue::enqueue(const int& num)
{
	data[rear] = num; // write where rear is
	++rear %= capacity; // move read, allowing for past the end condition
	++size;
	return true;
}
//Dequeue takes the item that has been inside the queue longest out first (first in first out)
bool ArrayQueue::dequeue(int& num)
{
	num = data[front];
	++front %= capacity;
	--size;
	return true;
}
//Check to see if the queue contains any items
bool ArrayQueue::isEmpty()
{
	return size == 0;
}
//This is the recursive function to add alphanumeric characters to both a queue and a stack
void enqueNpush(const std::string& s, ArrayQueue* aq, LLStack* lls){
	if (!s[0])
		return;
	if ((s[0] > 64 && s[0] < 91) || (s[0] > 96 && s[0] < 123) || (s[0] > 47 && s[0] < 58)){
		aq->enqueue(s[0]);
		lls->push(s[0]);
	}
	return enqueNpush(s.substr(1), aq, lls);
}
//This is the recursive function to remove alpha numeric characters from the stack and queue and compare the chars
int dequeNpop(ArrayQueue* aq, LLStack* lls){
	int temp1, temp2;
	if (aq->isEmpty())
		return 0;
	aq->dequeue(temp1);
	lls->pop(temp2);
	if (temp2 > 96)
		temp2 -= 32;
	if (temp1 > 96)
		temp1 -= 32;
	if (temp1 == temp2)
		return 1 + dequeNpop(aq, lls);
	else return 0;
}
//This is the test_string function which creates a stack and queue, pushes and enques,
//compares the pop and dequeue, and determines if a string is a palindrome or not
int Palindrome::test_string(const std::string& s){
	int count,temp;
	ArrayQueue* aq = new ArrayQueue(s.length());
	LLStack* lls = new LLStack();
	enqueNpush(s, aq, lls);
	count = aq->size;
	temp = dequeNpop(aq, lls);
	if (aq->isEmpty() || temp == count){
	  delete aq;
	  delete lls;
	  return -1;
	}
	delete aq;
	delete lls;
	return temp;
}
