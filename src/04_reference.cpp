#include "utility.hpp"

/* ==============================================================================

REFERENCE SEMANTICS

C++ has less pointer usage than C. This is because of the reference semantics introduced in C++. Either reference
semantics or smart pointers takes the place of pointers. Types of references are (after Modern C++) L value reference,
and R value reference. R value references are introduced with Modern C++. Using pointer semantics and reference
semantics is exactly same in generated assembly code. Reference semantics is only an ease for the programmer.
References are simply same as const pointers in assembly level.

Most used cases of references:
* Call by reference function calls.
* Returning an object from a function.

e.g.
--------------------------- */
static void change_r(int& r)
{
	r = 45;
}

static void reference_init()
{
	STARTF();
	// int& r; // Not valid. L value references cannot be default initialized since they are const.
	int x = 10;
	int &r = x; // Means r is a name that can replace x. r is x.
	r++;
	std::cout << "x is set to " << x << std::endl;
	int y = 20;
	r = y; // r is still x. x is set to the value of y.
	std::cout << "x is set to " << x << std::endl;
	change_r(r);
	std::cout << "x is set to " << x << std::endl;
	std::cout << "address of x is " << &x << std::endl;
	std::cout << "address of r is " << &r << std::endl;
	ENDF();
}
/* ---------------------------

References cannot be default initialized. Rembember that const objects also cannot be default initialized.

Note: "https://godbolt.org/" is a website that can turn C and C++ codes into assembly codes as lots of compilers do.

e.g. A swap function in both pointer and reference semantics. Check from godbolt that assembly for both are the same.
--------------------------- */
static void swap_ptr(int *p1, int *p2)
{
	int temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

static void swap_ref(int &r1, int &r2)
{
	int temp = r1;
	r1 = r2;
	r2 = temp;
}

static void swap_cmp(void)
{
	STARTF();
	int x = 10, y = 34;
	std::cout << "Initially x = " << x << ", y = " << y << std::endl;
	swap_ptr(&x, &y);
	std::cout << "After ptr swap: x = " << x << ", y = " << y << std::endl;
	swap_ref(x, y);
	std::cout << "After ref swap: x = " << x << ", y = " << y << std::endl;
	ENDF();
}

/* ---------------------------

e.g.
--------------------------- */
static int g = 10;

static int &return_ref(void)
{
	return g;
}

static void return_ref_from_func(void)
{
	STARTF();
	std::cout << "Prev g = " << g << std::endl;
	return_ref() = 25; // return_ref() is a left value and is assignable.
	std::cout << "Next g = " << g << std::endl;
	ENDF();
}
/* ---------------------------

There cannot be a reference array in C++.

Value Category: https://medium.com/@barryrevzin/value-categories-in-c-17-f56ae54bccbe

In C, value category of a variable can be either lvalue or rvalue. The expression that points to an object are lvalue
in C. In C++, value category can be lvalue, prvalue, and xvalue.

* Variable names are always lvalue expressions.
* The expressions containing operators are generally rvalue expressions except below:
	* In C, both "x++" and "++x" are rvalue expression. In C++, "x++" rvalue, "++x" lvalue.
* Constant expressions are always prvalue expressions.
* Array elements are lvalue expressions.
* Assign operator expressions are rvalue in C while lvalue in C++.

e.g.
				C			C++
++x				R			L
--x				R			L
(x, y)			R			L
a > 5 ? x : y	R			L
(x = y)			R			L

lvalue references can only be attached to lvalue expressions. Duh.
e.g.
---------------------------
void func1(int &r)
{
	// ..
}

void func2(void)
{
	int x = 34;
	func1(x); // Valid of course
	func1(x + 5); // Not valid because rvalue expression
	...
}
---------------------------

nullptr https://en.cppreference.com/w/cpp/language/nullptr

Always use nullptr instead of using "0" constant or "NULL" macro. "nullptr" is a constant, keyword that is of type
"nullptr_t".

There is implicit conversion from nullptr_t to any pointer type but not to arithmetic types.

REFERENCES AND CONST SEMANTICS

Const correctness is a very good way to determine a code quality. References cannot be assigned another variable after
init since they are simply equivalent to const pointers.
e.g. An important example that shows the importance of const correctness. Missing const on print_array function
causes the need to remove the constness of the array. Missing constness on function parameters can cause the need to
remove const variables and objects unnecessarily.
---------------------------
void print_array(int *ptr, size_t size);

void func(void)
{
	const int a[5] = { 0, 1, 2, 3, 4 };
	print_array(a, 5); // This is syntax error since a is const. We need to remove const of a for it to be valid.
	...
}
---------------------------

e.g. Const is similar in reference to const pointers
---------------------------
void func(void)
{
	const int x = 10;
	const int & const r = x; // First const makes r reference to const, second const is ignored.
	...
}
---------------------------

e.g. Reference to an array
---------------------------
void func(void)
{
	int a[5] = { 0, 1, 2, 3, 4 };
	int(&ra)[5] = a;
	...
}
---------------------------

e.g. Below is undefined behaviour.
---------------------------
static void func_(int &r)
{
	r = 30;
}

static void func(void)
{
	const int temp = 5;
	func_((int &)temp);
	...
}
---------------------------

e.g. An interesting case. You can do below to initialize references to consts. The temp_val has automatic lifetime.
---------------------------
static void func(void)
{
	double dval = 1.2;
	int& r1 = dval;			// Syntax error due to type mismatch
	int& r2 = 10;			// Syntax error due to 10 being prvalue while r2 is lvalue reference
	const int& r1 = dval;	// Valid
		// seudo code, whats happening behind the scenes
		// int temp_val{dval};
		// const int &r = temp_val;
	const int& r2 = 10;		// Valid
		// seudo code, whats happening behind the scenes
		// int temp_val{10};
		// const int &r = temp_val;
}
--------------------------- */
static void reference_to_const_initialize(void)
{
	STARTF();
	unsigned long x = 10;
	const long& r1 = x; // r1 is reference to the midway temp variable not x.
	const int& r2 = x; // r2 is reference to the midway temp variable not x.
	++x;

	std::cout << "x : " << x << std::endl;
	std::cout << "r1: " << r1 << std::endl;
	std::cout << "r2: " << r2 << std::endl;
	ENDF();
}
/* ---------------------------
void func1(T &); // You can only call func1 with lvalue expression.
void func2(const T &); // You can call func2 both with lvalue and rvalue expressions.
---------------------------

Differences between pointer and reference semantics:

* Pointers can be default initialized while references cannot.
* Pointers can point to different objects throughout their lifetime while references can only refer to the
	same object. References are not rebindable.
* There is null pointer while there is no null reference.
* There is ptr to ptr while there is no ref to ref (other than type deduction that we will learn).

Note: C++ Core Guidelines are developed by Bjarne and Herb Sutter, and tries to set some best practices for C++
https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines

cppcon is the greatest C++ Conference. It is a great way to learn more about C++.

Rvalue references are introduced with modern C++ and added specially for move semantics. Another reason is
perfect forwarding. We will see it now for a while and explore it fully in move semantics topic.
--------------------------- */
static void rvalue_reference_example(void)
{
	STARTF();
	int x = 10;
	int &r1 = x;		// lvalue reference
	// int &&y = x;		// rvalue reference, not valid because x is lvalue.
	int &&z = x + 5;	// rvalue reference and should be assigned rvalue expression like this.
	z; 					// z is rvalue reference but is a lvalue expression (simply because z is a variable name).
	int &r2 = z;		// Then this is valid
	std::cout << "r2: " << r2 << " z: " << z << std::endl;
	r2 = 20;
	std::cout << "r2: " << r2 << " z: " << z << std::endl;
	ENDF();
}
/* ---------------------------

If a function parameter is an rvalue reference, it is for sure about move semantics.

============================================================================== */

void reference(void)
{
	STARTT();
	reference_init();
	swap_cmp();
	return_ref_from_func();
	reference_to_const_initialize();
	rvalue_reference_example();
	ENDT();
}
