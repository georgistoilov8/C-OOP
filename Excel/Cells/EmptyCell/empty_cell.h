#pragma once

#include "./../cell.h"

#ifndef EMPTY_CELL_INCLUDED
#define EMPTY_CELL

class EmptyCell: public Cell {

	public:
		EmptyCell();
		~EmptyCell();
		EmptyCell* clone() const;
		void print() const;
		int getValue() const;
		void getCellToFile(std::ostream& file) const;
};
#endif // !EMPTY_CELL_INCLUDED
