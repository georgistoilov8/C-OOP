#pragma once

#include "post.h"

#include "image_post.h"
#include "link_post.h"
#include "text_post.h"

#include "post_collection.h"

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

	public:
		PostCollection posts;

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

		int getAge() const;
		char* getNickname() const;
		bool isBlocked() const;
		category getRole() const;

		void changeNickname(const char* nickname);

		void printInformation() const;
};
#endif // !USER_INCLUDED
