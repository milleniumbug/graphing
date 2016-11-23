#pragma once
#include <memory>
#include <map>

class Expression
{
	std::shared_ptr<Expression> evaluate();
	std::shared_ptr<Expression> lookup(std::string name);
	virtual ~Expression();
};

class ExecutionEnvironment
{
	std::map<std::string, std::shared_ptr<Expression>> variables;
};