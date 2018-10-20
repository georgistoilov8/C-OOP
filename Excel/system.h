#pragma once

#include "./table.h"
#include "./dynamic_array.h"

#ifndef SYSTEM_INCLUDED
#define SYSTEM

class System {
	DynamicArray<Table> tables;
	bool load(const char* filepath);
	void save(const char* filepath, const unsigned int table_number);
	void edit(const char* content, const unsigned int row, const unsigned int column, const unsigned int table_number);
	void print(const unsigned int table_number);
	void sort(const unsigned int table_number, int column, bool ascending_order);

	char* getInput(char c);

	int findLargestRow(const Table& table);
	public:
		System();
		void run();
};
#endif // !SYSTEM_INCLUDED
