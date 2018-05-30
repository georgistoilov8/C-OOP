#pragma once

#include <fstream>

#include "user.h"
#include "post.h"

#include "user_collection.h"

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
		UserCollection users;
	public:

		System();

		void run();

		void start();

		char* getInput();
		char* getInputToEnd();

		char* makeHtmlFileName(int post_index, char* name);
		void generateHtml(char* content, int post_index, char* name);
		void generateAllPostsHtml(const User& subject, char* name);

		void getAgeInput(int& age) const;

};

#endif // !SYSTEM_INCLUDED
