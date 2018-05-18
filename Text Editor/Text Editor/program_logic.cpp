#include <iostream>
#include <cstring>

#include "program_logic.h"
#include "file.h"

void getInstruction(char* instruction, const int size);
char* getFilepath();
void getLineNumber(int &line);
void getThreeInputs(int &line, int &from, int &to);
void print(char* text);

void start() {
	const char* make_heading = "makeHeading";
	const char* make_italic = "makeItalic";
	const char* make_bold = "makeBold";
	const char* make_combine = "makeCombine";
	const char* add_line = "addLine";
	const char* remove = "remove";
	const char* exit = "exit";
	const char* print_file = "print";

	bool is_edit_finish = false;
	File file;
	char* filepath = getFilepath();
	print(filepath);
	file.setFilepath(filepath);
	file.read();
	while (!is_edit_finish) {
		const int size_instruction = 12;
		char instruction[size_instruction];
		getInstruction(instruction, size_instruction);
		if (strcmp(instruction, make_heading) == 0) {
			//std::cout << "Make Heading" << std::endl;
			int line;
			getLineNumber(line);
			file.makeHeading(line);
		}
		else if (strcmp(instruction, make_italic) == 0) {
			//std::cout << "Make Italic" << std::endl;

			int line, from, to;
			getThreeInputs(line, from, to);
			file.makeItalic(line, from, to);
		}
		else if (strcmp(instruction, make_bold) == 0) {
			//std::cout << "Make Bold" << std::endl;

			int line, from, to;
			getThreeInputs(line, from, to);
			file.makeBold(line, from, to);
		}
		else if (strcmp(instruction, make_combine) == 0) {
			//std::cout << "Make Combine" << std::endl;

			int line, from, to;
			getThreeInputs(line, from, to);
			file.makeCombine(line, from, to);
		}
		else if (strcmp(instruction, add_line) == 0) {
			//std::cout << "Add line" << std::endl;
			char input[1024];
			std::cin.getline(input, 1024);
			file.addLine(input);
		}
		else if (strcmp(instruction, remove) == 0) {
			//std::cout << "Remove line" << std::endl;

			int line;
			getLineNumber(line);
			file.removeLine(line);
		}
		else if (strcmp(instruction, exit) == 0) {
			//std::cout << "Exit" << std::endl;
			file.save();
			is_edit_finish = true;
		}
		else if (strcmp(instruction, print_file) == 0) {
			file.print();
		}
	}
}

void getInstruction(char* instruction, const int max_size_instr) {
	int size = 0;
	char symbol;
	bool is_finished = false;
	while (!is_finished) {
		if (size >= max_size_instr) {
			size = 0;
			std::cerr << "Instruction fail. Try again." << std::endl;
		}
		else {
			std::cin.get(symbol);
			if (symbol != ' ' && symbol != '\n') {
				//std::cout << symbol << std::endl;
				instruction[size] = symbol;
				size++;
			}
			else {
				instruction[size] = '\0';
				is_finished = true;
			}
		}
	}
}

char* getFilepath() {
	int size = 0;
	int available = 16;
	char* path = new char[available];
	char symbol;
	bool is_finished = false;
	std::cout << "Insert path to .txt file: ";
	while (!is_finished) {
		std::cin.get(symbol);
		if (symbol == '\n') {
			is_finished = true;
		}
		else {
			if (size >= available) {
				available *= 2;
				char* temp = new char[available];
				for (int i = 0; i < size; i++) {
					temp[i] = path[i];
				}
				temp[size] = symbol;
				delete[] path;
				path = temp;
			}
			else {
				path[size] = symbol;
			}
			size++;
		}
	}
	if (size >= available) {
		available += 1;
		char* temp = new char[available];
		for (int i = 0; i < size; i++) {
			temp[i] = path[i];
		}
		temp[size] = '\0';
		delete[] path;
		path = temp;
	}
	else {
		path[size] = '\0';
	}

	return path;
}

void getLineNumber(int &line) {
	do {
		std::cin >> line;
	} while (!std::cin);
}

void getThreeInputs(int &line, int &from, int &to) {
	do {
		std::cin >> line;
	} while (!std::cin);
	do {
		std::cin >> from;
	} while (!std::cin);
	do {
		std::cin >> to;
	} while (!std::cin);
}

void print(char* text) {
	while (*text) {
		std::cout << *text;
		text++;
	}
	std::cout << std::endl;
}
