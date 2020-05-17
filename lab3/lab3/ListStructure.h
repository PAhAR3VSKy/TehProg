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

	void init(int size, const char* fileName); //инициализаци€ списка в файле
	void fromFile(); //вывод информации из файла
	T insert(T data); //вставка значени€ в файл
	void del(T data); //удаление значени€ из файла
	void pack(); //сортировка значений в файле

private:
	const char* fileName; //путь к файлу
	int size; //размер списка
	int delCounter; //счетчик удал€емого значени€

	void* find(T data); // нахождение указател€ дл€ удалени€

	List<T>* lst;

	class listInf // структура списка
	{
	public:
		bool deleteTag; // тег дл€ удалени€
		void* pointer; // указатель значени€
		T data; // значение 
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
			cout << "“ег удалени€: " << deleteTag
				<< " ”казатель: " << pointer
				<< " ƒанные: " << data << endl;
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

	lst = new List<T>; // инициализаци€ списка

	listInf* inf = new listInf[size]; //инициализаци€ структуры списка

	srand(time(NULL));

	fstream file(fileName, ios::binary | ios::out);

	if (!file.is_open())
		return;

	for (int i = 0; i < size; i++)
		lst->push_back(rand() % 100);

	for (int i = 0; i < size; i++)
	{
		inf[i].setInf(false, lst->getPoint(i), lst->operator[](i)); // установка информации из списка в структуру списка
	}

	void* pointerFirst = lst->getPoint(0);

	file.write((char*)&size, sizeof(int));
	file.write((char*)&lenType, sizeof(short int));
	file.write((char*)&pointerFirst, sizeof(void*));
	file.write((char*)&pointerDelete, sizeof(void*));

	for (int i = 0; i < size; i++)
	{
		file.write((char*)&inf[i], sizeof(listInf)); // запись структуры списка в файл
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

	cout << " оличество записей данных в файле: ";
	read<int>(fileName, 0, sizeof(int));

	cout << "ƒлина записи данных: ";
	read<short int>(fileName, 4, sizeof(short int));

	cout << "”казатель на логически первую запись списка: ";
	read<void*>(fileName, 6, sizeof(void*));

	cout << "”казатель на последнюю помеченную к удалению запись списка: ";
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

	void* ptrDelete; // указатель удалени€
	void* nullPtr = nullptr;

	file.seekg(14, ios::beg);
	file.read((char*)&ptrDelete, sizeof(void*));

	if (ptrDelete != nullptr)
	{
		lst->push_back(value); //запись значени€ в список

		temp.setInf(false, lst->getPoint(size - 2), lst->operator[](size));
		for (int i = 0; i < size; i++)
		{
			listInf tmp; // временна€ структура дл€ чтени€ из списка

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

	size++; //увеличить размер списка

	temp.setInf(false, lst->getPoint(size - 2), lst->operator[](size - 1)); //установка информацию о значении в списке

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

		pointer = tmp.getPoint(); //получение указател€ значени€ в структуре списка

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

			tmp.setTag(true); // установите дл€ тега удалени€ значение true

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

	for (int i = 0; i < delCounter; i++) // алгоритм дл€ сортировки списка
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