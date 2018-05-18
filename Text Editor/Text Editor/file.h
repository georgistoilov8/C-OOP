#include "line.h"

#pragma once

#ifndef FILE_H_INCLUDED
#define FILE_H

	class File {
		private:
			char* filepath;
			int filepath_size;
			Line* lines;
			int lines_size;
			int limit_lines;
		public:
			File(); // constructor
			File(File& other); // copy constructor
			//File& operator=(const File& other); // 
			~File(); // destructor
			File(char* filepath); // will open file and get lines
			
			int getLimitLines() const;
			void setLimitLines(const int number);

			int getFilepathSize() const;
			void setFilepathSize(int size);

			char* getFilepath() const;
			void setFilepath(const char* path);

			int getLinesSize() const;
			void setLinesSize(int size);

			void setLines(Line*& lines);

			void copy(File& file);
			void clean();

			void read();
			void save();

			void makeHeading(const int line_number);
			void makeItalic(const int line_number, const int from, const int to);
			void makeBold(const int line_number, const int from, const int to);
			void makeCombine(const int line_number, const int from, const int to);
			void addLine(const char* content);
			void removeLine(const int line_number);

			void print();
	};

#endif // FILE_H_INCLUDED
