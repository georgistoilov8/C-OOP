#include <iostream>
#include <fstream>

#include "./system.h"
#include "./Parsers/FileParser/file_parser.h"

#include "./Cells/RealNumberCell/real_number_cell.h"
#include "./Cells/IntegerCell/integer_cell.h"
#include "./Cells/StringCell/string_cell.h"
#include "./Cells/DateCell/date_cell.h"
#include "./Cells/EmptyCell/empty_cell.h"

System::System(){}

void System::run() {
	const char* load_file = "load";
	const char* save_file = "save";
	const char* edit_cell = "edit";
	const char* print_table = "print";
	const char* sort_table = "sort";
	const char* exit = "exit";
	while (true) {
		// commands: load, save, edit, print
		char* command = getInput(' ');
		if (strcmp(load_file, command) == 0) {
			// load file
			char* filepath = getInput('\0');
			bool correct = load(filepath);
			if (correct) {
				std::cout << "File: " << filepath << " was loaded successfully.\n";
			}
			else {
				delete[] filepath;
				delete[] command;
				break;
			}
			delete[] filepath;
		}
		else if (strcmp(save_file, command) == 0) {
			// save file
			int table_number;
			std::cin >> table_number;
			char* filepath = getInput('\0');
			save(filepath, table_number);
		}
		else if (strcmp(edit_cell, command) == 0) {
			// edit cell
			int table_number, row, column;
			std::cin >> table_number;
			std::cin >> row;
			std::cin >> column;
			char* content = getInput('\0');
			edit(content, row, column, table_number);
			delete[] content;
		}
		else if (strcmp(print_table, command) == 0) {
			// print table
			int table_number;
			std::cin >> table_number;
			print(table_number);
		}
		else if (strcmp(sort_table, command) == 0) {
			// sort table
			// sort 0 1 asc/desc
			int table_number;
			std::cin >> table_number;
			int column;
			std::cin >> column;
			char* ascending = getInput(' ');
			if (strcmp(ascending, "asc") == 0) {
				sort(table_number, column, true);
			}
			else if (strcmp(ascending, "desc") == 0) {
				sort(table_number, column, false);
			}
			delete[] ascending;
		}
		else if (strcmp(exit, command) == 0) {
			delete[] command;
			break;
		}
		delete[] command;
	}
}

bool System::load(const char* filepath) {
	FileParser parser;
	Table table = parser.parse(filepath);
	if (parser.foundError()) {
		return false;
	}
	//table.print();
	tables.add(table);
	return true;
}

void System::edit(const char* content, const unsigned int row, const unsigned int column, const unsigned int table_number) {
	if (table_number >= tables.size()) {
		std::cerr << "Invalid index.\n";
		return;
	}
	if (row >= tables[table_number].getRowsCount()) {
		std::cerr << "Row " << row << " doesn't exist\n";
		return;
	}
	if (tables[table_number].getRowCells(row) < column || column < 0) {
		std::cerr << "Column " << column << " doesn't exist\n";
		return;
	}
	FileParser parser;
	Cell::cell_type t;
	bool correct = parser.isContentCorrect(content, t);
	if (!correct) {
		std::cerr << content << " is not a valid data type.\n";
		return;
	}
	else {
		switch (t) {
			case Cell::cell_type::Date: {
				int day, month, year;
				bool normal_write = true;
				parser.extractDate(content, day, month, year, normal_write);
				DateCell cell(day, month, year, normal_write);
				tables[table_number].changeCell(row, column, cell);
				break;
			}
			case Cell::cell_type::Empty: {
				EmptyCell cell;
				tables[table_number].changeCell(row, column, cell);
				break;
			}
			case Cell::cell_type::Integer: {
				int number = parser.extractInteger(content);
				IntegerCell cell(number);
				tables[table_number].changeCell(row, column, cell);
				break;
			}
			case Cell::cell_type::RealNumber: {
				double number = parser.extractDouble(content);
				RealNumberCell cell(number);
				tables[table_number].changeCell(row, column, cell);
				break;
			}
			case Cell::cell_type::String: {
				char* d = parser.extractString(content);
				StringCell cell(d);
				tables[table_number].changeCell(row, column, cell);
				delete[] d;
				break;
			}
		}
	}
	std::cout << "Edit was successfull.\n";
}

void System::save(const char* filepath, const unsigned int table_number){
	if (table_number >= tables.size()) {
		std::cerr << "Invalid index.\n";
		return;
	}
	Table table;
	table = tables.get(table_number);
	std::ofstream file(filepath);
	if (!file) {
		std::cerr << "Error while opening file.\n";
		delete[] filepath;
		return;
	}
	table.saveToFile(file);
	file.close();
	delete[] filepath;
	std::cout << "Save is successfull.\n";
}

void System::print(const unsigned int table_number) {
	if (table_number >= tables.size()) {
		std::cerr << "Invalid index.\n";
		return;
	}
	Table table;
	table = tables.get(table_number);

	table.print();
}

void System::sort(const unsigned int table_number, int column, bool ascending_order) {
	if (table_number >= tables.size()) {
		std::cerr << "Invalid index.\n";
		return;
	}
	Table table;
	table = tables.get(table_number);
	int largest_row_cells = findLargestRow(table);
	if (column < 0 || column > largest_row_cells) {
		std::cerr << "No such column\n";
		return;
	}
	int rows_length = table.getRowsCount();
	bool isSorted = false;
	while (!isSorted) {
		isSorted = true;
		for (int rows = 0; rows < rows_length-1; rows++) {
			int columns_on_row = table.getRowCells(rows);
			int value;
			if (columns_on_row <= column) {
				value = 0;
			}
			else {
				value = table.getCellValue(rows, column);
			}
			int columns_on_next_row = table.getRowCells(rows+1);
			int next_value;
			if (columns_on_next_row <= column) {
				next_value = 0;
			}
			else {
				next_value = table.getCellValue(rows+1, column);
			}
			if (ascending_order) {
				if (value > next_value) {
					table.changeRows(rows, rows + 1);
					isSorted = false;
				}
			}
			else {
				if (value < next_value) {
					table.changeRows(rows, rows + 1);
					isSorted = false;
				}
			}
		}
	}
	tables[table_number] = table;
	std::cout << "Table number:" << table_number << " was sorted successfully.\n";
}

int System::findLargestRow(const Table& table) {
	return table.findLargestRow();
}

char* System::getInput(char c) {
	char* argument = new char[8];
	char symbol;
	int position = 0;
	int capacity = 8;
	while (true) {
		std::cin.get(symbol);
		if (symbol != c && symbol != '\n') {
			if (position >= capacity) {
				char* new_memory = new char[capacity * 2];
				capacity *= 2;
				for (int i = 0; i < position; ++i) {
					new_memory[i] = argument[i];
				}
				delete[] argument;
				argument = new_memory;
			}
			argument[position] = symbol;
			position++;
		}
		else {
			if (position != 0) {
				if (position >= capacity) {
					char* new_memory = new char[capacity * 2];
					capacity *= 2;
					for (int i = 0; i < position; ++i) {
						new_memory[i] = argument[i];
					}
					delete[] argument;
					argument = new_memory;
				}
				argument[position] = '\0';
				break;
			}
		}
	}
	return argument;
}
