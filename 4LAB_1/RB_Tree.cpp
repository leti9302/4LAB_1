#include "RB_Tree.h"

RB_Tree::RB_Tree()
{
	nil = new Node(' ', ' ', 'b');
	root = nil;
}

RB_Tree::~RB_Tree()
{
	clear();
}

void RB_Tree::insert(int key, int value)
{
	if (root == nil)
	{
		root = new Node(key, value, 'b', nil, nil);
		return;
	}
	else {
		Node* current = root;
		bool to_right = false;
		while (1)
		{
			if (current->key >= key && current->left != nil)
				current = current->left;
			else if (current->key >= key && current->left == nil)
				break;
			else if (current->key < key && current->right != nil)
				current = current->right;
			else {
				to_right = true;
				break;
			}
		}
		if (to_right == false)
		{
			current->left = new Node(key, value, 'r', nil, nil, current);
			insertRecovery(current->left);
		}
		else
		{
			current->right = new Node(key, value, 'r', nil, nil, current);
			insertRecovery(current->right);
		}
	}
}

void RB_Tree::insertRecovery(Node *newNode)
{
	Node* p, *gP;
	while (newNode != root && newNode->parent->color == 'r' && newNode->color != 'b')
	{
		p = newNode->parent;
		gP = p->parent;
		if (p == gP->left)
		{
			if (gP->right != nullptr && gP->right->color == 'r') { 
				gP->left->color = 'b';
				gP->right->color = 'b';
				gP->color = 'r';
				newNode = gP;
			}
			else {
				if (newNode == p->right)
				{
					newNode = p;
					leftRotate(newNode);
				}
				p->color = 'b';
				gP->color = 'r';
				rightRotate(gP);
			}
		}
		else
		{
			if (gP->left && gP->left->color == 'r')
			{
				gP->left->color = 'b';
				gP->right->color = 'b';
				gP->color = 'r';
				newNode = gP;
			}
			else
			{
				if (p->left == newNode)
				{
					newNode = p;
					rightRotate(newNode);
				}
				p->color = 'b';
				gP->color = 'r';
				leftRotate(gP);
			}
		}
	}
	root->color = 'b';
}

void RB_Tree::leftRotate(Node* x)
{
	if (x->right == nil) return;
	else
	{
		Node* y = x->right;
		if (y->left != nil)
		{
			x->right = y->left;
			y->left->parent = x;
		}
		else x->right = nil;
		if (!x->parent) {
			y->parent = nullptr;
			root = y;
		}
		else
		{
			y->parent = x->parent;
			if (x == x->parent->left) x->parent->left = y;
			else x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}
}

void RB_Tree::rightRotate(Node* y)
{
	if (y->left == nil) return;
	else
	{
		Node* x = y->left;
		if (x->right != nil)
		{
			y->left = x->right;
			x->right->parent = y;
		}
		else y->left = nil;
		if (!y->parent)
		{
			x->parent = nullptr;
			root = x;
		}
		else
		{
			x->parent = y->parent;
			if (y == y->parent->right) y->parent->right = x;
			else y->parent->left = x;
		}
		x->right = y;
		y->parent = x;
	}
}

void RB_Tree::remove(int key)
{
	Node* current = root;
	Node* x, *nodeToBeDeleted, *min;
	while (current != nil)
	{
		if (current->key == key) break;
		else if (current->key > key)
			current = current->left;
		else current = current->right;
	}

	if (current == nil) {
		throw "There is no such element!:";
	}

	else
	{
		nodeToBeDeleted = current;
		int originalColor = nodeToBeDeleted->color;
		if (current->left == nil) {
			x = current->right;
			if (current->parent == nullptr) {
				root = current->right;
			}
			else if (current == current->parent->left) {
				current->parent->left = current->right;
			}
			else {
				current->parent->right = current->right;
			}
			current->right->parent = current->parent;
		}
		else if (current->right == nil) {
			x = current->left;
			if (current->parent == nullptr) {
				root = current->left;
			}
			else if (current == current->parent->left) {
				current->parent->left = current->left;
			}
			else {
				current->parent->right = current->left;
			}
			current->left->parent = current->parent;
		}
		else {
			min = current->right;
			while (min->left != nil) min = min->left;
			nodeToBeDeleted = min;
			originalColor = nodeToBeDeleted->color;
			x = nodeToBeDeleted->right;
			if (nodeToBeDeleted->parent == current) {
				x->parent = nodeToBeDeleted;
			}
			else {
				if (nodeToBeDeleted->parent == nullptr) {
					root = nodeToBeDeleted->right;
				}
				else if (nodeToBeDeleted == nodeToBeDeleted->parent->left) {
					nodeToBeDeleted->parent->left = nodeToBeDeleted->right;
				}
				else {
					nodeToBeDeleted->parent->right = nodeToBeDeleted->right;
				}
				nodeToBeDeleted->right->parent = nodeToBeDeleted->parent;
				nodeToBeDeleted->right = current->right;
				nodeToBeDeleted->right->parent = nodeToBeDeleted;
			}

			if (current->parent == nullptr) {
				root = nodeToBeDeleted;
			}
			else if (current == current->parent->left) {
				current->parent->left = nodeToBeDeleted;
			}
			else {
				current->parent->right = nodeToBeDeleted;
			}
			nodeToBeDeleted->parent = current->parent;
			nodeToBeDeleted->left = current->left;
			nodeToBeDeleted->left->parent = nodeToBeDeleted;
			nodeToBeDeleted->color = current->color;
		}
		delete current;
		if (originalColor == 'b') {
			removeRecovery(x);
		}
	}
}

void RB_Tree::removeRecovery(Node* x)
{
	Node* bro = nil;
	while (x != root && x->color == 'b')
	{
		if (x->parent->left == x)
		{
			bro = x->parent->right;
			if (bro->color == 'r')
			{
				bro->color = 'b';
				x->parent->color = 'r';
				leftRotate(x->parent);
				bro = x->parent->right;
			}
			if (bro->left->color == 'b' && bro->right->color == 'b')
			{
				bro->color = 'r';
				x = x->parent;
			}
			else
			{
				if (bro->right->color == 'b')
				{
					bro->left->color = 'b';
					bro->color = 'r';
					rightRotate(bro);
					bro = x->parent->right;
				}
				bro->color = x->parent->color;
				x->parent->color = 'b';
				bro->right->color = 'b';
				leftRotate(x->parent);
				x = root;
			}
		}
		else
		{
			bro = x->parent->left;
			if (bro->color == 'r')
			{
				bro->color = 'b';
				x->parent->color = 'r';
				rightRotate(x->parent);
				bro = x->parent->left;
			}
			if (bro->left->color == 'b' && bro->right->color == 'b')
			{
				bro->color = 'r';
				x = x->parent;
			}
			else
			{
				if (bro->left->color == 'b')
				{
					bro->right->color = 'b';
					bro->color = 'r';
					leftRotate(bro);
					bro = x->parent->left;
				}
				bro->color = x->parent->color;
				x->parent->color = 'b';
				bro->left->color = 'b';
				rightRotate(x->parent);
				x = root;
			}
		}
	}
	x->color = 'b';
	root->color = 'b';
}

int RB_Tree::find(int key)
{
	Node* current = root;
	while (current != nil)
	{
		if (current->key == key)
			return current->value;
		else if (current->key > key)
			current = current->left;
		else current = current->right;
	}
	throw "There is no such element!:";
}

void RB_Tree::clear()
{
	while (root!=nil) remove(root->key);
	delete root;
}

std::list <int> RB_Tree::get_keys()
{
	std::list <int> keys;
	Iterator* bft_iterator = this->create_bft_iterator();
	while (bft_iterator->has_next())
	{
		keys.push_front(bft_iterator->next('k'));
	}
	return keys;
}

std::list<int> RB_Tree::get_values()
{
	std::list <int> values;
	Iterator* bft_iterator = this->create_bft_iterator();
	while (bft_iterator->has_next())
	{
		values.push_front(bft_iterator->next('v'));
	}
	return values;
}

char RB_Tree::color(int key)
{
	Node* current = root;
	while (current != nil)
	{
		if (current->key == key) break;
		else if (current->key > key)
			current = current->left;
		else current = current->right;
	}
	if (current != nil) return current->color;
	else return 0;
}