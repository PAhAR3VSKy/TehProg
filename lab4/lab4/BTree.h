#pragma once
#include <fstream>
#include <iostream>
#include "BTreeStructure.h"
#include "time.h"
using namespace std;
template <class T>
class BTree
{
public:
	BTree();

	void Init(int n, int m, const char* fileName); 
	void OutFile(); 
	T Insert(T data, int position); 
	void Del(T data, int position); 
	void Pack(); 

private:
	const char* File_Name; 
	int Size; 
	int ListSize;
	int IndexNumber;
	void* find(T data); 


};

template <class T>
BTree<T>::BTree()
{
	this->Size = 0;
	this->IndexNumber = 0;
	this->File_Name = nullptr;
}

template <class T>
void BTree<T>::Init(int n, int m, const char* fileName)
{
	srand(time(NULL));
	this->File_Name = fileName;
	short int LenghtType = sizeof(T);
	void* PointerDelete = nullptr;
	int SizeMain = 2 * n;
	int SizeChild = 2 * m + 1;
	this->ListSize = SizeMain;
	this->Size = SizeChild + 1;
	BTreeStructure<T> BMain;
	BMain.Init(SizeMain, nullptr, (void*)1, IndexNumber);
	IndexNumber++;
	BTreeStructure<T>* BChild = new BTreeStructure<T>[SizeChild];

	for (int i = 0; i < SizeChild; i++)
	{
		BChild[i].Init(SizeMain, (void*)1, (void*)(100 + rand() % 9000), IndexNumber);
		IndexNumber++;
	}

	fstream file(File_Name, ios::binary | ios::out);

	if (!file.is_open())
		return;

	void* MainPointer = BMain.Get_Point();

	file.write((char*)&SizeMain, sizeof(int));
	file.write((char*)&SizeChild, sizeof(int));
	file.write((char*)&LenghtType, sizeof(short int));
	file.write((char*)&MainPointer, sizeof(void*));

	file.write((char*)&BMain, sizeof(BTreeStructure<T>));

	for (int i = 0; i < SizeChild; i++)
	{
		file.write((char*)&BChild[i], sizeof(BTreeStructure<T>)); // write list structure in file
	}

	file.close();
}

template <class T>
void read(const char* path, int pos, int type)
{
	T* test = new T;

	fstream file(path, ios::binary | ios::in | ios::out);

	if (!file.is_open())
		return;

	file.seekg(pos, ios_base::beg);
	file.read((char*)test, type);

	cout << *test << endl;

	file.close();
}
template<class T>
inline void BTree<T>::OutFile()
{
	cout << "#########################" << endl;

	cout << "Размер корня: ";
	read<int>(File_Name, 0, sizeof(int));

	cout << "Размер наследника: ";
	read<int>(File_Name, 4, sizeof(int));

	cout << "Длина типа: ";
	read<short int>(File_Name, 8, sizeof(short int));

	cout << "Корневой указатель: ";
	read<void*>(File_Name, 10, sizeof(void*));
	cout << endl;
	fstream file(File_Name, ios::binary | ios::in);

	BTreeStructure<T> tmpRoot; 
	int positionRoot = 14;
	file.seekg(positionRoot, ios::beg);
	file.read((char*)&tmpRoot, sizeof(BTreeStructure<T>));
	tmpRoot.Get_Inf();

	for (int i = 1; i < Size; i++)
	{
		BTreeStructure<T> tmp; 
		int position = 14 + sizeof(BTreeStructure<T>) * i;
		file.seekg(position, ios::beg);
		file.read((char*)&tmp, sizeof(BTreeStructure<T>));

		tmp.Get_Inf();
	}

	cout << "#########################" << endl;

	file.close();
}

template<class T>
T BTree<T>::Insert(T value, int position)
{
	BTreeStructure<T> temp;

	fstream file(File_Name, ios::binary | ios::out | ios::in);

	int pos = 14 + sizeof(BTreeStructure<T>) * position;
	file.seekg(pos, ios::beg);

	file.read((char*)&temp, sizeof(BTreeStructure<T>));
	file.close();

	for (int i = 0; i < temp.Get_Size(); i++)
	{
		if (temp.Get_Tag(i) == true)
		{
			temp.Set_Value(value, i);
			file.open(File_Name, ios::binary | ios::out | ios::in);

			file.seekg(pos, ios::beg);
			file.write((char*)&temp, sizeof(BTreeStructure<T>));

			file.close();
			break;
		}
		else
		{
			if (temp.Set_Value(value) == temp.Get_Size())
			{
				BTreeStructure<T> BNew;
				BNew.Init(ListSize, temp.Get_SelfPoint(), (void*)(100 + rand() % 9000), IndexNumber);
				IndexNumber++;
				BNew.Set_Value(value, 0);

				temp.Set_Entries();

				file.open(File_Name, ios::binary | ios::out | ios::in);
				int NewPos = 14 + Size * sizeof(BTreeStructure<T>);
				file.seekg(NewPos, ios::beg);
				file.write((char*)&BNew, sizeof(BTreeStructure<T>));

				file.seekg(pos, ios::beg);
				file.write((char*)&temp, sizeof(BTreeStructure<T>));

				Size++;

				file.seekg(4, ios::beg);
				file.write((char*)&Size, sizeof(int));

				file.close();
				break;
			}

			file.open(File_Name, ios::binary | ios::out | ios::in);

			file.seekg(pos, ios::beg);
			file.write((char*)&temp, sizeof(BTreeStructure<T>));

			file.close();
			break;
		}

	}

	return value;
}

template<class T>
inline void BTree<T>::Del(T data, int position)
{
	BTreeStructure<T> temp;

	fstream file(File_Name, ios::binary | ios::out | ios::in);

	int pos = 14 + sizeof(BTreeStructure<T>) * position;
	file.seekg(pos, ios::beg);

	file.read((char*)&temp, sizeof(BTreeStructure<T>));
	file.close();

	for (int i = 0; i < temp.Get_Size(); i++) {
		if (temp.Get_Value(i) == data) {

			temp.Set_Tag(true, i);
		}
	}
	file.open(File_Name, ios::binary | ios::out | ios::in);
	file.seekg(pos, ios::beg);

	file.write((char*)&temp, sizeof(BTreeStructure<T>));
	file.close();

	if (temp.Get_Delete() > ListSize / 2)
	{
		temp.Set_List_DelTag(true);

		BTreeStructure<T> tempTop;
		BTreeStructure<T> tempDown;

		int TopPosition = 0;
		int DownPosition = 0;

		for (int i = 0; i < Size; i++) 
		{ 

			file.open(File_Name, ios::binary | ios::out | ios::in);

			int tempPos = 14 + sizeof(BTreeStructure<T>) * i;

			file.seekg(tempPos, ios::beg);
			file.read((char*)&tempTop, sizeof(BTreeStructure<T>));

			if (tempTop.Get_SelfPoint() == temp.Get_Point())
			{
				TopPosition = tempPos;
				file.close();
				break;
			}

			file.close();
		}

		for (int i = 0; i < Size; i++) 
		{ 

			file.open(File_Name, ios::binary | ios::out | ios::in);

			int tempPos = 14 + sizeof(BTreeStructure<T>) * i;

			file.seekg(tempPos, ios::beg);
			file.read((char*)&tempDown, sizeof(BTreeStructure<T>));

			if (tempDown.Get_Point() == temp.Get_SelfPoint())
			{
				DownPosition = tempPos;
				file.close();
				break;
			}
			else
			{
				DownPosition = -1;
			}

			file.close();
		}

		int tempcount = 0;

		for (int i = 0; i < temp.Get_Size(); i++) {

			if (temp.Get_Tag(i) == false) {
				tempcount++;
			}
		}

		for (int i = 0; i < (tempcount / 2 + tempcount % 2); i++)
		{
			for (int j = 0; j < temp.Get_Size(); j++) {
				if (temp.Get_Tag(j) == false) {

					tempTop.Set_Value(temp.Get_Value(j));
					temp.Set_Tag(true, j);

				}
			}
		}

		if (DownPosition != -1)
		{

			for (int i = 0; i < (tempcount / 2); i++)
			{
				for (int j = 0; j < temp.Get_Size(); j++) 
				{

					if (temp.Get_Tag(j) == false) {
						tempDown.Set_Value(temp.Get_Value(j));
						temp.Set_Tag(true, j);
					}

				}
			}
		}
		else
		{
			for (int i = 0; i < (tempcount / 2); i++)
			{
				for (int j = 0; j < temp.Get_Size(); j++) 
				{

					if (temp.Get_Tag(j) == false) {
						tempTop.Set_Value(temp.Get_Value(j));
						temp.Set_Tag(true, j);

					}
				}
			}
		}

		tempDown.Set_Point(tempTop.Get_SelfPoint());
		temp.Set_Point(nullptr);
		file.open(File_Name, ios::binary | ios::out | ios::in);


		file.seekg(TopPosition, ios::beg);
		file.write((char*)&tempTop, sizeof(BTreeStructure<T>));

		int posTemp = 14 + sizeof(BTreeStructure<T>) * position;
		file.seekg(posTemp, ios::beg);
		file.write((char*)&temp, sizeof(BTreeStructure<T>));

		if (DownPosition != -1) {

			file.seekg(DownPosition, ios::beg);
			file.write((char*)&tempDown, sizeof(BTreeStructure<T>));

		}

		file.close();
	}
}

template<class T>
inline void BTree<T>::Pack()
{

	BTreeStructure<T>* tempArr = new BTreeStructure<T>[Size - 1];
	fstream file;

	for (int i = 0; i < (Size - 1); i++) {

		file.open(File_Name, ios::binary | ios::out | ios::in);
		int pos = 14 + sizeof(BTreeStructure<T>) * (i + 1);

		file.seekg(pos, ios::beg);
		file.read((char*)&tempArr[i], sizeof(BTreeStructure<T>));

		file.close();
	}

	for (int i = 0; i < (Size - 2); i++) {
		for (int j = 0; j < (Size - 1); j++) {
			if (tempArr[i].Get_List_DelTag() == true) {
				BTreeStructure<T> tmp = tempArr[i];
				tempArr[i] = tempArr[i + 1];
				tempArr[i + 1] = tmp;
			}

		}

	}


	file.open(File_Name, ios::binary | ios::out | ios::in);

	for (int i = 0; i < (Size - 1); i++) {

		int pos = 14 + sizeof(BTreeStructure<T>) * (i + 1);

		file.seekg(pos, ios::beg);
		file.write((char*)&tempArr[i], sizeof(BTreeStructure<T>));
	}

	file.close();
	return;
}