#include <iostream>

#include "row.h"

Row::Row()
:cells(nullptr),
 cells_capacity(8),
 cells_size(0)
{
	cells = new(std::nothrow) Cell*[cells_capacity];
	if (!cells) {
		std::cerr << "Memory allocation error.\n";
	}
}

Row::Row(const Row& other) {
	copyFrom(other);
}

Row& Row::operator=(const Row& rhs) {
	if (this != &rhs) {
		clean();
		copyFrom(rhs);
	}

	return *this;
}

Row::~Row() {
	clean();
}

Cell& Row::operator[](const unsigned int index) {
	if (index >= cells_size) {
		throw std::out_of_range("Index out of bounds");
	}
	return *cells[index];
}

const Cell& Row::operator[](const unsigned int index) const {
	if (index >= cells_size) {
		throw std::out_of_range("Index out of bounds");
	}
	return *cells[index];
}

void Row::clean() {
	for (unsigned int i = 0; i < cells_size; i++) {
		delete cells[i];
	}
	delete[] cells;
	cells_capacity = 8;
	cells_size = 0;
}

void Row::initialize() {
	cells = new(std::nothrow) Cell*[cells_capacity];
	if (!cells) {
		std::cerr << "Memory allocation error.\n";
		return;
	}
}

void Row::copyFrom(const Row& rhs) {
	cells = new Cell*[rhs.cells_capacity];
	for (unsigned int i = 0; i < rhs.cells_size; i++) {
		cells[i] = rhs.cells[i]->clone();
	}
	cells_capacity = rhs.cells_capacity;
	cells_size = rhs.cells_size;
}

void Row::resize() {
	Cell** new_memory = new Cell*[cells_capacity * 2];
	for (unsigned int i = 0; i < cells_size; i++) {
		new_memory[i] = cells[i];
	}
	delete[] cells;
	cells = new_memory;
	cells_capacity *= 2;

}

void Row::addCell(const Cell& cell) {
	if (cells_size >= cells_capacity) {
		resize();
	}
	cells[cells_size] = cell.clone();
	cells_size++;
}

void Row::changeCell(const int index, const Cell& cell) {
	delete cells[index];
	cells[index] = cell.clone();
}

void Row::printRow() const {
	for (unsigned int i = 0; i < cells_size; i++) {
		cells[i]->print();
		std::cout << ", ";
	}
}

unsigned int Row::getCellsCount() const {
	return cells_size;
}

unsigned int Row::getCellsCapacity() const {
	return cells_capacity;
}

int Row::getCellValue(const int index) const {
	return cells[index]->getValue();
}

void Row::saveCellsToFile(std::ostream& file) {
	for (unsigned int i = 0; i < cells_size; i++) {
		cells[i]->getCellToFile(file);
		if (i + 1 < cells_size) {
			file << ',';
		}
	}
}