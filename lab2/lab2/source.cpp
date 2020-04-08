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


int main()
{
	setlocale(LC_ALL, "ru");
	int size;
	int operation = -1;
	int value;
	ListStructure<int>* list = new ListStructure<int>();
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
	return 0;
}