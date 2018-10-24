#pragma once

#include <iostream>

#include "dynamic_array.h"

#ifndef POLYNOMIAL_INCLUDED
#define POLYNOMIAL

template <typename T> class Polynomial;

template <typename T>
Polynomial<T> operator*(const Polynomial<T>& lhs, const T value);

template <typename T>
Polynomial<T> operator*(const Polynomial<T>& lhs, const Polynomial<T>& rhs);


template <typename T>
Polynomial<T> operator/(const Polynomial<T>& lhs, const T value);

template <typename T>
Polynomial<T> operator+(const Polynomial<T>& lhs, const Polynomial<T>& rhs);

template <typename T>
Polynomial<T> operator-(const Polynomial<T>& lhs, const Polynomial<T>& rhs);

template <typename T>
void getMaxExponent(unsigned int& max, const Polynomial<T>& pol);

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Polynomial<T>& p);

template <typename T>
std::istream& operator>>(std::istream& stream, Polynomial<T>& p);

template <typename T>
class Polynomial {
		DynamicArray<T> coefficients;

		void copyFrom(const Polynomial<T>& rhs);

	public:
		Polynomial(const DynamicArray<T>& arr);
		Polynomial(const Polynomial<T>& other);
		Polynomial<T>& operator=(const Polynomial<T>& rhs);

		void print() const;

		T getAtIndex(int index) const;
		
		// Operators
		bool operator==(const Polynomial<T>& rhs);
		bool operator<(const Polynomial<T>& rhs);

		Polynomial<T>& operator+=(const Polynomial<T>& other);
		Polynomial<T>& operator-=(const Polynomial<T>& other);
		Polynomial<T>& operator*=(const Polynomial<T>& other);
		T operator[](const unsigned int index);
		T operator()(const T value);
		T operator()(const T a, const T b);
		Polynomial<T>& operator++();
		Polynomial<T> operator++(int);
		Polynomial<T>& operator--();
		Polynomial<T> operator--(int);

		operator int() const;
		operator bool() const;

		friend void getMaxExponent<T>(unsigned int& max, const Polynomial& pol);
		friend Polynomial<T> operator*<T>(const Polynomial& pol, const T value);
		friend Polynomial<T> operator*<T>(const Polynomial& lhs, const Polynomial& rhs);
		friend Polynomial<T> operator/<T>(const Polynomial& pol, const T value);
		friend Polynomial<T> operator+<T>(const Polynomial& lhs, const Polynomial& rhs);
		friend Polynomial<T> operator-<T>(const Polynomial& lhs, const Polynomial& rhs);
		friend std::ostream& operator<<<T>(std::ostream& stream, const Polynomial& p);
		friend std::istream& operator>><T>(std::istream& stream, Polynomial& p);

		/* Just a try */
		/* Не съм го тествал. Също така ако са големи глупости просто го прескочете.*/
		class iterator {
				int i;
				DynamicArray<T>& parent;
			public:
				iterator(const DynamicArray<T>& p, int pos):parent(p),i(pos) {}
				T& operator*() {
					return parent[i];
				}
				/*Т* operator->(int) {
				}*/
				iterator& operator++() {
					while (i < parent.my_size) {
						i++;
						if (coefficients[i] != 0) {
							iterator* temp = this;
							return temp;
						}
					}
				}
				iterator& operator++(int) {
					while (i < coefficients.my_size) {
						i++;
						if (coefficients[i] != 0) {
							iterator* temp = this;
							i++;
							return temp;
						}
					}
				}
				iterator& operator--() {
					while (i > 0) {
						i--;
						if (coefficients[i] != 0) {
							iterator* temp = this;
							return temp;
						}
					}
				}
				iterator& operator--(int) {
					while (i > 0) {
						i--;
						if (coefficients[i] != 0) {
							iterator* temp = this;
							i--;
							return temp;
						}
					}
				}
				iterator& begin() {
					return iterator(parent, 0);
				}
				iterator& end() {
					int ex;
					getMaxExponent(ex, parent);
					return iterator(parent, ex);
				}
				bool operator==(const iterator& other) {
					if (i == other.i && *parent == *other.parent) {
						return true;
					}
					return false;
				}
				bool operator!=(const iterator& other) {
					if (*this == other) {
						return false;
					}
					return true;
				}				
		};
		/* End */
};

template <typename T>
void Polynomial<T>::copyFrom(const Polynomial<T>& rhs) {
	coefficients = rhs.coefficients;
}

template <typename T>
Polynomial<T>::Polynomial(const DynamicArray<T>& arr) {
	coefficients = arr;
}

template <typename T>
Polynomial<T>::Polynomial(const Polynomial<T>& rhs) {
	copyFrom(rhs);
}

template <typename T>
Polynomial<T>& Polynomial<T>::operator=(const Polynomial<T>& rhs) {
	if (this != &rhs) {
		copyFrom(rhs);
	}
	return *this;
}

template <typename T>
T Polynomial<T>::getAtIndex(int index) const {
	return coefficients.get(index);
}

template <typename T>
void Polynomial<T>::print() const {
	std::cout << *this;
}

template <typename T>
void getMaxExponent(unsigned int& max, const Polynomial<T>& pol){
	max = 0;
	int size = pol.coefficients.size();
	size--;
	while (size > 0) {
		if (pol.coefficients.get(size) != 0) {
			max = size;
			break;
		}
		size--;
	}
}

template <typename T>
T powerT(T base, unsigned int exp){
	T result = base;
	for (unsigned int i = 0; i < exp-1; i++) {
		result *= base;
	}
	return result;
}

// Operators
template <typename T>
bool Polynomial<T>::operator==(const Polynomial<T>& rhs) {
	unsigned int max_this;
	unsigned int max_rhs;
	getMaxExponent(max_this, *this);
	getMaxExponent(max_rhs, rhs);
	if (max_this != max_rhs) {
		return false;
	}
	for (unsigned int i = 0; i < max_this; i++) {
		if (coefficients.get(i) != rhs.coefficients.get(i)) {
			return false;
		}
	}
	return true;
}

template <typename T>
bool Polynomial<T>::operator<(const Polynomial<T>& rhs) {
	unsigned int max_this;
	unsigned int max_rhs;
	getMaxExponent(max_this, *this);
	getMaxExponent(max_rhs, rhs);
	if (max_this < max_rhs) {
		return true;
	}
	return false;
}

template <typename T>
Polynomial<T>& Polynomial<T>::operator+=(const Polynomial<T>& other) {
	unsigned int lhs_size;
	unsigned int rhs_size;
	getMaxExponent(lhs_size, *this);
	getMaxExponent(rhs_size, other);
	if (lhs_size > rhs_size) {
		for (unsigned int i = 0; i < rhs_size; i++) {
			this->coefficients[i] = this->coefficients.get(i) + other.coefficients.get(i);
		}
	}
	else {
		for (unsigned int i = 0; i < lhs_size; i++) {
			this->coefficients[i] = this->coefficients.get(i) + other.coefficients.get(i);
		}
		for (unsigned int i = lhs_size; i < rhs_size; i++) {
			this->coefficients.add(other.coefficients.get(i));
		}
	}
	return *this;
}

template <typename T>
Polynomial<T>& Polynomial<T>::operator-=(const Polynomial<T>& other) {
	unsigned int lhs_size;
	unsigned int rhs_size;
	getMaxExponent(lhs_size, *this);
	getMaxExponent(rhs_size, other);
	if (lhs_size > rhs_size) {
		for (unsigned int i = 0; i < rhs_size; i++) {
			this->coefficients[i] = this->coefficients.get(i) - other.coefficients.get(i);
		}
	}
	else {
		for (unsigned int i = 0; i < lhs_size; i++) {
			this->coefficients[i] = this->coefficients.get(i) - other.coefficients.get(i);
		}
		for (unsigned int i = lhs_size; i < rhs_size; i++) {
			this->coefficients.add(-other.coefficients.get(i));
		}
	}
	return *this;
}

template <typename T>
Polynomial<T>& Polynomial<T>::operator*=(const Polynomial<T>& other) {
	DynamicArray<T> new_coef;
	for (unsigned int i = 0; i < coefficients.size(); i++) {
		for (unsigned int j = 0; j < other.coefficients.size(); j++) {
			T result = coefficients.get(i)*other.coefficients.get(j);
			if (i + j < new_coef.size()) {
				new_coef[i + j] += result;
			}
			else {
				new_coef.add(result);
			}
		}
	}
	coefficients = new_coef;
	return *this;
}


template <typename T>
T Polynomial<T>::operator[](const unsigned int index) {
	if (index >= coefficients.size()) {
		return 0;
	}
	return coefficients[index];
}

template <typename T>
T Polynomial<T>::operator()(const T argument) {
	T result = coefficients.get(0);
	unsigned int end = coefficients.size();
	for(unsigned int i = 1; i < end; i++) {
		result += powerT(argument, i)*coefficients.get(i);
	}
	return result;
}

template <typename T>
T Polynomial<T>::operator()(const T a, const T b) {
	// integral in [a,b]
	Polynomial<T> new_polynomial(*this);
	++new_polynomial;
	return new_polynomial(b) - new_polynomial(a);
}

template <typename T>
Polynomial<T> operator*(const Polynomial<T>& lhs, const T value) {
	DynamicArray<T> temp_arr;

	unsigned int size = lhs.coefficients.size();
	for (unsigned int i = 0; i < size; i++) {
		temp_arr.add(lhs.coefficients.get(i)*value);
	}
	Polynomial<T> temp_pol(temp_arr);

	return temp_pol;
}

template <typename T>
Polynomial<T> operator*(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
	Polynomial<T> new_pol(lhs);
	new_pol *= rhs;
	return new_pol;
}


template <typename T>
Polynomial<T> operator/(const Polynomial<T>& lhs, const T value) {
	DynamicArray<T> temp_arr;

	unsigned int size = lhs.coefficients.size();
	for (unsigned int i = 0; i < size; i++) {
		temp_arr.add(lhs.coefficients.get(i)/value);
	}
	Polynomial<T> temp_pol(temp_arr);

	return temp_pol;
}

template <typename T>
Polynomial<T> operator+(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
	Polynomial<T> temp_pol(lhs);
	temp_pol += rhs;
	return temp_pol;
}

template <typename T>
Polynomial<T> operator-(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
	Polynomial<T> temp_pol(lhs);
	temp_pol -= rhs;
	return temp_pol;
}

template <typename T>
Polynomial<T>& Polynomial<T>::operator++() { // ++a;
	DynamicArray<T> new_coefficients;
	new_coefficients.add(0);					// x^0 is always removed
	unsigned int size = coefficients.size();
	for (unsigned int i = 0; i < size; i++) {
		new_coefficients.add(coefficients.get(i) / (i + 1));
	}
	this->coefficients = new_coefficients;
	return *this;
}

template <typename T>
Polynomial<T> Polynomial<T>::operator++(int) {   //a++
	Polynomial copy(*this);
	++(*this);
	return copy;
}

template <typename T>
Polynomial<T>& Polynomial<T>::operator--() { // --a;
	DynamicArray<T> new_coefficients;
	unsigned int size = coefficients.size();
	for (unsigned int i = 1; i < size; i++) {
		new_coefficients.add(this->coefficients.get(i)*i);
	}
	this->coefficients = new_coefficients;
	return *this;
}

template <typename T>
Polynomial<T> Polynomial<T>::operator--(int) {   //a--
	Polynomial copy(*this);
	--(*this);
	return copy;
}

template <typename T>
Polynomial<T>::operator int() const {
	unsigned int highest_ex;
	getMaxExponent(highest_ex, *this);
	return highest_ex;
}

template <typename T>
Polynomial<T>::operator bool() const {
	unsigned int highest_ex;
	getMaxExponent(highest_ex, *this);
	if (highest_ex != 0) {
		return false;
	}
	else {
		return true;
	}
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Polynomial<T>& polynomial){
	unsigned int size = polynomial.coefficients.size();
	for (unsigned int i = 0; i < size; i++) {
		stream << polynomial.coefficients.get(i) << "x^" << i << " ";
	}
	stream << "\n";
	return stream;
}

template <typename T>
std::istream& operator>>(std::istream& stream, Polynomial<T>& polynomial) { // polynomial is not const, because we want to change it
	T new_coefficient;
	int count;
	std::cout << "Give the highest exponential of x: ";
	stream >> count;
	std::cout << "Coefficients: ";
	for (int i = 0; i < count; i++) {
		stream >> new_coefficient;
		polynomial.coefficients.add(new_coefficient);
	}
	return stream;
}

#endif // !POLYNOMIAL_INCLUDED
