#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "user.h"

User::User()
:age(0),
 nickname(nullptr),
 blocked(false),
 role(User::category::user),
 posts_capacity(2),
 posts_count(0)
{
	this->posts = new Post*[this->posts_capacity];
}

User::User(const User& other)
:age(0),
 nickname(nullptr),
 blocked(false),
 role(User::category::user),
 posts_capacity(2),
 posts_count(0)
{
	this->posts = new Post*[this->posts_capacity];
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
	setPosts(other.getPosts(), other.getPostsCapacity(), other.getPostsCount());
}

void User::clean() {
	delete[] nickname;
	for (int i = 0; i < this->posts_count; i++) {
		delete this->posts[i];
	}
	delete[] this->posts;
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

void User::setPosts(Post** posts, int posts_capacity, int posts_count) {
	this->posts = new Post*[posts_capacity];
	this->posts_capacity = posts_capacity;
	for (int i = 0; i < posts_count; ++i) {
		createPost(*(posts[i]));
	}
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

Post** User::getPosts() const {
	return this->posts;
}

int User::getPostsCapacity() const {
	return this->posts_capacity;
}

int User::getPostsCount() const {
	return this->posts_count;
}

Post* User::getPost(int index) const {
	for (int i = 0; i < this->posts_count; ++i) {
		if (this->posts[i]->getId() == index) {
			return this->posts[i];
		}
	}
	return nullptr;
}

void User::changeNickname(const char* nickname) {
	delete[] this->nickname;
	setNickname(nickname);
	std::cout << "You successfully change your nickname to: " << this->nickname << std::endl;
}

void User::resize() {
	Post** new_memory = new Post*[this->posts_capacity * 2];
	for (int i = 0; i < this->posts_count; ++i) {
		new_memory[i] = this->posts[i];
	}
	delete[] this->posts;
	this->posts = new_memory;
	this->posts_capacity *= 2;
}

void User::reduce() {
	Post** new_memory = new Post*[this->posts_capacity / 2];
	for (int i = 0; i < this->posts_count; ++i) {
		new_memory[i] = this->posts[i];
	}
	delete[] this->posts;
	this->posts = new_memory;
	this->posts_capacity /= 2;
}

void User::createPost(const Post& post) {
	if (this->posts_capacity <= this->posts_count) {
		resize();
	}
	this->posts[this->posts_count] = post.clone();
	this->posts_count++;
	std::cout << "Post " << this->posts[this->posts_count - 1]->getId() << " created.\n";
}

void User::removePost(const int index) {
	for (int i = 0; i < this->posts_count; ++i) {
		if (this->posts[i]->getId() == index) {
			delete this->posts[i];
			this->posts[i] = this->posts[this->posts_count - 1];
			this->posts_count--;
			if ((this->posts_count <= this->posts_capacity / 2) && this->posts_count >= 2) {
				reduce();
			}
			std::cout << "Post " << index << " successfully removed\n";
			return;
		}
	}
}

void User::showPosts() const {
	for (int i = 0; i < this->posts_count; i++) {
		this->posts[i]->print();
	}
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
	std::cout << "Posts count: " << this->posts_count << std::endl;
	std::cout << "Posts capacity: " << this->posts_capacity << std::endl;
	std::cout << "Posts: \n";
	showPosts();
}