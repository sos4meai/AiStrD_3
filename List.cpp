#include "Heap.h"
#include<iomanip>
#include<iostream>
using namespace std;

Heap::List::List()
{
	head = nullptr;
	tail = nullptr;
	size = 0;
}


Heap::List::~List()
{
	List::clear();
}

void Heap::List::push_back(Node* data)
{
	Element* newElem = new Element(data);
	if (head == nullptr)
		head = newElem;
	else
		tail->next = newElem;
	tail = newElem;
	size++;
}

void Heap::List::push_front(Node* data)
{
	Element *newElem=new Element(data);
	if (head == nullptr)
		tail = newElem;
	else
		newElem->next = head;
	head = newElem;
	size++;
}

void Heap::List::pop_back()
{
	if (head != nullptr)
		if (head != tail)
		{
			Element *new_tail = head;
			while (new_tail->next != tail)
				new_tail = new_tail->next;
			delete tail;
			new_tail->next = nullptr;
			tail = new_tail;
			size--;
		}
		else
		{
			delete head;
			head = nullptr;
			tail = nullptr;
			size--;
		}
	else throw 0;
}

void Heap::List::pop_front()
{
	if (head != nullptr)
		if (head != tail)
		{
			Element *new_head = head->next;
			delete head;
			head = new_head;
			size--;
		}
		else
		{
			delete head;
			head = nullptr;
			tail = nullptr;
			size--;
		}
	else throw 0;
}

size_t Heap::List::get_size()
{
	return size;
}


void Heap::List::clear()
{
	while (head != nullptr)
		List::pop_front();
}

bool Heap::List::isEmpty()
{
	if (head == nullptr)
		return true;
	return false;
}



