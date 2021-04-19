//
// Created by Ayxan on 4/19/2021.
//

#pragma once

#include "../Enigma.hpp"
#include <string_view>
#include <stdexcept>

namespace EnigmaCpp::EnigmaTest
{
	class TestFailedException : public std::runtime_error
	{
	public:
		explicit TestFailedException(std::string_view msg = "Test case failed");
	};

	void Assert(bool condition, std::string_view msg = "Test case failed");

	void EncryptTest();
	void DecryptTest();
	void PlugBoardTest();
}

