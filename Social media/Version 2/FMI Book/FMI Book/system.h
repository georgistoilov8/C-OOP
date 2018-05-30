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
