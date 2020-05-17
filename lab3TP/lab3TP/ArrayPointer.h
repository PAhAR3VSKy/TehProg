#pragma once
class ArrayPointer
{
public:
	ArrayPointer();
	void setPointer(void* pointer);
	void* getPointer();
	ArrayPointer& operator=(const ArrayPointer& array);
private:
	void* pointer;
};

ArrayPointer::ArrayPointer()
{
	this->pointer = nullptr;
}
void ArrayPointer::setPointer(void* pointer)
{
	this->pointer = pointer;
}
void* ArrayPointer::getPointer()
{
	return this->pointer;
}
ArrayPointer& ArrayPointer::operator=(const ArrayPointer& array)
{
	this->pointer = array.pointer;
	return *this;
}