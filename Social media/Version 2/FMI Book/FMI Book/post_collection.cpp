#include <iostream>

#include "post_collection.h"

PostCollection::PostCollection()
:posts_capacity(2),
 posts_count(0)
{
	this->posts = new Post*[this->posts_capacity];
}

PostCollection::PostCollection(const PostCollection& other)
:posts_capacity(2),
 posts_count(0)
{
	this->posts = new Post*[this->posts_capacity];
	copyFrom(other);
}

PostCollection& PostCollection::operator=(const PostCollection& other) {
	if (this != &other) {
		copyFrom(other);
	}
	return *this;
}

PostCollection::~PostCollection() {
	clean();
}

void PostCollection::copyFrom(const PostCollection& other) {
	setPosts(other.getPosts(), other.getPostsCapacity(), other.getPostsCount());
}

void PostCollection::clean() {
	for (int i = 0; i < this->posts_count; i++) {
		delete this->posts[i];
	}
	delete[] this->posts;
}

void PostCollection::setPosts(Post** posts, int posts_capacity, int posts_count) {
	this->posts = new Post*[posts_capacity];
	this->posts_capacity = posts_capacity;
	this->posts_count = posts_count;
	for (int i = 0; i < posts_count; ++i) {
		createPost(*(posts[i]));
	}
}

Post** PostCollection::getPosts() const {
	return this->posts;
}

int PostCollection::getPostsCapacity() const {
	return this->posts_capacity;
}

int PostCollection::getPostsCount() const {
	return this->posts_count;
}


Post* PostCollection::getPost(int index) const {
	for (int i = 0; i < this->posts_count; ++i) {
		if (this->posts[i]->getId() == index) {
			return this->posts[i];
		}
	}
	return nullptr;
}

void PostCollection::resize() {
	Post** new_memory = new Post*[this->posts_capacity * 2];
	for (int i = 0; i < this->posts_count; ++i) {
		new_memory[i] = this->posts[i];
	}
	delete[] this->posts;
	this->posts = new_memory;
	this->posts_capacity *= 2;
}

void PostCollection::reduce() {
	Post** new_memory = new Post*[this->posts_capacity / 2];
	for (int i = 0; i < this->posts_count; ++i) {
		new_memory[i] = this->posts[i];
	}
	delete[] this->posts;
	this->posts = new_memory;
	this->posts_capacity /= 2;
}

void PostCollection::createPost(const Post& post) {
	if (this->posts_capacity <= this->posts_count) {
		resize();
	}
	this->posts[this->posts_count] = post.clone();
	this->posts_count++;
	std::cout << "Post " << this->posts[this->posts_count - 1]->getId() << " created.\n";
}

void PostCollection::removePost(const int index) {
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

void PostCollection::showPosts() const {
	for (int i = 0; i < this->posts_count; i++) {
		this->posts[i]->print();
	}
}

