#include <iostream>
#include <time.h>
#include <fstream>
#include "pages.h"
#include "virtualmemory.h"
using namespace std;

void CreateFileInt(int count) 
{	
	int random;
	ofstream file("file.bin", ios::binary | ios::out);
	srand(time(NULL));
	for (int i = 0; i < count; i++) 
	{
		random = rand() % 10;
		file.write((char*)&random, sizeof(int));
	}
	file.close();
}
void CreateFileChar(int count)
{
	char random;
	ofstream file("filechar.bin", ios::binary | ios::out);
	srand(time(NULL));
	for (int i = 0; i < count; i++)
	{
		random = 97 + rand() % 25;
		file.write((char*)& random, sizeof(char));
	}
	file.close();
}

int checkValue()
{
	int value;
	while (true)
	{
		cin >> value;
		if (!cin)
		{
			cout << "Oops, that input is invalid.  Please try again."<<endl;
			cin.clear();
			while (cin.get() != '\n');
		}
		else 
			return value;
	}
}

void workWithInt() 
{
	int page;
	int pagesize;
	cout << "Enter count of page and size:"<<endl;

	cout << "size of page:";
	pagesize = checkValue();

	cout << "count of page:";
	page = checkValue();


	int count = (pagesize / sizeof(int)) * page;

	CreateFileInt(count);
	virtualmemory<int> pages(pagesize,page, "file.bin");

	cout << endl;
	cout << "Value in file"<<endl;
	for (int i = 1; i <= count; i++)
	cout << i << " : " << pages.vget(i) << endl;
	int a = -1;
	while (a != 0)
	{
		cout << "Choose operation:" << endl;
		cout << "Add 1-vput , get 2-vget" << endl;
		a = checkValue();
		switch (a)
		{
		case 1:
			int index, value;
			cout << "index : ";
			index = checkValue();
			cout << "value : ";
			value = checkValue();
			cout << endl;
			pages.vput(index, value);
			break;
		case 2:
			cout << "index : ";
			index = checkValue();
			cout << index << " index: " << pages.vget(index) << endl;
			break;
		}
		cout << endl;
	}

}

void workWithChar()
{
	int page;
	int pagesize;
	cout << "Enter count of page and size:" << endl;
	cout << "size of page:";
	cin >> pagesize;
	cout << "count of page:";
	cin >> page;

	int count = pagesize / sizeof(char) * page;
	CreateFileChar(count);
	virtualmemory<char> pages(pagesize, page, "filechar.bin");

	cout << "Value in file" << endl;
	for (int i = 1; i <= count; i++)
		cout << i << " : " << pages.vget(i) << endl;

	int a = -1;
	while (a != 0)
	{
		cout << "Choose operation:" << endl;
		cout << "Add 1-vput , get 2-vget" << endl;
		cin >> a;
		switch (a)
		{
		case 1:
			int index;
			char value;
			cout << "index : ";
			cin >> index;
			cout << "value : ";
			cin >> value;
			cout << endl;
			pages.vput(index, value);
			break;
		case 2:
			cout << "index : ";
			cin >> index;
			cout << index << " index: " << pages.vget(index) << endl;
			break;
		default:
			cout << "Incorrect value";
			return ;
			break;
		}
		cout << endl;
	}

}
int main()
{
	int a;
	cout << "1-with int , 2-with char"<<endl;
	cin >> a;
	switch (a) 
	{
	case 1:
		workWithInt();
		cout << endl;
		break;
	case 2:
		workWithChar();
		cout << endl;
		break;
	default:
		cout << "Incorrect value";
		return 0;
		break;
		
	}

	return 0;
}