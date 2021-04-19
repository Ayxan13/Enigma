//
// Created by Ayxan Haqverdili on 4/18/2021.
//

#pragma once

#include <vector>
#include <string_view>

#include "Rotor.hpp"

namespace EnigmaCpp
{
	class Reflector
	{
	private:
		std::vector<int> _forwardWiring;

	public:
		explicit Reflector(std::string_view encoding);

		enum class Name
		{
			B, C,
		};

		explicit Reflector(Name name);

		[[nodiscard]] int Forward(int c) const noexcept;
	};

}
