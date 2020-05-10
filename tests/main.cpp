#include <brainfuck.hpp>


int main(int argc, char** argv)
{
	cbf::parse("test2.bf");
	cbf::interpret();
}
