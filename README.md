# C++ Enigma

This is a C++ implementation of an Enigma machine. Largely based on [this](https://github.com/mikepound/enigma) project.

Here is how you use it:

```c++
#include <iostream>

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

```

