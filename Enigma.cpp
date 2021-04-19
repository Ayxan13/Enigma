//
// Created by Ayxan Haqverdili on 4/19/2021.
//

#include "Enigma.hpp"
#include <algorithm>
using namespace EnigmaCpp;

Enigma::Enigma(Rotor leftRotor, Rotor middleRotor, Rotor rightRotor, Reflector reflector, PlugBoard plugBoard)
	: _leftRotor(std::move(leftRotor))
	  , _middleRotor(std::move(middleRotor))
	  , _rightRotor(std::move(rightRotor))
	  , _reflector(std::move(reflector))
	  , _plugBoard(std::move(plugBoard))
{
}
void Enigma::Rotate() noexcept
{
	if (_middleRotor.IsAtNotch())
	{
		_middleRotor.TurnOver();
		_leftRotor.TurnOver();
	}
	else if (_rightRotor.IsAtNotch())
	{
		_middleRotor.TurnOver();
	}

	_rightRotor.TurnOver();
}
int Enigma::Encrypt(int c) noexcept
{
	Rotate();
	// PlugBoard in
	c = _plugBoard.Forward(c);

	// Right to left
	int const c1 = _rightRotor.Forward(c);
	int const c2 = _middleRotor.Forward(c1);
	int const c3 = _leftRotor.Forward(c2);

	// Reflector
	int const c4 = _reflector.Forward(c3);

	// Left to right
	int const c5 = _leftRotor.Backward(c4);
	int const c6 = _middleRotor.Backward(c5);
	int const c7 = _rightRotor.Backward(c6);

	return _plugBoard.Forward(c7);
}
char Enigma::Encrypt(char const c) noexcept
{
	return static_cast<char>( Encrypt(c - 65) + 65 );
}
std::string Enigma::Encrypt(std::string_view const input) noexcept
{
	std::string output(input.size(), 0);
	std::ranges::transform(input.begin(), input.end(), output.begin(), [this](char const ch) {
		return Encrypt(ch);
	});
	return output;
}
