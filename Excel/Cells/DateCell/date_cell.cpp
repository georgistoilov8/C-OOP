#include <iostream>

#include "date_cell.h"

DateCell::DateCell()
	:day(1), month(1), year(0){}

DateCell::DateCell(unsigned int day, unsigned int month, unsigned int year, bool normal_write)
:day(day),
 month(month),
 year(year),
 normal_write(normal_write)
{}

DateCell::~DateCell(){}

DateCell::DateCell(const DateCell& other) {
	day = other.day;
	month = other.month;
	year = other.year;
}

DateCell& DateCell::operator=(const DateCell& rhs) {
	if (this != &rhs) {
		day = rhs.day;
		month = rhs.month;
		year = rhs.year;
	}
	return *this;
}

void DateCell::getDate(unsigned int& day, unsigned int& month, unsigned int& year, bool& normal_write) const {
	day = this->day;
	month = this->month;
	year = this->year;
	normal_write = this->normal_write;
}

DateCell* DateCell::clone() const {
	return new DateCell(*this);
}

void DateCell::print() const {
	if (normal_write) {
		std::cout << day << "." << month << "." << year;
	}
	else {
		std::cout << year << "." << month << "." << day;
	}
}

int DateCell::getValue() const {
	int result = 0;
	result += day;
	int temp_month = month;
	while (temp_month > 0) {
		if (temp_month == 1 || temp_month == 3 || temp_month == 5 || temp_month == 7 || temp_month == 8 || temp_month == 10 || temp_month == 12) {
			result += 31;
		}
		else if (temp_month == 4 || temp_month == 6 || temp_month == 9 || temp_month == 11) {
			result += 30;
		}
		else if (temp_month == 2) {
			if (year % 4 == 0) {
				result += 29;
			}
			else {
				result += 28;
			}
		}
		temp_month--;
	}
	int temp_year = year;
	while (temp_year >= 1990) {
		if (temp_year % 4 == 0) {
			result += 366;
		}
		else {
			result += 365;
		}
		temp_year--;
	}
	return result;
}

void DateCell::getCellToFile(std::ostream& file) const {
	if (normal_write) {
		file << day << '.' << month << '.' << year;
	}
	else {
		file << year << '.' << month << '.' << day;
	}
}