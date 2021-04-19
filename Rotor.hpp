//
// Created by Ayxan Haqverdili on 4/18/2021.
//

#pragma once

#include <vector>
#include <span>
#include <string_view>
#include <memory>

#include "RotorTypeSpecific.hpp"

namespace EnigmaCpp
{
	class Rotor final
	{
	private:
		using NotchDetectorType = RotorTypeSpecific::NotchDetectorType;

		std::vector<int> _forwardWiring;
		std::vector<int> _backwardWiring;

		NotchDetectorType _isAtNotch = nullptr;

		int _rotorPosition = 0;
		int _notchPosition = 0;
		int _ringSetting = 0;

	public:
		Rotor(RotorTypeSpecific::RotorName rotorName, int rotorPosition, int ringSetting);

		Rotor(std::string_view encoding,
			int rotorPosition,
			int notchPosition,
			int ringSetting,
			NotchDetectorType isAtNotch);

		[[nodiscard]] int Position() const noexcept;
		[[nodiscard]] int Forward(int c) const noexcept;
		[[nodiscard]] int Backward(int c) const noexcept;
		[[nodiscard]] bool IsAtNotch() const noexcept;
		void TurnOver() noexcept;
	};
}