// implementation of class DArray
#include <iostream>
#include <iomanip>
#include "DArray.h"
#include <assert.h>
using namespace std;

// default constructor
DArray::DArray() {
	Init();
}

// set an array with default values
DArray::DArray(int nSize, double dValue)
	: a_Data(new double[nSize]), a_Size(nSize)
{
	for (int i = 0; i < nSize; i++) {
		a_Data[i] = dValue;
	}
}

DArray::DArray(const DArray& arr)
	: a_Data(new double[arr.a_Size]), a_Size(arr.a_Size)
{
	for (int i = 0; i < arr.a_Size; i++) {
		a_Data[i] = arr.a_Data[i];
	}
}

// deconstructor
DArray::~DArray() {
	Free();
}

// display the elements of the array
void DArray::Print() const {
	cout << "the size is " << a_Size << "->";
	for (int i = 0; i < a_Size; i++) {
		cout << fixed << setprecision(2) << a_Data[i] << " ";
	}
	cout << endl;
}

// initilize the array
void DArray::Init() {
	a_Data = nullptr;
	a_Size = 0;
}

// free the array
void DArray::Free() {
	delete[] a_Data;
	a_Data = nullptr;
	a_Size = 0;
}

// get the size of the array
int DArray::GetSize() const {
	return a_Size;
}

// set the size of the array
void DArray::SetSize(int nSize) {
	if (a_Size == nSize)
		return;
	double* Data = new double[nSize];
	int temp = nSize < a_Size ? nSize : a_Size;
	for (int i = 0; i < temp; i++) {
		Data[i] = a_Data[i];
	}
	for (int i = temp; i < nSize; i++) {
		Data[i] = 0.;
	}
	delete[] a_Data;
	a_Data = Data;
	a_Size = nSize;
}

// get an element at an index
const double& DArray::GetAt(int nIndex) const {
	assert(nIndex >= 0 && nIndex < a_Size);
	return a_Data[nIndex];
}

// set the value of an element 
void DArray::SetAt(int nIndex, double dValue) {
	assert(nIndex >= 0 && nIndex < a_Size);
	a_Data[nIndex] = dValue;
}

// overload operator '[]'
const double& DArray::operator[](int nIndex) const {
	assert(nIndex >= 0 && nIndex < a_Size);
	return a_Data[nIndex];
}

// add a new element at the end of the array
void DArray::PushBack(double dValue) {
	double* temp = new double[static_cast<size_t>(a_Size) + 1];
	for (int i = 0; i < a_Size; i++) {
		temp[i] = a_Data[i];
	}
	temp[a_Size] = dValue;
	delete[] a_Data;
	a_Data = temp;
	a_Size++;
}

// delete an element at some index
void DArray::DeleteAt(int nIndex) {
	assert(nIndex >= 0 && nIndex < a_Size);
	double* temp = new double[static_cast<size_t>(a_Size) - 1];
	for (int i = 0; i < nIndex; i++) {
		temp[i] = a_Data[i];
	}
	for (int i = nIndex; i < a_Size - 1; i++) {
		temp[i] = a_Data[i + 1];
	}
	delete[] a_Data;
	a_Data = temp;
	a_Size--;
}

// insert a new element at some index
void DArray::InsertAt(int nIndex, double dValue) {
	assert(nIndex >= 0 && nIndex <= a_Size);
	double* temp = new double[static_cast<size_t>(a_Size) + 1];
	for (int i = 0; i < nIndex; i++) {
		temp[i] = a_Data[i];
	}
	temp[nIndex] = dValue;
	for (int i = nIndex + 1; i < a_Size + 1; i++) {
		temp[i] = a_Data[i - 1];
	}
	delete[] a_Data;
	a_Data = temp;
	a_Size++;
}

// overload operator '='
DArray& DArray::operator = (const DArray& arr) {
	delete[] a_Data;
	a_Size = arr.a_Size;
	a_Data = new double[a_Size];
	for (int i = 0; i < a_Size; i++) {
		a_Data[i] = arr.a_Data[i];
	}
	return *this;
}
