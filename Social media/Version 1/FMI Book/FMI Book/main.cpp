#include <iostream>
#include "system.h"

int main() {
	
	System system;
	try {
		system.run();
	}
	catch(std::bad_alloc &e){
		std::cout << e.what() << std::endl;
		return -1;
	}
	return 0;
}