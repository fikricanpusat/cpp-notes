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

Remember: const objects also cannot be default initialized.

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
	const int a[5] = { 0, 1, 2, 3, 4 };
	int(&ra)[5] = a;
	...
}
---------------------------

============================================================================== */

void reference_semantics(void)
{
	STARTT();
	reference_init();
	swap_cmp();
	return_ref_from_func();
	ENDT();
}
