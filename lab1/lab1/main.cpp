#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <vector>
#include <fstream>
#define NPAGES 2
#define PAGESIZE 512

using namespace std;

struct VIRTUAL {
	FILE* Fp; /*файловый указатель виртуального массива*/
	int Type; /*размер элемента в байтах*/
	int Status[NPAGES]; /*статус страницы (флаг модификации)*/
	int Number[NPAGES]; /*номер страницы*/
	char Page[PAGESIZE]; /*буфер страниц*/
};

VIRTUAL* vini(long size, int Type)
{
	VIRTUAL* vp = new VIRTUAL[size];
	vp->Fp = fopen("test.asd", "w+");
	fclose(vp->Fp);
	return vp;
}
void* addres(VIRTUAL* array, long index)
{
	vector<int> page;
	srand(time(0));
	page.resize(2);
	void* indexElement;
	long hh = 512;
	array->Fp = fopen("test.asd", "w+");
	int page1 = (index - 1) / (PAGESIZE / (sizeof(int) * 8)) + 1;
	for (int i = 0; i < _msize(array) / sizeof(VIRTUAL); i++)
		for (int j = 0; j < PAGESIZE; j++)
		{
			array[i].Page[j] == index ? page.at(0) = i, page.at(1) = j : 0;
		}
	indexElement = &array[page.at(0)].Page[page.at(1)];



	return NULL;
}
template<typename VTYPE>
int vput(VIRTUAL* array, long index, VTYPE* value)
{
	addres(array, index);
	return 0;
}
template<typename VTYPE>
int vget(VIRTUAL* array, long index, VTYPE* value)
{
	addres(array, index);
	return 0;
}
void CreateFile(int count)
{
	int random;
	ofstream file("file.bin", ios::binary | ios::out);
	srand(time(NULL));
	for (int i = 0; i < count; i++) {
		random = rand() % 322;
		file.write((char*)&random, sizeof(int));
	}
	file.close();
}
int main()
{
	//addres(vini(NPAGES, PAGESIZE),100);
	fstream inOut;
	char s[100];
	CreateFile(100);
	inOut.open("file.bin", ios::binary | ios::in);
	for (int i = 0; i < 100; i++) {
		inOut >> s[i];
		cout << s[i];
	}
	inOut.close();
	return 0;
}