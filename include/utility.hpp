#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <iostream>

#define STARTF() \
	do { \
		std::cout << "======== START ========" << std::endl; \
		std::cout << "File: " << __FILE__ << ", Function: " << __func__ << ", Line: " << __LINE__ << std::endl; \
	} while(0)

#define ENDF() \
	do { \
		std::cout << "========  END  ========" << std::endl << std::endl; \
	} while(0)

#endif /* UTILITY_HPP */
