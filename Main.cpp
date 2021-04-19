//
// Created by Ayxan Haqverdili on 4/18/2021.
//

#define ENIGMA_TEST

#include "Test/EnigmaTest.hpp"
#include <cstdio>


int main()
{
#ifdef ENIGMA_TEST
	try {
		EnigmaCpp::EnigmaTest::EncryptTest();
		EnigmaCpp::EnigmaTest::DecryptTest();
		EnigmaCpp::EnigmaTest::PlugBoardTest();
		std::puts("Test cases passed!");

	} catch (std::exception const& ex) {
		std::fputs("Test failed\n", stderr);
	}
#endif // ENIGMA_TEST
}
