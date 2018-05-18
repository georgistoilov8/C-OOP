#include <iostream>

#include "program_logic.h"

#include "word.h"
#include "line.h"

int main() {

	try {
		start();
	}
	catch (std::bad_alloc) {
		std::cerr << "Memory error occured." << std::endl;
	}

	return 0;
}