#pragma once
#include <iostream>

using namespace std;

template <class T>
class BTreeStructure
{
public:
	BTreeStructure();
	void Init(int size, void* pointer, void* self_pointer, int index);
	void Set_Point(void* pointer);
	int Set_Value(T value);
	int Set_Value(T value, int position);
	void Set_Tag(bool tag, int n);
	void Set_Entries();
	void Set_List_DelTag(bool tag);
	void* Get_Point();
	void* Get_SelfPoint();
	T Get_Value(int n);
	bool Get_Tag(int n);
	bool Get_List_DelTag();
	void Get_Inf();
	int Get_Size();
	int Get_Delete();


private:
	T* value;
	bool List_DelTag;
	bool* DelTag;
	void* pointer;
	void* Self_pointer;
	int Number_of_Entries;
	int Number_of_Delete;
	int IndexNumber;
	int count;
	int size;
};

template<class T>
inline void BTreeStructure<T>::Init(int size, void* pointer, void* self_pointer, int index)
{

	this->size = size;
	value = new T[size];
	DelTag = new bool[size];
	List_DelTag = false;
	Number_of_Entries = 0;
	Number_of_Delete = 0;
	IndexNumber = index;
	for (int i = 0; i < size; i++) {
		DelTag[i] = false;
		value[i] = 0;
	}

	this->Self_pointer = self_pointer;
	this->pointer = pointer;

	count = 0;
}

template <class T>
BTreeStructure<T>::BTreeStructure()
{

	value = nullptr;
	pointer = nullptr;
	DelTag = nullptr;
	List_DelTag = false;
	IndexNumber = 0;
	count = 0;
}


template <class T>
void BTreeStructure<T>::Set_Point(void* pointer)
{
	this->pointer = pointer;
}
template <class T>
int BTreeStructure<T>::Set_Value(T value)
{
	if ((this->count + 1) > size)
	{
		return size;
	}

	this->value[this->count] = value;

	this->count++;

	return 0;
}

template <class T>
int BTreeStructure<T>::Set_Value(T value, int position)
{
	this->value[position] = value;
	return 0;
}

template<class T>
void BTreeStructure<T>::Set_Tag(bool tag, int n)
{
	this->DelTag[n] = tag;
	Number_of_Delete++;
}

template<class T>
void BTreeStructure<T>::Set_Entries()
{
	this->Number_of_Entries++;
}

template<class T>
void BTreeStructure<T>::Set_List_DelTag(bool tag)
{
	this->List_DelTag = tag;
}

template <class T>
void* BTreeStructure<T>::Get_Point()
{
	return this->pointer;
}

template <class T>
void* BTreeStructure<T>::Get_SelfPoint()
{
	return this->Self_pointer;
}

template <class T>
T BTreeStructure<T>::Get_Value(int n)
{
	if (n >= size)
		return T();
	return this->value[n];
}
template <class T>
bool BTreeStructure<T>::Get_Tag(int n)
{
	return this->DelTag[n];
}

template <class T>
bool BTreeStructure<T>::Get_List_DelTag()
{
	return List_DelTag;
}

template <class T>
void BTreeStructure<T>::Get_Inf()
{
	cout << "Список#" << IndexNumber << endl;
	cout << "Собственный указатель: " << Self_pointer << endl;
	cout << "Указатель: " << pointer << endl;
	cout << "Размер: " << size << endl;
	cout << "Количество входов: " << Number_of_Entries << endl;
	cout << "Тег удаления списка: " << List_DelTag << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "Значение #" << i + 1 << " " << this->value[i] << " Тег удаления: " << this->DelTag[i] << endl;
	}
	cout << endl;
}

template <class T>
int BTreeStructure<T>::Get_Size()
{
	return this->size;
}

template <class T>
int BTreeStructure<T>::Get_Delete()
{
	return Number_of_Delete;
}