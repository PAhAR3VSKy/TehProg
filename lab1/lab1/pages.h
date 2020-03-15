#pragma once
#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;
template <typename T>
class pages
{
public:
	pages();
	void init(int size,const char *file);
	~pages();
	void setBuff(long index,T value);
	T getBuff(long index);
	T getDump(long index);
	void setDump(long index, T value);
	void fromFile(int page);
	void fileSize();
private:
	char* buff;
	const char* fileName;
	bool modificator;
	int buffNumber;
	int buffSize;
	int fileMaxSize;
};

template <typename T>
pages<T>::pages()
{
	buff = nullptr;
	fileName = nullptr;
	modificator = true;
}

template <typename T>
void pages<T>::init(int size, const char* file)
{
	buff = new char[size];
	buffSize = size;
	fileName = file;
	modificator = true;
	buffNumber = -1;
	fileSize();
}
template <typename T>
pages<T>::~pages()
{
	delete[] buff;
}

template <typename T>
void pages<T>::setBuff(long index, T value)
{
	if (index < 1 || index > buffSize / sizeof(T))
	{
		MessageBox(GetActiveWindow(), "Out of range array", "RangeError", MB_ICONERROR);
		return ;
	}
	char* temp;
	temp = (char*)&value;
	int length = sizeof(T);
	for (int i = 0; i < length ;i++)
		buff[(index - 1) * length + i] = temp[i];
	int k;
}

template <typename T>
T pages<T>::getBuff(long index)
{
	if (index < 1 || index > buffSize / sizeof(T))
	{
		MessageBox(GetActiveWindow(), "Out of range array", "RangeError", MB_ICONERROR);
		return (T)0;
	}
	int length = sizeof(T);

	char* temp = new char[length];

	for (int i = 0; i < length; i++)
	temp[i] = buff[(index - 1) * length + i];
	T* value = (T*)temp;

	return *value;
}

template <typename T>
void pages<T>::setDump(long index, T value)
{
	if (index < 1 || index > fileMaxSize / (sizeof(T)))
	{
		MessageBox(GetActiveWindow(), "Out of range array", "RangeError", MB_ICONERROR);
		return;
	}
	int abPage = (index-1) / (buffSize / sizeof(T));
	int relPage = (index-1) % (buffSize / sizeof(T));
	this->fromFile(abPage);
	setBuff(relPage + 1, value);
}

template <typename T>
T pages<T>::getDump(long index)
{
	if (index < 1 || index >fileMaxSize / sizeof(T))
	{
		MessageBox(GetActiveWindow(), "Out of range array", "RangeError", MB_ICONERROR);
		return (T)0;
	}
	int abPage = (index - 1) / (buffSize / sizeof(T));
	int relPage = (index - 1) % (buffSize / sizeof(T));
	this->fromFile(abPage);
	return getBuff(relPage + 1);
}
template <typename T>
void pages<T>::fromFile(int page)
{
	if (!modificator)
	{
			fstream file(fileName, ios::binary | ios::out | ios::in);
			if (!file.is_open()) 
			{
				MessageBox(GetActiveWindow(), "File is not open", "FileError", MB_ICONERROR);
				return;
			}

			file.seekg(buffNumber * buffSize, ios::beg);
			file.write(buff, buffSize);
			file.close();
			delete[] this->buff;
			buff = nullptr;
			modificator = true;
	}

	if (this->buffNumber == page)
		return;

	this->buffNumber = page;
	fstream file(fileName, ios::binary | ios::out | ios::in);
	if (!file.is_open())
	{
		MessageBox(GetActiveWindow(), "File is not open", "FileError", MB_ICONERROR);
		return;
	}

	if (buff == nullptr)
		this->buff = new char[buffSize];
	file.seekg(page*buffSize, ios::beg);
	file.read(buff, buffSize);
	modificator = false;
	file.close();
}

template <typename T>
void pages<T>::fileSize() 
{
	fstream file(fileName, ios::binary | ios::out | ios::in);
	file.seekg(0, ios::end);
	fileMaxSize = file.tellg();
	file.close();
}