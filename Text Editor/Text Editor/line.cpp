#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#include "line.h"

Line::Line()
:words(nullptr),
 whitespaces(nullptr),
 word_count(0),
 content(nullptr),
 size(0),
 removed(false),
 start_word(false)
{}

Line::Line(const Line& other) {
	copy(other);
}

Line& Line::operator=(const Line& other) {
	if (this != &other) {
		copy(other);
	}
	return *this;
}

Line::~Line() {
	clear();
}

// ------ Setters and getters
int Line::getWordCount() const {
	return word_count;
}

void Line::setWordCount(const int number) {
	if (number >= 0) {
		word_count = number;
	}
}

int Line::getWhitespaceCount() const {
	return whitespaces_count;
}

void Line::setWhitespaceCount(const int number) {
	if (number >= 0) {
		whitespaces_count = number;
	}
}

int Line::getContentSize() const {
	return size;
}

void Line::setContentSize(const int number) {
	if (number >= 0) {
		size = number;
	}
}

bool Line::isRemoved() const {
	return removed;
}

void Line::setRemove(const bool b) {
	removed = b;
}

bool Line::startWithWord() const {
	return start_word;
}

void Line::setStartWord(const bool b) {
	start_word = b;
}

void Line::getContent(char* text) const {
	if (content) {
		text = new char[getContentSize() + 1];
		strcpy(text, content);
		text[getContentSize()] = '\0';
	}
}

void Line::setContent(const char* content) {
	if (content) {
		setContentSize(strlen(content));
		this->content = new char[getContentSize() + 1];
		strcpy(this->content, content);
		this->content[getContentSize()] = '\0';
	}
}

void Line::clearContent() {
	delete[] content;
}
// ------ End

Word& Line::getWord(const int number) const {
	return words[number];
}

Word& Line::getWhitespace(const int number) const {
	return whitespaces[number];
}

void Line::startWith(const char* content) {
	if (isWordLetter(content[0])) {
		setStartWord(true);
	}
	else {
		setStartWord(false);
	}
}

void Line::rebuildLine(char* final_line) {
	int size = findSize();
	//final_line = new char[size + 1];
	int w_count = getWordCount();
	int wh_count = getWhitespaceCount();
	bool word_start = startWithWord();
	//std::cout << w_count << std::endl;
	//std::cout << word_start << std::endl;
	//std::cout << wh_count << std::endl;
	if (word_start && w_count == wh_count) {
		for (int i = 0; i < w_count; i++) {
			if (i == 0) {
				char* c = new char[words[i].getSize() + 1];
				words[i].get(c);
				strcpy(final_line, c);
				delete[] c;
				//std::cout << final_line << std::endl;
				c = new char[whitespaces[i].getSize() + 1];
				whitespaces[i].get(c);
				strcat(final_line, c);
				delete[] c;
			}
			else {
				char* c = new char[words[i].getSize() + 1];
				words[i].get(c);
				//std::cout << c << std::endl;
				strcat(final_line, c);
				delete[] c;
				//std::cout << final_line << std::endl;
				c = new char[whitespaces[i].getSize() + 1];
				whitespaces[i].get(c);
				strcat(final_line, c);
				delete[] c;
			}
		}
	}
	else if (word_start && w_count != wh_count) {
		for (int i = 0; i < w_count; i++) {
			if (i == 0) {
				char* c = new char[words[i].getSize() + 1];
				words[i].get(c);
				strcpy(final_line, c);
				delete[] c;
				//std::cout << final_line << std::endl;
				if (i + 1 < w_count) {
					c = new char[whitespaces[i].getSize() + 1];
					whitespaces[i].get(c);
					strcat(final_line, c);
					delete[] c;
				}
			}
			else {
				char* c = new char[words[i].getSize() + 1];
				words[i].get(c);
				//std::cout << c << std::endl;
				strcat(final_line, c);
				delete[] c;
				//std::cout << final_line << std::endl;
				if (i + 1 < w_count) {
					c = new char[whitespaces[i].getSize() + 1];
					whitespaces[i].get(c);
					strcat(final_line, c);
					delete[] c;
				}
			}
		}
	}
	else if (!word_start && w_count == wh_count) {
		for (int i = 0; i < wh_count; i++) {
			if (i == 0) {
				char* c = new char[whitespaces[i].getSize() + 1];
				whitespaces[i].get(c);
				strcpy(final_line, c);
				delete[] c;
				//std::cout << final_line << std::endl;
				c = new char[words[i].getSize() + 1];
				words[i].get(c);
				strcat(final_line, c);
				delete[] c;
			}
			else {
				char* c = new char[whitespaces[i].getSize() + 1];
				whitespaces[i].get(c);
				//std::cout << c << std::endl;
				strcat(final_line, c);
				delete[] c;
				//std::cout << final_line << std::endl;
				c = new char[words[i].getSize() + 1];
				words[i].get(c);
				strcat(final_line, c);
				delete[] c;
			}
		}
	}
	else if (!word_start && w_count != wh_count) {
		for (int i = 0; i < wh_count; i++) {
			if (i == 0) {
				char* c = new char[whitespaces[i].getSize() + 1];
				whitespaces[i].get(c);
				strcpy(final_line, c);
				delete[] c;
				//std::cout << final_line << std::endl;
				if (i + 1 < wh_count) {
					c = new char[words[i].getSize() + 1];
					words[i].get(c);
					strcat(final_line, c);
					delete[] c;
				}
			}
			else {
				char* c = new char[whitespaces[i].getSize() + 1];
				whitespaces[i].get(c);
				//std::cout << c << std::endl;
				strcat(final_line, c);
				delete[] c;
				//std::cout << final_line << std::endl;
				if (i + 1 < wh_count) {
					c = new char[words[i].getSize() + 1];
					words[i].get(c);
					strcat(final_line, c);
					delete[] c;
				}
			}
		}
	}
}

void Line::copyWords(const Line& line) {
	delete[] this->words;
	this->words = new Word[line.getWordCount()];
	for (int i = 0; i < line.getWordCount(); i++) {
		this->words[i] = line.getWord(i);
	}
	setWordCount(line.getWordCount());
}

void Line::copyWhitespaces(const Line& line) {
	delete[] this->whitespaces;
	this->whitespaces = new Word[line.getWhitespaceCount()];
	for (int i = 0; i < line.getWhitespaceCount(); i++) {
		this->whitespaces[i] = line.getWhitespace(i);
	}
	setWhitespaceCount(line.getWhitespaceCount());
}

void Line::setWords(const char* content) {
	int counter = wordCount(content);
	setWordCount(counter);
	words = new Word[getWordCount()];
	counter = 0;
	for (int i = 0; i < getWordCount(); i++) {
		while (*content && !isWordLetter(*content)) {
			content++;
		}
		if (*content) {
			const char* start = content;
			while (isWordLetter(*content)) {
				content++;
			}
			int length = content - start;
			char* temp = new char[length + 1];
			for (int pos = 0; pos < length; pos++) {
				temp[pos] = start[pos];
			}
			temp[length] = '\0';
			words[counter].set(temp);
			counter++;
			delete[] temp;
		}
	}
	//printWords();
}

void Line::setWhitespaces(const char* content) {
	int counter = whitespaceCount(content);
	setWhitespaceCount(counter);
	whitespaces = new Word[getWhitespaceCount()];
	counter = 0;
	for (int i = 0; i < getWhitespaceCount(); i++) {
		while (*content && isWordLetter(*content)) {
			content++;
		}
		if (*content) {
			const char* start = content;
			while (!isWordLetter(*content)) {
				content++;
			}
			int length = content - start;
			char* temp = new char[length + 1];
			for (int pos = 0; pos < length; pos++) {
				temp[pos] = start[pos];
			}
			temp[length] = '\0';
			whitespaces[counter].set(temp);
			counter++;
			delete[] temp;
		}
	}
	//printWhitespaces();
}

int Line::findSize() {
	int size = 0;
	int w_count = getWordCount();
	int wh_count = getWhitespaceCount();
	for (int i = 0; i < w_count; i++) {
		size += words[i].getSize();
	}
	for (int i = 0; i < wh_count; i++) {
		size += whitespaces[i].getSize();
	}

	return size;
}

void Line::copy(const Line& other) {
	setWordCount(other.getWordCount());
	char* c = nullptr;
	other.getContent(c);
	setContent(c);
	setRemove(other.isRemoved());
	setStartWord(other.startWithWord());
	copyWords(other);
	copyWhitespaces(other);
}

void Line::clear() {
	delete[] words;
	delete[] whitespaces;
}

void Line::printWords() const {
	for (int i = 0; i < getWordCount(); i++) {
		words[i].print();
	}
}

void Line::printWhitespaces() const {
	for (int i = 0; i < getWhitespaceCount(); i++) {
		whitespaces[i].print();
	}
}

bool isWordLetter(char c){
	return (c >= 'A' && c <= 'Z') ||
		(c >= 'a' && c <= 'z') ||
		(c >= '0' && c <= '9') ||
		c == '_';
}

int wordCount(const char* text){
	int counter = 0;
	while (*text){
		while (*text && !isWordLetter(*text)){
			text++;
		}
		if (*text){
			counter++;
		}
		while (isWordLetter(*text)){
			text++;
		}
	}
	return counter;
}

int whitespaceCount(const char* text) {
	int counter = 0;
	while (*text) {
		while (isWordLetter(*text)) {
			text++;
		}
		if (*text) {
			counter++;
		}
		while (*text && !isWordLetter(*text)) {
			text++;
		}
	}
	return counter;
}