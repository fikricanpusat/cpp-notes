#include "utility.hpp"

/* ==============================================================================

INITIALIZE

https://en.cppreference.com/w/cpp/language/initialization

Initialization is giving a first value to a variable. Initialization is not an assignment.
e.g. Only copy and default init is common both for C and C++.
---------------------------
void func(void)
{
	int x = 5;	// "=" is not an operator here. This is not an assignment. This is a copy initialization.
	int y;		// This is default initialization.
	x = 10;		// An assignment.
	...
}
---------------------------

Storage Duration (Storage Class): https://en.cppreference.com/w/cpp/language/storage_duration
All objects in a program have one of the following storage durations:

1. Automatic Storage Duration: The storage for the object is allocated at the beginning of the enclosing code block
and deallocated at the end. All local objects have this storage duration, except those declared static, extern or
thread_local.

2. Static Storage Duration: The storage for the object is allocated when the program begins and deallocated when the
program ends. Only one instance of the object exists. All objects declared at namespace scope (including global
namespace) have this storage duration, plus those declared with static or extern, plus string literals.

3. Thread Storage Duration. The storage for the object is allocated when the thread begins and deallocated when the
thread ends. Each thread has its own instance of the object. Only objects declared thread_local have this storage
duration. thread_local can appear together with static or extern to adjust linkage. (since C++11)

4. Dynamic Storage Duration: Objects created by new-expressions (see new-expression for details on initialization of
these objects), implicitly created objects, and exception objects have this storage duration. The storage for the
object is allocated and deallocated upon request by using dynamic memory allocation functions if the object is
created by a new-expression, or allocated and deallocated in an unspecified way if the object is an exception object,
or overlapping with some existing storage if the object is implicitly created.

Initialization Types:

1. Default Initialization: https://en.cppreference.com/w/cpp/language/default_initialization

Default init rules are the same in both C and C++ and depends on the storage class.

* Zero initialization is performed automatically by the compiler when static storage variables are default initialized:
e.g. Below is an example of zero initialization happening for default initialization.
--------------------------- */
int x;
void print_zero_init(void)
{
	static int y;
	STARTF();
	std::cout << x << " " << y << std::endl;
	ENDF();
}
/* ---------------------------

* Automatic storage variables are initialized with indetermined (garbage) value when default initialized.
e.g. Using garbage value is undefined behavior.
--------------------------- */
void print_garbage_init(void)
{
	int x;
	STARTF();
	std::cout << x << std::endl;
	ENDF();
}
/* ---------------------------

Best Practice: Keep your variable scopes as small as possible in C++ and also in modern C. Keeping it large when no
need is called scope leakage.

Best Practice: When there is no reason not to, initialize your variables with values, not start them with
garbage value.

2. Direct Initialization: https://en.cppreference.com/w/cpp/language/direct_initialization
e.g. Below two are both direct initialization
---------------------------
void func(void)
{
	int x(10); // This is not included in C. Only C++ (Direct Initialization).
	int y{10}; // This is not included in C. Only C++ (List -Brace, Uniform- Direct Initialization).
	...
}
---------------------------

Narrowing implicit conversions are not allowed with a list initialization:
e.g.
---------------------------
void func(void)
{
	double dval = 3.96;
	int ival1 = dval;	// Narrowing conversion happens and ival is 3.
	int ival2{dval};	// Syntax error
	...
}
---------------------------
My Note: It does compile with the Makefile under this project (g++ std=c++17 without more flags).

3. Copy Initialization: https://en.cppreference.com/w/cpp/language/copy_initialization

4. Value initialization: https://en.cppreference.com/w/cpp/language/value_initialization
e.g. Zero initialization no matter what storage class is.
---------------------------
void func(void)
{
	int x{};
	...
{
---------------------------

Note:
e.g. Warning for below code for "k".
---------------------------
void func(void)
{
	int x = 10;	// Valid.
	int y(10);	// Valid.
	int z{10};	// Valid.
	int t{};	// Valid.
	int k();	// Valid but not a variable declaration. It is a function declaration.
	k = 10;		// Simply a syntax error since k is known as a function.
	...
{
---------------------------

SCOPE

https://en.cppreference.com/w/cpp/language/scope

All names has a scope in C++. If there is an identifier (not necessarily a variable), it has a scope. Scope is a code
chunk that an identifier is known/accessible. The terms "scope" and "name lookup" are embedded together.

In C, there are 4 scope categories: file, function, block, function prototype.
e.g. Scope categories.
---------------------------
void func(int x);	// x has function prototype scope
int y = 10;	//		// y has file scope
void func(int z)	// z has block scope
{
	int t = 20;		// t has block scope
	...
out:				// Function scope (In function before or after declaration. Only good for labels generally)
	...
}
---------------------------

In C++, things are a little different. There are these scope types: Namespace, class, block, function prototype,
function.

Note: There is an operator in C++ that is not in C. It is the scope resolution operator. It forces compiler to
do the name lookup on namespace scope.
e.g.
---------------------------
int x = 10;
void func(void)
{
	int x = 20;
	::x += x;	// Add local x to global x and assign to global x. "::x" is is looked up in namespace scope.
}
---------------------------

Best Practice: Legal, but never let an inner scope name shadow (name hiding, name shadowing) the outer scope one.
e.g.
---------------------------
voud func(void)
{
	int x = 10;
	if (x > 10) {
		int x = 56;
		...
	}
}
---------------------------

============================================================================== */

void initialize_things(void)
{
	STARTT();
	print_zero_init();
	print_garbage_init();
	ENDT();
}
