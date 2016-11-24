#include "parsing.hpp"

namespace
{
	std::shared_ptr<Expression> try_parse_function()
	{
		return std::shared_ptr<Expression>();
	}
}

std::vector<std::shared_ptr<Expression>> parse(Lexer& lexer)
{
	return std::vector<std::shared_ptr<Expression>>();
}