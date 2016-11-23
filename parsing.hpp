#pragma once
#include "program.hpp"
#include "lexing.hpp"
#include <vector>

std::vector<std::shared_ptr<Expression>> parse(Lexer& lexer);