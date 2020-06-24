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
			cout << "� ���������, ���� ���� �������. ����������, ���������� ��� ���." << endl
				<< "�������� :";
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

	cout << "������� �������� ������:";
	n = checkValue<T>();
	cout << "������� ������ ����������:";
	m = checkValue<T>();

	btree.Init(n, m, "btree.bin");
	btree.OutFile();

	while (operation != 0) {
		cout << "|�������� ��������:	|" << endl
			<< "|1-�������� ��������	|" << endl
			<< "|2-������� ��������	|" << endl
			<< "|3-�����������		|" << endl;

		operation = checkValue<int>();

		switch (operation)
		{
		case 1:
			cout << "������� �������� ��� ������� � btree: ";
			value = checkValue<T>();
			cout << "������� �������: ";
			position = checkValue<T>();
			btree.Insert(value,position);
			btree.OutFile();
			break;
		case 2:
			cout << "������� �������� ��� �������� �� btree: ";
			value = checkValue<T>();
			cout << "������� ������� � ������ btree: ";
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