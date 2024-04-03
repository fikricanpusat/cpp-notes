#include "utility.hpp"

/* ==============================================================================

Lecture 02

NAME LOOKUP

Note: Smallest piece of word that compiler can read and understand is called "token". The process of dividing code
to tokens is called "tokenizing" or "lexical analysis".

Tokens are:
Keywords
Identifiers
Numeric, Boolean and Pointer Literals
String and Character Literals
User-Defined Literals
Operators
Punctuators

Identifiers are a type of token which are names of variables, functions, types... Declaration a piece of code that
tells the compiler what this name is all about.

Name lookup is compiler trying to find a declaration for an identifier token. The rules of name lookup follows:

* Name lookup happens in a predetermined order in increasingly larger blocks
e.g.
--------------------------- */
int inc_x = 5;
void increasing_block_name_lookup(void) {
	STARTF();
	std::cout << inc_x << std::endl;
	const char* inc_x = "local";
	std::cout << inc_x << std::endl;
	{
		float inc_x = 2.4;
		std::cout << inc_x << std::endl;
	}
	ENDF();
}
/* ---------------------------

* Name lookup is done once, and when name is found, lookup ends and does not start again. Context control starts after
name lookup is done: name lookup --> context control --> access control (access control is not in C)
e.g. Name printf is found in the main function block and not searched in latter stages.
So name printf is only an integer variable name for the compiler and not a function name. So calling it as function
fails due to context error (notice that it is not a name lookup error). However using it as a variable is valid.
e.g.
---------------------------
#include <stdio.h>
int main() {
	int printf = 5;
	// printf("Hello");	// Syntax error, not a name lookup problem but a context problem.
	// printf++;		// Valid
}
---------------------------
e.g. An interesting name lookup example.
--------------------------- */
void interesting_name_lookup(void)
{
	STARTF();
	int printf = 5;
	printf = 10;
	::printf("%d\n", printf);
	ENDF();
}
/* ---------------------------

at: 1:07:00 initialize

============================================================================== */

void name_lookup(void)
{
	increasing_block_name_lookup();
	interesting_name_lookup();
}
