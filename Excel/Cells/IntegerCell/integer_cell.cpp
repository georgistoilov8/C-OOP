#include <iostream>

#include "integer_cell.h"

IntegerCell::IntegerCell()
:number(0)
{
	type = cell_type::Integer;
}

IntegerCell::IntegerCell(int number)
:number(number)
{
	type = cell_type::Integer;
}

IntegerCell::IntegerCell(const IntegerCell& other) {
	this->number = other.get();
	type = cell_type::Integer;
}

IntegerCell& IntegerCell::operator=(const IntegerCell& rhs) {
	this->number = rhs.get();
	return *this;
}

void IntegerCell::set(const int number) {
	this->number = number;
}

int IntegerCell::get() const {
	return this->number;
}

IntegerCell* IntegerCell::clone() const {
	return new IntegerCell(*this);
}

void IntegerCell::print() const {
	std::cout << number;
}

int IntegerCell::getValue() const {
	return number;
}

void IntegerCell::getCellToFile(std::ostream& file) const {
	file << number;
}
