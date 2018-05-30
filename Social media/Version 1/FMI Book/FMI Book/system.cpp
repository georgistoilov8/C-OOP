#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "system.h"

System::System()
:users(nullptr),
 user_count(0),
 user_capacity(2)
{
	this->users = new User*[this->user_capacity];
}

System::~System() {
	clean();
}

void System::clean() {
	for (int i = 0; i < this->user_count; ++i) {
		delete this->users[i];
	}
	delete[] this->users;
}

void System::run() {
	const char* filepath_users = "users.dat";
	const char* filepath_posts = "posts.dat";
	loadUsersFromFile(filepath_users);
	loadPostsFromFile(filepath_posts);
	
	try {
		start();
	}
	catch (const std::bad_alloc &e) {
		std::cout << e.what() << "\n";
		throw;
	}

	savePostsToFile(filepath_posts);
	saveUsersToFile(filepath_users);
}

void System::loadUsersFromFile(const char* filepath) {
	/*
		user_type;
		int age;
		int nickname_length;
		char* nickname;
		bool blocked
	*/
	std::ifstream file(filepath, std::ios::binary);
	if (!file) {
		return;
	}

	file.seekg(0, std::ios::end);
	std::streamoff size = file.tellg();
	if (size == 0) {
		return;
	}
	file.seekg(0, std::ios::beg);

	while (!file.eof() && size > file.tellg()) {
		User::category type;
		file.read(reinterpret_cast<char*>(&type), sizeof(type));
		int age, nickname_length;
		char* nickname;
		bool blocked;
		file.read(reinterpret_cast<char*>(&age), sizeof(age));
		file.read(reinterpret_cast<char*>(&nickname_length), sizeof(nickname_length));
		nickname = new char[nickname_length+1];
		file.read(nickname, sizeof(char)*nickname_length);
		nickname[nickname_length] = '\0';
		file.read(reinterpret_cast<char*>(&blocked), sizeof(blocked));
		User user;
		user.setAge(age);
		user.setBlocked(blocked);
		user.setNickname(nickname);
		user.setRole(type);
		addUser(user);
		
		delete[] nickname;
		if (!file) {
			file.close();
			return;
		}
	}

	file.close();
}

void System::loadPostsFromFile(const char* filepath) {
	/*
		int id;
		int content_size;
		char* content;
		int user_nickname_size;
		char* user_nickname;
		post_type
	*/

	std::ifstream file(filepath, std::ios::binary);
	if (!file) {
		return;
	}

	file.seekg(0, std::ios::end);
	std::streamoff size = file.tellg();
	if (size == 0) {
		return;
	}
	file.seekg(0, std::ios::beg);
	while (!file.eof() && size > file.tellg()) {
		int id, content_size, user_nickname_size;
		char* content;
		char* user_nickname;
		Post::post_category type;
		file.read(reinterpret_cast<char*>(&id), sizeof(id));
		file.read(reinterpret_cast<char*>(&content_size), sizeof(content_size));
		content = new char[content_size+1];
		file.read(content, sizeof(char)*content_size);
		content[content_size] = '\0';
		file.read(reinterpret_cast<char*>(&user_nickname_size), sizeof(user_nickname_size));
		user_nickname = new char[user_nickname_size+1];
		file.read(user_nickname, sizeof(char)*user_nickname_size);
		user_nickname[user_nickname_size] = '\0';
		file.read(reinterpret_cast<char*>(&type), sizeof(type));
		User* user = checkUserExistence(user_nickname);
		switch (type) {
			case Post::post_category::image: {
				ImagePost post;
				post.setContent(content);
				post.setId(id);
				post.setType(type);
				user->createPost(post);
				break;
			}
			case Post::post_category::text: {
				TextPost post;
				post.setContent(content);
				post.setId(id);
				post.setType(type);
				user->createPost(post);
				break;
			}
			case Post::post_category::link: {
				LinkPost post;
				post.setContent(content);
				post.setId(id);
				post.setType(type);
				user->createPost(post);
				break;
			}
		}
		delete[] user_nickname;
		delete[] content;
		if (!file) {
			file.close();
			return;
		}
	}
	file.close();
}

void System::saveUsersToFile(const char* filepath) const {
	/*
		user_type;
		int age;
		int nickname_length;
		char* nickname;
		bool blocked
	*/

	std::fstream file(filepath, std::ios::binary | std::ios::out | std::ios::trunc);
	if (!file) {
		std::cerr << "Error in open in save\n";
		return;
	}

	for (int i = 0; i < this->user_count; ++i) {
		int age = this->users[i]->getAge();
		char* user_nickname = this->users[i]->getNickname();
		int nickname_length = strlen(user_nickname);
		bool blocked = this->users[i]->isBlocked();
		User::category type = this->users[i]->getRole();
		file.write(reinterpret_cast<char*>(&type), sizeof(type));
		file.write(reinterpret_cast<char*>(&age), sizeof(age));
		file.write(reinterpret_cast<char*>(&nickname_length), sizeof(nickname_length));
		file.write(user_nickname, sizeof(char)*nickname_length);
		file.write(reinterpret_cast<char*>(&blocked), sizeof(blocked));
		if (!file) {
			file.close();
			std::cerr << "Error in write in save\n";
			return;
		}
	}

	file.close();
}

void System::savePostsToFile(const char* filepath) const {
	/*
		int id;
		int content_size;
		char* content;
		int user_nickname_size;
		char* user_nickname;
		post_type
	*/
	std::fstream file(filepath, std::ios::binary | std::ios::out | std::ios::trunc);
	if (!file) {
		std::cerr << "Error in write in save\n";
		return;
	}

	for (int i = 0; i < this->user_count; ++i) {
		int posts_count = this->users[i]->getPostsCount();
		for (int j = 0; j < posts_count; ++j) {
			int id = this->users[i]->getPosts()[j]->getId();
			char* content = this->users[i]->getPosts()[j]->getContent();
			int content_length = strlen(content);
			char* user_nickname = this->users[i]->getNickname();
			int user_nickname_length = strlen(user_nickname);
			Post::post_category post_type = this->users[i]->getPosts()[j]->getType();
			file.write(reinterpret_cast<char*>(&id), sizeof(id));
			file.write(reinterpret_cast<char*>(&content_length), sizeof(content_length));
			file.write(content, sizeof(char)*content_length);
			file.write(reinterpret_cast<char*>(&user_nickname_length), sizeof(user_nickname_length));
			file.write(user_nickname, sizeof(char)*user_nickname_length);
			file.write(reinterpret_cast<char*>(&post_type), sizeof(post_type));
			if (!file) {
				file.close();
				std::cerr << "Error in write in save\n";
				return;
			}
		}
	}

	file.close();

}

void System::start() {
	const char* add_user = "add_user";						// add user to the system
	const char* add_moderator = "add_moderator";			// add moderator to the system
	const char* remove_user = "remove_user";				// remove user from the system
	const char* block = "block";							// block both moderator or user
	const char* unblock = "unblock";						// unblock both moderator or user
	const char* post = "post";								// create post (image, text, link)
	const char* remove_post = "remove_post";				// remove post (- || -)
	const char* view_post = "view_post";					// generate html file for one post
	const char* view_all_posts = "view_all_posts";			// generate html file for every posts of a user
	const char* info = "info";								// get information about the system
	const char* quit = "quit";								// exit and save in file
	const char* rename = "rename";							// change nickname of a user
	
	//Additional commands:
	const char* help = "help"; // shows all comands and how to struct them also current state of the system

	/* 
		Commands structure
		argument-command-rest; Rest depends on argument and command
		Example: Kiril		post		image C://Programs//Pictures//example.jpg;
				{argument}  {command}   { rest                                   }
	*/

	if (checkForAdmin()) {
		// We have admin who can operate.
	}
	else {
		std::cout << "Set admin's nickname: ";
		char* admin_nickname;
		admin_nickname = getInput();
		std::cout << "Set admin's age: ";
		int admin_age;
		getAgeInput(admin_age);
		User temp_admin;
		temp_admin.setAge(admin_age);
		temp_admin.setNickname(admin_nickname);
		temp_admin.setRole(User::category::admin);
		delete[] admin_nickname;
		addUser(temp_admin);
	}



	bool isRunning = true;
	while (isRunning) {
		char* argument;
		argument = getInput();
		if (strcmp(argument, quit) == 0) {
			std::cout << "End\n";
			isRunning = false;
		}
		else if (strcmp(argument, info) == 0) {
			printInformation();
		}
		else if (strcmp(argument, help) == 0) {
			printUsers();
		}
		else {
			// The argument is nickname of a user, moderator or admin
			char* command;
			command = getInput();
			User* actor = checkUserExistence(argument);

			if ( (strcmp(command, add_user) == 0) || (strcmp(command, add_moderator) == 0)) {
				char* nickname;
				nickname = getInput();
				int age;
				getAgeInput(age);
				if (!actor) {
					std::cout << "Sorry. Admin with nickname " << argument << " doesn't exist\n";
				}
				else {
					if (actor->getRole() == User::category::admin) {
						
						if (age > 0 && age < 100) {
							if (isNicknameUnique(nickname)) {
								User temp_user;
								temp_user.setAge(age);
								temp_user.setNickname(nickname);
								if (strcmp(command, add_user) == 0) {
									temp_user.setRole(User::category::user);
								}
								else if (strcmp(command, add_moderator) == 0) {
									temp_user.setRole(User::category::moderator);
								}
								addUser(temp_user);
							}
							else {
								std::cout << "Nickname is already used by other user." << std::endl;
							}
						}
						else {
							std::cout << "Invalid age given. It should be between 0 and 100." << std::endl;
						}
					
					}
					else {
						std::cout << "Denied. You do not have permission for this action\n";
					}
				}
				delete[] nickname;
			}
			else if (strcmp(command, remove_user) == 0) {
				char* nickname;
				nickname = getInput();
				if (!actor) {
					std::cout << "Sorry. Admin with nickname " << argument << " doesn't exist\n";
				}
				else {
					if (actor->getRole() == User::category::admin) {
						if (strcmp(actor->getNickname(), nickname) == 0) {
							std::cout << "Admin is trying to remove himself from the system." << std::endl;
						}
						else {
							removeUser(nickname);
						}

						delete[] nickname;
					}
					else {
						std::cout << "Denied. You do not have permission for this action\n";
					}
				}
				
				
			}
			else if (strcmp(command, block) == 0) {
				char* nickname;
				nickname = getInput();
				if (!actor) {
					std::cout << "Sorry. Admin or moderator with nickname " << argument << " doesn't exist\n";
				}
				else {
					if (actor->getRole() == User::category::user) {
						std::cout << "User with nickname " << argument << " doesn't have permision for this action\n";
					}
					else {
						User* subject = checkUserExistence(nickname);
						if (!subject) {
							std::cout << "User with nickname " << nickname << " doesn't have permision for this action\n";
						}
						else {
							if (actor->getRole() == User::category::moderator && subject->getRole() == User::category::admin) {
								std::cout << "Moderator can not block admin.\n";
							}
							else {
								if (subject->isBlocked()) {
									std::cout << "User " << nickname << " is already blocked\n";
								}
								else {
									subject->setBlocked(true);
									std::cout << subject->getNickname() << " is blocked.\n";
								}
							}

						}
					}
				}
				delete[] nickname;
			}
			else if (strcmp(command, unblock) == 0) {
				char* nickname;
				nickname = getInput();
				if (!actor) {
					std::cout << "Sorry. Admin or moderator with nickname " << argument << " doesn't exist\n";
				}
				else {
					if (actor->getRole() == User::category::user) {
						std::cout << "User with nickname " << argument << " doesn't have permision for this action\n";
					}
					else {
						User* subject = checkUserExistence(nickname);
						if (!subject) {
							std::cout << "User with nickname " << nickname << " doesn't have permision for this action\n";
						}
						else {
							if (actor->getRole() == User::category::moderator && strcmp(actor->getNickname(), subject->getNickname()) == 0) {
								std::cout << "Moderator " << actor->getNickname() << " is trying to unblock himself. Busted.\n";
							}
							else {
								if (actor->getRole() == User::category::moderator && subject->getRole() == User::category::admin) {
									std::cout << "Moderator " << actor->getNickname() << " can not unblock admin.\n";
								}
								else {
									if (!subject->isBlocked()) {
										std::cout << "Already unblocked\n";
									}
									else {
										subject->setBlocked(false);
										std::cout << subject->getNickname() << " is unblocked.\n";
									}
								}
							}
						}
					}
				}

				delete[] nickname;
			}
			else if (strcmp(command, post) == 0) {
				char* post_type;
				post_type = getInput();
				char* source;
				source = getInputToEnd();
				const char* image = "[image]";
				const char* text = "[text]";
				const char* link = "[link]";
				if (!actor) {
					std::cout << "Sorry. User with nickname " << argument << " doesn't exist\n";
				}
				else {
					if (actor->isBlocked()) {
						std::cout << "User " << argument << " is blocked and can not post.\n";
					}
					else {
						int id = getUniqueId();
						if (strcmp(post_type, image) == 0) {
							ImagePost image_temp;
							image_temp.setContent(source);
							image_temp.setId(id);
							image_temp.setType(ImagePost::post_category::image);
							actor->createPost(image_temp);
						}
						else if (strcmp(post_type, text) == 0) {
							TextPost text_temp;
							text_temp.setContent(source);
							text_temp.setId(id);
							text_temp.setType(ImagePost::post_category::text);
							actor->createPost(text_temp);
						}
						else if (strcmp(post_type, link) == 0) {
							LinkPost link_temp;
							link_temp.setContent(source);
							link_temp.setId(id);
							link_temp.setType(ImagePost::post_category::link);
							actor->createPost(link_temp);
						}
						else {
							std::cout << "Undefined post type\n";
						}
					}
				}

				delete[] source;
				delete[] post_type;
			}
			else if (strcmp(command, remove_post) == 0) {
				/*
					Admin can remove anyone's post.
					Moderators can remove their posts, users posts and other moderators posts.
					Users can remove only their posts.
				*/

				int id;
				getAgeInput(id);
				if (!actor) {
					std::cout << "Sorry. User with nickname " << argument << " doesn't exist\n";
				}
				else {
					User* subject = findUserWithPost(id);
					if (!subject) {
						std::cout << "Post with index " << id << " doesn't exist.\n";
					}
					else {
						if (subject->getRole() == User::category::admin && actor->getRole() != User::category::admin) {
							std::cout << "User with nickname " << argument << " can not remove admin's post.\n";
						}
						else {
							if (subject->getRole() == User::category::moderator && actor->getRole() == User::category::user) {
								std::cout << "User with nickname " << argument << " can not remove post with id " << id << std::endl;
							}
							else {
								subject->removePost(id);
							}
						}
					}
				}
			}
			else if (strcmp(command, view_post) == 0) {
				int id;
				getAgeInput(id);
				if (!actor) {
					std::cout << "Sorry. User with nickname " << argument << " doesn't exist\n";
				}
				else {
					User* subject = findUserWithPost(id);
					if (!subject) {
						std::cout << "Sorry. Post with id " << id << " doens't exist\n";
					}
					else {
						Post* post = subject->getPost(id);
						if (!post) {
							std::cout << "There is no user with post with id:" << id << std::endl;
						}
						else {
							char* content = post->wrapToHtml();
							generateHtml(content, post->getId(), actor->getNickname());
							delete[] content;
						}
					}
					
				}
			}
			else if (strcmp(command, view_all_posts) == 0) {
				if (!actor) {
					std::cout << "Sorry. User with nickname " << argument << " doesn't exist\n";
				}
				else {
					char* nickname;
					nickname = getInput();
					User* subject = checkUserExistence(nickname);
					if (!subject) {
						std::cout << "Sorry. User with nickname " << nickname << " doesn't exist\n";
					}
					else {
						generateAllPostsHtml(*subject, actor->getNickname());
					}
					delete[] nickname;
				}
			}
			else if (strcmp(command, rename) == 0) {
				if (!actor) {
					std::cout << "Sorry. User with nickname " << argument << " doesn't exist\n";
				}
				else {
					char* new_nickname;
					new_nickname = getInput();
					if (isNicknameUnique(new_nickname)) {
						actor->changeNickname(new_nickname);
					}
					else {
						std::cout << "This nickname is already in use.\n";
					}
					delete[] new_nickname;
				}
			}
			else {
				std::cout << "Undefined command\n";
			}
			delete[] command;
		}
		delete[] argument;
	}
}

void System::setUserCount(const int user_count) {
	this->user_count = user_count;
}

void System::setUserCapacity(const int user_capacity) {
	this->user_capacity = user_capacity;
}

int System::getUserCount() const {
	return this->user_count;
}

int System::getUserCapacity() const {
	return this->user_capacity;
}

User** System::getUsers() {
		return this->users;
}

char* System::getInput() {
	char* argument = new char[16];
	char symbol;
	int position = 0;
	int capacity = 16;
	while (true) {
		std::cin.get(symbol);
		if (symbol != ' ' && symbol != '\n') {
			if (position >= capacity) {
				char* new_memory = new char[capacity * 2];
				capacity *= 2;
				for (int i = 0; i < position; ++i) {
					new_memory[i] = argument[i];
				}
				delete[] argument;
				argument = new_memory;
			}
			argument[position] = symbol;
			position++;
		}
		else {
			if (position != 0) {
				if (position >= capacity) {
					char* new_memory = new char[capacity * 2];
					capacity *= 2;
					for (int i = 0; i < position; ++i) {
						new_memory[i] = argument[i];
					}
					delete[] argument;
					argument = new_memory;
				}
				argument[position] = '\0';
				break;
			}
		}
	}
	return argument;
}

char* System::getInputToEnd() {
	char* argument = new char[16];
	char symbol;
	int position = 0;
	int capacity = 16;
	while (true) {
		std::cin.get(symbol);
		if (symbol != '\n') {
			if (position >= capacity) {
				char* new_memory = new char[capacity * 2];
				capacity *= 2;
				for (int i = 0; i < position; ++i) {
					new_memory[i] = argument[i];
				}
				delete[] argument;
				argument = new_memory;
			}
			argument[position] = symbol;
			position++;
		}
		else {
			if (position != 0) {
				if (position >= capacity) {
					char* new_memory = new char[capacity * 2];
					capacity *= 2;
					for (int i = 0; i < position; ++i) {
						new_memory[i] = argument[i];
					}
					delete[] argument;
					argument = new_memory;
				}
				argument[position] = '\0';
				break;
			}
		}
	}
	return argument;
}

User* System::findUserWithPost(int id) {
	for (int i = 0; i < this->user_count; ++i) {
		int p_count = this->users[i]->getPostsCount();
		for (int j = 0; j < p_count; ++j) {
			if (id == this->users[i]->getPosts()[j]->getId()) {
				return this->users[i];
			}
		}
	}
	return nullptr;
}

User* System::checkUserExistence(char* nickname) const {
	for (int i = 0; i < user_count; ++i) {
		if (strcmp(this->users[i]->getNickname(), nickname) == 0) {
			return this->users[i];
		}
	}
	return nullptr;
}

bool System::checkForAdmin() const {
	for (int i = 0; i < this->user_count; ++i) {
		if (this->users[i]->getRole() == User::category::admin) {
			return true;
		}
	}
	return false;
}

bool System::isNicknameUnique(const char* nickname) const {
	for (int i = 0; i < this->user_count; ++i) {
		if (strcmp(this->users[i]->getNickname(), nickname) == 0) {
			return false;
		}
	}
	return true;
}

void System::resize() {
	User** new_memory = new User*[this->user_capacity * 2];
	for(int i = 0; i < this->user_count; ++i){
		new_memory[i] = this->users[i];
	}
	delete[] this->users;
	this->users = new_memory;
	this->user_capacity *= 2;
}

void System::reduce() {
	User** new_memory = new User*[this->user_capacity / 2];
	for (int i = 0; i < this->user_count; ++i) {
		new_memory[i] = this->users[i];
	}
	delete[] this->users;
	this->users = new_memory;
	this->user_capacity /= 2;
}

void System::addUser(const User& new_user) {
	if (this->user_count >= this->user_capacity) {
		resize();
	}
	
	this->users[this->user_count] = new_user.clone();
	this->user_count++;

	std::cout << "User " << this->users[this->user_count-1]->getNickname() << " successfully created." << std::endl;
}

void System::removeUser(const char* nickname) {
	for (int i = 0; i < this->user_count; ++i) {
		if (strcmp(this->users[i]->getNickname(), nickname) == 0) {
			delete this->users[i];
			this->users[i] = this->users[this->user_count - 1];
			this->user_count--;
			if ( (this->user_count <= this->user_capacity / 2) && this->user_count >= 2) {
				reduce();
			}
			std::cout << "User " << nickname << " was successfully removed.\n";
			return;
		}
	}
}

char* System::makeHtmlFileName(int post_index, char* name) {
	int name_length = strlen(name);
	char* filename = new char[name_length + 32];
	int counter = 0;
	
	strcpy(filename, name);

	filename[name_length] = '_';
	counter = name_length + 1;
	int start_pos = counter;
	if (post_index == 0) {
		filename[counter] = '0';
		counter++;
	}
	else {
		while (post_index > 0) {
			filename[counter] = '0' + post_index % 10;
			post_index /= 10;
			counter++;
		}

		for (int i = start_pos; i < counter / 2; ++i) {
			char temp = filename[i];
			filename[i] = filename[counter - 1 - i];
			filename[counter - 1 - i] = temp;
		}
	}
	filename[counter] = '.';
	filename[counter + 1] = 'h';
	filename[counter + 2] = 't';
	filename[counter + 3] = 'm';
	filename[counter + 4] = 'l';
	filename[counter + 5] = '\0';
	return filename;
}

void System::generateHtml(char* content, int post_index, char* name) {
	char* filename = makeHtmlFileName(post_index, name);
	std::fstream file(filename, std::ios::out | std::ios::trunc);
	if (!file) {
		std::cerr << "File can not open" << std::endl;
		delete[] filename;
		return;
	}
	file << content;
	if (!file) {
		std::cerr << "Error while write" << std::endl;
		file.close();
		delete[] filename;
		return;
	}
	file.close();
	std::cout << "File generated with name: " << filename << std::endl;
	delete[] filename;
}

void System::generateAllPostsHtml(const User& subject, char* name) {
	char* filename;
	filename = makeHtmlFileName(0, name);

	std::fstream file(filename, std::ios::out | std::ios::trunc);
	if (!file) {
		std::cerr << "File can not open" << std::endl;
		delete[] filename;
		return;
	}
	int posts_count = subject.getPostsCount();
	file << "<!DOCTYPE html><html><body>";
	for (int i = 0; i < posts_count; ++i) {
		char* content = subject.getPosts()[i]->getHtmlContent();
		file << content;

		if (!file) {
			std::cerr << "Error while write" << std::endl;
			file.close();
			delete[] content;
			delete[] filename;
			return;
		}
		delete[] content;
	}
	file << "</body></html>";
	file.close();
	std::cout << "File generated with name: " << filename << std::endl;
	delete[] filename;
}

int System::getUniqueId() const {
	int id = 0;
	int u_count = getUserCount();
	for (int i = 0; i < u_count; ++i) {
		int p_count = this->users[i]->getPostsCount();
		for (int j = 0; j < p_count; ++j) {
			int post_id = this->users[i]->getPosts()[j]->getId();
			if (id <= post_id) {
				id = post_id + 1;
			}
		}
	}
	return id;
}

void System::getAgeInput(int& age) const {
	while (!(std::cin >> age)) {
		std::cin.clear(); //clear bad input flag
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
		std::cout << "Invalid input. Please re-enter age for the user." << std::endl;
	}
}

void System::printUsers() const {
	std::cout << std::endl;
	std::cout << "System help guide\n";
	
	std::cout << "Information about all users and their posts: \n";
	for (int i = 0; i < this->user_count; ++i) {
		this->users[i]->printInformation();
	}

	std::cout << std::endl;

	std::cout << "Commands: \n";
	std::cout << "<actor> add_user <nickname> <age>  -> To add new user to the system\n";
	std::cout << "<actor> add_moderator <nickname> <age>  -> To add new moderator to the system\n";
	std::cout << "<actor> remove_user <nickname>  -> Remove user/moderator from the system\n";
	std::cout << "<actor> block <nickname>  -> Block user. The subject can not post when he is blocked\n";
	std::cout << "<actor> unblock <nickname>  -> Unblock user. Subject can post\n";
	std::cout << "<actor> post [text],[image],[link] <source>  -> Post text, image or link\n";
	std::cout << "<actor> remove_post <post_index>  -> Remove certain post\n";
	std::cout << "<actor> rename <nickname>  -> User change his nickname to given\n";
	std::cout << "<actor> view_post <post_index>  -> Generate HTML file with post with given index\n";
	std::cout << "<actor> view_all_posts <nickname>  -> Generate HTML file with all posts of subject\n";
	std::cout << "info  -> Gives information and statistics about the system\n";
	std::cout << "help  -> Gives all information about the system and this commands\n";
	std::cout << "quit  -> Exit the system\n";
	std::cout << std::endl;
}

void System::printInformation() const {
	int count_users = 0;
	int count_moderators = 0;
	int blocked_users = 0;
	int most_posts = 0;
	int min_age = 100;
	int max_age = 0;
	std::cout << "Blocked users: \n";
	for (int i = 0; i < user_count; ++i) {
		if (this->users[i]->getRole() == User::category::user) {
			count_users++;
		}
		else if (this->users[i]->getRole() == User::category::moderator) {
			count_moderators++;
		}

		if (this->users[i]->isBlocked()) {
			blocked_users++;
			std::cout << this->users[i]->getNickname() << std::endl;
		}

		if (this->users[i]->getPostsCount() > most_posts) {
			most_posts = this->users[i]->getPostsCount();
		}

		if (this->users[i]->getAge() > max_age) {
			max_age = this->users[i]->getAge();
		}

		if (this->users[i]->getAge() < min_age) {
			min_age = this->users[i]->getAge();
		}
	}
	std::cout << "Blocked users count: " << blocked_users << std::endl;
	std::cout << "Users in the system: " << count_users << std::endl;
	std::cout << "Moderators in the system: " << count_moderators << std::endl;

	std::cout << "Users with the most posts: \n";
	for (int i = 0; i < user_count; ++i) {
		if (this->users[i]->getPostsCount() == most_posts) {
			std::cout << this->users[i]->getNickname() << std::endl;
		}
	}

	std::cout << "Oldest users in the system: \n";
	for (int i = 0; i < user_count; ++i) {
		if (this->users[i]->getAge() == max_age) {
			std::cout << this->users[i]->getNickname() << std::endl;
		}
	}

	std::cout << "Youngest users in the system: \n";
	for (int i = 0; i < user_count; ++i) {
		if (this->users[i]->getAge() == min_age) {
			std::cout << this->users[i]->getNickname() << std::endl;
		}
	}
}