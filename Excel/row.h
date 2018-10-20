#pragma once

#ifndef ROW_INCLUDED
#define ROW

#include "./Cells/cell.h"

class Row {
		Cell** cells;
		unsigned int cells_capacity;
		unsigned int cells_size;

		void resize();
		void copyFrom(const Row& rhs);
	public:
		Row();
		Row(const Row& other);
		Row& operator=(const Row& rhs);
		~Row();

		Cell& operator[](const unsigned int index);
		const Cell& operator[](const unsigned int index) const;
		
		void addCell(const Cell& cell);
		void changeCell(const int index, const Cell& cell);
		void printRow() const;
		void clean();			// it's bad but can't think of any other 
		void initialize();		// option
		unsigned int getCellsCount() const;
		unsigned int getCellsCapacity() const;

		int getCellValue(const int index) const;

		void saveCellsToFile(std::ostream& file);
};

#endif // !ROW_INCLUDED
