#pragma once
#include <memory>
#include <map>

class Expression : public std::enable_shared_from_this<Expression>
{
public:
	virtual std::shared_ptr<Expression> evaluate() = 0;
	virtual std::shared_ptr<Expression> lookup(std::string name) = 0;
	virtual ~Expression();
};

class ExecutionEnvironment
{

};

std::shared_ptr<Expression> test_expression();