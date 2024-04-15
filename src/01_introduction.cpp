/* ==============================================================================

INTRODUCTION TO C++

C++ is designed and developed by Bjarne Stroustrup with name "C with classes". Currently it is maintained by the
C++ Standards Committee under "isocpp.org". Bjarne Stroustrup is also a part of this committee. C++ is tandardized
first in 1998.

In 2011, C++11 is introduced with drastic changes. New version is commonly called by "Modern C++". This is where
the power of C++ lies in. C++14 is a minor change, C++17, and C++20 is another major changes. These notes are based
on C++17.

Best sources to learn C++ are C++ Primer (Stanley B. Lippman, Josee Lajoie, and Barbara Moo) and The C++ Standard
Library (Nicolai M. Josuttis - another member of C++ Standards Committee). Reference website is "cppreference.com".

C++ is multi-paradigm language, supporting procedural, object-oriented, generic, and functional (e.g., lambda
functions) with high degree of compatibility and portability.

============================================================================== */



/* ==============================================================================
DIFFERENCES BETWEEN C and C++ (C INSIDE C++)

C inside C++ is not exactly matches with C Programming Language. Common parts slowly diverges more. So C++ does not
contain all C Programming Language (generally C99) in itself (e.g., compound literals, variable length arrays). So,
not all C programs compile smoothly with a C++ compiler. C is a minimalist language. The compilers are also minimal.
In C, the type control is loose while in C++ type control is strict. This strict type control causes compiler errors
for C programs that are tried to compiled with C++ compilers. Bjarne Stroustrup calls this C inside C++ "a better
C".

1. There is an ugly rule on C that is not loved by a lot called "implicit int". When type is not given, variables
are cast as signed int. In below code, function return type is implicitly determined as int in C. This is not done
in C++ and below code would not compile.
---------------------------
func()
{
	return 1;
}
---------------------------

2. Implicit function declaration. causes a name lookup difference. Below code would compile with warning in C
while it does not in C++. In C, declaration of this function is implicitly done.
---------------------------
void func()
{
	foo();
}
---------------------------

3. Old-style function definition. This does not compile for C++ while it compiles for C.
---------------------------
int func(a, b, c)
double b, c; // a is int
{
	return 1;
}
---------------------------

4. Missing return value. This compiles but causes undefined behavior in C when return value is used but does not
compile for C++.
---------------------------
int func(int x) { }
---------------------------

5. Below two function declarations mean different things in C. It means I don't give parameter information for "func",
while other means no parameter for this functuon for "foo". However, it means the same (no parameter) in C++.
---------------------------
void func();
void foo(void);

int main()
{
	func(1, 2, 3);	// No compile error in C.
	func(1, 2);		// No compile error in C.
	foo(2, 5);		// Causes compile error in C.
}
---------------------------

6. Before C99, variables should be defined before statements. After C99 and in C++, variables can be defined anywhere.
---------------------------
int main()
{
	int x;
	x = 10;
	int y;
}
---------------------------

7. Defining variables in "for" loops was not a thing before C99. It is, and best practice, after C99 and C++.
int main()
{
	for (int i = 0; i < 10; i++){
		//...
	}
}

8. Below compiles and valid in C but does not compile in C++.
---------------------------
int main()
{
	for (int i = 0; i < 10; i++){
		int i = 20;
		printf("%d", i);
	}
}
---------------------------

Differences about Types:

9. "_Bool" is a legit keyword and type in C99 while it is not in C++.

10. "bool" is a macro in C99 under "stdbool.h". "bool, true, false" are all keywords and "bool" is guaranteed to be
1 byte in size. There is implicit type conversion from other types to bool such as below in C++.
---------------------------
void func(void)
{
	int x = 12;
	bool b = x; // b would be 12 in C99, "true" in C++.
}
---------------------------

11. Character literals are "int" in C while "char" in C++;

Differences about implicit type conversions:

12. In C there are implicit type conversions:
	a) between different address types
	b) between arithmetic types and address types
but these are not allowed in C++.
---------------------------
void func(void)
{
	int x = 10;
	int *p = x;		// Allowed with warning in C but not allowed in C++
	char *p = &x;	// Allowed with warning in C but not allowed in C++
}
---------------------------

13. You should initialize a const variable in C++ while it is not a rule in C:
---------------------------
const int x; // Allowed in C but not allowed in C++
---------------------------

14. In C, global const variables' linkage is external (meaning reachable from other source files). In C++, global
const variables have internal linkage automatically just like defined with "static" implicitly.

15. In C the const variables that are initialized with a constant expressions cannot be used in places where constant
expression are needed (e.g., array sizes, switch case labels).
---------------------------
void func(void)
{
	const int x = 10;
	int a[x]; // Does not compile in C while compiles in C++.
}
---------------------------

16. Implicit type conversion from constant pointer type to pointer type is allowed while it is not allowed in C++.
void func(const int *p) {
	int *ptr = p; // Allowed in C, not allowed in C++.
	//...
}
---------------------------

17. void* ==> int* is valid in C while does not compile in C++.
---------------------------
void func(const int *p)
{
	size_t n = 100;
	int *p1 = malloc(n * sizeof(int)); // Allowed in C, not allowed in C++
	int *p2 = (int *)malloc(n * sizeof(int)); // Corrected for C++
	//...
}
---------------------------

18. typedef is needed for C while it is not in C++.
---------------------------
struct Data {
	int a, b, c;
};

union Nec {
	unsigned int x;
	char str[4];
}

enum Color {Red, Black, Gray};

void func(void)
{
	Data mydata; // Invalid in C while valid in C++.
	Nec mynec; // Invalid in C while valid in C++.
	Color mycolor; // Invalid in C while valid in C++.
}
---------------------------

19. Empty (no variable) struct is not allowed in C while it is in C++.
---------------------------
struct Data { };
---------------------------

20. auto keyword gives a variable automatic lifespan while static makes it static. But auto is not used that much
anymore since not using it defaults to auto. In C++ auto is completely different keyword. Used for type deduction.
---------------------------
auto int x = 20;	// Valid in C, not valid in C++
auto x = 20;		// Valid in C++, not valid in C
---------------------------

21. A char array can be non null terminated in C while it cannot in C++.
---------------------------
char str[4]= "umut"; // Valid in C, not allowed in C++.
---------------------------

22. String literals are const char array in C++ while they are char array in C.
---------------------------
"ali" // char [4] in C, const char [4] in C++
---------------------------

23. Enumeration types are really type "int" in background in C. However, C++ has underlying types for enumeration.
You can change this default "int" underlying type. It is not guaranteed that "enum" types are actually "int" on
background.
e.g.
---------------------------
enum Color {White, Gray, Red, Black}; // Normal C type enum definition, underlying type is int by default on C++.
enum Color : unsigned char {White, Gray, Red, Black}; // Underlying type is "unsigned char" now.
enum Color {White, Gray, Red, Black = 254L}; // Underlying type is "long" now since Black is given a long value.
enum Color : unsigned int; // You can also set underlying type in an enum declaration.
---------------------------

One critical difference between C and C++ is that, there is implicit type conversion from arithmetic types to
enum types in C ("enum" types are "int" after all) but not in C++.
e.g. All the lines below are valid in C while not best practice or good code. They are syntax error on C++.
---------------------------
enum Color {White, Gray, Red, Black};
enum Pos {Off, On, Standby};
void func(void)
{
	enum Color mycolor
	double dval = 4.5;
	mycolor = 3;
	mycolor = 23;
	mycolor = dval; // Narrowing conversion in C
	mycolor = Off;
}
---------------------------

However, there is a new "enum" category in C++ which is called "scoped enum" and generally, C type "enum" is
obsolete. The reason for the need for this new category is explained below in three examples.
e.g. Scope of color names are same as the scope of enum type name "ScreenColor" or "TrafficLight".
Below code generates syntax error in both C due to name redefinition of "Red" on name lookup.
---------------------------
// screen.h
// enum ScreenColor {White, Gray, Red, Black};
# include "screen.h"
// traffic.h
// enum TrafficLight {Yellow, Green, Red};
# include "traffic.h"
---------------------------
e.g. There is implicit conversion from "enum" types to arithmetic types. This is not a desired behavior.
---------------------------
enum ScreenColor {White, Gray, Red, Black};
void func(void)
{
	ScreenColor color = Gray;
	int ival = 23;
	color = ival; // This is valid in C but not valid in C++.
	ival = color; // This is both valid in C and C++ and a cause a new enum category.
}
---------------------------
e.g. Incomplete type / forward declaration was impossible on C++ with enum types in C++ before C++11 due to
underlying type. This is not a problem in C because "enum" is simply "int" and sizeof "int" is known by
the compiler .
---------------------------
enum Color; // Forward declaration
enum Color : unsigned char; // Also was not possible before C++11.
struct Data {
	enum Color x; // Compiler has no way knowing sizeof enum Color.
};
---------------------------
So below is the solution:
---------------------------
enum class ScreenColor {White, Red, Brown, Magenta, Black};
enum class TrafficLight {Yellow, Green, Red};
void func(void)
{
	ScreenColor color = ScreenColor::Red; // Valid
	color = Red; // Not valid
	int ival = ScreenColor::White; // Not valid
}
---------------------------

============================================================================== */

/* ==============================================================================
EXTRA NOTES

Note: Undefined behavior in C and C++ refers to behavior that can occur when a program is executed with code that
does not conform to the language specifications. In other words, the standard does not define how the program should
behave in such cases. This can lead to unpredictable results that may vary depending on the compiler, platform,
optimization settings, and other factors.
e.g.
* Dereferencing a null pointer.
* Accessing an array beyond its bounds.
* Modifying a variable more than once between two sequence points in C.
* Using an uninitialized variable.
* Performing arithmetic operations that result in overflow or underflow.
* Using format specifiers that do not match the corresponding arguments in functions like printf and scanf.
* Using the result of a function that modifies one of its arguments before the sequence point.
* Accessing memory after it has been deallocated (a dangling pointer).
* Dividing by zero.
* Using a non-constant expression in a case label in a switch statement in C++.
* Changing a const variable in C. Changing a string literal in C and C++.
e.g. An interesting undefined behavior that is encountered a lot:
---------------------------
char *p = "temp";
*p = 'k'; // Changing a string literal is ub.
---------------------------


Note: Unspecified behaivours occur when developers use a functionality and compilers implement different
ways for this functionality choosing from multiple possible ways explained in language standards.
e.g. char type can be unsigned or signed in different implementations.
e.g. Different compilers keeps "ayse" in different or same address.
---------------------------
void func(void)
{
	const char *p1 = "ayse";
	const char *p2 = "ayse";
	(p1 == p2) ? printf("dogru\n") : printf("yanlis\n");
}
---------------------------

Note: Implementation defined behavior is a subset of unspecified behavior but compilers should document the behavior.

============================================================================== */
