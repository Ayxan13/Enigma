//
// Created by Ayxan Haqverdili on 4/18/2021.
//

#include "Test/EnigmaTest.hpp"
#include <cstdio>

int main()
try {
	EnigmaCpp::EnigmaTest::EncryptTest();
	EnigmaCpp::EnigmaTest::DecryptTest();
	EnigmaCpp::EnigmaTest::PlugBoardTest();

	std::puts("Test cases passed!");

} catch (std::exception const& ex) {
	std::fputs("Test failed\n", stderr);
}
