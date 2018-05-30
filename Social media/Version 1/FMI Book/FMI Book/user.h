#pragma once

#include "post.h"

#include "image_post.h"
#include "link_post.h"
#include "text_post.h"

#ifndef USER_INCLUDED
#define USER

class User {
	public:
		enum category{user, moderator, admin};
		
	protected:
		int age;
		char* nickname;
		bool blocked;
		category role;

		Post** posts;
	
		int posts_capacity = 2;
		int posts_count = 0;

	public:
		User();
		User(const User& other);
		User& operator=(const User& other);
		~User();

		void copyFrom(const User& other);
		void clean();

		User* clone() const;

		void setAge(const int age);
		void setNickname(const char* nickname);
		void setBlocked(const bool blocked);
		void setRole(const category type);
		void setPosts(Post** posts, int posts_capacity, int posts_count);

		int getAge() const;
		char* getNickname() const;
		bool isBlocked() const;
		category getRole() const;
		Post** getPosts() const;
		int getPostsCapacity() const;
		int getPostsCount() const;
		Post* getPost(int index) const;

		void changeNickname(const char* nickname);

		void createPost(const Post& post);
		
		void resize();
		void reduce();

		void removePost(const int index);

		void showPosts() const;

		void printInformation() const;
};
#endif // !USER_INCLUDED
