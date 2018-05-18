#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>

#include "word.h"

Word::Word()
:word(NULL),
 size(0)
{}

Word::Word(Word& other)
:word(NULL),
 size(other.size)
{
	copy(other);
}

Word& Word::operator=(const Word& other) {
	if (this != &other) {
		copy(other);
	}
	return *this;
}

Word::~Word() {
	clear();
}

int Word::getSize() const {
	return size;
}

void Word::setSize(int size) {
	if (size >= 0) {
		this->size = size;
	}
}

void Word::get(char* word) const {
	if (this->word) {
		//word = new char[getSize()+1];
		strcpy(word, this->word);
		word[size] = '\0';
	}
}

void Word::set(const char* w) {
	if (NULL == w) {
		std::cerr << "Invalid word.";
		return;
	}
	delete[] this->word;

	setSize(strlen(w));
	this->word = new char[getSize()+1];
	this->word = strcpy(this->word, w);
	this->word[this->size] = '\0';
}

void Word::print() const {
	for (int i = 0; i < getSize(); i++) {
		std::cout << word[i];
	}
	std::cout << std::endl;
}

void Word::copy(const Word& other) {
	setSize(other.size);
	if (other.word) {
		set(other.word);
	}
}

void Word::clear() {
	delete[] word;
}

void Word::addFront(const char* text) {
	if (!text) {
		return;
	}
	char* temp = new char[strlen(text) + getSize() + 1];
	strcpy(temp, text);
	strcat(temp, word);
	temp[strlen(text) + getSize()] = '\0';
	//std::cout << temp << std::endl;
	
	set(temp);
}

void Word::addEnd(const char* text) {
	if (!text) {
		return;
	}
	char* temp = new char[strlen(text) + getSize() + 1];
	strcpy(temp, word);
	strcat(temp, text);
	temp[strlen(text) + getSize()] = '\0';

	set(temp);
}