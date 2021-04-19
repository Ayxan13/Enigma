//
// Created by Ayxan on 4/19/2021.
//

#include "PlugBoard.hpp"
#include <unordered_set>
#include <numeric>

[[nodiscard]] std::vector<std::string_view> Split(std::string_view const str, char const delimiter)
{
	std::vector<std::string_view> strList;
	std::size_t beg = 0;
	std::size_t end = 0;
	while ((end = str.find(delimiter, end)) != std::string_view::npos)
	{
		strList.emplace_back(str.data() + beg, str.data() + end);
		beg = ++end;
	}
	strList.emplace_back(str.data() + beg, str.data() + str.size());
	return strList;
}

[[nodiscard]] static std::vector<int> IdentityPlugBoard()
{
	std::vector<int> mapping(26);
	std::iota(mapping.begin(), mapping.end(), 0);
	return mapping;
}

EnigmaCpp::PlugBoard::PlugBoard(std::string_view const connections)
	: wiring(DecodePlugBoard(connections))
{
}

int EnigmaCpp::PlugBoard::Forward(int const c) const noexcept
{
	return wiring[c];
}

std::vector<int> EnigmaCpp::PlugBoard::DecodePlugBoard(std::string_view const plugBoard)
{
	if (plugBoard.empty())
		return IdentityPlugBoard();

	std::vector<std::string_view> const pairings = Split(plugBoard, ' ');
	std::unordered_set<int> pluggedCharacters;

	std::vector<int> mapping = IdentityPlugBoard();
	for (auto const& pair : pairings)
	{
		if (pair.length() != 2)
			return IdentityPlugBoard();

		int const c1 = pair[0] - 65;
		int const c2 = pair[1] - 65;

		if (pluggedCharacters.contains(c1) || pluggedCharacters.contains(c2))
			return IdentityPlugBoard();

		pluggedCharacters.insert(c1);
		pluggedCharacters.insert(c2);

		mapping[c1] = c2;
		mapping[c2] = c1;
	}

	return mapping;
}

std::unordered_set<int> EnigmaCpp::PlugBoard::GetUnpluggedCharacters(std::string_view const plugBoard)
{
	std::unordered_set<int> unpluggedCharacters;
	unpluggedCharacters.reserve(26);
	for (int i = 0; i < 26; ++i)
		unpluggedCharacters.insert(i);

	if (plugBoard.empty())
		return unpluggedCharacters;

	for (auto const& pair : Split(plugBoard, ' '))
	{
		int const c1 = pair[0] - 65;
		int const c2 = pair[1] - 65;

		unpluggedCharacters.erase(c1);
		unpluggedCharacters.erase(c2);
	}

	return unpluggedCharacters;
}
