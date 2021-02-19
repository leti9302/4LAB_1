#pragma once
#include"Iterator.h"
#include<list>

class RB_Tree
{
private:
	class Node
	{
	public:
		Node(int key, int value, char color = 'r', Node* left = nullptr, Node* right = nullptr, Node* parent = nullptr) {
			this->key = key;
			this->value = value;
			this->color = color;
			this->left = left;
			this->right = right;
			this->parent = parent;
		};
		~Node() {};

		int key;
		int value;
		char color;
		Node* left;
		Node* right;
		Node* parent;
	};

	Node* root;
	Node* nil;
public:
	RB_Tree();
	~RB_Tree();

	void insert(int key, int value);
	void insertRecovery(Node*);
	void leftRotate(Node*);
	void rightRotate(Node*);
	void remove(int);
	void removeRecovery(Node*);
	int find(int);
	void clear();
	std::list <int> get_keys();
	std::list <int> get_values();
	char color(int);

	class Queue
	{
	private:
		class QueueNode//Class for the QueueNode of the Queue
		{
		public:
			QueueNode(Node* elem, QueueNode* next = nullptr)
			{
				this->elem = elem;
				this->next = next;
			};
			~QueueNode() {};

			Node* elem;
			QueueNode* next;
		};
		QueueNode* first; //Top element of the Queue
		QueueNode* last;
	public:
		Queue();
		~Queue();

		void enqueue(Node*);
		Node* dequeue();
		bool isEmpty();
		Node* peek();
	};

	Iterator* create_bft_iterator();
	class bftIterator : public Iterator {
	public:
		bftIterator(Node* start);
		bool has_next() override;
		int next(char flag) override;
	private:
		Queue* queue;
	};
};