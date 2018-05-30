#pragma once

#include <fstream>

#include "user.h"
#include "post.h"

#ifndef SYSTEM_INCLUDED
#define SYSTEM

class System {
	protected:
		/*
			��������� ����� �� ��������� ��� ������, ������� �� 
			���� ������ �� ���� ���� ���, ������ ���� �� ���� ������
			��� �� ��������� �������� �� ���� ����� ����� � �������� 
			���� ���� �� ������� � ������. ���� �� �������� resize()
			� reduce(). ��� ���� ���� ���� �������� ��� �����, ���� �� 
			������ ������ � �� ������ ���������, ����� �� ����� ����� �����.
			������ �, �� � ������ �� ������ �� ��� � �������� ����� �� 
			�����������.
		*/
		/*
			�� ����� ��� ������� user �� ��� ����. ������� ��� �� ���������� ����
			���������� �� ������ �������(���� �� � �����, ��������� ��� ��������� ����������),
			� ���� ���� ���-������ ���� �����������(��������� ����������)
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
