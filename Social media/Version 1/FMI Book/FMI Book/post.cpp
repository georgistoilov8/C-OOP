#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "post.h"

Post::Post()
:content(nullptr),
 id(0),
 type(Post::post_category::image)
{}

Post::Post(const Post& other) {
	copyFrom(other);
}

Post& Post::operator=(const Post& other) {
	if (this != &other) {
		copyFrom(other);
	}
	return *this;
}

Post::~Post() {
	clean();
}

void Post::copyFrom(const Post& other) {
	clean();
	setContent(other.getContent());
	setId(other.getId());
	setType(other.getType());
}

void Post::clean() {
	delete[] content;
}

void Post::setId(const int id) {
	this->id = id;
}

void Post::setContent(const char* content) {
	this->content = new char[strlen(content) + 1];
	strcpy(this->content, content);
}

void Post::setType(const Post::post_category type) {
	this->type = type;
}

int Post::getId() const {
	return this->id;
}

char* Post::getContent() const {
	return this->content;
}

Post::post_category Post::getType() const {
	return this->type;
}

void Post::print() const {
	std::cout << "Content: " << this->content << std::endl;
	std::cout << "Id: " << this->id << std::endl;
	std::cout << "Type: " << this->type << std::endl;
}

char* Post::wrapToHtml() const {
	return nullptr;
}

char* Post::getHtmlContent() const {
	return nullptr;
}

Post* Post::clone() const {
	return nullptr;
}