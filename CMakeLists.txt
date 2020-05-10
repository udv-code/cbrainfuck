cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(cbrainfuck
	VERSION 1.0
	LANGUAGES CXX)

add_subdirectory("bench")
add_subdirectory("cbrainfuck-main")
add_subdirectory("tests")