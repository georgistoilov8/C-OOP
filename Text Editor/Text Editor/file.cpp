#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>

#include "file.h"
#include "line.h"
File::File() 
:filepath(nullptr),
 filepath_size(0),
 //lines(nullptr),
 lines_size(0),
 limit_lines(0)
{}

File::File(File& other)
:filepath(nullptr),
 filepath_size(0),
 lines(nullptr),
 lines_size(0),
 limit_lines(0)
{
	copy(other);
}

/*File& File::operator=(const File& other) {
	//if (this != &other) {
		//copy(other);
	//}
	return *this;
}*/

File::~File() {
	clean();
}

File::File(char* filepath) {
	setFilepath(filepath);
	read();
}

int File::getLimitLines() const {
	return limit_lines;
}

void File::setLimitLines(const int number) {
	limit_lines = 0;
}

int File::getFilepathSize() const {
	return filepath_size;
}

void File::setFilepathSize(int size) {
	if (size >= 0) {
		filepath_size = size;
	}
	else {
		std::cerr << "Filepath size can't be a negative number" << std::endl;
	}
}

char* File::getFilepath() const {
	return filepath;
}

void File::setFilepath(const char* path) {
	if (path) {
		setFilepathSize(strlen(path));
		filepath = new char[filepath_size + 1];
		strcpy(filepath, path);
		filepath[filepath_size] = '\0';
	}
	else {
		std::cout << "Error in path" << std::endl;
	}
}

int File::getLinesSize() const {
	return lines_size;
}

void File::setLinesSize(int size) {
	if (size >= 0) {
		lines_size = size;
	}
	else {
		std::cout << "Lines size can't be a negative number" << std::endl;
	}
}

void File::setLines(Line*& lines) {
	for (int i = 0; i < this->lines_size; i++) {
		this->lines[i] = lines[i];
	}
}

void File::copy(File& file) {
	if (!file.filepath || !file.lines) {
		return;
	}
	setFilepathSize(file.filepath_size);
	setFilepath(file.filepath);
	setLinesSize(file.lines_size);
	setLines(file.lines);
	setLimitLines(file.getLimitLines());
}

void File::clean() {
	delete[] filepath;
}

void File::read() {
	if (!filepath) {
		std::cerr << "Filepath is not set." << std::endl;
		return;
	}
	std::ifstream file(filepath);
	if (!file) {
		std::cerr << "Error while oppening " << filepath << std::endl;
		return;
	}

	int limit = 8;
	setLimitLines(limit);
	this->lines = new Line[limit];
	char line[1024];
	int counter = 0;
	while (file) {
		if(counter >= limit){
			limit *= 2;
			setLimitLines(limit);
			Line* temp_lines = new Line[limit];
			for (int i = 0; i < counter; i++) {
				temp_lines[i] = this->lines[i];
			}
			for (int i = 0; i < counter; i++) {
				this->lines[i].clearContent();
			}
			delete[] this->lines;
			this->lines = temp_lines;
		}
		file.getline(line, 1024);
		this->lines[counter].setContent(line);
		
		this->lines[counter].setWords(line);
		this->lines[counter].setWhitespaces(line);
		this->lines[counter].startWith(line);
		counter++;
	}
	file.clear();
	file.close();
	//std::cout << counter << std::endl;
	setLinesSize(counter - 1);
	for (int i = 0; i < getLinesSize(); i++) {
		this->lines[i].clearContent();
	}
}

void File::save() {
	filepath[filepath_size - 1] = '\0';
	filepath[filepath_size - 2] = 'd';
	filepath[filepath_size - 3] = 'm';
	setFilepathSize(filepath_size - 1);
	//std::cout << filepath << std::endl;

	std::ofstream file(filepath);
	if (!file) {
		std::cerr << "Error while oppening " << filepath << std::endl;
		return;
	}
	for (int i = 0; i < getLinesSize(); i++) {
		if (!lines[i].isRemoved()) {
			char* c = new char[lines[i].findSize() + 1];
			lines[i].rebuildLine(c);
			file << c;
			file << '\n';
			if (!file) {
				std::cerr << "Losho" << std::endl;
			}
			delete[] c;
		}
	}
	file.close();
}

void File::makeHeading(const int line_number) {
	this->lines[line_number].getWord(0).addFront("#");
}

void File::makeItalic(const int line_number, const int from, const int to) {
	this->lines[line_number].getWord(from).addFront("_");
	this->lines[line_number].getWord(to).addEnd("_");
}

void File::makeBold(const int line_number, const int from, const int to) {
	this->lines[line_number].getWord(from).addFront("**");
	this->lines[line_number].getWord(to).addEnd("**");
}

void File::makeCombine(const int line_number, const int from, const int to) {
	this->lines[line_number].getWord(from).addFront("_**");
	this->lines[line_number].getWord(to).addEnd("**_");
}

void File::addLine(const char* content) {
	// Doesn't work ...
	/*Line l;
	l.setContent(content);
	l.setWords(content);
	l.setWhitespaces(content);
	l.startWith(content);
	int line_size = getLinesSize();
	int limit = getLimitLines();
	if (limit > line_size + 1) {
		this->lines[limit] = l;
		setLinesSize(line_size + 1);
	}
	else {
		std::cout << limit << std::endl;
		Line* temp_lines = new Line[limit + 1];
		for (int i = 0; i < limit; i++) {
			temp_lines[i] = this->lines[i];
		}
		for (int i = 0; i < limit; i++) {
			this->lines[i].clearContent();
		}
		temp_lines[limit] = l;
		delete this->lines;
		this->lines = temp_lines;
		setLimitLines(limit + 1);
		setLinesSize(line_size + 1);
	}
	
	
	
	//temp_lines[limit] = l;
	//setLinesSize(limit + 1);
	//l.clearContent();*/
}

void File::removeLine(const int line_number) {
	this->lines[line_number].setRemove(true);
}

void File::print() {
	//std::cout << getLinesSize() << std::endl;
	for (int i = 0; i < getLinesSize(); i++) {
		lines[i].printWords();
	}
}