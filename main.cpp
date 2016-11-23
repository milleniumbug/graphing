#include "lexing.hpp"
#include "program.hpp"
#include <iostream>
#include <typeinfo>

int main()
{
	Lexer lexer(std::cin);
	while(boost::optional<LexicalUnit> lexopt = lexer())
	{
		print_lexical_unit(*lexopt, std::cout);
		std::cout << "\n";
	}
}