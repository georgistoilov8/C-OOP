#include <iostream>

#include "./Cells/cell.h"

Cell::Cell()
{
	this->type = Cell::cell_type::Empty;
}

Cell::~Cell(){}


void Cell::setType(const cell_type type) {
	this->type = type;
}

Cell::cell_type Cell::getType() const {
	return this->type;
}