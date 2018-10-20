#include <iostream>

#include "./real_number_cell.h"

RealNumberCell::RealNumberCell()
	:number(0)
{
	type = cell_type::RealNumber;
}

RealNumberCell::RealNumberCell(const double number)
	: number(number)
{
	type = cell_type::RealNumber;
}

RealNumberCell::RealNumberCell(const RealNumberCell& other) {
	this->number = other.get();
	type = cell_type::RealNumber;
}

RealNumberCell& RealNumberCell::operator=(const RealNumberCell& rhs) {
	this->number = rhs.get();
	return *this;
}

RealNumberCell::~RealNumberCell(){}

void RealNumberCell::set(const double number) {
	this->number = number;
}

double RealNumberCell::get() const {
	return this->number;
}

RealNumberCell* RealNumberCell::clone() const {
	return new RealNumberCell(*this);
}

void RealNumberCell::print() const {
	std::cout << number;
}

int RealNumberCell::getValue() const {
	return (int)number;
}

void RealNumberCell::getCellToFile(std::ostream& file) const {
	file << number;
}
