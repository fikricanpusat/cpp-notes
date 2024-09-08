#include "utility.hpp"

/* ==============================================================================

DEFAULT FUNCTION ARGUMENTS

e.g. In C++, you can determine default arguments for function parameters and place them AT THE END of the parameter
list in the declaration or the definition. Then an argument is not necessarily sent by the function user and default
value is used.
--------------------------- */
void default_arg(int, int, int = 10);

void default_arg(int a, int b, int c)
{
	std::cout << a << " " << b << " " << c << std::endl;
}

void default_arg_usage(void)
{
	STARTF();
	std::cout << "Assume \"void default_arg(int, int, int = 10);\"" << std::endl;
	std::cout << "When function called like func(1, 2, 3): " << std::endl;
	default_arg(1, 2, 3);
	std::cout << "When function called like func(1, 2): " << std::endl;
	default_arg(1, 2);
	ENDF();
}
/* ---------------------------

This is a compile time feature. Using default function arguments has no effect on runtime performance.
C correspondant of this feature is "Wrapper functions".

e.g. Below are some fine rules about this feature
---------------------------
int g{};
void foo1(int &r = g);			// Can be a global variable reference
void foo2(int x = 10);
void foo3(int x = foo2());		// Default value does not have to be a constant expression
void foo4(int a, int b = a);	// This is not valid.
// Assume a function declaration "void foo5(int, int)" comes from an included header:
void foo5(int, int = 10);		// You can redeclare that function to have default arguments
// Interestingly, assume a function declaration "void foo6(int, int = 10)" comes from an included header:
void foo6(int = 5, int);		// You can cummulatively redeclare that function to force first to be default arg too.
void foo6(int, int = 7);		// You cannot redeclare to change default argument value tho.


void func(void) {
	foo1();		// Refs are not used very much but fine rule-wise.
	foo3(10);	// Perfectly fine
	foo3();		// Perfectly fine, function foo2 call happens
	foo5(5);	// Perfectly fine
	...
}
---------------------------

e.g. A well used default argument structure:
---------------------------
void foo(int, int *ptr = nullptr); // Generally sets ptr when not nullptr
// strtod is a good example: https://en.cppreference.com/w/cpp/string/byte/strtof
---------------------------

FUNCTION OVERLOADING

Defining different functions with same names. It is simply because some functions do the same thing even if their
implementations are different. Consider abs functions in C. "labs", "fabs", etc. calculate the abs of "long" and
"float". In C++, the name can be simply the same for different types for the ease of user of the functions.

Function overloading has no effect on runtime but negative impact on the compile time.

Function overloading happens when two conditions are satisfied:
1. Multiple functions should have the same name on the same scope.
2. Functions with the same name on the same scope should have different signatures.
Function signatures are unique function specifiers that are comprised of function name, number of params, and param
types (Only return type is not included in the signature on a function declaration).

---------------------------
int func(int);		// Valid overload
int func(int, int);	// Valid overload
int func(double);	// Valid overload
int func(int *);	// Valid overload
double func(int *);	// Not valid since signature is the same as the upper one.
int func(int *);	// Valid, not an overload but a redeclaration
---------------------------

e.g. Some overloading rules
---------------------------
void func(int);
// Constness of a function parameter does not change the signature of the function.
void func(const int);		// This is a redeclaration since the signature is the same as the upper one
void func(int *);
void func(const int *);		// Now this is overloading (const overloading)
void func(int * const);		// Again redeclaration
typedef int itype;			// or "using itype = int;"
void func(itype);			// Redeclaration. typedef types are not counted as different types
void func(char);			// Overload
void func(signed char);		// Overload
void func(unsigned char);	// Overload, these 3 types are distinct types
void func(int32_t);			// Depends on the compiler. Compiler can alias the int32_t to int or some other type
void func(int &);			// Overload
void func(const int &);		// Overload just like ptr to constant
void func(int &&);			// Overload
void func(int, ...);		// Overload
void func(int[]);			// Redeclaration since "int[]" simply means "int *" in this context
void func(int[5]);			// Redeclaration again
---------------------------

FUNCTION OVERLOAD RESOLUTION

Function overload resolution results either one of below two:
1. Resolution succeeds
2. Resolution fails
	2.1. due to no match
	2.2. due to ambiguity

Process happens in 3 stages:

1. Compiler finds the candidate functions which are the functions with the same name on the same scope.

2. Compiler finds the "viable functions". These are the functions that would match to the call if the function was
	not overloaded. The call args count should match the function param count and the call arg types should
	be able to implicitly convert to param types. If no viable functions, resolution fails with "no match", if
	there is only one, resolution succeeds.
---------------------------
void foo1(long double);	// Viable function
void foo1(char);		// Viable function
void foo1(int, int);	// Not viable function
void foo1(int *);		// Not viable function since there is no implicit conversion from arithmetic type to ptr type

void foo2(int *);		// Not viable, no conversion from "void *" to "T *"
void foo2(void *);		// Viable
void foo2(nullptr_t);	// Not viable, no conversion from "void *" to "nullptr_t"

enum class Color {White, Red, Green, Blue};
void func3(int);	// Not viable
void func3(Color);	// Viable

void func4(bool);	// Viable
void func4(void *);	// Viable

void func(void)
{
	foo1(21);
	foo2(malloc(1000));
	foo3(Color::White);
	int x{};
	foo4(&x);
	...
}
---------------------------

3. If viable function number is more than 1, this step happens where best viable is picked or cannot be picked due to
	"ambiguity". From the viable functions. best one is tried to be picked. Types of conversion from argument to
	parameter, from worst to best:
		a. Variadic conversion
		b. User defined conversion
---------------------------
struct Data {
	int x;
	Data(int);
};

void func(void)
{
	Data mydata;
	mydata = 10; // This is legal due to "Data(int)" user defined conversion
	...
}
---------------------------
		c. Standard conversion (including implicit and narrowing conversions)
			c.1. conversion
			c.2. promotion (integral promotion -> below int to int or float to double)
			c.3. exact match (including array decay, const conversion, func to ptr conversion)
---------------------------
void foo(long double);
void foo(char);
void foo(int *);
void foo(const int *);

void func(void)
{
	foo(2.4L)	// exact match
	foo('A')	// exact match
	int a[] = {1, 2, 3, 4, 5, 6, 7};
	foo(a);		// exact match
	int x{12};
	func(&x);	// exact match
	...
}
---------------------------

e.g. Some overloading rules
---------------------------
// Functions taking default arguments
void foo1(int x, int y = 10);
void foo1(int x);
// Call by ref call by value ambiguity
void foo2(int);
void foo2(int &);
// Const overloading - an important concept
void foo3(int *ptr);
void foo3(cosnt T *ptr);	// An important type of overloading

void func(void)
{
	foo1(20);	// Ambiguity syntax error due to default arg
	int x {};
	foo2(x);	// Ambiguity syntax error due to call by ref/value
	...
}
---------------------------

e.g. An important concept of overloading is constant overloading
--------------------------- */
void overload_ptr(int *p)
{
	std::cout << "No const overload(\"void overload_ptr(int *p)\") is called." << std::endl;
}

void overload_ptr(const int *p)
{
	std::cout << "Const overload(\"void overload_ptr(const int *p)\") is called." << std::endl;
}

void const_overload_ptr_usage(void)
{
	STARTF();
	const int x{10};
	int y{10};

	std::cout << "Argument is &x where x is init as \"const int x = 10;\"\t-> ";
	overload_ptr(&x);	// Only viable function is below overload since there is no const T* -> T* conversion
	std::cout << "Argument is &y where y is init with \"int y = 10;\"\t-> ";
	overload_ptr(&y);	// Both are viable but best is exact match
	ENDF();
}
/* ---------------------------

e.g. Same applies to references too of course.
--------------------------- */
void overload_ref(int &) // Notice you don't have to name params in func def too. This rule is to create sign diffs
{
	std::cout << "\"void overload_ref(int &)\" is called." << std::endl;
}

void overload_ref(const int &)
{
	std::cout << "\"void overload_ref(const int &)\" is called." << std::endl;
}

void const_overload_ref_usage(void)
{
	STARTF();
	const int x{10};
	int y{10};

	std::cout << "Argument is &x where x is init as \"const int x{10};\"\t-> ";
	overload_ref(x); // Only viable function is below overload since there is no const T& -> T& conversion
	std::cout << "Argument is &y where y is init with \"int y{10};\"\t-> ";
	overload_ref(y); // Both are viable but best is exact match
	ENDF();
}
/* ---------------------------

e.g. Another important concept of overloading is right/left value overloading includinc const overloading.
--------------------------- */
void right_left_overload(int &)
{
	std::cout << "\"void right_left_overload(int &)\" is called." << std::endl;
}

void right_left_overload(const int &)
{
	std::cout << "\"void right_left_overload(const int &)\" is called." << std::endl;
}

void right_left_overload(int &&)
{
	std::cout << "\"void right_left_overload(int &&)\" is called." << std::endl;
}

void right_left_overload_usage(void)
{
	STARTF();
	int x{14};
	const int y{14};

	std::cout << "Argument is x where x is init as \"int x{14};\"\t\t-> ";
	right_left_overload(x); // First two are viable, best match is first due to const overloading rules.
	std::cout << "Argument is y where y is init as \"const int y{14};\"\t-> ";
	right_left_overload(y); // Only second is viable due to const overloading rules.
	std::cout << "Argument is \"2\" which is an rvalue\t\t\t-> ";
	right_left_overload(2); // Last two viable, best match last one. Second viable due to r/l overload rules
	ENDF();
}
/* ---------------------------

01:05:00

============================================================================== */

void func_args_and_overloading(void)
{
	STARTT();
	default_arg_usage();
	const_overload_ptr_usage();
	const_overload_ref_usage();
	right_left_overload_usage();
	ENDT();
}
