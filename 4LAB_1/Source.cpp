#include "RB_Tree.h"
#include<iostream>

void main()
{
	RB_Tree* rb_tree = new RB_Tree();
	rb_tree->insert(55, 1);
	rb_tree->insert(40, 2);
	rb_tree->insert(65, 3);
	rb_tree->insert(60, 4);
	rb_tree->insert(75, 3);
	rb_tree->insert(57, 3);
	rb_tree->remove(40);
	std::list <int> keys;
	keys = rb_tree->get_keys();
	delete rb_tree;
}