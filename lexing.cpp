#include "lexing.hpp"
#include "utility.hpp"
#include <iostream>
#include <map>
#include <cstdlib>
#include <boost/utility/string_ref.hpp>
#include <boost/bimap.hpp>

namespace
{
	bool is_digit(int c)
	{
		return c >= '0' && c <= '9';
	}

	bool is_letter(int c)
	{
		static_assert('A' == 65, "assuming ASCII compatible character set");
		return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
	}

	bool is_correct_identifier_start(int c)
	{
		return is_letter(c) || c == '_';
	}

	bool is_identifier_character(int c)
	{
		return is_digit(c) || is_correct_identifier_start(c);
	}

	bool is_integral_literal(boost::string_ref str)
	{
		return std::all_of(str.begin(), str.end(), is_digit);
	}

	bool is_whitespace(int c)
	{
		return c == ' ' || c == '\t' || c == '\r' || c == '\n';
	}

	static const boost::bimap<std::string, Keyword> keyword_map = []()
	{
		boost::bimap<std::string, Keyword> m;
		m.left.insert({"def", Keyword::Def});
		m.left.insert({"return", Keyword::Return});
		m.left.insert({"let", Keyword::Let});
		return m;
	}();

	boost::optional<const Keyword&> to_keyword(boost::string_ref str)
	{
		return at(keyword_map.left, str.to_string());
	}

	boost::optional<const std::string&> from_keyword(Keyword kw)
	{
		return at(keyword_map.right, kw);
	}

	bool is_identifier(boost::string_ref str)
	{
		if(str.empty())
			return false;
		if(is_digit(str[0]))
			return false;
		if(!to_keyword(str))
			return false;
		return std::all_of(str.begin(), str.end(), [](char c)
		{
			return is_digit(c) || is_letter(c);
		});	
	}
}

enum class LexerState : unsigned
{
	initial,
	integer,
	word,
	comment
};

struct Printer
{
	template<typename Whatever>
	void operator()(Whatever x) const
	{
		std::cout << boost::core::demangle(typeid(decltype(x)).name());
	}

	void operator()(Identifier id) const
	{
		std::cout << "Identifier(" << id.name << ")";
	}

	void operator()(Keyword kw) const
	{
		std::cout << "Keyword(" << from_keyword(kw).value() << ")";
	}

	std::ostream& os;
};

void print_lexical_unit(const LexicalUnit& lexicalUnit, std::ostream &os)
{
	boost::apply_visitor(Printer{os}, lexicalUnit);
}

boost::optional<LexicalUnit> Lexer::operator()()
{
	const int eof = std::istream::traits_type::eof();
	int ch;
	while((ch = is.get()) != eof)
	{
		auto change_state = [&](LexerState newstate)
		{
			state = newstate;
		};
		auto flush_token = [&](auto token)
		{
			state = LexerState::initial;
			buffer.clear();
			return LexicalUnit(token);
		};
		if(state == LexerState::integer)
		{
			if(!is_digit(ch))
			{
				is.unget();
				change_state(LexerState::initial);
				return flush_token(IntegralLiteral{std::strtoll(buffer.c_str(), nullptr, 10)});
			}
		}
		else if(state == LexerState::word)
		{
			if(!is_identifier_character(ch))
			{
				is.unget();
				if(auto keywordopt = to_keyword(buffer))
					return flush_token(*keywordopt);
				return flush_token(Identifier{buffer});
			}
		}
		else if(state == LexerState::initial)
		{
			if(is_digit(ch))
				change_state(LexerState::integer);
			else if(is_correct_identifier_start(ch))
				change_state(LexerState::word);
			else if(ch == '{')
				return flush_token(BraceBegin());
			else if(ch == '}')
				return flush_token(BraceEnd());
			else if(ch == '(')
				return flush_token(ParenBegin());
			else if(ch == ')')
				return flush_token(ParenEnd());
			else if(ch == ',')
				return flush_token(Comma());
			else if(ch == ';')
				return flush_token(Semicolon());
			else if(is_whitespace(ch))
				continue;
		}
		buffer.push_back(ch);
	}
	return boost::none;
}

Lexer::Lexer(std::istream& is) :
	is(is),
	state(LexerState::initial)
{

}