#include "utility.hpp"

/* ==============================================================================

REFERENCE SEMANTICS

C++ has less pointer usage than C. This is because of the reference semantics introduced in C++. Either reference
semantics or smart pointers takes the place of pointers. Types of references are (after Modern C++) L value reference,
and R value reference. R value references are introduced with Modern C++. Using pointer semantics and reference
semantics is exactly same in generated assembly code. Reference semantics is only an ease for the programmer.

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
	// int& r; // Not valid. L value references cannot be default initialized.
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
static int swap_ptr(int *p1, int *p2)
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

01:39:00

============================================================================== */

void reference_semantics(void)
{
	STARTT();
	reference_init();
	swap_cmp();
	return_ref_from_func();
	ENDT();
}
