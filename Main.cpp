#include <iomanip>
#include <iostream>
#include "Heap.h"
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	Heap A;
	cout << "Ввод кучи. 0-конец заполнения\n";
	while (1)
	{
		int data;
		cin >> data; cout << endl << endl;
		if (data == 0)
			break;
		A.insert(data); 
		cout << "--------------------------------------------------\n"; 
		A.print(A.root, 0); 
		cout  << "--------------------------------------------------\n" << endl;
	}

	A.print(A.root, 0);
	
	int to_remove; 
	cout << "Удалить элемент/ы с ключом:\n";
		while (1)
		{
			cin >> to_remove; cout << endl << endl;
			if (to_remove == 0)
				break;
			A.req_remove(to_remove, A.root);
			cout << "--------------------------------------------------\n";
			A.print(A.root, 0);
			cout << "--------------------------------------------------\n" << endl;
			if (!A.root) break;
		}
	cout << endl;
	A.print(A.root, 0);
	if (A.root)
	{
	cout << endl << endl<<"Depth traverse: ";
	A.depth_first_traverse();
	cout << endl<<"Breath traverse: ";
	A.breadth_first_traverse();
	}

	system("pause");
	return 0;
 }