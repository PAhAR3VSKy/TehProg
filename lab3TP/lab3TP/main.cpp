#include <iostream>
#include "Structure.h"

using namespace std;

template<class T>
T checkValue()
{
	T value;
	while (true)
	{
		cin >> value;
		if (!cin)
		{
			cout << "� ���������, ���� ���� �������. ����������, ���������� ��� ���." << endl
				<< "�������� :";
			cin.clear();
			while (cin.get() != '\n');
		}
		else
			return value;
	}
}

template<class T>
void interface()
{
	int size;
	int operation = -1;
	int value;
	Structure<T>list;
	cout << "������� ������ ������:";
	size = checkValue<int>();
	list.init(size, "fileProd.bin", "fileSpec.bin");
	list.fromFileProduct();
	list.fromFileSpecific();
	while (operation != 0) {
		cout << "|  �������� ��������:                           |" << endl
			<< "|� 1-������� �������� � ������ Product          |" << endl
			<< "|� 2-������� ��������                           |" << endl
			<< "|� 3-����������� ������ Product                 |" << endl
			<< "|� 4-������� ������ Product �� ������� Specific	|" << endl
			<< "|� 5-�������� ������������ � ������ Specific	|" << endl
			<< "|� 6-��������� ������ Specific			|" << endl;
		operation = checkValue<int>();
		switch (operation)
		{
		case 1:
			cout << "������� �������� ��� ������� � ������ : ";
			value = checkValue<T>();
			list.insert(value);
			list.fromFileProduct();
			break;
		case 2:
			cout << "������� �������� ��� �������� �� ������ : ";
			value = checkValue<T>();
			list.del(value);
			list.fromFileSpecific();
			break;
		case 3:
			list.pack();
			list.fromFileProduct();
			cout << "������ ��� ���������� " << endl;
			break;
		case 4:
			int pNum, sNum;
			cout << "����� Product �� specification" << endl;
			cout << "������� ����� Product: ";
			pNum = checkValue<int>();;
			cout << "������� ����� Specification: ";
			sNum = checkValue<int>();;
			list.link(pNum, sNum);
			list.fromFileProduct();
			list.fromFileSpecific();
			break;
		case 5:
			cout << "������� �������� ��� ������� � ������: ";
			value = checkValue<T>();
			list.insertSpecific(value);
			list.fromFileProduct();
			list.fromFileSpecific();
			break;
		case 6:
			cout << "������� ���������� �����, ����� ��������� ������: ";
			value = checkValue<T>();
			list.resizeSpecific(value);
			list.fromFileProduct();
			list.fromFileSpecific();
			break;
		}
	}

}
int main()
{
	setlocale(LC_ALL, "ru");
	interface<int>();
}