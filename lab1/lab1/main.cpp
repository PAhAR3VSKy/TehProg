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
    int Status; /*статус страницы (флаг модификации)*/
    int Number; /*номер страницы*/
    char Page[PAGESIZE]; /*буфер страниц*/
};

VIRTUAL* vini(long size, int Type)
{
    VIRTUAL* vp = new VIRTUAL[size];
    for (int i = 0; i < NPAGES; i++) {
        vp[i].Number = 0;
        vp[i].Status = 0;
    }
    //vp->Fp = fopen("test.asd", "w+");
    //fclose(vp->Fp);
    return vp;
}
template<typename VTYPE>
void setInPage(char* buffer, VTYPE value, long index)
{
    char* temp = (char*)&value;
    int length = sizeof(VTYPE);

    for (int i = 0; i < length; i++)
        buffer[(index - 1) * length + i] = temp[i];

}
template<typename VTYPE>
int vput(VIRTUAL* array, long index, VTYPE value)
{
    int absolutePage = (index - 1) / (sizeof(array->Page) / sizeof(value)) + 1;
    for (int i = 0; i < NPAGES; i++)
    {
        if (absolutePage == array[i].Number)
        {
            int relativePage = (index - 1) % (sizeof(array->Page) / sizeof(value)) + 1;
            array[i].Page[relativePage] = (char)&value;
            return 0;
        }
    }
    for (int i = 0; i < NPAGES; i++)
    {
        if (array[i].Status == 0)
        {
            array[i].Status == 1;
            array[i].Number = absolutePage;
            setInPage(array[i].Page, value, index);
            cout << value << endl;
            for (int j = 0; j < 512; j++)
                cout << array[i].Page[j];

            return 0;
        }
    }
    srand(time(NULL));
    int r = rand() % 2;
    array[r].Number = absolutePage;
    array[r].Page[index] = (char)&value;
    return 0;
}
template<typename VTYPE>
int vget(VIRTUAL* array, long index, VTYPE* value)
{

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
    ifstream file;
    int s = 4;
    CreateFile(100);
    vput(vini(2, 3), 2, s);
    file.close();
    return 0;
}