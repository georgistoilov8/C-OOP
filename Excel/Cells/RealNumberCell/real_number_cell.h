#pragma once

#include "./../cell.h"

#ifndef REAL_NUMBER_CELL_INCLUDED
#define REAL_NUMBER

class RealNumberCell: public Cell {
	double number;

public:
	RealNumberCell();
	RealNumberCell(const double number);
	RealNumberCell(const RealNumberCell& other);
	RealNumberCell& operator=(const RealNumberCell& rhs);
	~RealNumberCell();

	void set(const double number);
	double get() const;
	RealNumberCell* clone() const;

	void print() const;
	int getValue() const;
	void getCellToFile(std::ostream& file) const;
};

#endif // !REAL_NUMBER_CELL
