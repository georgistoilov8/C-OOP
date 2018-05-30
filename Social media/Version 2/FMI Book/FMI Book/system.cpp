#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "system.h"

System::System()
:users(UserCollection())
{}

void System::run() {
	const char* filepath_users = "users.dat";
	const char* filepath_posts = "posts.dat";
	users.loadUsersFromFile(filepath_users);
	users.loadPostsFromFile(filepath_posts);
	
	try {
		start();
	}
	catch (const std::bad_alloc &e) {
		std::cout << e.what() << "\n";
		throw;
	}

	users.savePostsToFile(filepath_posts);
	users.saveUsersToFile(filepath_users);
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

	if (users.checkForAdmin()) {
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
		users.addUser(temp_admin);
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
			users.printInformation();
		}
		else if (strcmp(argument, help) == 0) {
			users.printUsers();
		}
		else {
			// The argument is nickname of a user, moderator or admin
			char* command;
			command = getInput();
			User* actor = users.checkUserExistence(argument);

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
							if (users.isNicknameUnique(nickname)) {
								User temp_user;
								temp_user.setAge(age);
								temp_user.setNickname(nickname);
								if (strcmp(command, add_user) == 0) {
									temp_user.setRole(User::category::user);
								}
								else if (strcmp(command, add_moderator) == 0) {
									temp_user.setRole(User::category::moderator);
								}
								users.addUser(temp_user);
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
							users.removeUser(nickname);
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
						User* subject = users.checkUserExistence(nickname);
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
						User* subject = users.checkUserExistence(nickname);
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
						int id = users.getUniqueId();
						if (strcmp(post_type, image) == 0) {
							ImagePost image_temp;
							image_temp.setContent(source);
							image_temp.setId(id);
							image_temp.setType(ImagePost::post_category::image);
							actor->posts.createPost(image_temp);
						}
						else if (strcmp(post_type, text) == 0) {
							TextPost text_temp;
							text_temp.setContent(source);
							text_temp.setId(id);
							text_temp.setType(ImagePost::post_category::text);
							actor->posts.createPost(text_temp);
						}
						else if (strcmp(post_type, link) == 0) {
							LinkPost link_temp;
							link_temp.setContent(source);
							link_temp.setId(id);
							link_temp.setType(ImagePost::post_category::link);
							actor->posts.createPost(link_temp);
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
					User* subject = users.findUserWithPost(id);
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
								subject->posts.removePost(id);
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
					User* subject = users.findUserWithPost(id);
					if (!subject) {
						std::cout << "Sorry. Post with id " << id << " doens't exist\n";
					}
					else {
						Post* post = subject->posts.getPost(id);
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
					User* subject = users.checkUserExistence(nickname);
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
					if (users.isNicknameUnique(new_nickname)) {
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
	int posts_count = subject.posts.getPostsCount();
	file << "<!DOCTYPE html><html><body>";
	for (int i = 0; i < posts_count; ++i) {
		char* content = subject.posts.getPosts()[i]->getHtmlContent();
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

void System::getAgeInput(int& age) const {
	while (!(std::cin >> age)) {
		std::cin.clear(); //clear bad input flag
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
		std::cout << "Invalid input. Please re-enter age for the user." << std::endl;
	}
}