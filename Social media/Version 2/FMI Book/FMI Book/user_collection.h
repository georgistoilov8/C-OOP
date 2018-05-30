#pragma once

#include <iostream>
#include <fstream>
#include "user.h"

#ifndef USER_COLLECTION_INCLUDED
#define USER_COLLECTION

class UserCollection {
		User** users;
		int user_count;
		int user_capacity;
	public:
		UserCollection();
		~UserCollection();

		void clean();

		void setUserCount(const int user_count);
		void setUserCapacity(const int user_capacity);

		int getUserCount() const;
		int getUserCapacity() const;

		User** getUsers();

		User* findUserWithPost(int id);
		User* checkUserExistence(char* nickname) const;
		bool checkForAdmin() const;
		bool isNicknameUnique(const char* nickname) const;

		void resize();
		void reduce();

		void addUser(const User& new_user);
		void removeUser(const char* nickname);

		int getUniqueId() const;

		void printUsers() const;
		
		void printInformation() const;

		void loadUsersFromFile(const char* filepath);
		void loadPostsFromFile(const char* filepath);

		void saveUsersToFile(const char* filepath) const;
		void savePostsToFile(const char* filepath) const;
};

#endif // !USER_COLLECTION_INCLUDED
