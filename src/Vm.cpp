/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vm.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmartin <stmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:59:38 by stmartin          #+#    #+#             */
/*   Updated: 2018/04/14 15:41:46 by stmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vm.hpp"
#include "IOperand.hpp"
#include "Factory.hpp"

Vm::Vm( void ): _end(0), _factory(new Factory)
{ }

Vm::Vm( Vm const & src )
{
	*this = src;
}

Vm::~Vm()
{ }

Vm 			&Vm::operator=( Vm const & rhs )
{
	if (this != &rhs)
		*this = rhs;
	return *this;
}

void	Vm::run()
{
	std::string buf;

    while (!_end)
    {
    	if (!std::getline(std::cin, buf))
    		break;
		read_args(buf);
	}
}


void		Vm::run(char *av)
{
	std::ifstream file;
	std::string buf;

	file.open(av);
	if (!file)
		throw std::invalid_argument("Wrong file name !");
	else if (file.is_open() == false)
		throw std::runtime_error("File open failed !");
	while (file.eof() == false)
	{
			std::getline(file, buf);
			std::cout << buf << std::endl;
	}
	file.close();
}

const std::map<std::string, int> 	Vm::createMap()
{
	std::map<std::string, int> m;

	m["Int8"] = 1;
	m["Int16"] = 2;
	m["Int32"] = 3;
	m["Float"] = 4;
	m["Double"] = 5;
	return m;
}

void		Vm::read_args(std::string buf)
{
    // revoir la ligne des commentaires et pour le exit
	if (buf.find(";;") == 0)
		_end = 1;
	else if (buf.find(";") == 0)
		;
	else if (buf.find("push") == 0)
		check_operand(buf, PUSH, 3);
	else if (buf.find("add") == 0)
	{
		check_stack();
		add();
	}
	else if(buf.find("sub") == 0)
	{
		check_stack();
		sub();
	}
	else if(buf.find("mul") == 0)
	{
		check_stack();
		mul();
	}
	else if(buf.find("div") == 0)
	{
		check_stack();
		div();
	}
	else if(buf.find("mod") == 0)
	{
		check_stack();
		mod();
	}
	else
		throw std::invalid_argument("Invalid Argument !");
}

void		Vm::check_stack()
{
	if (_stack.empty())
		throw std::runtime_error("Stack is empty !");
	// for (std::vector<const IOperand *>::reverse_iterator it = _stack.rbegin() ; it != _stack.rend(); ++it)

}

void		Vm::check_operand(std::string const &buf, eAsmArgs n, size_t start)
{
	size_t pos;

	if (n == 0 && (pos = buf.find(" ", start)) == start + 1)
		chooseType(buf, pos + 1);
	else if (n == 0 && pos != start + 1)
		throw std::runtime_error("Wrong instruction format !");
}

void		Vm::chooseType(std::string const & buf, size_t start)
{

	if (buf.find("int8", start) == start)
	{
		_type = Int8;
		_value = "Int8";
		start += 4;
	}
	else if (buf.find("int16", start) == start)
	{
		_type = Int16;
		_value = "Int16";
		start += 5;
	}
	else if (buf.find("int32", start) == start)
	{
		_type = Int32;
		_value = "Int32";
		start += 5;
	}
	else if (buf.find("float", start) == start)
	{
		_type = Float;
		_value = "Float";
		start += 5;
	}
	else if (buf.find("double", start) == start)
	{
		_type = Double;
		_value = "Double";
		start += 6;
	}
	else if (buf.find("\0", start) == start)
		throw std::runtime_error("Wrong instruction format !");
	check_bracket(buf, start);
}

void		Vm::check_bracket(std::string const & buf, size_t start)
{
	size_t opBr;
	size_t clBr;
	size_t len = 0;
	std::string nb;

	if ((opBr = buf.find("(", start)) == start)
	{
		if ((clBr = buf.find(")", start)) < opBr || buf.find(")", start) > 1000)
			throw BracketException("No closing Brackets match !");
		else
		{
				len = (clBr - opBr) - 1;
				nb = buf.substr(opBr + 1, len);
				if (_type == Int8 || _type == Int16 || _type == Int32)
					checkInteger(nb);
				else
					checkDecimal(nb);
				castValue(nb);
		}
	}
}

void		Vm::checkInteger(std::string const &value)
{
	if (value == "+" || value == "-"
|| !std::regex_match(value, std::regex("^[+\\-]?(?:0|[1-9]\\d*)?$")))
		throw LexicalSyntacticException("Syntactic exception (Value is not an integer)");
}

void		Vm::checkDecimal(std::string const &value)
{
	if (value == "+" || value == "-" || value == "+." || value == "-." || value == "."
	|| !std::regex_match(value, std::regex("^[+\\-]?(?:|0|[1-9]\\d*)(?:\\.\\d*)?(?:[eE][+\\-]?\\d+)?$")))
		throw LexicalSyntacticException("Syntactic exception (Value is not a decimal number)");
}

void		Vm::castValue(std::string const & nb)
{
	if (_type == Int8)
	{
		_value = nb;
		_stack.push_back(_factory->createOperand(_type, _value));
	}
	else if (_type == Int16)
	{
		_value = nb;
		_stack.push_back(_factory->createOperand(_type, _value));
	}
	else if (_type == Int32)
	{
		_value = nb;
		_stack.push_back(_factory->createOperand(_type, _value));
	}
	else if (_type == Float)
	{
		_value = nb;
		_stack.push_back(_factory->createOperand(_type, _value));
	}
	else if (_type == Double)
	{
		_value = nb;
		_stack.push_back(_factory->createOperand(_type, _value));
	}
	// for (std::vector<const IOperand *>::reverse_iterator it = _stack.rbegin() ; it != _stack.rend(); ++it)
    // 	// std::cout << ' ' << (*it)->toString() << std::endl;
}

void		Vm::add()
{
	IOperand const 		*left, *right, *rsl;

	right = *(_stack.rbegin());
	left = *(_stack.rbegin() + 1);
	rsl = *left + *right;
	_stack.pop_back();
	_stack.pop_back();
	_stack.push_back(rsl);
	for (std::vector<const IOperand *>::reverse_iterator it = _stack.rbegin() ; it != _stack.rend(); ++it)
		std::cout << "debug display: " << (*it)->toString() << std::endl;
}

void		Vm::sub()
{
	IOperand const 		*left, *right, *rsl;

	right = *(_stack.rbegin());
	left = *(_stack.rbegin() + 1);
	rsl = *left - *right;
	_stack.pop_back();
	_stack.pop_back();
	_stack.push_back(rsl);
	for (std::vector<const IOperand *>::reverse_iterator it = _stack.rbegin() ; it != _stack.rend(); ++it)
		std::cout << "debug display: " << (*it)->toString() << std::endl;
}

void		Vm::mul()
{
	IOperand const 		*left, *right, *rsl;

	right = *(_stack.rbegin());
	left = *(_stack.rbegin() + 1);
	rsl = *left * *right;
	_stack.pop_back();
	_stack.pop_back();
	_stack.push_back(rsl);
	for (std::vector<const IOperand *>::reverse_iterator it = _stack.rbegin() ; it != _stack.rend(); ++it)
		std::cout << "debug display: " << (*it)->toString() << std::endl;
}

void		Vm::div()
{
	IOperand const 		*left, *right, *rsl;

	right = *(_stack.rbegin());
	left = *(_stack.rbegin() + 1);
	rsl = *left / *right;
	_stack.pop_back();
	_stack.pop_back();
	_stack.push_back(rsl);
	for (std::vector<const IOperand *>::reverse_iterator it = _stack.rbegin() ; it != _stack.rend(); ++it)
		std::cout << "debug display: " << (*it)->toString() << std::endl;
}

void		Vm::mod()
{
	IOperand const 		*left, *right, *rsl;

	right = *(_stack.rbegin());
	left = *(_stack.rbegin() + 1);
	rsl = *left % *right;
	_stack.pop_back();
	_stack.pop_back();
	_stack.push_back(rsl);
	for (std::vector<const IOperand *>::reverse_iterator it = _stack.rbegin() ; it != _stack.rend(); ++it)
		std::cout << "debug display: " << (*it)->toString() << std::endl;
}
