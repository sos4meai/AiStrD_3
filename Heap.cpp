#include "Heap.h"
#include <stdexcept> 
#include <string> 
#include <iostream> 
#include <windows.h> 
using namespace std;

Heap::Heap()
{
	root = nullptr;
	size = 0;
	last = nullptr;
}


Heap::~Heap()
{
	delete_heap(root);
}



bool Heap::contains(Node* root, int key)
{
	if (root)
	{
		if (root->key == key)
			return true;
		return (contains(root->left, key) || contains(root->right, key));
	}
	return false;
}

void Heap::depth_first_traverse()
{
	Iterator* diterator = Heap::depthcreate_iterator();
		while (diterator->has_next())
		{
			std::cout << " " << diterator->next();
		}
}

void Heap::breadth_first_traverse()
{
	Iterator* biterator1 = Heap::breadthcreate_iterator();

	while (biterator1->has_next())
	{
		std::cout << " " << biterator1->next();
	}
}

void Heap::delete_heap(Node* node)
{
	if (node)
	{
		delete_heap(node->left);
		delete_heap(node->right);
		if (node == root)
			root = nullptr;
		delete node;
		/*node->left = nullptr;
		node->right = nullptr;
		node->parent = nullptr;*/
		size--;
	}
}

void Heap::insert(int key)
{

	Node *elem = new Node;
	elem->key = key;
	elem->prev_last = last;
	if (root == nullptr)
	{
		root = elem;
		last = root;
		size++;
		return;
	}
	Node *current = last;
	while (current->parent != nullptr && current == current->parent->right)
		current = current->parent;

	if (current->parent != nullptr)
	{
		if (current->parent->right != nullptr)//у родителя есть правый узел 
		{
			current = current->parent->right;//переходим на него 
			while (current->left != nullptr)//если у того есть левый 
				current = current->left;
		}

		else current = current->parent;//нет правого узла,вставим в правый 
	}
	else
	{ //мы в корне 
		while (current->left != nullptr)
			current = current->left;
	}

	if (current->left != nullptr)//вставка вправо 
	{
		current->right = elem;
		last = current->right;
	}

	else
	{
		current->left = elem;
		last = current->left;
	}
	elem->parent = current;
	elem->left = nullptr;
	elem->right = nullptr;

	size++;
	sort(last);
}


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void Heap::req_remove(int key, Node* node)
{
	if (node&&contains(node, key))
	{
		req_remove(key, node->left);
		req_remove(key, node->right);
		
		if (size == 1)
		{
			Heap::delete_heap(root);
			return;
		}

		if (node->key == key)
		{
			cout << "Find! Parent:"<< node->parent->key;
			node->key = last->key;
			if (last == last->parent->left)
				last->parent->left = nullptr;
			if (last == last->parent->right)
				last->parent->right = nullptr;
			last = last->prev_last;
			size--;
		}

	}
	else return;

}

void Heap::print(Node* root, int level)
{
	if (root)
	{
		print(root->right, level + 1);
		for (int i = 0; i < level; i++) cout << "    ";
		cout << root->key << endl;
		print(root->left, level + 1);
	}
}

void Heap::sort(Node* elem)
{
	while (elem->parent != nullptr && elem->key > elem->parent->key) {
		int temp = elem->key;

		if (elem->key > elem->parent->key) {
			elem->key = elem->parent->key;
			elem->parent->key = temp;
		}

		elem = elem->parent;
	}
}

/*************************************************************************/

Iterator* Heap::breadthcreate_iterator()
{
	return new breadthIterator(this->root);
}
int Heap::breadthIterator::next()
{
	if (q.get_size() == 0)
		q.push_back(current);
	current = q.head->data;
	q.pop_front();
	const int key = current->key;
	if (current->left) {
		q.push_back(current->left);
	}
	if (current->right) {
		q.push_back(current->right);
	}
	return key;
}

bool Heap::breadthIterator::has_next()
{
	return (q.get_size() || current->left != nullptr && current->right != nullptr);
}

int Heap::depthIterator::next()
{
	if (current != nullptr) {
		int key = current->key;
		if (current->right != nullptr)
			s.push_front(current);
		current = current->left;
		return key;
	}
	if (current == nullptr) {
		current = s.head->data;
		s.pop_front();
		current = current->right;
		next();
	}
}

bool Heap::depthIterator::has_next()
{
	return (s.get_size() || current != nullptr);
}


Iterator * Heap::depthcreate_iterator()//в глубину 
{
	return new depthIterator(this->root);
}

/*************************************************************************/

