#pragma once
#include <string>

template<typename Type>
struct PrettyPrinter
{

};

template<>
struct PrettyPrinter<long long>
{
	std::string operator()(long long value) const
	{
		return std::to_string(value);
	}
};