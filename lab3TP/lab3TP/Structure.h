#pragma once
#include <fstream>
#include <iostream>
#include "List.h"
#include "time.h"
#include "ArrayPointer.h"
using namespace std;
template <class T>
class Structure
{
public:
	Structure();
	~Structure();

	void init(int, const char*, const char*);
	void fromFileProduct();
	void fromFileSpecific();
	void link(int, int);
	T insert(T);
	void del(T);
	void pack();

private:
	const char* fileProd;
	const char* fileSpec;
	int size;
	int sizeSpecific;
	int delCounter;
	void* find(T);
	void createFileProd(int, short int, void*);
	void createFileSpec(int, short int, void*);
	List<T>* listProduct;
	List<T>* listSpecifications;

	class listInfProduct
	{
	public:
		bool deleteTag;
		void* pointer;
		T data;
		listInfProduct()
		{
			deleteTag = false;
			pointer = nullptr;
			data = T();
		}
		inline void setInf(bool deleteTag, void* pointer, T data)
		{
			this->deleteTag = deleteTag;
			this->pointer = pointer;
			this->data = data;
		}
		inline void getInf()
		{
			cout << "Тег удаления: " << deleteTag
				<< " Указатель: " << pointer
				<< " Данные: " << data << endl;
		}
		inline void setTag(bool Tag) { this->deleteTag = Tag; }
		inline void setPoint(void* point) { this->pointer = point; }
		inline void setData(T data) { this->data = data; }
		inline bool getTag() { return deleteTag; }
		inline void* getPoint() { return pointer; }
		inline T getData() { return data; }
	};
	class listInfSpecific
	{
	public:

		void* pointer;
		ArrayPointer* pProd;
		T data;
		int occurRate;
		int sizeS;
		int count;
		listInfSpecific()
		{
			occurRate = 0;
			pointer = nullptr;
			pProd = nullptr;
			sizeS = 0;
			data = T();
			count = 0;
		}
		inline void setInf(void* pointer, T data, int size, int occurRate = 0)
		{
			this->pointer = pointer;
			this->sizeS = size;
			this->pProd = new ArrayPointer[this->sizeS];
			this->data = data;
			this->occurRate = occurRate;

		}
		inline void getInf()
		{
			cout << " Указатель: " << pointer << endl;

			for (int i = 0; i < this->sizeS; i++)
				cout << " Указатель Product " << i + 1 << ": "
				<< pProd[i].getPointer() << endl;

			cout << " Число вхождений:" << occurRate << endl
				<< " Данные: " << data << "\n\n";
		}
		inline void setPoint(void* point) { this->pointer = point; }
		inline void setPointProd(void* pointerProd)
		{
			pProd[count].setPointer(pointerProd);
			count++;
		}
		inline void minPointProd() { count--; }
		inline void setPointProdNull(int i) { pProd[i].setPointer(nullptr); }
		inline void setRate() { this->occurRate++; }
		inline void setRate(int occurRate) { this->occurRate = occurRate; }
		inline void setData(T data) { this->data = data; }
		void ResizeArray()
		{
			ArrayPointer* temp = new ArrayPointer[4];
			for (int i = 0; i < this->sizeS; i++)
			{
				temp[i] = pProd[i];
			}
			delete[] pProd;
			this->sizeS++;
			pProd = new ArrayPointer[this->sizeS];
			for (int i = 0; i < this->sizeS - 1; i++)
			{
				pProd[i] = temp[i];
			}
		}
		void Sort()
		{
			for (int i = 0; i < occurRate; i++)
			{
				for (int j = 1; j < sizeS; j++)
				{
					if (pProd[j - 1].getPointer() == nullptr)
					{
						ArrayPointer temp = pProd[j - 1];
						pProd[j - 1] = pProd[j];
						pProd[j] = temp;

					}
				}
			}

		}
		void* getPointProd(int i) { return this->pProd[i].getPointer(); }
		inline void* getPoint() { return pointer; }
		inline T getData() { return data; }
		inline int getRate() { return occurRate; }
	};
};

template <class T>
Structure<T>::Structure()
{
	this->size = 0;
	this->sizeSpecific = 0;
	this->delCounter = 0;
	this->fileProd = nullptr;
	listProduct = nullptr;
}

template <class T>
Structure<T>::~Structure()
{
	delete listProduct;
	delete listSpecifications;
}

template <class T>
void Structure<T>::createFileProd(int size, short int lenType, void* pointerDelete)
{
	listInfProduct* inf = new listInfProduct[size];
	void* pointerSpec = nullptr;


	fstream file(fileProd, ios::binary | ios::out | ios::in);

	if (!file.is_open())
		return;

	for (int i = 0; i < size; i++)
		listProduct->push_back(rand() % 100);

	for (int i = 0; i < size; i++)
		inf[i].setInf(false, listProduct->getPoint(i), listProduct->operator[](i));

	void* pointerFirst = listProduct->getPoint(0);

	file.write((char*)&size, sizeof(int));
	file.write((char*)&lenType, sizeof(short int));
	file.write((char*)&pointerFirst, sizeof(void*));
	file.write((char*)&pointerDelete, sizeof(void*));
	file.write((char*)&fileSpec, sizeof(const char*));
	file.write((char*)&pointerSpec, sizeof(void*));

	for (int i = 0; i < size; i++)
		file.write((char*)&inf[i], sizeof(listInfProduct));

	file.close();
}

template <class T>
void Structure<T>::createFileSpec(int size, short int lenType, void* pointerDelete)
{
	listInfSpecific* inf = new listInfSpecific[size];
	fstream file(fileSpec, ios::binary | ios::out | ios::in);

	if (!file.is_open())
		return;

	for (int i = 0; i < size; i++)
		listSpecifications->push_back(rand() % 100);

	for (int i = 0; i < size; i++)
		inf[i].setInf(listSpecifications->getPoint(i), listSpecifications->operator[](i), size);

	void* pointerFirst = listSpecifications->getPoint(0);

	file.write((char*)&size, sizeof(int));
	file.write((char*)&lenType, sizeof(short int));
	file.write((char*)&pointerFirst, sizeof(void*));
	file.write((char*)&pointerDelete, sizeof(void*));

	for (int i = 0; i < size; i++)
		file.write((char*)&inf[i], sizeof(listInfSpecific));

	file.close();
}

template <class T>
void Structure<T>::init(int size, const char* fileProd, const char* fileSpec)
{
	srand(time(NULL));
	this->fileProd = fileProd;
	this->fileSpec = fileSpec;
	this->size = size;
	this->sizeSpecific = size;
	short int lenType = sizeof(T);
	void* pointerDelete = nullptr;
	listProduct = new List<T>;
	listSpecifications = new List<T>;
	createFileProd(size, lenType, pointerDelete);
	createFileSpec(size, lenType, pointerDelete);
}

template<class T>
inline void Structure<T>::link(int prodNumber, int specNumber)
{
	fstream fileS(fileSpec, ios::binary | ios::out | ios::in);
	fstream fileP(fileProd, ios::binary | ios::out | ios::in);
	listInfProduct tempProd;
	listInfSpecific tempSpec;
	int posProd = 22 + sizeof(listInfProduct) * (prodNumber - 1);
	int posSpec = 14 + sizeof(listInfSpecific) * (specNumber - 1);

	fileP.seekg(posProd, ios_base::beg);
	fileP.read((char*)&tempProd, sizeof(listInfProduct));
	fileP.close();
	fileS.seekg(posSpec, ios_base::beg);
	fileS.read((char*)&tempSpec, sizeof(listInfSpecific));
	fileS.close();

	for (int i = 0; i < size; i++)
		if (tempSpec.getPointProd(i) == tempProd.getPoint())
			return;

	tempSpec.setPointProd(tempProd.getPoint());
	tempSpec.setRate();

	fileP.open(fileProd, ios::binary | ios::out | ios::in);
	fileP.seekg(18, ios_base::beg);
	void* pointSpec = tempSpec.getPoint();
	fileP.write((char*)&pointSpec, sizeof(void*));
	fileP.close();

	fileS.open(fileSpec, ios::binary | ios::out | ios::in);
	fileS.seekg(posSpec, ios_base::beg);
	fileS.write((char*)&tempSpec, sizeof(listInfSpecific));
	fileS.close();
}

template <class T>
void read(const char* path, int pos, int type)
{
	T* test = new T;

	fstream file(path, ios::binary | ios::in | ios::out);

	if (!file.is_open())
		return;

	file.seekg(pos, ios_base::beg);
	file.read((char*)test, type);

	cout << *test << endl;

	file.close();

	delete[] test;
}

template<class T>
inline void Structure<T>::fromFileProduct()
{
	cout << "#################################################" << endl;
	cout << "<<|Products|>>" << endl;
	cout << "Размер списка: ";
	read<int>(fileProd, 0, sizeof(int));

	cout << "Длина типа: ";
	read<short int>(fileProd, 4, sizeof(short int));

	cout << "Первый указатель в списке: ";
	read<void*>(fileProd, 6, sizeof(void*));

	cout << "Последний указатель на удаление: ";
	read<void*>(fileProd, 10, sizeof(void*));
	cout << "Название файла Product:";
	read<const char*>(fileProd, 14, sizeof(const char*));
	cout << "Указатель спецификации:";
	read<void*>(fileProd, 18, sizeof(void*));
	fstream file(fileProd, ios::binary | ios::in | ios::out);

	listInfProduct tmp;
	for (int i = 0; i < size; i++)
	{
		file.seekg(22 + sizeof(listInfProduct) * i, ios::beg);
		file.read((char*)&tmp, sizeof(listInfProduct));

		tmp.getInf();
	}

	cout << "#################################################" << endl;

	file.close();
}

template<class T>
inline void Structure<T>::fromFileSpecific()
{
	cout << "#################################################" << endl;
	cout << "<<|Specification|>>" << endl;
	cout << "Размер списка: ";
	read<int>(fileSpec, 0, sizeof(int));

	cout << "Длина типа: ";
	read<short int>(fileSpec, 4, sizeof(short int));

	cout << "Первый указатель в списке: ";
	read<void*>(fileSpec, 6, sizeof(void*));

	cout << "Послдений указатель на удаление: ";
	read<void*>(fileSpec, 10, sizeof(void*));

	fstream file(fileSpec, ios::binary | ios::in | ios::out);

	listInfSpecific tmp;
	for (int i = 0; i < sizeSpecific; i++)
	{
		int posSpec = 14 + sizeof(listInfSpecific) * i;
		file.seekg(posSpec, ios::beg);
		file.read((char*)&tmp, sizeof(listInfSpecific));

		tmp.getInf();
	}

	cout << "#################################################" << endl;

	file.close();
}

template<class T>
T Structure<T>::insert(T value)
{
	srand(time(NULL));

	fstream file(fileProd, ios::binary | ios::in | ios::out);
	listInfProduct temp;

	void* ptrDelete;
	void* pDTag = nullptr;
	void* nullPtr = nullptr;
	bool Tag = false;

	file.seekg(10, ios::beg);
	file.read((char*)&ptrDelete, sizeof(void*));
	if (ptrDelete == nullptr)
	{
		for (int i = 0; i < size; i++)
		{
			fstream file(fileProd, ios::binary | ios::in | ios::out);
			int posProduct = 22 + sizeof(listInfProduct) * i;

			listInfProduct tmp;

			file.seekg(posProduct, ios::beg);
			file.read((char*)&tmp, sizeof(listInfProduct));
			if (tmp.getTag() == 1)
			{
				Tag = tmp.getTag();
				ptrDelete = tmp.getPoint();
				file.close();
				break;
			}

		}
	}
	if (ptrDelete != nullptr || Tag == 1)
	{
		listProduct->push_back(value);
		temp.setInf(false, listProduct->getPoint(listProduct->GetSize() - 2),
			listProduct->operator[](listProduct->GetSize() - 1));
		for (int i = 0; i < size; i++)
		{
			int posProduct = 22 + sizeof(listInfProduct) * i;

			listInfProduct tmp;

			file.seekg(posProduct, ios::beg);
			file.read((char*)&tmp, sizeof(listInfProduct));

			if (tmp.getPoint() == ptrDelete)
			{

				file.close();

				file.open(fileProd, ios::binary | ios::out | ios::in);

				file.seekg(posProduct, ios::beg);
				file.write((char*)&temp, sizeof(listInfProduct));

				file.seekg(10, ios::beg);
				file.write((char*)&nullPtr, sizeof(void*));

				file.close();

				return value;
			}
		}
	}

	file.close();

	listProduct->push_back(value);

	size++;


	for (int i = 0; i < sizeSpecific; i++)
	{
		fstream fileS(fileSpec, ios::binary | ios::out | ios::in);

		listInfSpecific temp;
		fileS.seekg(14 + sizeof(listInfSpecific) * i, ios::beg);
		fileS.read((char*)&temp, sizeof(listInfSpecific));
		fileS.close();
		temp.ResizeArray();

		fileS.open(fileSpec, ios::binary | ios::out | ios::in);
		fileS.seekg(14 + sizeof(listInfSpecific) * i, ios::beg);
		fileS.write((char*)&temp, sizeof(listInfSpecific));
		fileS.close();
	}


	temp.setInf(false, listProduct->getPoint(size - 2), listProduct->operator[](size - 1));

	file.open(fileProd, ios::binary | ios::out | ios::in);

	file.seekg(0, ios::beg);
	file.write((char*)&size, sizeof(int));

	int posProduct = 22 + sizeof(listInfProduct) * (size - 1);
	file.seekg(posProduct, ios::beg);
	file.write((char*)&temp, sizeof(listInfProduct));

	file.close();

	return value;
}

template<class T>
inline void* Structure<T>::find(T data)
{
	fstream file(fileProd, ios::binary | ios::in);

	void* pointer = nullptr;

	for (int i = 0; i < size; i++)
	{
		listInfProduct tmp;
		file.seekg(22 + sizeof(listInfProduct) * i, ios::beg);
		file.read((char*)&tmp, sizeof(listInfProduct));

		pointer = tmp.getPoint();

		if (tmp.getData() == data)
		{
			file.close();
			return pointer;
		}
	}
	file.close();
	return (void*)-1;
}

template<class T>
inline void Structure<T>::del(T data)
{
	fstream fileP(fileProd, ios::binary | ios::in | ios::out);
	fstream fileS;
	if (!fileP.is_open())
		return;

	void* pointer = nullptr;

	for (int i = 0; i < size; i++)
	{
		listInfProduct tmpP;
		listInfSpecific tmpS;

		int posProd = 22 + sizeof(listInfProduct) * i;

		fileP.seekg(posProd, ios::beg);
		fileP.read((char*)&tmpP, sizeof(listInfProduct));

		pointer = tmpP.getPoint();

		if (find(data) == pointer)
		{
			for (int i = 0; i < sizeSpecific; i++)
			{
				fileS.open(fileSpec, ios::binary | ios::in | ios::out);
				int posSpec = 14 + sizeof(listInfSpecific) * i;
				fileS.seekg(posSpec, ios_base::beg);
				fileS.read((char*)&tmpS, sizeof(listInfSpecific));
				fileS.close();
				for (int j = 0; j < sizeSpecific; j++)
				{
					if (tmpS.getPointProd(j) == pointer)
					{
						fileS.open(fileSpec, ios::binary | ios::in | ios::out);
						tmpS.setPointProdNull(j);

						if (tmpS.getRate() != 0)
							tmpS.setRate(tmpS.getRate() - 1);
						tmpS.minPointProd();
						tmpS.Sort();
						fileS.seekg(posSpec, ios_base::beg);
						fileS.write((char*)&tmpS, sizeof(listInfSpecific));
						fileS.close();
					}

				}
			}

			fileP.close();

			fileP.open(fileProd, ios::binary | ios::in | ios::out);

			tmpP.setTag(true);

			fileP.seekg(22 + sizeof(listInfProduct) * i, ios::beg);
			fileP.write((char*)&tmpP, sizeof(listInfProduct));

			fileP.seekg(10, ios::beg);
			fileP.write((char*)&pointer, sizeof(void*));
		}
	}
	fileP.close();
	delCounter++;
	return;
}

template<class T>
inline void Structure<T>::pack()
{
	fstream file(fileProd, ios::binary | ios::in | ios::out);

	if (!file.is_open())
		return;

	listInfProduct* arr = new listInfProduct[size];

	for (int i = 0; i < size; i++)
	{
		file.seekg(22 + sizeof(listInfProduct) * i, ios::beg);
		file.read((char*)&arr[i], sizeof(listInfProduct));
	}

	file.close();

	for (int i = 0; i < delCounter; i++)
	{
		for (int j = 0; j < (size - 1); j++)
		{
			if (arr[j].getTag() == true)
			{
				listInfProduct temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;

			}
		}
	}

	file.open(fileProd, ios::binary | ios::out | ios::in);

	for (int i = 0; i < size; i++)
	{
		file.seekg(22 + sizeof(listInfProduct) * i, ios::beg);
		file.write((char*)&arr[i], sizeof(listInfProduct));
	}

	file.close();

	return;
}

