#pragma once

#include "./../../dynamic_array.h"
#include "./../../table.h"


#ifndef FILE_PARSER_INCLUDED
#define FILE_PARSER

class FileParser {

	bool error;

	public:
		FileParser();
		~FileParser();
		Table parse(const char* filepath);
		bool foundError();
		bool isContentCorrect(const char* content, Cell::cell_type& type) const;
	
		int extractInteger(const char* content) const;
		double extractDouble(const char* content) const;
		char* extractString(const char* content) const;
		bool extractDate(const char* content, int& day, int& month, int& year, bool& normal_write) const;

	private:
		DynamicArray<char> getFileContent(const char* file);


		bool isDigit(const char c) const;
		
		bool isContentNumber(const char* content) const;
		bool isContentRealNumber(const char* content) const;
		bool isContentEmpty(const char* content) const;
		bool isContentDate(const char* content) const;
		bool isContentString(const char* content) const;

		bool isCommaMissing(const char* content, int& comma_place);
};

#endif // !FILE_PARSER_INCLUDED

