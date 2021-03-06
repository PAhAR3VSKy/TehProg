#pragma once
#include <fstream>
#include <iostream>
#include "List.h"
#include "time.h"
using namespace std;
template <class T>
class ListStructure
{
public:
	ListStructure();
	~ListStructure();

	void init(int size, const char* fileName); //������������� ������ � �����
	void fromFile(); //����� ���������� �� �����
	T insert(T data); //������� �������� � ����
	void del(T data); //�������� �������� �� �����
	void pack(); //���������� �������� � �����

private:
	const char* fileName; //���� � �����
	int size; //������ ������
	int delCounter; //������� ���������� ��������

	void* find(T data); // ���������� ��������� ��� ��������

	List<T>* lst;

	class listInf // ��������� ������
	{
	public:
		bool deleteTag; // ��� ��� ��������
		void* pointer; // ��������� ��������
		T data; // �������� 
		listInf()
		{
			deleteTag = false;
			pointer = nullptr;
			data = T();
		}
		inline void setInf(bool deleteTag, void* pointer, T data)
		{
			this->deleteTag = deleteTag;
			this->pointer = pointer;
			this->data = data;
		}
		inline void getInf()
		{
			cout << "��� ��������: " << deleteTag
				<< " ���������: " << pointer
				<< " ������: " << data << endl;
		}
		inline void setTag(bool Tag)
		{
			this->deleteTag = Tag;
		}
		inline void setPoint(void* point)
		{
			this->pointer = point;
		}
		inline void setData(T data)
		{
			this->data = data;
		}
		inline bool getTag()
		{
			return deleteTag;
		}
		inline void* getPoint()
		{
			return pointer;
		}
		inline T getData()
		{
			return data;
		}
	};
};

template <class T>
ListStructure<T>::ListStructure()
{
	this->size = 0;
	this->delCounter = 0;
	this->fileName = nullptr;
	lst = nullptr;
}

template <class T>
ListStructure<T>::~ListStructure()
{
	delete fileName;
	delete lst;
}

template <class T>
void ListStructure<T>::init(int size, const char* fileName)
{
	this->fileName = fileName;
	this->size = size;
	short int lenType = sizeof(T);
	void* pointerDelete = nullptr;

	lst = new List<T>; // ������������� ������

	listInf* inf = new listInf[size]; //������������� ��������� ������

	srand(time(NULL));

	fstream file(fileName, ios::binary | ios::out);

	if (!file.is_open())
		return;

	for (int i = 0; i < size; i++)
		lst->push_back(rand() % 100);

	for (int i = 0; i < size; i++)
	{
		inf[i].setInf(false, lst->getPoint(i), lst->operator[](i)); // ��������� ���������� �� ������ � ��������� ������
	}

	void* pointerFirst = lst->getPoint(0);

	file.write((char*)&size, sizeof(int));
	file.write((char*)&lenType, sizeof(short int));
	file.write((char*)&pointerFirst, sizeof(void*));
	file.write((char*)&pointerDelete, sizeof(void*));

	for (int i = 0; i < size; i++)
	{
		file.write((char*)&inf[i], sizeof(listInf)); // ������ ��������� ������ � ����
	}

	file.close();
}

template <class T>
void read(const char* path, int pos, int type)
{
	T* test = new T;

	fstream file("file.bin", ios::binary | ios::in | ios::out);

	if (!file.is_open())
		return;

	file.seekg(pos, ios_base::beg);
	file.read((char*)test, type);

	cout << *test << endl;

	file.close();

	delete[] test;
}
template<class T>
inline void ListStructure<T>::fromFile()
{
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	cout << "���������� ������� ������ � �����: ";
	read<int>(fileName, 0, sizeof(int));

	cout << "����� ������ ������: ";
	read<short int>(fileName, 4, sizeof(short int));

	cout << "��������� �� ��������� ������ ������ ������: ";
	read<void*>(fileName, 6, sizeof(void*));

	cout << "��������� �� ��������� ���������� � �������� ������ ������: ";
	read<void*>(fileName, 14, sizeof(void*));

	fstream file(fileName, ios::binary | ios::in);

	listInf tmp; 
	for (int i = 0; i < size; i++)
	{
		file.seekg(22 + sizeof(listInf) * i, ios::beg);
		file.read((char*)&tmp, sizeof(listInf));

		tmp.getInf(); 
	}

	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	file.close();
}

template<class T>
T ListStructure<T>::insert(T value)
{
	srand(time(NULL));

	fstream file(fileName, ios::binary | ios::in | ios::out);

	listInf temp; 

	void* ptrDelete; // ��������� ��������
	void* nullPtr = nullptr;

	file.seekg(14, ios::beg);
	file.read((char*)&ptrDelete, sizeof(void*));

	if (ptrDelete != nullptr)
	{
		lst->push_back(value); //������ �������� � ������

		temp.setInf(false, lst->getPoint(size - 2), lst->operator[](size));
		for (int i = 0; i < size; i++)
		{
			listInf tmp; // ��������� ��������� ��� ������ �� ������

			file.seekg(22 + sizeof(listInf) * i, ios::beg);
			file.read((char*)&tmp, sizeof(listInf));

			file.close();

			if (tmp.getPoint() == ptrDelete)
			{
				file.open(fileName, ios::binary | ios::out | ios::in);

				file.seekg(22 + sizeof(listInf) * i, ios::beg);
				file.write((char*)&temp, sizeof(listInf));

				file.seekg(14, ios::beg);
				file.write((char*)&nullPtr, sizeof(void*));

				file.close();

				return value;
			}
		}
	}

	file.close();

	lst->push_back(value); 

	size++; //��������� ������ ������

	temp.setInf(false, lst->getPoint(size - 2), lst->operator[](size - 1)); //��������� ���������� � �������� � ������

	file.open(fileName, ios::binary | ios::out | ios::in);

	file.seekg(0, ios::beg);
	file.write((char*)&size, sizeof(int));

	file.seekg(22 + sizeof(listInf) * (size - 1), ios::beg);
	file.write((char*)&temp, sizeof(listInf));

	file.close();

	return value;
}

template<class T>
inline void* ListStructure<T>::find(T data)
{
	fstream file(fileName, ios::binary | ios::in);

	void* pointer = nullptr;

	for (int i = 0; i < size; i++)
	{
		listInf tmp;
		file.seekg(22 + sizeof(listInf) * i, ios::beg);
		file.read((char*)&tmp, sizeof(listInf));

		pointer = tmp.getPoint(); //��������� ��������� �������� � ��������� ������

		if (tmp.getData() == data)
		{
			file.close();
			return pointer;
		}
	}
	file.close();
	return (void*)-1;
}

template<class T>
inline void ListStructure<T>::del(T data)
{
	fstream file(fileName, ios::binary | ios::in | ios::out);

	if (!file.is_open())
		return;

	void* pointer = nullptr;

	for (int i = 0; i < size; i++)
	{
		listInf tmp;

		file.seekg(22 + sizeof(listInf) * i, ios::beg);
		file.read((char*)&tmp, sizeof(listInf));

		pointer = tmp.getPoint();

		if (find(data) == pointer)
		{
			file.close();

			file.open(fileName, ios::binary | ios::in | ios::out);

			tmp.setTag(true); // ���������� ��� ���� �������� �������� true

			file.seekg(22 + sizeof(listInf) * i, ios::beg);
			file.write((char*)&tmp, sizeof(listInf));

			file.seekg(14, ios::beg);
			file.write((char*)&pointer, sizeof(void*));
		}
	}
	file.close();
	delCounter++;
	return;
}

template<class T>
inline void ListStructure<T>::pack()
{
	fstream file(fileName, ios::binary | ios::in | ios::out);

	if (!file.is_open())
		return;

	listInf* arr = new listInf[size];

	for (int i = 0; i < size; i++)
	{
		file.seekg(22 + sizeof(listInf) * i, ios::beg);
		file.read((char*)&arr[i], sizeof(listInf));
	}

	file.close();

	for (int i = 0; i < delCounter; i++) // �������� ��� ���������� ������
	{
		for (int i = 0; i < (size - 1); i++)
		{
			if (arr[i].getTag() == true)
			{
				listInf temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;

			}
		}
	}

	file.open(fileName, ios::binary | ios::out | ios::in);

	for (int i = 0; i < size; i++)
	{
		file.seekg(22 + sizeof(listInf) * i, ios::beg);
		file.write((char*)&arr[i], sizeof(listInf));
	}

	file.close();

	return;
}