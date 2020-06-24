#include "BTree.h"

template <class T>
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

template <class T>
void interface()
{
	int n;
	int m;
	int operation = -1;
	int position = 0;
	T value;
	BTree<T> btree;

	cout << "Введите значение списка:";
	n = checkValue<T>();
	cout << "Введите размер наследника:";
	m = checkValue<T>();

	btree.Init(n, m, "btree.bin");
	btree.OutFile();

	while (operation != 0) {
		cout << "|Выберите операцию:	|" << endl
			<< "|1-Вставить значение	|" << endl
			<< "|2-Удалить значение	|" << endl
			<< "|3-Сортировать		|" << endl;

		operation = checkValue<int>();

		switch (operation)
		{
		case 1:
			cout << "Введите значение для вставки в btree: ";
			value = checkValue<T>();
			cout << "Введите позицию: ";
			position = checkValue<T>();
			btree.Insert(value,position);
			btree.OutFile();
			break;
		case 2:
			cout << "Введите значение для удаления из btree: ";
			value = checkValue<T>();
			cout << "Введите позицию в списке btree: ";
			position = checkValue<T>();
			btree.Del(value, position);
			btree.OutFile();
			break;
		case 3:
			btree.Pack();
			btree.OutFile();
			break;
		}
	}

}
int main()
{
	setlocale(LC_ALL, "ru");
	interface<int>();

	return 0;
}