//
// Created by Ayxan Haqverdili on 4/18/2021.
//

#include "Rotor.hpp"
#include <algorithm>

using namespace std::string_view_literals;

[[nodiscard]] static std::vector<int> InverseWiring(std::span<int const> wiring)
{
	std::vector<int> inverse(wiring.size());
	for (int i = 0; i < static_cast<int>(wiring.size()); ++i)
	{
		inverse[wiring[i]] = i;
	}
	return inverse;
}

[[nodiscard]] static std::vector<int> DecodeWiring(std::string_view encoding)
{
	std::vector<int> wiring(encoding.size());

	std::ranges::transform(encoding.begin(), encoding.end(), wiring.begin(), [](char const ch)
	{
	  return ch - 65;
	});

	return wiring;
}

[[nodiscard]] static int Encipher(int k, int pos, int ring, std::span<int const> mapping) noexcept
{
	int const shift = pos - ring;
	return (mapping[(k + shift + 26) % 26] - shift + 26) % 26;
}

bool EnigmaCpp::Rotor::IsAtNotch() const noexcept
{
	return _isAtNotch(_rotorPosition, _notchPosition);
}

int EnigmaCpp::Rotor::Forward(int const c) const noexcept
{
	return Encipher(c, _rotorPosition, _ringSetting, _forwardWiring);
}

int EnigmaCpp::Rotor::Backward(int c) const noexcept
{
	return Encipher(c, _rotorPosition, _ringSetting, _backwardWiring);
}

void EnigmaCpp::Rotor::TurnOver() noexcept
{
	_rotorPosition = (_rotorPosition + 1) % 26;
}

EnigmaCpp::Rotor::Rotor(RotorTypeSpecific::RotorName rotorName, int rotorPosition, int ringSetting)
	: Rotor(RotorTypeSpecific::Encoding(rotorName),
	rotorPosition,
	RotorTypeSpecific::NotchPosition(rotorName),
	ringSetting,
	RotorTypeSpecific::NotchDetector(rotorName))
{
}

EnigmaCpp::Rotor::Rotor(std::string_view const encoding,
	int const rotorPosition,
	int const notchPosition,
	int const ringSetting,
	NotchDetectorType const isAtNotch)
	: _forwardWiring(DecodeWiring(encoding))
	  , _backwardWiring(InverseWiring(_forwardWiring))
	  , _rotorPosition(rotorPosition)
	  , _notchPosition(notchPosition)
	  , _ringSetting(ringSetting)
	  , _isAtNotch(isAtNotch)
{
}

int EnigmaCpp::Rotor::Position() const noexcept
{
	return _rotorPosition;
}
