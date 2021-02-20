#pragma once
#include<list>
#include<iostream>
using namespace std;

template <class T>
class RB_Tree
{
private:
	template<typename T>
	class Node
	{
	public:
		Node(T key, T value, Node<T>* left = nullptr, Node<T>* right = nullptr, Node<T>* parent = nullptr, char color = 'r') {
			this->key = key;
			this->value = value;
			this->color = color;
			this->left = left;
			this->right = right;
			this->parent = parent;
		};
		~Node() {};

		T key;
		T value;
		char color;
		Node<T>* left;
		Node<T>* right;
		Node<T>* parent;
	};

	Node<T>* root;
	Node<T>* nil;
public:
	RB_Tree();
	~RB_Tree();

	void insert(T key, T value);
	void insertRecovery(Node<T>*);
	void leftRotate(Node<T>*);
	void rightRotate(Node<T>*);
	void remove(T);
	void removeRecovery(Node<T>*);
	T find(T);
	void clear();
	std::list<T> get_keys();
	void get_next_key(std::list<T>*,Node<T>* current);
	std::list<T> get_values();
	void get_next_value(std::list<T>*, Node<T>* current);
	void print(Node<T>* current = nullptr);
	char color(T);
};

template<typename T>
RB_Tree<T>::RB_Tree()
{
	nil = new Node<T>(' ', ' ', nullptr, nullptr, nullptr, 'b');
	root = nil;
}

template<typename T>
RB_Tree<T>::~RB_Tree()
{
	clear();
	delete root;
}

template<typename T>
void RB_Tree<T>::insert(T key, T value)
{
	if (root == nil)
	{
		root = new Node<T>(key, value, nil, nil, nullptr, 'b');
		return;
	}
	else {
		Node<T>* current = root;
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
			current->left = new Node<T>(key, value, nil, nil, current, 'r');
			insertRecovery(current->left);
		}
		else
		{
			current->right = new Node<T>(key, value, nil, nil, current, 'r');
			insertRecovery(current->right);
		}
	}
}

template<typename T>
void RB_Tree<T>::insertRecovery(Node<T>* newNode)
{
	Node<T>* p, * gP;
	while (newNode->parent && newNode->parent->color == 'r')
	{
		p = newNode->parent;
		gP = p->parent;
		if (p == gP->left)
		{
			if (gP->right->color == 'r') {
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
				newNode->parent->color = 'b';
				newNode->parent->parent->color = 'r';
				rightRotate(newNode->parent->parent);
			}
		}
		else
		{
			if (gP->left->color == 'r')
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
				newNode->parent->color = 'b';
				newNode->parent->parent->color = 'r';
				leftRotate(newNode->parent->parent);
			}
		}
	}
	root->color = 'b';
}

template<typename T>
void RB_Tree<T>::leftRotate(Node<T>* x)
{
	if (x->right == nil) return;
	else
	{
		Node<T>* y = x->right;
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

template<typename T>
void RB_Tree<T>::rightRotate(Node<T>* y)
{
	if (y->left == nil) return;
	else
	{
		Node<T>* x = y->left;
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

template<typename T>
void RB_Tree<T>::remove(T key)
{
	Node<T>* current = root;
	Node<T>* x, * nodeToBeDeleted, * min;
	while (current != nil)
	{
		if (current->key == key) break;
		else if (current->key > key)
			current = current->left;
		else current = current->right;
	}

	if (current == nil) {
		throw "There is no such element!";
	}

	else
	{
		nodeToBeDeleted = current;
		char originalColor = nodeToBeDeleted->color;
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

template<typename T>
void RB_Tree<T>::removeRecovery(Node<T>* x)
{
	Node<T>* bro = nil;
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

template<typename T>
T RB_Tree<T>::find(T key)
{
	Node<T>* current = root;
	while (current != nil)
	{
		if (current->key == key)
			return current->value;
		else if (current->key > key)
			current = current->left;
		else current = current->right;
	}
	throw "There is no such element!";
}

template<typename T>
void RB_Tree<T>::clear()
{
	while (root != nil) remove(root->key);
}

template<typename T>
std::list<T> RB_Tree<T>::get_keys()
{
	std::list<T>keys;
	Node<T>* current = root;
	get_next_key(&keys, current);
	return keys;
}

template<class T>
void RB_Tree<T>::get_next_key(std::list<T>* keys, Node<T>* current)
{
	if (current != nil)
	{
		keys->push_back(current->key);
		get_next_key(&*keys, current->left);
		get_next_key(&*keys, current->right);
	}
}

template<typename T>
std::list<T> RB_Tree<T>::get_values()
{
	std::list<T>values;
	Node<T>* current = root;
	get_next_value(&values, current);
	return values;
}

template<typename T>
void RB_Tree<T>::get_next_value(std::list<T>* values, Node<T>* current)
{
	if (current != nil)
	{
		values->push_back(current->value);
		get_next_value(&*values, current->left);
		get_next_value(&*values, current->right);
	}
}

template<class T>
void RB_Tree<T>::print(Node<T>* current)
{
	if (root == nil)
	{
		cout << "Tree is empty.";
		return;
	}
	else if (current == nullptr) current = root;
	cout << "Key: " << current->key << "; value: " << current->value<<"; color: "<<current->color;
	if (!current->parent) cout << "; parent: no parent";
	else cout << "; parent: " << current->parent->key;
	if (current->left == nil) cout << "; left-child: nil";
	else cout << "; left-child: "<<current->left->key;
	if (current->right == nil) cout << "; right-child: nil";
	else cout << "; right-child: " << current->right->key;
	cout << '\n';
	if (current->left != nil) print(current->left);
	if (current->right != nil) print(current->right);
}

template<typename T>
char RB_Tree<T>::color(T key)
{
	Node<T>* current = root;
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