#include "ListStructure.h"
int checkValue()
{
	int value;
	while (true)
	{
		cin >> value;
		if (!cin)
		{
			cout << "� ���������, ���� ���� �������. ����������, ���������� ��� ���." << endl
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
	cout << "������� ������ ������:";
	size = checkValue();
	list->init(size, "file.bin");
	list->fromFile();
	while (operation != 0) {
		cout << "�������� ��������:" << endl
			<< "� 1-�������� ��������	�" << endl
			<< "� 2-������� ��������	�" << endl
			<< "� 3-����������� ������	�" << endl;
		operation = checkValue();
		switch (operation)
		{
		case 1:
			cout << "������� �������� ��� ������� � ������: ";
			value = checkValue();
			list->insert(value);
			list->fromFile();
			break;
		case 2:
			cout << "������� �������� ��� �������� �� ������: ";
			value = checkValue();
			list->del(value);
			list->fromFile();
			break;
		case 3:
			list->pack();
			list->fromFile();
			cout << "������ ��� ����������" << endl;
			break;
		}
	}
	return 0;
}