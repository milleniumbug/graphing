#include "program.hpp"
#include "pretty_printing.hpp"
#include <iostream>

class Error : public Expression
{
public:
	std::shared_ptr<Expression> evaluate() override
	{
		std::cout << "ERROR" << "\n";
		return shared_from_this();
	}

	std::shared_ptr<Expression> lookup(std::string) override
	{
		return shared_from_this();
	}
};

class NoPropertyExpression : public Expression
{
public:
	std::shared_ptr<Expression> lookup(std::string) override
	{
		return std::make_shared<Error>();
	}
};

class Printable
{
public:
	virtual std::string stringRepr() const = 0;
	virtual ~Printable() {}
};

template<typename Type>
class Value : public NoPropertyExpression, public Printable
{
public:
	std::shared_ptr<Expression> evaluate() override
	{
		return shared_from_this();
	}

	Value(Type value) :
			value(std::move(value))
	{

	}

	std::string stringRepr() const
	{
		return PrettyPrinter<Type>()(value);
	}

	Type value;
};

class PrintExpression : public NoPropertyExpression
{
	std::shared_ptr<Expression> underlying;
public:
	std::shared_ptr<Expression> evaluate() override
	{
		auto p = std::dynamic_pointer_cast<Printable>(underlying->evaluate());
		std::cout << (p ? p->stringRepr() : "GIT GUD");
		return shared_from_this();
	}

	PrintExpression(std::shared_ptr<Expression> underlying) :
		underlying(underlying)
	{

	}
};

class BinaryOperation : public NoPropertyExpression
{
	std::shared_ptr<Expression> left;
	std::shared_ptr<Expression> right;
protected:
	virtual std::shared_ptr<Expression> evaluate(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) = 0;
public:
	std::shared_ptr<Expression> evaluate() override
	{
		return evaluate(left, right);
	}

	BinaryOperation(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) :
		left(left),
		right(right)
	{

	}
};

template<typename Type, typename StatelessFunctionObject>
class BinaryIntegralOperation : public BinaryOperation
{
protected:
	std::shared_ptr<Expression> evaluate(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) override
	{
		auto l = std::dynamic_pointer_cast<Value<Type>>(left->evaluate());
		auto r = std::dynamic_pointer_cast<Value<Type>>(right->evaluate());
		auto value = StatelessFunctionObject()(l->value, r->value);
		return std::make_shared<Value<decltype(value)>>(std::move(value));
	}
public:
	using BinaryOperation::BinaryOperation;
};

std::shared_ptr<Expression> test_expression()
{
	return
	std::make_shared<PrintExpression>(
		std::make_shared<BinaryIntegralOperation<long long, std::plus<>>>(
			std::make_shared<Value<long long>>(3),
			std::make_shared<Value<long long>>(2)));
}

Expression::~Expression()
{

}