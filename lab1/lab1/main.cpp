#define _CRT_SECURE_NO_WARNINGS 
#include <iostream> 
#include <time.h> 
#include <stdio.h> 
#include <vector>
#include <stdlib.h> 
#include <Windows.h> 
#define NPAGES 2 
#define PAGESIZE 512 

using namespace std;

struct VIRTUAL {
	FILE* Fp; /*файловый указатель виртуального массива*/
	int Type; /*размер элемента в байтах*/
	int Status[NPAGES]; /*статус страницы (флаг модификации)*/
	int Number[NPAGES]; /*номер страницы*/
	char Page[NPAGES * PAGESIZE]; /*буфер страниц*/
};

VIRTUAL* vini(long size, int Type)
{
	VIRTUAL *vp = new VIRTUAL[size];
	FILE *test;
	test = fopen("test.txt", "w");
	srand(time(0));
	//fwrite(vp->Page, Type, size, test);
	fclose(test);
	return vp;
}

void* AllocPage()
{
	void* pvAdress;
	pvAdress = VirtualAlloc(PVOID(NULL), PAGESIZE, MEM_RESERVE, PAGE_READWRITE);
	return &pvAdress;
}

template<typename VTYPE>
int vput(VIRTUAL* array, long index, VTYPE* value)
{
	return 0;
}

template<typename VTYPE>
int vget(VIRTUAL* array, long index, VTYPE* value)
{
	return 0;
}

void* addres(VIRTUAL* array, long index)
{
	vector<int> page;
	page.resize(2);

	for (int i = 0; i < sizeof(array) / sizeof(VIRTUAL); i++)
	{
		for (int j = 0; j < NPAGES; j++)
		{
			array[i].Page[j] = index ? page.at(0) = i, page.at(1) = j : 0;
		}
	}
	if (PVOID(array[page.at(0)].Page[page.at(1)]) != AllocPage)
	{
		//array[page.at(0)].Page[page.at(1)] = new (AllocPage()) VIRTUAL;
	}
	return 0;
}

int main()
{
	vini(NPAGES, PAGESIZE);

	return 0;

}