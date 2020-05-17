#include "Structure.h"

int checkValue()
{
	int value;
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

void interface()
{
	int size;
	int operation = -1;
	int value;
	Structure<int>list;
	cout << "Введите размер списка:";
	size = checkValue();
	list.init(size, "fileProd.bin", "fileSpec.bin");
	list.fromFileProduct();
	list.fromFileSpecific();
	while (operation != 0) {
		cout << "|  Выберите операцию:                           |" << endl
			<< "|· 1-Введите значение в список Product          |" << endl
			<< "|· 2-удалить значение                           |" << endl
			<< "|· 3-сортировать список Product                 |" << endl
			<< "|· 4-Связать список Product со списком Specific	|" << endl;
		switch (operation)
		{
		case 1:
			cout << "Введите значение для вставки в список : ";
			value = checkValue();
			list.insert(value);
			list.fromFileProduct();
			break;
		case 2:
			cout << "Введите значение для удаления из списка : ";
			value = checkValue();
			list.del(value);
			list.fromFileProduct();
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
			pNum = checkValue();;
			cout << "Введите номер Specification: ";
			sNum = checkValue();;
			list.link(pNum, sNum);
			list.fromFileProduct();
			list.fromFileSpecific();
		}
	}

}
int main()
{
	setlocale(LC_ALL, "ru");
	interface();
}