#pragma once
#include <iosfwd>
#include <boost/variant.hpp>
#include <boost/optional.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <vector>

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

class Lexer;

class LexerIterator : public boost::iterator_facade<LexerIterator, LexicalUnit, boost::forward_traversal_tag>
{
	friend class boost::iterator_core_access;

	std::size_t position;
	Lexer* lexer;

	void increment();
	bool equal(const LexerIterator& other) const;
	LexicalUnit& dereference() const;
public:
	LexerIterator();
	LexerIterator(Lexer& lexer);
};

class Lexer
{
	std::string buffer;
	std::istream& is;
	LexerState state;
	bool advance();
	std::vector<LexicalUnit> lexicalUnits;
	friend class LexerIterator;
public:
	Lexer(std::istream& is);
	LexerIterator begin();
	LexerIterator end();
};

void print_lexical_unit(const LexicalUnit& lexicalUnit, std::ostream& os);