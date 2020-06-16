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
			cout << "К сожалению, этот ввод неверен. Пожалуйста, попробуйте еще раз." << endl
				<< "значение :";
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
	cout << "Введите размер списка:";
	size = checkValue<int>();
	list.init(size, "fileProd.bin", "fileSpec.bin");
	list.fromFileProduct();
	list.fromFileSpecific();
	while (operation != 0) {
		cout << "|  Выберите операцию:                           |" << endl
			<< "|· 1-Введите значение в список Product          |" << endl
			<< "|· 2-удалить значение                           |" << endl
			<< "|· 3-сортировать список Product                 |" << endl
			<< "|· 4-Связать список Product со списком Specific	|" << endl
			<< "|· 5-Вставить спецификацию в список Specific	|" << endl
			<< "|· 6-Увеличить размер Specific			|" << endl;
		operation = checkValue<int>();
		switch (operation)
		{
		case 1:
			cout << "Введите значение для вставки в список : ";
			value = checkValue<T>();
			list.insert(value);
			list.fromFileProduct();
			break;
		case 2:
			cout << "Введите значение для удаления из списка : ";
			value = checkValue<T>();
			list.del(value);
			list.fromFileSpecific();
			break;
		case 3:
			list.pack();
			list.fromFileProduct();
			cout << "Список был сортирован " << endl;
			break;
		case 4:
			int pNum, sNum;
			cout << "Связь Product со specification" << endl;
			cout << "Введите номер Product: ";
			pNum = checkValue<int>();;
			cout << "Введите номер Specification: ";
			sNum = checkValue<int>();;
			list.link(pNum, sNum);
			list.fromFileProduct();
			list.fromFileSpecific();
			break;
		case 5:
			cout << "Введите значение для вставки в список: ";
			value = checkValue<T>();
			list.insertSpecific(value);
			list.fromFileProduct();
			list.fromFileSpecific();
			break;
		case 6:
			cout << "Введите конкретный номер, чтобы увеличить размер: ";
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