#include "utility.hpp"

/* ==============================================================================

TYPE DEDUCTION

Type deduction is C++ compilers checking code and deducting a type for a data. It is purely about compile time.
It is not a dynamic type system in C++. To tools to do that are:

auto
decltype
decltype (auto)
template
lambda expression

"auto" was normally a keyword in C to give variable an automatic lifetime. We know that local objects have this
storage duration, except those explicitly declared "static". So the use of "auto" becomes redundant. In time it
indeed became obsolete.

Note: An irrelevant C side note.
---------------------------
void func(void)
{
	auto x = 10;	// Valid and x is implicitly type "int"
	const y = 10;	// Valid and x is implicitly type "const int"
}
---------------------------


"auto" keyword ıs entirely different in C++ and the greatest tool for type deduction. When used, compiler deduces
type type for us for ease of programming. Variables cannot be default initialized using "auto".
e.g.
---------------------------
struct Data {}
Data foo();
void func(void)
{
	auto x;			// Not valid
	auto x = 10;	// x is deduced to be an "int" as initialized expression.
	auto x = 1.0;	// x is deduced to be a "double" as initialized expression.
	auto x = 1.0f;	// x is deduced to be a "float" as initialized expression.
	auto x = foo();	// x is deduced to be a "Data" as initialized expression.
	...
}
---------------------------

Acronyms are overly used on C++ community. Arthur Dwyer collected them under here:
https://quuxplusone.github.io/blog/2019/08/02/the-tough-guide-to-cpp-acronyms/
https://en.cppreference.com/w/cpp/language/acronyms

One of these about usage of "auto" is fetched by Herb Sutter about a coding style: AAA (Almost always auto)
e.g. Use this:
---------------------------
void func(void)
{
	auto dx = x1 - x2;
	auto p = std::make_unique<int>(42);
	auto i = 0;
}
---------------------------
e.g. Insted of this:
---------------------------
void func(void)
{
	double dx = x1 - x2;
	std::unique_ptr<int> p = std::make_unique<int>(42);
	int i = 0;
}
---------------------------

Why AAA?

1. Types can get longer and longer such that a vector type that holds list iterators... Wrıtıng the type
everytime is confusing and time consuming. Get rid of the verbosity.

e.g. Look at the difference for this vector
---------------------------
std::vector<std::list<int>::const iterator> func1(void);
void func2(void)
{
	auto x = func();
	std::vector<std::list<int>::const iterator> y = func();
}
---------------------------
e.g. Look at the difference for a function pointer
---------------------------
const char *func1(const char *, const char *);
void func2(void)
{
	auto fp = &func1;
	const char * (*fp)(cosnt char *, const char *) = &func1;
}
---------------------------

2. Using "auto" forces to initialize since auto is not valid with default initializer.

3. Provides advantage against changes.
e.g. Changing return type of foo does not effect below code.
---------------------------
int foo();
void func(void)
{
	auto x = foo();
	...
}
---------------------------

Type deduction details:

e.g. Type deduction rules when there is no declarator other than "auto".
CV (const and volatile) qualification drops before type deduction.
Array decay happens before type deduction.
---------------------------
void func(void)
{
	int a[10]{};
	auto x = a;			// x becomes "int*" since array decay happens before type deduction
	const int b[10]{};
	auto y = a;			// y becomes "const int*"
	auto z = "Orkun";	// z is of type "const char *"
	const int t = 10;
	auto l = t;			// constness is dropped. l is of type "int"
	int u = 10;
	int &r = u;
	auto y = r;			// reference is dropped. y is of type "int"
	...
}
---------------------------

e.g. Type deduction rules when there is reference declarator with "auto".
CV (const and volatile) qualification does not drop before auto.
Array decay does not happen before type deduction.
---------------------------
void func(void)
{
	int x = 20;
	auto &r1 = x;	// r1 is "int reference"
	auto &r2 = 10;	// Not valid. r2 is "int reference", 10 is prvalue expression.
	const int y = 10;
	auto &r3 = y;	// r3 is of type const int reference. When used with ref declarator, constness does not drop
	int arr1[10] {1, 2, 3, 4, 5};
	auto &r4 = arr1;	// r4 is ref to 5 sized array.
	const int arr2[10] {1, 2, 3, 4, 5};
	auto &r5 = arr2;	// r4 is ref to const 5 sized array.
	auto &r6 = "Ezgi";	// r6 is reference to const char[5] since string literals are const char array in C++.
	...
}
---------------------------

e.g. Type deduction rules when there is refref declarator with "auto". (Universal reference or forwarding reference)
In this case, type corresponding to auto is determined by the value category of the initializing expression.
If lvalue expression: corresponding type is lvalue reference (not r, only corresponding type is)
If rvalue expression: corresponding type is not reference, but type itself.
e.g. Reference collapsing. Normally there is no ref to ref in C++. In this specific type deduction example, as a
result of type deduction, ref to ref is created. Then the compiler will apply reference collapsing rules.
t && &  -> T& (lvalue reference)
t &  &  -> T& (lvalue reference)
t &  && -> T& (lvalue reference)
t && && -> T& (lvalue reference)
---------------------------
void func(void)
{
	int x = 20;
	auto &&r2 = x + 5;	// auto corresponds to int, r2 is int rvalue reference. Easy.
	auto &&r1 = x;		// auto corresponds to int&, then r1 is int& &&. Reference collapsing. r is lvalue reference.
	...
}
---------------------------

Let's see "decltype" specifier now. It is sometimes mentioned as operator. The rules of decltype changes if:
1. Operand is a name, simple enough. Same as operand.
2. Operand is not a name. Correspanding type depends on the value category of the operand.
	* if prvalue expression: corresponding type is T
	* if lvalue expression : corresponding type is T&
	* if xvalue expression : corresponding type is T&&
e.g.
---------------------------
void func(void)
{
	int x = 5;
	int &r = x;
	const int arr[10] { };
	int *ptr = &x;
	// Operand is name:
	// decltype(x)
	// decltype(ptr->x)
	// decltype(ptr.x)
	decltype(x) a = 10;			// a is simply "int"
	decltype(r) b = x;			// b is simply "int &"
	decltype(arr) c = x;		// c is simply "const int[10]"
	// Operand is not name:
	// decltype(x + 5)
	// decltype(*ptr)
	// decltype((x))
	decltype(x + 5) d = 10;		// d is simply "int"
	decltype(*ptr) e = x;		// e is "int&"" since "*ptr" is lvalue expression
	decltype(x) f = x;			// f is "int"
	decltype((x)) g = x;		// g is "int&"
	...
}
---------------------------

============================================================================== */

void type_deduction(void)
{
	STARTT();
	ENDT();
}
