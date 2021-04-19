//
// Created by Ayxan on 4/19/2021.
//

#pragma once

#include "../Enigma.hpp"
#include <string_view>
#include <stdexcept>
#include <random>
#include <iterator>

namespace EnigmaCpp::EnigmaTest
{
#ifdef ENIGMA_TEST
	static void Assert(bool condition, std::string_view msg = "Test case failed")
	{
		if (!condition)
			throw std::runtime_error(std::string{msg});
	}

	static void EncryptTest()
	{
		using namespace RotorTypeSpecific;

		std::string_view const input =
			"ABCDEFGHIJKLMNOPQRSTUVWXYZAAAAAAAAAAAA"
			"AAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBB"
			"BBABCDEFGHIJKLMNOPQRSTUVWXYZ";

		{ // Basic settings
			Enigma e(Rotor(RotorName::I, 0, 0),
				Rotor(RotorName::II, 0, 0),
				Rotor(RotorName::III, 0, 0),
				Reflector(Reflector::Name::B),
				PlugBoard(""));

			Assert(e.Encrypt(input) ==
				"BJELRQZVJWARXSNBXORSTNCFMEYHCXTGYJFLI"
				"NHNXSHIUNTHEORXOPLOVFEKAGADSPNPCMHRVZ"
				"CYECDAZIHVYGPITMSRZKGGHLSRBLHL");
		}

		{ // Varied rotors
			Enigma e(Rotor(RotorName::VII, 10, 1),
				Rotor(RotorName::V, 5, 2),
				Rotor(RotorName::IV, 12, 3),
				Reflector(Reflector::Name::B),
				PlugBoard(""));
			Assert(e.Encrypt(input) ==
				"FOTYBPKLBZQSGZBOPUFYPFUSETWKNQQHVNHLKJ"
				"ZZZKHUBEJLGVUNIOYSDTEZJQHHAOYYZSENTGXN"
				"JCHEDFHQUCGCGJBURNSEDZSEPLQP");
		}

		{ // Long input
			Enigma e(Rotor(RotorName::III, 3, 11),
				Rotor(RotorName::VI, 5, 13),
				Rotor(RotorName::VIII, 9, 19),
				Reflector(Reflector::Name::B),
				PlugBoard(""));
			std::string longInput(500, 'A');
			Assert(e.Encrypt(longInput) ==
				"YJKJMFQKPCUOCKTEZQVXYZJWJFROVJMWJVXRCQYF"
				"CUVBRELVHRWGPYGCHVLBVJEVTTYVMWKJFOZHLJEX"
				"YXRDBEVEHVXKQSBPYZNIQDCBGTDDWZQWLHIBQNTY"
				"PIEBMNINNGMUPPGLSZCBRJULOLNJSOEDLOBXXGEV"
				"TKCOTTLDZPHBUFKLWSFSRKOMXKZELBDJNRUDUCOT"
				"NCGLIKVKMHHCYDEKFNOECFBWRIEFQQUFXKKGNTST"
				"VHVITVHDFKIJIHOGMDSQUFMZCGGFZMJUKGDNDSNS"
				"JKWKENIRQKSUUHJYMIGWWNMIESFRCVIBFSOUCLBY"
				"EEHMESHSGFDESQZJLTORNFBIFUWIFJTOPVMFQCFC"
				"FPYZOJFQRFQZTTTOECTDOOYTGVKEWPSZGHCTQRPG"
				"ZQOVTTOIEGGHEFDOVSUQLLGNOOWGLCLOWSISUGSV"
				"IHWCMSIUUSBWQIGWEWRKQFQQRZHMQJNKQTJFDIJY"
				"HDFCWTHXUOOCVRCVYOHL");
		}
	}

	static void DecryptTest()
	{
		using namespace RotorTypeSpecific;
		RotorName allRotors[] = { RotorName::I, RotorName::II, RotorName::III,
								  RotorName::IV, RotorName::V, RotorName::VI,
								  RotorName::VII, RotorName::VIII };

		std::mt19937 randEng(std::random_device{}());

		std::string input;
		input.reserve(1000);
		std::ranges::generate_n(back_inserter(input), 1000,
			[&randEng, distribution = std::uniform_int_distribution(0 + 65, 25 + 65)]
			{
			  return distribution(randEng);
			});

		for (int test = 0; test < 10; ++test)
		{
			RotorName rotorNames[3];
			std::sample(std::begin(allRotors), std::end(allRotors), rotorNames, std::size(rotorNames), randEng);
			std::uniform_int_distribution upTo26(0, 25);
			Rotor leftRotor(rotorNames[0], upTo26(randEng), upTo26(randEng));
			Rotor middleRotor(rotorNames[1], upTo26(randEng), upTo26(randEng));
			Rotor rightRotor(rotorNames[2], upTo26(randEng), upTo26(randEng));

			// Encrypt with one machine
			Enigma e(leftRotor, middleRotor, rightRotor, Reflector(Reflector::Name::B), PlugBoard(""));
			auto const cipherText = e.Encrypt(input);

			// Decrypt with another
			Enigma e2(leftRotor, middleRotor, rightRotor, Reflector(Reflector::Name::B), PlugBoard(""));
			auto const plainText = e2.Encrypt(cipherText);

			Assert(input == plainText);
		}
	}

	static void PlugBoardTest()
	{
		using namespace RotorTypeSpecific;
		using namespace std::string_view_literals;
		PlugBoard pb("AG HR YT KI FL WE NM SD OP QJ");

		{ // Simple test - 4 plugs
			Enigma e(Rotor(RotorName::I, 0, 0),
				Rotor(RotorName::II, 0, 0),
				Rotor(RotorName::III, 0, 0),
				Reflector(Reflector::Name::B),
				PlugBoard("AC FG JY LW"));

			auto const input = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"sv;
			auto const expectedOutput = "QREBNMCYZELKQOJCGJVIVGLYEMUPCURPVPUMDIWXPPWROOQEGI"sv;
			auto const output = e.Encrypt(input);
			Assert(expectedOutput == output);
		}

		{ // 6 plugs
			Enigma e(Rotor(RotorName::IV, 0, 0),
				Rotor(RotorName::VI, 10, 0),
				Rotor(RotorName::III, 6, 0),
				Reflector(Reflector::Name::B),
				PlugBoard("BM DH RS KN GZ FQ"));
			auto const input = "WRBHFRROSFHBCHVBENQFAGNYCGCRSTQYAJNROJ"
							   "AKVKXAHGUZHZVKWUTDGMBMSCYQSKABUGRVMIUO"
							   "WAPKCMHYCRTSDEYTNJLVWNQY"sv;
			auto const expectedOutput =
				"FYTIDQIBHDONUPAUVPNKILDHDJGCWFVM"
				"JUFNJSFYZTSPITBURMCJEEAMZAZIJMZA"
				"VFCTYTKYORHYDDSXHBLQWPJBMSSWIPSW"
				"LENZ"sv;
			auto const output = e.Encrypt(input);
			Assert(expectedOutput == output);
		}

		{ // 10 plugs
			Enigma e(Rotor(RotorName::I, 0, 5),
				Rotor(RotorName::II, 1, 5),
				Rotor(RotorName::III, 20, 4),
				Reflector(Reflector::Name::B),
				PlugBoard("AG HR YT KI FL WE NM SD OP QJ"));

			auto const input =
				"RNXYAZUYTFNQFMBOLNYNYBUYPMWJUQSBY"
				"RHPOIRKQSIKBKEKEAJUNNVGUQDODVFQZH"
				"ASHMQIHSQXICTSJNAUVZYIHVBBARPJADRH"sv;
			auto const expectedOutput =
				"CFBJTPYXROYGGVTGBUTEBURBXNUZGGRAL"
				"BNXIQHVBFWPLZQSCEZWTAWCKKPRSWOGNY"
				"XLCOTQAWDRRKBCADTKZGPWSTNYIJGLVIUQ"sv;
			auto const output = e.Encrypt(input);
			Assert(expectedOutput == output);
		}
	}
#endif // ENIGMA_TEST
}

#undef ENIGMA_ONLY_AVAILABLE_IN_TEST_MODE