#include "lexing.hpp"
#include "program.hpp"
#include <iostream>

int main()
{
	test_expression()->evaluate();
	Lexer lexer(std::cin);
	for(auto& lexical_unit : lexer)
	{
		print_lexical_unit(lexical_unit, std::cout);
		std::cout << "\n";
	}
}