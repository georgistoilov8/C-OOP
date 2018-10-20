#include <iostream>

#include "empty_cell.h"

EmptyCell::EmptyCell()
{
	type = Cell::cell_type::Empty;
}

EmptyCell::~EmptyCell(){}

EmptyCell* EmptyCell::clone() const {
	return new EmptyCell(*this);
}

void EmptyCell::print() const {
	std::cout << " ";
}

int EmptyCell::getValue() const {
	return 0;
}

void EmptyCell::getCellToFile(std::ostream& file) const {
	file << ' ';
}