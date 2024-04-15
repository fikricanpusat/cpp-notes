#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <iostream>

#define STARTT() \
	do { \
		std::cout << "\033[1;34m" << "File: " << __FILE__ << std::endl << \
		"======== START ========\n" << "\033[0m" << std::endl; \
	} while(0)

#define ENDT() \
	do { \
		std::cout << "\033[1;34m========  END  ========\033[0m" << "\n\n\n"; \
	} while(0)

#define STARTF() \
	do { \
		std::cout << "\033[0;36m" << "---> Function Start: \033[0m" << __func__ << std::endl; \
	} while(0)

#define ENDF() \
	do { \
		std::cout << "\033[0;36m" << "---> Function End\033[0m" << std::endl << std::endl; \
	} while(0)

#endif /* UTILITY_HPP */
