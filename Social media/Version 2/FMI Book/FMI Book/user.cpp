#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "user.h"

User::User()
:age(0),
 nickname(nullptr),
 blocked(false),
 role(User::category::user),
 posts(PostCollection())
{}

User::User(const User& other)
:age(0),
 nickname(nullptr),
 blocked(false),
 role(User::category::user)
{
	copyFrom(other);
}

User& User::operator=(const User& other) {
	if (this != &other) {
		copyFrom(other);
	}
	return *this;
}

User::~User() {
	clean();
}

void User::copyFrom(const User& other) {
	clean();
	setNickname(other.getNickname());
	setAge(other.getAge());
	setBlocked(other.isBlocked());
	setRole(other.getRole());
}

void User::clean() {
	delete[] nickname;
}

User* User::clone() const {
	return (new User(*this));
}

void User::setAge(const int age) {
	if (age < 0 || age > 100) {
		std::cout << "Invalid age given" << std::endl;
		return;
	}
	this->age = age;
}

void User::setNickname(const char* nickname) {
	this->nickname = new char[strlen(nickname) + 1];
	strcpy(this->nickname, nickname);
}

void User::setBlocked(const bool blocked) {
	this->blocked = blocked;
}

void User::setRole(const category type) {
	this->role = type;
}

int User::getAge() const {
	return this->age;
}

char* User::getNickname() const {
	return this->nickname;
}

bool User::isBlocked() const {
	return this->blocked;
}

User::category User::getRole() const {
	return this->role;
}

void User::changeNickname(const char* nickname) {
	delete[] this->nickname;
	setNickname(nickname);
	std::cout << "You successfully change your nickname to: " << this->nickname << std::endl;
}

void User::printInformation() const {
	std::cout << "nickname: " << this->nickname << std::endl;
	std::cout << "Age: " << this->age << std::endl;
	std::cout << "Blocked: ";
	std::cout << (this->blocked ? "yes\n" : "no\n");
	std::cout << "Type: ";
	switch (this->role) {
		case category::user:  
			std::cout << "user\n";
			break;
		case category::moderator:
			std::cout << "moderator\n";
			break;
		case category::admin:
			std::cout << "admin\n";
			break;
	}
	std::cout << "Posts count: " << this->posts.getPostsCount() << std::endl;
	std::cout << "Posts capacity: " << this->posts.getPostsCapacity() << std::endl;
	std::cout << "Posts: \n";
	this->posts.showPosts();
}