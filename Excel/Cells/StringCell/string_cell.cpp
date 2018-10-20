#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "string_cell.h"

StringCell::StringCell()
	:string(nullptr),
	 string_size(0)
{}

StringCell::StringCell(const char* new_string) {
	copyFrom(new_string);
}

StringCell::StringCell(const StringCell& other) {
	copyFrom(other.string);
}

StringCell& StringCell::operator=(const StringCell& rhs) {
	if (this != &rhs) {
		clean();
		copyFrom(rhs.string);
	}
	return *this;
}

StringCell::~StringCell() {
	clean();
}

void StringCell::print() const {
	for (unsigned int i = 0; i < string_size; i++) {
		std::cout << string[i];
	}
}

StringCell* StringCell::clone() const {
	return new StringCell(*this);
}

void StringCell::clean() {
	delete[] string;
}

void StringCell::copyFrom(const char* new_string) {
	unsigned int new_length = strlen(new_string);
	string = new(std::nothrow) char[new_length+1];
	if (!string) {
		std::cerr << "Memory allocation problem.\n";
		return;
	}
	strcpy(string, new_string);
	string_size = new_length;
}

int StringCell::getValue() const {
	bool is_number = true;
	for (unsigned int i = 0; string[i] != '\0'; i++) {
		if (string[i] < '0' || string[i] > '9') {
			is_number = false;
		}
	}
	if (!is_number) {
		return 0;
	}
	int result = 0;
	for (unsigned int i = 0; string[i] != '\0'; i++) {
		result = result * 10 + string[i] - '0';
	}
	return result;
}

void StringCell::getCellToFile(std::ostream& file) const {
	int length = strlen(string);
	char* new_string = new char[length + 3];
	strcpy(new_string, "\"");
	strcat(new_string, string);
	strcat(new_string, "\"");
	file << new_string;
	delete[] new_string;
}
