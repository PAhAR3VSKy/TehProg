#include "Structure.h"

int checkValue()
{
	int value;
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

void interface()
{
	int size;
	int operation = -1;
	int value;
	Structure<int>list;
	cout << "������� ������ ������:";
	size = checkValue();
	list.init(size, "fileProd.bin", "fileSpec.bin");
	list.fromFileProduct();
	list.fromFileSpecific();
	while (operation != 0) {
		cout << "|  �������� ��������:                           |" << endl
			<< "|� 1-������� �������� � ������ Product          |" << endl
			<< "|� 2-������� ��������                           |" << endl
			<< "|� 3-����������� ������ Product                 |" << endl
			<< "|� 4-������� ������ Product �� ������� Specific	|" << endl;
		switch (operation)
		{
		case 1:
			cout << "������� �������� ��� ������� � ������ : ";
			value = checkValue();
			list.insert(value);
			list.fromFileProduct();
			break;
		case 2:
			cout << "������� �������� ��� �������� �� ������ : ";
			value = checkValue();
			list.del(value);
			list.fromFileProduct();
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
			pNum = checkValue();;
			cout << "������� ����� Specification: ";
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