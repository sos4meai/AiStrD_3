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
		if (current->parent->right != nullptr)//ó ðîäèòåëÿ åñòü ïðàâûé óçåë 
		{
			current = current->parent->right;//ïåðåõîäèì íà íåãî 
			while (current->left != nullptr)//åñëè ó òîãî åñòü ëåâûé 
				current = current->left;
		}

		else current = current->parent;//íåò ïðàâîãî óçëà,âñòàâèì â ïðàâûé 
	}
	else
	{ //ìû â êîðíå 
		while (current->left != nullptr)
			current = current->left;
	}

	if (current->left != nullptr)//âñòàâêà âïðàâî 
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
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void Heap::siftDown(Node* current)
{
	if (!current)
		return;
	Node* maxChild=nullptr;

	if (!current->left && !current->right)
		return;

	if (current->left&&current->right)
		if (current->left->key >= current->right->key)
			maxChild = current->left;
		else
			maxChild = current->right;
	if (current->left && !current->right)
		maxChild = current->left;
	if (current->right&&!current->left)
		maxChild = current->right;

	if (current->key<maxChild->key)
	{
		int temp = maxChild->key;
		maxChild->key = current->key;
		current->key = temp;
	}
	
	siftDown(current->left);
	siftDown(current->right);

}

void Heap::req_remove(int key, Node* node)
{
	if (node && contains(root, key))
	{

		if (node->key == key)
		{
			if (size == 1)
			{
				Heap::delete_heap(root);
				return;
			}

			node->key = last->key;
			siftDown(node);



			if (last == last->parent->left)
				last->parent->left = nullptr;
			if (last == last->parent->right)
				last->parent->right = nullptr;
			last = last->prev_last;
			size--;

			req_remove(key, node);
		}

		req_remove(key, node->left);
		req_remove(key, node->right);

	}
	else return;

}

void Heap::remove(int key)
{
	req_remove(key, root);
}

void Heap::print(Node* root, int level)
{
	if (root)
	{
		print(root->right, level + 1);
		for (int i = 0; i < level; i++) cout << "    ";
		if (root->parent && root == root->parent->left)
			cout << "\\ L:";
		if (root->parent && root == root->parent->right)
			cout << "/ R:";
		cout << root->key << endl<<endl;
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


Iterator * Heap::depthcreate_iterator()//â ãëóáèíó 
{
	return new depthIterator(this->root);
}

/*************************************************************************/

