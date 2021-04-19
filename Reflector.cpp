//
// Created by Ayxan Haqverdili on 4/18/2021.
//

#include "Reflector.hpp"
#include <algorithm>

using namespace std::string_view_literals;

[[nodiscard]] static std::vector<int> DecodeWiring(std::string_view encoding)
{
	std::vector<int> wiring(encoding.size());

	std::ranges::transform(encoding.begin(), encoding.end(), wiring.begin(), [](char const ch)
	{
	  return ch - 65;
	});

	return wiring;
}

[[nodiscard]] constexpr static std::string_view Encoding(EnigmaCpp::Reflector::Name name) noexcept
{
	switch (name)
	{
	case EnigmaCpp::Reflector::Name::B:
		return "YRUHQSLDPXNGOKMIEBFZCWVJAT"sv;
	case EnigmaCpp::Reflector::Name::C:
		return "FVPJIAOYEDRZXWGCTKUQSBNMHL"sv;
	default:
		return "ZYXWVUTSRQPONMLKJIHGFEDCBA"sv;
	}
}

EnigmaCpp::Reflector::Reflector(std::string_view const encoding)
	: _forwardWiring(::DecodeWiring(encoding))
{
}
EnigmaCpp::Reflector::Reflector(EnigmaCpp::Reflector::Name name)
	: Reflector(Encoding(name))
{
}
int EnigmaCpp::Reflector::Forward(int const c) const noexcept
{
	return _forwardWiring[c];
}
