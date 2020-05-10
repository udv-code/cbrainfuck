#ifndef CBF_BRAINFUCK
#define CBF_BRAINFUCK

#include <bfdef.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define BENCHMARK
#include <timer.hpp>

#define MAX_SIZE 10000

namespace cbf
{
	static cell_t memory[MAX_SIZE];
	static uint16_t count = 0;
	static char instructions[MAX_SIZE];

	static void find_closing(uint16_t& ptr)
	{
		int balance = 1;

		do
		{
			++ptr;
			if (instructions[ptr] == TOKEN_OPEN_LOOP)
			{
				++balance;
			}
			else if (instructions[ptr] == TOKEN_CLOSE_LOOP)
			{
				--balance;
			}
		}
		while (balance != 0);
	}

	static void find_opening(uint16_t& ptr)
	{
		int balance = 0;

		do
		{
			if (instructions[ptr] == TOKEN_OPEN_LOOP)
			{
				++balance;
			}
			else if (instructions[ptr] == TOKEN_CLOSE_LOOP)
			{
				--balance;
			}
			--ptr;
		}
		while (balance != 0);
	}

	static bool is_valid_instruction(char instruction)
	{
		switch (instruction)
		{
		case TOKEN_INCREMENT:
		case TOKEN_DECREMENT:
		case TOKEN_INPUT:
		case TOKEN_OUTPUT:
		case TOKEN_SHIFT_LEFT:
		case TOKEN_SHIFT_RIGHT:
		case TOKEN_OPEN_LOOP:
		case TOKEN_CLOSE_LOOP:
			return true;
		default:
			return false;
		}
	}

	static void parse(const std::string&& file_path)
	{
		BENCHMARK_THIS;
		std::ifstream in_file(file_path);

		if (!in_file.is_open())
		{
			std::cout << "Can't open file: " << file_path << "\n";
			return;
		}

		char instruction;
		uint16_t ptr = 0;
		while (in_file >> instruction)
		{
			if (is_valid_instruction(instruction))
			{
				instructions[ptr] = instruction;
				++ptr;
				++count;
			}
		}
	}

	static void interpret()
	{
		std::ios_base::sync_with_stdio(false);
		std::cin.tie(0);
		std::cout.tie(0);

		uint16_t memptr = 0;
		uint16_t ptr = 0;
		while (ptr <= count)
		{
			switch (instructions[ptr])
			{
			case TOKEN_INCREMENT:
				{
					++memory[memptr];
					break;
				}
			case TOKEN_DECREMENT:
				{
					--memory[memptr];
					break;
				}
			case TOKEN_INPUT:
				{
					std::cin >> memory[memptr];
					break;
				}
			case TOKEN_OUTPUT:
				{
					std::cout << memory[memptr];
					break;
				}
			case TOKEN_SHIFT_LEFT:
				{
					if (memptr > 0)
					{
						--memptr;
					}
					break;
				}
			case TOKEN_SHIFT_RIGHT:
				{
					if (memptr < MAX_SIZE)
					{
						++memptr;
					}
					break;
				}
			case TOKEN_OPEN_LOOP:
				{
					if (memory[memptr] == 0)
					{
						find_closing(ptr);
					}
					break;
				}
			case TOKEN_CLOSE_LOOP:
				{
					if (memory[memptr] != 0)
					{
						find_opening(ptr);
					}
					break;
				}
			default:
				break;
			}
			++ptr;
		}
	}
}
#endif // CBF_BRAINFUCK
