#include <iostream>

#include "polynomial.h"

void test();

int main() {
	
	try {
		test();
	}catch(const std::out_of_range& oor){
		std::cout << oor.what() << std::endl;
		char c;
		std::cout << "Press Enter to exit\n";
		std::cin.get(c);
	}
	
	return 0;
}

void test() {
	DynamicArray<int> arr;
	//arr[10] = 2; if you uncomment this line exception is thrown and catched.
	arr.add(0);
	arr.add(1);
	arr.add(2);
	arr.add(3);

	Polynomial<int> b(arr);
	b.print();

	Polynomial<int> c(b);
	c.print();

	DynamicArray<int> arr2;
	arr2.add(0);
	arr2.add(1);
	arr2.add(2);
	arr2.add(3);

	Polynomial<int> d(arr2);

	// Test operator ==(Polynomial);
	std::cout << "Test operator==(Polynomial)\n";
	std::cout << "Polynomial a: "; d.print();
	std::cout << "Polynomial b: "; b.print();
	std::cout << "a==b ? - ";
	if (d == b) {
		std::cout << "Yes" << std::endl;
	}
	else {
		std::cout << "No" << std::endl;
	}
	std::cout << std::endl;

	arr2.add(4);
	Polynomial<int> d2(arr2);
	std::cout << "Test operator<(Polynomial)\n";
	std::cout << "Polynomial a: "; d.print();
	std::cout << "Polynomial b: "; d2.print();
	if (d < d2) {
		std::cout << "Polynomial b is bigger" << std::endl;
	}
	else {
		std::cout << "Polynomial a is bigger" << std::endl;
	}

	std::cout << std::endl;

	// Test operator *(polynomial, T);
	std::cout << "Test operator *(polynomial, T)\n";
	d = d2 * 5;
	d.print();

	std::cout << '\n';

	// Test operator *(polynomial, T);
	std::cout << "Test operator /(polynomial, T)\n";
	d = d / 5;
	d.print();

	std::cout << '\n';

	// Test operator +(polynomial, polynomial);
	std::cout << "Test operator +(polynomial, polynomial)\n";
	std::cout << "Polynomial a: "; b.print();
	std::cout << "Polynomial b: "; d2.print();
	Polynomial<int> ex = b + d2;
	std::cout << "Polynomial c = a+b: "; ex.print();

	std::cout << '\n';

	// Test operator +=(polynomial);
	std::cout << "Test operator +=(polynomial)\n";
	std::cout << "Polynomial a: "; b.print();
	std::cout << "Polynomial b: "; d2.print();
	b += d2;
	std::cout << "Polynomial a+=b: "; b.print();

	std::cout << std::endl;

	// Test operator -=(polynomial)
	std::cout << "Test operator -=(polynomial)\n";
	std::cout << "Polynomial a: "; b.print();
	std::cout << "Polynomial b: "; d.print();
	b -= d;
	std::cout << "Polynomial a-=b: "; b.print();

	std::cout << std::endl;

	// Test operator -=(polynomial)
	std::cout << "Test operator -(polynomial, polynomial)\n";
	std::cout << "Polynomial a: "; b.print();
	std::cout << "Polynomial b: "; d.print();
	Polynomial<int> z = b - d;
	std::cout << "Polynomial c = a - b: "; z.print();

	std::cout << std::endl;

	// Test operator [](polynomial)
	std::cout << "Test operator [](T)\n";
	std::cout << "Polynomial a: "; b.print();
	std::cout << "0 coefficient - " << b[0] << std::endl;
	std::cout << "1 coefficient - " << b[1] << std::endl;
	std::cout << "4 coefficient - " << b[4] << std::endl;
	std::cout << "25 coefficient - " << b[25] << std::endl;

	std::cout << std::endl;
	// Test operator ()(T)
	std::cout << "Test operator ()(T)\n";
	std::cout << "Polynomial a: "; b.print();
	std::cout << "Result in x = 2 is: " << b(2) << std::endl;
	std::cout << "Result in x = 10 is: " << b(10) << std::endl;

	std::cout << std::endl;

	// Test operator ()(T, T)
	DynamicArray<int> test; test.add(5); test.add(6);
	Polynomial<int> test_p(test);
	std::cout << "Test operator ()(T, T)\n";
	std::cout << "Polynomial a: "; test_p.print();
	std::cout << "Integral in [a,b]=[2,3] is: " << test_p(2, 3) << std::endl;

	std::cout << std::endl;

	// Test operator ++()
	std::cout << "Test operator ++()\n";
	std::cout << "Polynomial a: "; test_p.print();
	++test_p;
	std::cout << "New polynomial after ++a: "; test_p.print();

	std::cout << std::endl;

	// Test operator ++(int)
	std::cout << "Test operator ++(int)\n";
	std::cout << "Polynomial a: "; test_p.print();
	test_p++;
	std::cout << "New polynomial after a++: "; test_p.print();

	std::cout << std::endl;


	// Test operator --()
	DynamicArray<int> test_m; test_m.add(5); test_m.add(4); test_m.add(3);
	Polynomial<int> pol_m(test_m);
	std::cout << "Test operator --()\n";
	std::cout << "Polynomial a: "; pol_m.print();
	--pol_m;
	std::cout << "New polynomial after a++: "; pol_m.print();

	std::cout << std::endl;

	// Test operator cast to int
	DynamicArray<int> test_c_i; test_c_i.add(5); test_c_i.add(4); test_c_i.add(3); test_c_i.add(0); test_c_i.add(0);
	Polynomial<int> pol_c_i(test_c_i);
	std::cout << "Test operator cast to int\n";
	std::cout << "Polynomial a: "; pol_c_i.print();
	std::cout << "Highest x is: " << (int)pol_c_i << std::endl;

	std::cout << std::endl;
	// Test operator cast to bool
	DynamicArray<double> test_c_b; test_c_b.add(0); test_c_b.add(0);
	Polynomial<double> pol_c_b(test_c_b);
	std::cout << "Test operator cast to bool\n";
	std::cout << "Polynomial a: "; pol_c_b.print();
	if (pol_c_b) {
		std::cout << "Polynomial is full of 0s(empty)\n";
	}
	else {
		std::cout << "Polynomial is not empty\n";
	}
	if (!pol_c_b) {
		std::cout << "Polynomial is not empty again but with different check\n";
	}
	else {
		std::cout << "Polynomial is full of 0s(empty) again but with different check\n";
	}

	std::cout << std::endl;

	//Test operator *(polynomial)
	std::cout << "Test operator *(polynomial, polynomial)\n";
	DynamicArray<int> arr_mult_; arr_mult_.add(1); arr_mult_.add(3); arr_mult_.add(2);
	DynamicArray<int> arr_mult2_; arr_mult2_.add(4); arr_mult2_.add(3);
	Polynomial<int> pol_mult_(arr_mult_);
	Polynomial<int> pol_mult2_(arr_mult2_);
	Polynomial<int> mult_res = pol_mult2_ * pol_mult_;
	mult_res.print();

	std::cout << std::endl;

	//Test operator *=(polynomial)
	std::cout << "Test operator *=(polynomial)\n";
	DynamicArray<int> arr_mult; arr_mult.add(1); arr_mult.add(3); arr_mult.add(2);
	DynamicArray<int> arr_mult2; arr_mult2.add(4); arr_mult2.add(3);
	Polynomial<int> pol_mult(arr_mult);
	Polynomial<int> pol_mult2(arr_mult2);
	pol_mult *= pol_mult2;
	pol_mult.print();

	std::cout << std::endl;

	// Test operator <<
	std::cout << "Test operator <<\n";
	DynamicArray<double> test_arr; test_arr.add(5.4); test_arr.add(4.2); test_arr.add(8.912); test_arr.add(10.14); test_arr.add(3.14);
	test_arr.add(4.832); test_arr.add(1.223); test_arr.add(9.15); test_arr.add(6.7821); test_arr.add(15.1009);
	Polynomial<double> test_pol(test_arr);
	std::cout << test_pol << std::endl;

	// Test operator >>
	std::cout << "Test operator >>\n";
	DynamicArray<int> t_a;
	Polynomial<int> t(t_a);
	std::cin >> t;
	std::cout << t << std::endl;

	system("pause");
}