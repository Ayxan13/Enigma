//
// Created by Ayxan on 4/19/2021.
//

#pragma once

#include "Rotor.hpp"
#include "Reflector.hpp"
#include "PlugBoard.hpp"
#include <string>
#include <string_view>

namespace EnigmaCpp
{
	class Enigma
	{
	private:
		Rotor _leftRotor;
		Rotor _middleRotor;
		Rotor _rightRotor;
		Reflector _reflector;
		PlugBoard _plugBoard;

	public:

		Enigma(Rotor leftRotor, Rotor middleRotor, Rotor rightRotor,
			Reflector reflector,
			PlugBoard plugBoard);

		void Rotate() noexcept;
		[[nodiscard]] int Encrypt(int c) noexcept;
		[[nodiscard]] char Encrypt(char c) noexcept;
		[[nodiscard]] std::string Encrypt(std::string_view input) noexcept;
	};
}