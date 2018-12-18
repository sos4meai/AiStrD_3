#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AiStrD_lab3/Heap.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Heap_is_empty)
		{
			Heap heap;
			Assert::IsTrue(heap.root==nullptr);
		}

		TEST_METHOD(insert_heap_isnt_empty)
		{
			Heap heap;
			heap.insert(0);
			Assert::IsTrue(heap.root);
			heap.delete_heap(heap.root);
		}

		TEST_METHOD(insert_increase_size)
		{
			Heap heap;
			heap.insert(0);
			Assert::AreEqual((size_t)1, heap.size);
			heap.delete_heap(heap.root);
		}

		TEST_METHOD(insert_new_element_greater_than_root)
		{
			Heap heap;
			heap.insert(0);
			heap.insert(1);
			Assert::AreEqual(1, heap.root->key);
			heap.delete_heap(heap.root);
		}

		TEST_METHOD(insert_root_greater_than_new_elem)
		{
			Heap heap;
			heap.insert(0);
			heap.insert(-1);
			Assert::AreEqual(0, heap.root->key);
			heap.delete_heap(heap.root);
		}

		TEST_METHOD(delheap_make_heap_empty)
		{
			Heap heap;
			heap.insert(0);
			heap.insert(-1);
			heap.delete_heap(heap.root);
			Assert::IsTrue(!heap.root);
		}

		TEST_METHOD(delheap_size_0)
		{
			Heap heap;
			heap.insert(0);
			heap.insert(-1);
			heap.delete_heap(heap.root);
			Assert::AreEqual((size_t)0, heap.size);
		}

		TEST_METHOD(remove_delete_root)
		{
			Heap heap;
			heap.insert(0);
			heap.remove(0);
			Assert::IsTrue(!heap.root);
		}

		TEST_METHOD(remove_delete_middle_one_elem)
		{
			Heap heap;
			heap.insert(0);
			heap.insert(-1);
			heap.remove(-1);
			Assert::IsFalse(heap.contains(heap.root, -1));
			heap.delete_heap(heap.root);

		}

		TEST_METHOD(remove_delete_middle_elems)
		{
			Heap heap;
			heap.insert(0);
			heap.insert(-1);
			heap.insert(1);
			heap.insert(0);
			heap.insert(-1);
			heap.insert(1);
			heap.remove(1);
			Assert::IsFalse(heap.contains(heap.root, 1));
			heap.delete_heap(heap.root);
		}

		TEST_METHOD(remove_change_size)
		{
			Heap heap;
			heap.insert(0);
			heap.insert(-1);
			heap.insert(1);
			heap.insert(0);
			heap.insert(-1);
			heap.insert(1);
			heap.remove(1);
			Assert::AreEqual((size_t)4, heap.size);
			heap.delete_heap(heap.root);
		}

		TEST_METHOD(contains_true)
		{
			Heap heap;
			heap.insert(0);
			heap.insert(-1);
			heap.insert(1);
			heap.insert(0);
			heap.insert(-2);
			heap.insert(3);
			heap.remove(5);
			Assert::IsTrue(heap.contains(heap.root, 1));
			heap.delete_heap(heap.root);
		}
		/*

		TEST_METHOD(tree_btf_iterator)
		{
			AvlTree* avl = new AvlTree(5);
			avl->Insert(10);
			avl->Insert(0);
			auto* iterator = avl->create_bft_iterator();
			Assert::IsTrue(iterator->has_next() && iterator->next() == 5 && iterator->next() == 0 && iterator->next() == 10 && !iterator->has_next());
		}

		TEST_METHOD(tree_dtf_iterator)
		{
			AvlTree* avl = new AvlTree(5);
			avl->Insert(10);
			avl->Insert(0);
			auto* iterator = avl->create_dft_iterator();
			Assert::IsTrue(iterator->has_next() && iterator->next() == 5 && iterator->next() == 0 && iterator->next() == 10 && !iterator->has_next());
		}


		
		}*/



		TEST_METHOD(contains_false)
		{
			Heap heap;
			heap.insert(0);
			heap.insert(-1);
			heap.insert(1);
			heap.insert(0);
			heap.insert(-1);
			heap.insert(1);
			heap.remove(1);
			Assert::IsFalse(heap.contains(heap.root, 99));
			heap.delete_heap(heap.root);
		}
	};
}