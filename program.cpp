#include "program.hpp"

std::shared_ptr<Expression> Expression::evaluate()
{

}

Expression::~Expression()
{

}

std::shared_ptr<Expression> Expression::lookup(std::string name)
{
	return std::shared_ptr<Expression>();
}
