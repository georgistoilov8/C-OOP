#pragma once

#include "./../cell.h"

#ifndef DATE_CELL_INCLUDED
#define DATE_CELL

class DateCell :public Cell {
	unsigned int day;
	unsigned int month;
	unsigned int year;
	bool normal_write;

	public:
		DateCell();
		DateCell(unsigned int day, unsigned int month, unsigned int year, bool normal_write);
		DateCell(const DateCell& other);
		DateCell& operator=(const DateCell& rhs);
		~DateCell();

		void getDate(unsigned int& day, unsigned int& month, unsigned int& year, bool& normal_write) const;

		DateCell* clone() const;

		void print() const;
		int getValue() const;
		void getCellToFile(std::ostream& file) const;
};
#endif // !DATE_CELL_INCLUDED
