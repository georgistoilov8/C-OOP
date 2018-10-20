#include <iostream>

#include "system.h"

#include "./table.h"
#include "./row.h"
#include "./Cells/IntegerCell/integer_cell.h"
#include "./Cells/RealNumberCell/real_number_cell.h"

int main(int argc, const char* argv[]) {
	/*
	Table t;
	Row r, r2, r3;
	IntegerCell c(2);
	r.addCell(c); r.addCell(c); r.addCell(c);
	IntegerCell c2(49);
	r2.addCell(c2); r2.addCell(c2); r2.addCell(c2); r2.addCell(c2); r2.addCell(c2); r2.addCell(c);
	IntegerCell c3(97);
	r3.addCell(c3); r3.addCell(c2); 
	RealNumberCell c4(3.14);
	Row col;
	col.addCell(c4); col.addCell(c); col.addCell(c4);
	try {
		//t.addRow(r);
		t(r, true);			// When second parameter is true, we add row
							// If it's false we add column
		t(r2, true);
		t(r3, true);
		t.print();
		t(col, false);
		std::cout << "----------------\n";
		t.print();
		t[0][1].print();
		std::cout << std::endl;
		//t[0][0] = c2;
		//c = c2;
		//c.print();
		t[0][0].print();
		std::cout << std::endl;
	}
	catch (const std::out_of_range& oor) {
		std::cerr << "Out of range error: " << oor.what() << "\n";
	}
	*/
	try {
		System test;
		test.run();
	}
	catch (const std::out_of_range& oor) {
		std::cerr << "Out of range error: " << oor.what() << "\n";
	}
	catch (const std::bad_alloc& e) {
		std::cerr << "Memory allocation error: " << e.what() << "\n";
	}
	
	return 0;
}