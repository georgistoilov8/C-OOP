#pragma once

#include <fstream>

#include "user.h"
#include "post.h"

#ifndef SYSTEM_INCLUDED
#define SYSTEM

class System {
	protected:
		/*
			Използвам масив от указатели към обекти, въпреки че 
			имам обекти от само един тип, защото мога да трия обекти
			без да извършвам заделяне на ново парче памет и копиране 
			след това на старата в новата. Това са методите resize()
			и reduce(). Тъй като имам само указател към обект, мога да 
			изтрия обекта и да оставя указателя, който не заема много памет.
			Лошото е, че в случая ще трябва да има и заделено място за 
			указателите.
		*/
		/*
			На места съм ползвал user за две неща. Единият път го разглеждам като
			потребител от цялата система(може да е админ, модератор или обикновен потребител),
			а друг като най-ниския слой потребители(обикновен потребител)
		*/
		User** users;
		int user_count;
		int user_capacity;
	public:
		System();
		~System();

		void clean();

		void run();

		void loadUsersFromFile(const char* filepath);
		void loadPostsFromFile(const char* filepath);

		void saveUsersToFile(const char* filepath) const;
		void savePostsToFile(const char* filepath) const;

		void start();

		void setUserCount(const int user_count);
		void setUserCapacity(const int user_capacity);

		int getUserCount() const;
		int getUserCapacity() const;

		User** getUsers();

		char* getInput();
		char* getInputToEnd();

		User* findUserWithPost(int id);
		User* checkUserExistence(char* nickname) const;
		bool checkForAdmin() const;
		bool isNicknameUnique(const char* nickname) const;

		void resize();
		void reduce();

		void addUser(const User& new_user);
		void removeUser(const char* nickname);
		
		char* makeHtmlFileName(int post_index, char* name);
		void generateHtml(char* content, int post_index, char* name);
		void generateAllPostsHtml(const User& subject, char* name);

		int getUniqueId() const;

		void getAgeInput(int& age) const;
		void printUsers() const;

		void printInformation() const;

};

#endif // !SYSTEM_INCLUDED
