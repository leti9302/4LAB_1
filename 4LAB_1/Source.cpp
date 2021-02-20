#include "RB_Tree.h"

void main()
{
	RB_Tree<int>* rb_tree = new RB_Tree<int>();
	rb_tree->insert(33, 1);
	rb_tree->insert(13, 2);
	rb_tree->insert(53, 3);
	list <int> keys;
	list <int> values;
	keys = rb_tree->get_keys();
	values = rb_tree->get_values();
	rb_tree->print();
	delete rb_tree;
}