#include "ListStructure.h"
int checkValue()
{
	int value;
	while (true)
	{
		cin >> value;
		if (!cin)
		{
			cout << "К сожалению, этот ввод неверен. Пожалуйста, попробуйте еще раз." << endl
				<< "value :";
			cin.clear();
			while (cin.get() != '\n');
		}
		else
			return value;
	}
}

void CreateListInt()
{
	ListStructure<int>* list = new ListStructure<int>();
	int size,
		operation = -1,
		value;
	cout << "Введите размер списка:";
	size = checkValue();
	list->init(size, "file.bin");
	list->fromFile();
	while (operation != 0) {
		cout << "Выберите операцию:" << endl
			<< "· 1-вставить значение	·" << endl
			<< "· 2-удалить значение	·" << endl
			<< "· 3-сортировать список	·" << endl;
		operation = checkValue();
		switch (operation)
		{
		case 1:
			cout << "Введите значение для вставки в список: ";
			value = checkValue();
			list->insert(value);
			list->fromFile();
			break;
		case 2:
			cout << "Введите значение для удаления из списка: ";
			value = checkValue();
			list->del(value);
			list->fromFile();
			break;
		case 3:
			list->pack();
			list->fromFile();
			cout << "Список был сортирован" << endl;
			break;
		}
	}
}

void CreateListChar()
{
	ListStructure<char>* list = new ListStructure<char>();
	int size,
		operation = -1;
	char value;
	cout << "Введите размер списка:";
	size = checkValue();
	list->init(size, "file.bin");
	list->fromFile();
	while (operation != 0) {
		cout << "Выберите операцию:" << endl
			<< "· 1-вставить значение	·" << endl
			<< "· 2-удалить значение	·" << endl
			<< "· 3-сортировать список	·" << endl;
		operation = checkValue();
		switch (operation)
		{
		case 1:
			cout << "Введите значение для вставки в список: ";
			cin >> value;
			list->insert(value);
			list->fromFile();
			break;
		case 2:
			cout << "Введите значение для удаления из списка: ";
			cin >> value;
			list->del(value);
			list->fromFile();
			break;
		case 3:
			list->pack();
			list->fromFile();
			cout << "Список был сортирован" << endl;
			break;
		}
	}
}


int main()
{
	setlocale(LC_ALL, "ru");
	int choice;
	cout << "Выбирите тип данных:" << endl
		 << "1. Int" << endl
		 << "2. Char" << endl;
	cin >> choice;
	switch (choice)
	{
	case 1:
		CreateListInt();
		break;
	case 2:
		CreateListChar();
		break;
	default:
		cout << "Неверно введено значение" << endl;
		break;
	}
	return 0;
}