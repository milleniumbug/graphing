#pragma once
#include <iosfwd>
#include <boost/variant.hpp>
#include <boost/optional.hpp>

enum class Operator
{
	Addition,
	Subtraction,
	Multiplication,
	Division,
	Assignment
};

enum class Keyword
{
	Def,
	Return,
	Let
};

struct Identifier
{
	std::string name;
};

struct IntegralLiteral
{
	long long value;
};

struct FloatingPointLiteral
{
	double value;
};

struct BraceBegin {};
struct BraceEnd {};
struct ParenBegin {};
struct ParenEnd {};
struct Comma {};
struct Semicolon {};

using LexicalUnit = boost::variant<
	Operator,
	Keyword,
	Identifier,
	IntegralLiteral,
	BraceBegin,
	BraceEnd,
	ParenBegin,
	ParenEnd,
	Comma,
	Semicolon>;

enum class LexerState : unsigned;

class Lexer
{
	std::string buffer;
	std::istream& is;
	LexerState state;
public:
	boost::optional<LexicalUnit> operator()();
	Lexer(std::istream& is);
};

void print_lexical_unit(const LexicalUnit& lexicalUnit, std::ostream& os);