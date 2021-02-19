#include "RB_Tree.h"
#include <stdexcept>

Iterator* RB_Tree::create_bft_iterator()
{
	return new bftIterator(root);
}

RB_Tree::bftIterator::bftIterator(Node* start)
{
	queue = new Queue();
	queue->enqueue(start);
}

bool RB_Tree::bftIterator::has_next()
{
	return !queue->isEmpty();
}

int RB_Tree::bftIterator::next(char flag)
{
	if (!has_next()) throw std::out_of_range("No more elements!");
	Node* current = queue->dequeue();
	if ((current->left->left != nullptr) && (current->left->right!=nullptr)) queue->enqueue(current->left);
	if ((current->right->left != nullptr) && (current->right->right != nullptr)) queue->enqueue(current->right);
	if (flag == 'k') return current->key;
	else return current->value;
}