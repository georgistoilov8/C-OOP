#pragma once

#ifndef DYNAMIC_ARRAY_INCLUDED
#define DYNAMIC_ARRAY

template <typename T>
class DynamicArray {
	T* buffer;
	unsigned int my_size;
	unsigned int my_capacity;

	void copyFrom(const DynamicArray<T>& rhs);
	void clear();
	void resize(unsigned int size);

public:
	DynamicArray();
	DynamicArray(const DynamicArray<T>& rhs);
	DynamicArray<T>& operator=(const DynamicArray<T>& rhs);
	~DynamicArray();

	T& operator[](const unsigned int index);

	unsigned int capacity() const;
	unsigned int size() const;
	bool empty() const;

	void add(const T value);
	void removeLast();

	T get(unsigned int index) const;

	void show() const;

};

template <typename T>
DynamicArray<T>::DynamicArray()
	:my_capacity(8),
	my_size(0),
	buffer(nullptr)
{
	buffer = new T[my_capacity];
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& rhs) {
	copyFrom(rhs);
}


template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& rhs) {
	if (this != &rhs) {
		clear();
		copyFrom(rhs);
	}
	return *this;
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
	clear();
}

template <typename T>
T& DynamicArray<T>::operator[](const unsigned int index) {
	if (index >= my_size) {
		throw std::out_of_range("DynamicArray: index is out of bounds!");
	}
	return buffer[index];
}

template <typename T>
void DynamicArray<T>::copyFrom(const DynamicArray<T>& rhs) {
	my_size = rhs.my_size;
	my_capacity = rhs.my_capacity;
	buffer = new T[my_capacity];
	for (unsigned int i = 0; i < my_size; i++) {
		buffer[i] = rhs.buffer[i];
	}
}

template <typename T>
void DynamicArray<T>::clear() {
	delete[] buffer;
	my_capacity = 8;
	my_size = 0;
}

template <typename T>
unsigned int DynamicArray<T>::capacity() const {
	return my_capacity;
}

template <typename T>
unsigned int DynamicArray<T>::size() const {
	return my_size;
}

template <typename T>
bool DynamicArray<T>::empty() const {
	return my_size == 0;
}

template <typename T>
void DynamicArray<T>::add(const T value) {
	if (my_size >= my_capacity) {
		resize(my_capacity * 2);
	}
	buffer[my_size] = value;
	my_size++;
}

template <typename T>
void DynamicArray<T>::removeLast() {
	if (!empty()) {
		my_size--;
	}
}

template <typename T>
T DynamicArray<T>::get(unsigned int index) const {
	if (index > my_size) {
		throw std::out_of_range("DynamicArray: index is out of bounds!");
	//	return 0;
	}
	return buffer[index];
}

template <typename T>
void DynamicArray<T>::resize(unsigned int size) {
	while (my_capacity < size) {
		my_capacity *= 2;
	}
	T* temp = new T[my_capacity];
	for (unsigned int i = 0; i < my_size; i++) {
		temp[i] = buffer[i];
	}
	delete[] buffer;
	buffer = temp;
}

template <typename T>
void DynamicArray<T>::show() const {
	for (unsigned int i = 0; i < my_size; i++) {
		std::cout << buffer[i];
	}
}

#endif