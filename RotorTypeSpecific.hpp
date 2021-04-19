//
// Created by Ayxan Haqverdili on 4/18/2021.
//

#pragma once
#include <string_view>

// Get info specific to a rotor (I, II, III, IV, V, VI, VII, VIII)
namespace EnigmaCpp::RotorTypeSpecific
{
	using NotchDetectorType = bool (*)(int rotorPosition, int notchPosition);

	enum class RotorName
	{
		I, II, III, IV, V, VI, VII, VIII,
	};
	
	static std::string_view Encoding(RotorName const rotorName) noexcept
	{
		using namespace std::string_view_literals;

		switch (rotorName)
		{
		case RotorName::I:
			return "EKMFLGDQVZNTOWYHXUSPAIBRCJ"sv;
		case RotorName::II:
			return "AJDKSIRUXBLHWTMCQGZNPYFVOE"sv;
		case RotorName::III:
			return "BDFHJLCPRTXVZNYEIWGAKMUSQO"sv;
		case RotorName::IV:
			return "ESOVPZJAYQUIRHXLNFTGKDCMWB"sv;
		case RotorName::V:
			return "VZBRGITYUPSDNHLXAWMJQOFECK"sv;
		case RotorName::VI:
			return "JPGVOUMFYQBENHZRDKASXLICTW"sv;
		case RotorName::VII:
			return "NZJHGRCXMYSWBOUFAIVLPEKQDT"sv;
		case RotorName::VIII:
			return "FKQHTLXOCBJSPDZRAMEWNIUYGV"sv;
		default:
			return "ABCDEFGHIJKLMNOPQRSTUVWXYZ"sv;
		}
	}

	static int NotchPosition(RotorName const rotorName) noexcept
	{
		switch (rotorName)
		{
		case RotorName::I:
			return 16;
		case RotorName::II:
			return 4;
		case RotorName::III:
			return 21;
		case RotorName::IV:
			return 9;
		case RotorName::V:
			return 25;
		default:
			return 0;
		}
	}

	static NotchDetectorType NotchDetector(RotorName const rotorName) noexcept
	{
		switch (rotorName)
		{
		case RotorName::VI:
		case RotorName::VII:
		case RotorName::VIII:
			return [](int const rotorPosition, int) -> bool
			{
			  return rotorPosition == 12 || rotorPosition == 25;
			};
		default:
			return [](int const rotorPosition, int const notchPosition) -> bool
			{
			  return notchPosition == rotorPosition;
			};
		}
	}
};


