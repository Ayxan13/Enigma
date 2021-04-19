//
// Created by Ayxan Haqverdili on 4/18/2021.
//

#include <cstdio>

#include "Enigma.hpp"

int main()
{
	using namespace EnigmaCpp;
	using namespace RotorTypeSpecific;
	Enigma enigmaMachine(
		Rotor(RotorName::VII, 10, 1),
		Rotor(RotorName::V, 5, 2),
		Rotor(RotorName::IV, 12, 3),
		Reflector(Reflector::Name::B),
		PlugBoard("AD FT WH JO PN"));

	auto const plainText = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	auto const cipherText = enigmaMachine.Encrypt(plainText);

	std::printf("'%s' encrypted is '%s'\n",
		plainText, cipherText.c_str());
}
