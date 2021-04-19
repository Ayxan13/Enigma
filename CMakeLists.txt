cmake_minimum_required(VERSION 3.17)
project(Enigma)

set(CMAKE_CXX_STANDARD 20)

add_executable(Enigma Main.cpp Rotor.hpp Reflector.cpp Reflector.hpp Rotor.cpp RotorTypeSpecific.hpp PlugBoard.cpp PlugBoard.hpp Enigma.cpp Enigma.hpp Test/EnigmaTest.hpp)
add_compile_options(-Wall -Wextra -Wpedantic)