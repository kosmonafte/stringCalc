// 23.02.23_4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
void separator(int arr[], int size, int*& ptr1, int& size1, int*& ptr2, int& size2, int*& ptr3, int& size3);
void printArray(int* ptr, int size);
int main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(0));
	int* ptr1 = nullptr, * ptr2 = nullptr, * ptr3 = nullptr, size1 = 0, size2 = 0, size3 = 0;
	int stArray[30];
	for (int i = 0; i < 30; i++) {
		stArray[i] = rand() % 200 - 100;
	}
	//Нули выпадают очень редко, поэтому для наглядности добавил рандом нулей
	int rnd = rand() % 10;
	for (int i = 0; i < rnd; i++) {
		stArray[rand() % 30] = 0;
	}
	for (int i = 0; i < 30; i++) {
		cout << stArray[i] << " ";
	}
	cout << endl << endl;
	separator(stArray, 30, ptr1, size1, ptr2, size2, ptr3, size3);
	printArray(ptr1, size1);
	printArray(ptr2, size2);
	printArray(ptr3, size3);
}
void printArray(int* ptr, int size) {
	if (size == 0) {
		cout << "В массиве нет элементов";
	}
	else {
		if (ptr[0] < 0) {
			cout << "Массив с отрицательными элементами имеет " << size << " элементов: " << endl;
		}
		else if (ptr[0] > 0) {
			cout << "Массив с положительными элементами имеет " << size << " элементов: " << endl;
		}
		else {
			cout << "Массив с нулевыми элементами имеет " << size << " элементов: " << endl;
		}
		for (int i = 0; i < size; i++) {
			cout << ptr[i] << " ";
		}
	}
	cout << endl << endl;
}
void separator(int arr[], int size, int*& ptr1, int& size1, int*& ptr2, int& size2, int*& ptr3, int& size3) {
	int plus = 0, minus = 0, zero = 0;
	for (int i = 0; i < size; i++) {
		if (arr[i] < 0) {
			minus++;
		}
		else if (arr[i] == 0) {
			zero++;
		}
		else {
			plus++;
		}
	}
	ptr1 = new int[minus];
	ptr2 = new int[zero];
	ptr3 = new int[plus];
	minus = 0; zero = 0; plus = 0;
	for (int i = 0; i < size; i++) {
		if (arr[i] < 0) {
			ptr1[minus] = arr[i];
			minus++;
		}
		else if (arr[i] == 0) {
			ptr2[zero] = arr[i];
			zero++;
		}
		else {
			ptr3[plus] = arr[i];
			plus++;
		}
	}
	size1 = minus;
	size2 = zero;
	size3 = plus;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
