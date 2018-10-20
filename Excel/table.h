#pragma once

#ifndef TABLE_INCLUDED
#define TABLE

#include "dynamic_array.h"
#include "row.h"

#include "./Cells/EmptyCell/empty_cell.h"

class Table {
	DynamicArray<Row> rows;
	unsigned int rows_count;
public:
	Table();
	~Table();
	Table(const Table& other);
	Table& operator=(const Table& rhs);
	Row& operator[](const unsigned int index);

	void operator()(const Row& row, bool is_row);

	unsigned int getRowsCount() const;
	unsigned int getRowCells(const int index) const;

	void addRow(const Row& row);
	void addColumn(const Row& row);
	void changeCell(const int row, const int column, const Cell& cell);

	int findLargestRow() const;

	int getCellValue(const int row, const int column) const;

	void changeRows(const int row1, const int row2);

	void print() const;

	void saveToFile(std::ostream& file) const;
};

#endif // !TABLE_INCLUDED

