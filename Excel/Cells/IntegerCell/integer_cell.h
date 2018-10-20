#pragma once

#ifndef NUMBER_CELL_INCLUDED
#define NUMBER_CELL

#include "./../cell.h"

class IntegerCell : public Cell {
	int number;
	
	public:
		IntegerCell();
		IntegerCell(const int number);
		IntegerCell(const IntegerCell& other);
		IntegerCell& operator=(const IntegerCell& rhs);
		//Cell& operator=(const Cell& rhs);

		void set(const int number);
		int get() const;

		IntegerCell* clone() const;
		void print() const;
		int getValue() const;
		void getCellToFile(std::ostream& file) const;

};
#endif // !NUMBER_CELL_INCLUDED
