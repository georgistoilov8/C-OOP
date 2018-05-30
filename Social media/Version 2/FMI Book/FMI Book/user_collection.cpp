#include "user_collection.h"

UserCollection::UserCollection()
:user_count(0),
 user_capacity(2)
{
	this->users = new User*[this->user_capacity];
}

UserCollection::~UserCollection() {
	clean();
}

void UserCollection::clean() {
	for (int i = 0; i < this->user_count; ++i) {
		delete this->users[i];
	}
	delete[] this->users;
}

void UserCollection::setUserCount(const int user_count) {
	this->user_count = user_count;
}

void UserCollection::setUserCapacity(const int user_capacity) {
	this->user_capacity = user_capacity;
}

int UserCollection::getUserCount() const {
	return this->user_count;
}

int UserCollection::getUserCapacity() const {
	return this->user_capacity;
}

User** UserCollection::getUsers() {
	return this->users;
}

User* UserCollection::findUserWithPost(int id) {
	for (int i = 0; i < this->user_count; ++i) {
		int p_count = this->users[i]->posts.getPostsCount();
		for (int j = 0; j < p_count; ++j) {
			if (id == this->users[i]->posts.getPosts()[j]->getId()) {
				return this->users[i];
			}
		}
	}
	return nullptr;
}

User* UserCollection::checkUserExistence(char* nickname) const {
	for (int i = 0; i < user_count; ++i) {
		if (strcmp(this->users[i]->getNickname(), nickname) == 0) {
			return this->users[i];
		}
	}
	return nullptr;
}

bool UserCollection::checkForAdmin() const {
	for (int i = 0; i < this->user_count; ++i) {
		if (this->users[i]->getRole() == User::category::admin) {
			return true;
		}
	}
	return false;
}

bool UserCollection::isNicknameUnique(const char* nickname) const {
	for (int i = 0; i < this->user_count; ++i) {
		if (strcmp(this->users[i]->getNickname(), nickname) == 0) {
			return false;
		}
	}
	return true;
}

void UserCollection::resize() {
	User** new_memory = new User*[this->user_capacity * 2];
	for (int i = 0; i < this->user_count; ++i) {
		new_memory[i] = this->users[i];
	}
	delete[] this->users;
	this->users = new_memory;
	this->user_capacity *= 2;
}

void UserCollection::reduce() {
	User** new_memory = new User*[this->user_capacity / 2];
	for (int i = 0; i < this->user_count; ++i) {
		new_memory[i] = this->users[i];
	}
	delete[] this->users;
	this->users = new_memory;
	this->user_capacity /= 2;
}

void UserCollection::addUser(const User& new_user) {
	if (this->user_count >= this->user_capacity) {
		resize();
	}

	this->users[this->user_count] = new_user.clone();
	this->user_count++;

	std::cout << "User " << this->users[this->user_count - 1]->getNickname() << " successfully created." << std::endl;
}

void UserCollection::removeUser(const char* nickname) {
	for (int i = 0; i < this->user_count; ++i) {
		if (strcmp(this->users[i]->getNickname(), nickname) == 0) {
			delete this->users[i];
			this->users[i] = this->users[this->user_count - 1];
			this->user_count--;
			if ((this->user_count <= this->user_capacity / 2) && this->user_count >= 2) {
				reduce();
			}
			std::cout << "User " << nickname << " was successfully removed.\n";
			return;
		}
	}
}

int UserCollection::getUniqueId() const {
	int id = 0;
	int u_count = getUserCount();
	for (int i = 0; i < u_count; ++i) {
		int p_count = this->users[i]->posts.getPostsCount();
		for (int j = 0; j < p_count; ++j) {
			int post_id = this->users[i]->posts.getPosts()[j]->getId();
			if (id <= post_id) {
				id = post_id + 1;
			}
		}
	}
	return id;
}

void UserCollection::printUsers() const {
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

void UserCollection::printInformation() const {
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

		if (this->users[i]->posts.getPostsCount() > most_posts) {
			most_posts = this->users[i]->posts.getPostsCount();
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
		if (this->users[i]->posts.getPostsCount() == most_posts) {
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

void UserCollection::loadUsersFromFile(const char* filepath) {
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
		nickname = new char[nickname_length + 1];
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

void UserCollection::loadPostsFromFile(const char* filepath) {
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
		content = new char[content_size + 1];
		file.read(content, sizeof(char)*content_size);
		content[content_size] = '\0';
		file.read(reinterpret_cast<char*>(&user_nickname_size), sizeof(user_nickname_size));
		user_nickname = new char[user_nickname_size + 1];
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
			user->posts.createPost(post);
			break;
		}
		case Post::post_category::text: {
			TextPost post;
			post.setContent(content);
			post.setId(id);
			post.setType(type);
			user->posts.createPost(post);
			break;
		}
		case Post::post_category::link: {
			LinkPost post;
			post.setContent(content);
			post.setId(id);
			post.setType(type);
			user->posts.createPost(post);
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

void UserCollection::saveUsersToFile(const char* filepath) const {
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

	for (int i = 0; i < getUserCount(); ++i) {
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

void UserCollection::savePostsToFile(const char* filepath) const {
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
		int posts_count = this->users[i]->posts.getPostsCount();
		for (int j = 0; j < posts_count; ++j) {
			int id = this->users[i]->posts.getPosts()[j]->getId();
			char* content = this->users[i]->posts.getPosts()[j]->getContent();
			int content_length = strlen(content);
			char* user_nickname = this->users[i]->getNickname();
			int user_nickname_length = strlen(user_nickname);
			Post::post_category post_type = this->users[i]->posts.getPosts()[j]->getType();
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