#pragma once

#include "./../cell.h"

#ifndef STRING_CELL_INCLUDED
#define STRING_CELL

class StringCell : public Cell {
	char* string;
	unsigned int string_size;
	public:
		StringCell();
		StringCell(const char* new_string);
		StringCell(const StringCell& other);
		StringCell& operator=(const StringCell& rhs);
		~StringCell();

		void print() const;

		StringCell* clone() const;
		int getValue() const;
		void getCellToFile(std::ostream& file) const;
	private:
		void clean();
		void copyFrom(const char* new_string);
};

#endif // !STRING_CELL_INCLUDED
