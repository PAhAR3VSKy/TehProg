#include "ListStructure.h"
template <class T>
void read(int pos,int type)
{
	T* test=new T;
	fstream file("file.bin", ios::binary | ios::in | ios::out);
	if (!file.is_open())
		return;
	file.seekg(pos, ios_base::beg);
	file.read((char*)test,type);
	cout <<*test<<endl;
	file.close();
	delete[] test;
}
int main() 
{
	ListStructure<int> *list = new ListStructure<int>();

	list->init(5,"file.bin");
	list->insert(22);
	read<int>(0,sizeof(int));
	read<short int>(4, sizeof(short int));
	read<void*>(6, sizeof(void*));
	read<void*>(14, sizeof(void*));
	for(int i=0;i<list->getSize();i++)
	list->fromFile(i);
	int x;
	int count;
	cin >> count;
	for (int i = 0; i < count; i++)
	{
	cin >> x;
		list->del(x);
	}
	
	list->pack();

	read<int>(0, sizeof(int));
	read<short int>(4, sizeof(short int));
	read<void*>(6, sizeof(void*));
	read<void*>(14, sizeof(void*));
	for (int i = 0; i < list->getSize(); i++)
		list->fromFile(i);

	return 0;
}