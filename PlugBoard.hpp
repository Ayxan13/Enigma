//
// Created by Ayxan Haqverdili on 4/19/2021.
//

#pragma once

#include <vector>
#include <string_view>
#include <unordered_set>


namespace EnigmaCpp
{
	class PlugBoard
	{
	private:
		std::vector<int> wiring;

	public:
		explicit PlugBoard(std::string_view connections);

		[[nodiscard]] int Forward(int c) const noexcept;
		[[nodiscard]] static std::vector<int> DecodePlugBoard(std::string_view plugBoard);
		[[nodiscard]] static std::unordered_set<int> GetUnpluggedCharacters(std::string_view plugBoard);
	};
}