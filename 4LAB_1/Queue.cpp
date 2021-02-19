#include "RB_Tree.h"

RB_Tree::Queue::Queue()
{
	first = nullptr;
	last = nullptr;
}

RB_Tree::Queue::~Queue()
{
	while (first != nullptr) dequeue();
	delete first;
}

void RB_Tree::Queue::enqueue(Node* newElem)
{
	if (!isEmpty())
	{
		last->next = new QueueNode(newElem);
		last = last->next;
	}
	else {
		first = new QueueNode(newElem);
		last = first;
	}
}

RB_Tree::Node* RB_Tree::Queue::dequeue()
{
	Node* temp = first->elem;
	first = first->next;
	return temp;
}

bool RB_Tree::Queue::isEmpty()
{
	if (first == nullptr) return true;
	else return false;
}

RB_Tree::Node* RB_Tree::Queue::peek()
{
	return first->elem;
}