#include <iostream>

#include "table.h"

Table::Table()
:rows_count(0)
{}

Table::~Table(){}

Table::Table(const Table& other) {
	rows = other.rows;
	rows_count = other.rows_count;
}

Table& Table::operator=(const Table& rhs) {
	if (this != &rhs) {
		rows = rhs.rows;
		rows_count = rhs.rows_count;
	}
	return *this;
}

Row& Table::operator[](const unsigned int index) {
	if (index >= rows.size()) {
		throw std::out_of_range("Index out of range");
	}
	return rows[index];
}

void Table::operator()(const Row& row, bool is_row) {
	if (is_row) {
		addRow(row);
	}
	else {
		addColumn(row);
	}
}

unsigned int Table::getRowsCount() const {
	return rows_count;
}

unsigned int Table::getRowCells(const int index) const {
	return rows.get(index).getCellsCount();
}

void Table::addRow(const Row& row) {
	rows.add(row);
	rows_count++;
}

void Table::addColumn(const Row& column) {
	int col_length = column.getCellsCount();
	int rows_size = rows.size();
	if (col_length > rows_size) {
		std::cerr << "Column is too large.\n";
		return;
	}
	int largest_row = findLargestRow();
	for (int i = 0; i < rows_size; i++) {
		int cells_count = rows[i].getCellsCount();
		if (largest_row > cells_count) {
			for (int j = cells_count; j < largest_row; j++) {
				EmptyCell c;
				rows[i].addCell(c);
			}
			if (col_length > i) {
				rows[i].addCell(column[i]);
			}
			else {
				EmptyCell c;
				rows[i].addCell(c);
			}
		}
		else {
			if (col_length > i) {
				rows[i].addCell(column[i]);
			}
			else {
				EmptyCell c;
				rows[i].addCell(c);
			}
		}
	}
}

int Table::findLargestRow() const {
	unsigned int length = this->getRowsCount();
	unsigned int max_cells = 0;
	for (unsigned int i = 0; i < length; i++) {
		unsigned int cells = this->getRowCells(i);
		if (cells > max_cells) {
			max_cells = cells;
		}
	}
	return max_cells;
}
void Table::changeCell(const int row, const int column, const Cell& cell) {
	rows[row].changeCell(column, cell);
}

int Table::getCellValue(const int row, const int column) const {
	return rows.get(row).getCellValue(column);
}

void Table::print() const {
	for (unsigned int i = 0; i < rows.size(); i++) {
		rows.get(i).printRow();
		std::cout << std::endl;
	}
}

void Table::changeRows(const int index1, const int index2) {
	Row temp_row;
	temp_row = rows.get(index1);
	rows[index1] = rows.get(index2);
	rows[index2] = temp_row;
}

void Table::saveToFile(std::ostream& file) const {
	int length = rows.size();
	for (int i = 0; i < length; i++) {
		rows.get(i).saveCellsToFile(file);
		file << '\n';
	}
}