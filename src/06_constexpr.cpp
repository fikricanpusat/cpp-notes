#include "utility.hpp"

/* ==============================================================================

CONSTEXPR

e.g. Const objects can be used instead of a constant expression in C++ if the obj is init with a constant expression.
---------------------------
int foo();
void func(void)
{
	const int x = 10;		// You can initialize a const variable with a const expression
	const int y = foo();	// You can initialize a const variable with a non-const expression
	int a[x] = { 0 };		// This is legal in C++ while not legal in C. You can use const obj initialized with
							// a const expression when a constant expression is needed.
	int b[y] = { 0 };		// Not legal in both since y is not initialized with a constant expression
	...
}
----------------------------

"constexpr" keyword is introduced with Modern C++ (C++11). Just like const obj, you need to initialize a constexpr
variable. Different than "const" objects however, you should initialize a constexpr variable with a constant expression
for sure. Then, you can use a constexpr variable anywhere and when you need to use a constant expression.

e.g.
----------------------------
int foo();
void func(void)
{
	constexpr int y = foo(); // Syntax error in C++
	...
}
---------------------------

Note: Global variable addresses are constant expressions while local variable addresses are not.

eg. Functions can be also "constexpr". They should abide some rules. A few of them:
	* You cannot use static local variables. All variables should have automatic life.
	* You should initialize local variables.
If all the arguments sent into this kind of a function are constant expressions then the output of the function is
determined in compile time. Then, calls to this function yields constant expressions.
----------------------------
constexpr int square(int x)
{
	return x * x;
}

void function(void)
{
	int x = 3;
	int y = square(x + 3);	// Valid, output not determined at compile time
	int a[square(15)];		// Perfectly valid since output is constexpr and determined in compile time
	int a[square(x + 3)];	// Not valid
	...
}
----------------------------

Note: "constexpr" for a function describes the function itself, not the return type.

e.g.
--------------------------- */
constexpr bool isprime(int val)
{
	int valo = 5;
	if (val == 0 || val == 1)
		return false;
	if (val % 2 == 0)
		return val == 2;
	if (val % 3 == 0)
		return val == 3;
	if (val % 5 == 0)
		return val == 5;

	for (int i = 7; i * i <= val; i += 2)
		if (val % i == 0)
			return false;

	return true;
}

void constexpr_usage(void)
{
	STARTF();
	const int thenumber = 41;
	constexpr bool b = isprime(thenumber); // b is found in compile time. Try it through vscode.
	std::cout << "The number " << thenumber << " is " << (b ? "prime." : " not prime.") << std::endl;
	constexpr int x = 2121;
	constexpr int y = 2;
	ENDF();
}
/* ---------------------------

Programming tip: If an expressions value is determined before runtime, it's not efficient to calculate it on runtime.
"constexpr" provides this efficiency automatically. It determines in compile time if possible, not if not.

Some codes even if they are definitions, should be in header files:
* constexpr functions
* inline functions
* template codes
* inline variables

============================================================================== */

void constexpr_(void)
{
	STARTT();
	constexpr_usage();
	ENDT();
}
