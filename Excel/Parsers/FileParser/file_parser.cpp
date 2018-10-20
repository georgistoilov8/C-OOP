#include <iostream>
#include <fstream>

#include "file_parser.h"
#include "./../../dynamic_array.h"

#include "./../../Cells/RealNumberCell/real_number_cell.h"
#include "./../../Cells/IntegerCell/integer_cell.h"
#include "./../../Cells/StringCell/string_cell.h"
#include "./../../Cells/DateCell/date_cell.h"
#include "./../../Cells/EmptyCell/empty_cell.h"

FileParser::FileParser()
:error(false)
{}

FileParser::~FileParser() {
	error = false;
}

bool FileParser::foundError() {
	return error;
}

DynamicArray<char> FileParser::getFileContent(const char* filepath) {
	std::fstream file(filepath);
	DynamicArray<char> text;
	if (!file) {
		std::cerr << "Error. File " << filepath << " can not be opened.\n";
		return text;
	}
	int i = 0;
	while (!file.eof() && file.good()) {
		char symbol = file.get();
		if (symbol >= 0) {
			text.add(symbol);
			if (!file) {
				std::cerr << "Read error\n";
				DynamicArray<char> err;
				return err;
			}
		}
		
	}
	file.close();
	return text;
}

Table FileParser::parse(const char* filepath) {
	DynamicArray<char> arr(getFileContent(filepath));
	Table table;
	unsigned int counter = 0;
	bool isParsed = false;
	int row_count = 1;
	int column_count = 1;
	Row row;
	bool isNewLine = false;
	while (!isParsed) {
		if (counter >= arr.size()) {
			table.addRow(row);
			isParsed = true;
			break;
		}
		unsigned int begin = counter;
		while (arr[counter] != ',' && arr[counter] != '\n' && arr[counter] != '\0') {
			counter++;
			if (counter >= arr.size()) {
				isParsed = true;
				break;
			}
		}
		if (arr[counter] == '\n' || counter >= arr.size()) {
			isNewLine = true;
		}
		unsigned int end = counter;
		counter++;
		unsigned int length = end - begin;
		char* new_str = new(std::nothrow) char[length + 1];
		for (unsigned int i = 0; i < length; i++) {
			new_str[i] = arr[begin + i];
		}
		new_str[length] = '\0';

		if(isContentEmpty(new_str)){
			EmptyCell c;
			row.addCell(c);
			column_count++;
		}
		else if (isContentNumber(new_str)) {
			// Cell should be Integer
			int number = extractInteger(new_str);
			IntegerCell c(number);
			row.addCell(c);
			column_count++;
		}
		else if (isContentRealNumber(new_str)) {
			double number = extractDouble(new_str);
			RealNumberCell c(number);
			row.addCell(c);
			column_count++;
		}
		else if (isContentString(new_str)) {
			char* d = extractString(new_str);
			StringCell c(d);
			row.addCell(c);
			delete[] d;
		}
		else if (isContentDate(new_str)) {
			int day, month, year;
			bool normal_write = true;
			extractDate(new_str,day, month, year, normal_write);
			DateCell c(day, month, year, normal_write);
			row.addCell(c);
			column_count++;
		}
		else {
			error = true;
			int comma_place;
			if (isCommaMissing(new_str, comma_place)) {
				std::cerr << "Error: row: " << row_count << ", after symbol number: " << comma_place << ", is missing comma.\n";
				delete new_str;
				return table;
			}
			std::cerr << "Error: row: " << row_count << ", column: " << column_count << ", " << new_str <<  " is unknown data type\n";
			delete new_str;
			return table;
		}

		delete new_str;
		if (isNewLine) {
			table.addRow(row);
			row.clean();
			row.initialize();
			isNewLine = false;
			row_count++;
			column_count = 1;
		}
	}

	return table;
}

/* Integer functions */
bool FileParser::isContentNumber(const char* content) const {
	int specific_symbol_count = 0;
	bool is_error_found = false;
	int count_digits = 0;
	for (int i = 0; content[i] != '\0'; i++) {
		if (content[i] != ' ') {
			if ( (content[i] == '+' || content[i] == '-' ) && specific_symbol_count == 0) {
				if (count_digits == 0) {
					specific_symbol_count++;
				}
				else {
					is_error_found = true;
				}
			}
			else if (!isDigit(content[i])) {
				is_error_found = true;
			}
			else {
				count_digits++;
			}
		}
	}

	if (!is_error_found) {
		return true;
	}
	else {
		return false;
	}
}

bool FileParser::isDigit(const char c) const {
	return (c >= '0' && c <= '9');
}

int FileParser::extractInteger(const char* content) const {
	bool isNumberPositive = true;
	int result = 0;
	for (int i = 0; content[i] != '\0'; i++) {
		if (content[i] != ' ') {
			if (content[i] == '-') {
				isNumberPositive = false;
			}
			else if (content[i] != '+') {
				result = result * 10 + (content[i] - '0');
			}
		}
	}
	if (!isNumberPositive) {
		return -result;
	}
	else {
		return result;
	}
}
/* End */

double FileParser::extractDouble(const char* content) const {
	double result = 0;
	bool is_left = true;
	bool is_positive = true;
	int count_right = 0;
	for (unsigned int i = 0; content[i] != '\0'; i++) {
		if (content[i] != ' ') {
			if (content[i] == '-') {
				is_positive = false;
			}
			else if (content[i] == '+') {
				//skip
			}
			else if (content[i] == '.') {
				is_left = false;
			}
			else {
				if (is_left) {
					result = 10 * result + (content[i] - '0');
				}
				else {
					result = 10 * result + (content[i] - '0');
					count_right++;
				}
			}
		}
	}
	for (int i = 0; i < count_right; i++) {
		result /= 10;
	}
	if (!is_positive) {
		return -result;
	}
	return result;
}

char* FileParser::extractString(const char* content) const {
	int counter = 0;
	int begin = 0;
	int end = 0; 
	bool is_first_found = false;
	for (int i = 0; content[i] != '\0'; i++) {
		if (content[i] == '"' && !is_first_found) { begin = i+1; is_first_found = true; }
		if (content[i] == '"') { end = i; }
	}
	int length = end - begin;
	char* result = new(std::nothrow) char[length + 1];
	if (!result) {
		std::cerr << "Memory error.\n";
		return nullptr;
	}
	for (int i = begin; i < end; i++) {
		result[i - begin] = content[i];
	}
	result[length] = '\0';
	return result;
}

bool FileParser::extractDate(const char* content, int& day, int& month, int& year, bool& normal_write) const {
	// dd.mm.yyyy - normal_write is true
	// yyyy.mm.dd - normal_write is false
	int result = 0;
	int count_dots = 0;
	for (int i = 0; content[i] != '\0'; i++) {
		if (content[i] == ' ') {
			//skip
		}
		else if(content[i] != '.'){
			result = result * 10 + content[i] - '0';
		}
		else if(content[i] == '.' || content[i] == '\0'){
			if (count_dots == 0) {
				day = result;
			}
			else if (count_dots == 1) {
				month = result;
			}
			else if (count_dots == 2) {
				year = result;
			}
			count_dots++;
			result = 0;
		}
	}
	year = result;
	if(year > 0 && year <= 30 && month > 0 && month <= 12 && day >= 1000 && day <= 9999){
		normal_write = false;
		return true;
	}
	else if (day > 0 && day <= 30 && month > 0 && month <= 12 && year >= 1000 && year <= 9999) {
		normal_write = true;
		return true;
	}
	return false;
}

bool FileParser::isContentRealNumber(const char* content) const {
	unsigned int count_floating_points = 0;
	int index = 0;
	int end = 0;
	int count_special_symbols = 0;
	for (unsigned int i = 0; content[i] != '\0'; i++) {
		if (content[i] == '.') {
			index = i;
			count_floating_points++;
		}
		else if (content[i] == '+' || content[i] == '-') {
			count_special_symbols++;
		}
		end++;
	}
	if (count_floating_points != 1 || count_special_symbols > 1) {
		return false;
	}
	char* left_side = new(std::nothrow) char[index+1];
	if (!left_side) {
		std::cerr << "Memory error.\n";
		return false;
	}
	for (int i = 0; i < index; i++) {
		left_side[i] = content[i];
	}
	left_side[index] = '\0';
	if(!isContentNumber(left_side)){
		return false;
	}
	delete[] left_side;

	char* right_side = new(std::nothrow) char[end - index];

	if (!right_side) {
		std::cerr << "Memory error.\n";
		return false;
	}
	for (int i = index + 1; i < end; i++) {			//to escape the dot; example 123.234 is separated to 123 and 234
		right_side[i-index-1] = content[i];
	}
	right_side[end - index-1] = '\0';
	if (!isContentNumber(right_side)) {
		return false;
	}
	delete[] right_side;

	return true;
}

bool FileParser::isContentEmpty(const char* content) const {
	for (unsigned int i = 0; content[i] != '\0'; i++) {
		if (content[i] != ' ' && content[i] != '\n' ) {
			return false;
		}
	}
	return true;
}

bool FileParser::isContentDate(const char* content) const {
	int count_floating_points = 0;
	for (unsigned int i = 0; content[i] != '\0'; i++) {
		if (content[i] == '.') {
			count_floating_points++;
		}
		else if (content[i] != ' ' && !isDigit(content[i])) {
			return false;
		}
	}
	if (count_floating_points != 2) { return false; }
	int day, month, year;
	bool normal_write = true;
	if (extractDate(content, day, month, year, normal_write)) {
		return true;
	}
	return false;
}

bool FileParser::isContentString(const char* content) const {
	int count_quotes = 0;
	int count_slashes = 0;
	int count_symbols = 0;
	bool is_quote_open = false;
	for (unsigned int i = 0; content[i] != '\0'; i++) {
		if (content[i] != ' ' && count_symbols == 0) {
			if (content[i] == '"' && count_symbols != 0) {
				if (!is_quote_open) {
					return false;
				}
			}
			else if(content[i] == '"' && count_symbols == 0) {
				is_quote_open = true;
			}
			else if (content[i] != '\\' && content[i] != '"') {
				count_symbols++;
			}
			else if (content[i] == '\\') {
				count_slashes++;
			}
			else if (content[i] == '"') {
				count_quotes++;
			}
		}
	}
	if (count_quotes + count_slashes % 2 != 0) {
		return false;
	}
	count_quotes = 0;
	count_slashes = 0;
	for (unsigned int i = 0; content[i] != '\0'; i++) {
		if (content[i] == '"' && i > 0) {
			if(content[i-1] != '\\'){
				count_quotes++;
			}
		}
		else if (content[i] == '"' && i == 0) {
			count_quotes++;
		}
	}
	if (count_quotes != 2) {
		return false;
	}

	return true;
}

bool FileParser::isContentCorrect(const char* content, Cell::cell_type& t) const {
	if (isContentDate(content)) {
		t = Cell::cell_type::Date;
		return true;
	}
	if (isContentNumber(content)) {
		t = Cell::cell_type::Integer;
		return true;
	}
	if (isContentRealNumber(content)) {
		t = Cell::cell_type::RealNumber;
		return true;
	}
	if (isContentString(content)) {
		t = Cell::cell_type::String;
		return true;
	}
	if (isContentEmpty(content)) {
		t = Cell::cell_type::Empty;
		return true;
	}
	return false;
}

bool FileParser::isCommaMissing(const char* content, int& comma_place) { // Not working correctly
	int counter = 0;
	int begin, end;
	int count_objects = 0;
	while (content[counter] != '\0') {
		while (content[counter] && content[counter] == ' ') {
			counter++;
		}
		begin = counter;
		while (content[counter] && content[counter] != ' ') {
			counter++;
		}
		end = counter;
		int length = end - begin;
		char* new_memory = new char[length + 1];
		for (int i = begin; i < end; i++) {
			new_memory[i - begin] = content[i];
			counter++;
		}
		new_memory[length] = '\0';
		if (isContentDate(new_memory) || isContentNumber(new_memory) || isContentRealNumber(new_memory) || isContentString(new_memory)) {
			count_objects++;
			//std::cout << new_memory << std::endl;
		}
		if (count_objects >= 2) {
			delete[] new_memory;
			return true;
		}
		else {
			comma_place = end;
		}

		delete[] new_memory;
	}
	return false;
}