#pragma once
#include "Iterator.h"
#include <stack> 
#include <queue> 

class Heap
{
public:
	Heap();
	~Heap();
	
	
	
	class Node
	{
	public:
		int key;
		Node* parent;
		Node* left;
		Node* right;
		Node* prev_last;
		Node(int key = 0, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr, Node* prev_last=nullptr)
		{
			this->key = key;
			this->parent = parent;
			this->left = left;
			this->right = right;
			this->prev_last = prev_last;
		};
	};




	class List
	{
	
	public:
		class Element
		{
		public:
			Node* data;
			Element* next;
			Element(Node* data = nullptr, Element* next = nullptr)
			{
				this->data = data;
				this->next = next;
			}

		};
		Element* head;
		Element* tail;
		size_t size;

	
		List();
		~List();

		void push_back(Node* data);
		void push_front(Node* data);
		void pop_back();
		void pop_front();
		size_t get_size();
		void clear();
		bool isEmpty();

	};



	class depthIterator : public Iterator
	{
	public:
		depthIterator(Node * root)
		{
			current = root;
		};
		int next() override;
		bool has_next() override;

	private:
		List s;
		Node * current;
	};

	class breadthIterator : public Iterator
	{
	public:
		breadthIterator(Node * root)
		{
			current = root;
		};
		int next() override;
		bool has_next() override;

	private:
		List q;
		Node * current;
	};

	Node* root;
	Node* last;
	size_t size = 0;


	void insert(int key); // добавление элемента в дерево по ключу
	void req_remove(int key, Node* node); // удаление элемента дерева по ключу
	void sort(Node* elem);
	void delete_heap(Node* root);
	Iterator * breadthcreate_iterator();
	Iterator * depthcreate_iterator();
	void print(Node* root, int level); // красивый вывод дерева в консоль
	bool contains(Node* root, int key); // поиск элемента в дереве по ключу
	void depth_first_traverse();
	void breadth_first_traverse();
};

