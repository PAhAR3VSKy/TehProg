#pragma once
#include "pages.h"
template <typename T>
class virtualmemory
{
public:
	virtualmemory(int sizePages,int nPages,const char* fileName);
	~virtualmemory();
	void vput(long index,T value);
	T vget(long index);
private:
	pages<T> *page;
	int*Number;
	int*Status;
	int nPages;
	int size;
};

template<typename T>
virtualmemory<T>::virtualmemory(int sizePages, int nPages, const char* fileName)
{
	page = new pages<T>[nPages];
	Number = new int[nPages];
	Status = new int[nPages];
	size = sizePages;
	this->nPages = nPages;
	for (int i = 0; i < nPages;i++)
	{
		Number[i] = 0;
		Status[i] = 0;
		page[i].init(sizePages, fileName);
	}
}
template<typename T>
virtualmemory<T>::~virtualmemory()
{
	delete[] page;
	delete[] Number;
	delete[] Status;
}

template<typename T>
void virtualmemory<T>::vput(long index, T value)
{
	int absolutePage = (index - 1) / (size / sizeof(value)) + 1;
	for (int i = 0; i < nPages; i++)
	{
		
		if (absolutePage == Number[i])
		{
			int relativePage = (index - 1) % (size / sizeof(value)) + 1;
			page[i].setBuff(relativePage, value);
			return ;
		}

		if (Status[i] == 0)
		{
			Status[i] = 1;
			Number[i] = absolutePage;
			page[i].setDump(index, value);
			return ;
		}
	}
	srand(time(NULL));
	int r = rand() % nPages;
	Number[r] = absolutePage;
    page[r].setDump(index, value);
	return ;
}

template<typename T>
T virtualmemory<T>::vget(long index) 
{
	int absolutePage = (index - 1) / (size / sizeof(T)) + 1;
	for (int i = 0; i < nPages; i++)
	{
		
	
		if (Number[i] == absolutePage)
		{
			int relativePage = 1 + (index - 1) % (size / sizeof(T));
			return page[i].getBuff(relativePage);
		}

		if (Status[i] == 0)
		{
			Number[i] = absolutePage;
			Status[i] = 1;
			return page[i].getDump(index);
		}
	}
	srand(time(NULL));

	int r = rand() % nPages;

	Number[r] = absolutePage;

	return page[r].getDump(index);
}