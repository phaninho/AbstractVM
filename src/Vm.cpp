/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vm.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmartin <stmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:59:38 by stmartin          #+#    #+#             */
/*   Updated: 2018/04/16 16:41:38 by stmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vm.hpp"
#include "IOperand.hpp"
#include "Factory.hpp"

Vm::Vm( void ):
_end(0),
_factory(new Factory),
_exit(0)
{
	(void)_exit;
}

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
	if (_end && !_exit)
		throw std::runtime_error("error : Program stop before exit");
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
		if (!std::getline(file, buf))
			break;
		read_args(buf);
	}
	file.close();
	if ((_end && !_exit) || (!_end && !_exit))
		throw std::runtime_error("error : Program stop before exit");
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

	if (buf.find(";;") == 0)
		_end = 1;
	else if (buf.find(";") != std::string::npos && buf.find(";") == 0)
		return ;
	else if (!_exit && buf.find("push") == 0)
	{
		_asmArg = PUSH;
		check_operand(buf, 3);
	}
	else if (!_exit && buf.find("assert") == 0)
	{
		_asmArg = ASSERT;
		check_stack();
		check_operand(buf, 5);
	}
	else if (!_exit && buf.find("dump") == 0 && check_word(buf, 4))
		dump_stack();
	else if (!_exit && buf.find("add") == 0 && check_word(buf, 3))
	{
		check_stack();
		add();
	}
	else if (!_exit && buf.find("sub") == 0 && check_word(buf, 3))
	{
		check_stack();
		sub();
	}
	else if (!_exit && buf.find("mul") == 0 && check_word(buf, 3))
	{
		check_stack();
		mul();
	}
	else if(!_exit && buf.find("div") == 0 && check_word(buf, 3))
	{
		check_stack();
		divi();
	}
	else if (!_exit && buf.find("mod") == 0 && check_word(buf, 3))
	{
		check_stack();
		mod();
	}
	else if (!_exit && buf.find("pop") == 0 && check_word(buf, 3))
	{
		check_stack();
		_stack.pop_back();
	}
	else if (!_exit && buf.find("print") == 0 && check_word(buf, 5))
	{
		_asmArg = PRINT;
		check_stack();
		check_for_print();
	}
	else if (buf.find("exit") == 0 && check_word(buf, 4))
		_exit = 1;
	else if (!_exit && buf.find(";") != std::string::npos && buf.find(";") > 2)
		return ;
	else if (!_exit)
		throw std::invalid_argument("Invalid Argument !");
}

bool		Vm::check_word(std::string buf,size_t s)
{
	if (buf.length() == s || (buf.find(";") == s && buf.find(";") != std::string::npos))
		return 1;
	return 0;
}

void		Vm::check_stack()
{
	if (_stack.empty())
		throw std::runtime_error("Stack is empty !");
	else if (_stack.size() < (_asmArg == PRINT ? 1 : 2))
		throw std::runtime_error("Stack have less than 2 elements !");
}

void		Vm::check_operand(std::string const &buf, size_t start)
{
	size_t pos;

	if ((_asmArg == PUSH || _asmArg == ASSERT) && (pos = buf.find(" ", start)) == start + 1)
		chooseType(buf, pos + 1);
	else if ((_asmArg == PUSH || _asmArg == ASSERT) && pos != start + 1)
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
		if ((clBr = buf.find(")", start)) < opBr || buf.find(")", start) == std::string::npos)
			throw BracketException("No closing Brackets match !");
		else if (!check_word(buf, clBr + 1))
			throw std::runtime_error("Wrong instruction after closing bracket !");
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

void		Vm::check_for_print()
{
	std::stringstream	ss;
	int					c;

	std::vector<const IOperand *>::reverse_iterator it = _stack.rbegin();
	if ((*it)->getType() != Int8)
		throw std::runtime_error("Not a type char");
	else
	{
		ss << (*it)->toString();
		ss >> c;
		std::cout << static_cast<char>(c) << std::endl;
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
	if (_type == Int8 || _type == Int16 || _type == Int32 || _type == Float || _type == Double)
	{
		_value = nb;
		if (_asmArg == PUSH)
			_stack.push_back(_factory->createOperand(_type, _value));
		else if (_asmArg == ASSERT)
		{
			_stack.push_back(_factory->createOperand(_type, _value));
			std::vector<const IOperand *>::reverse_iterator it = _stack.rbegin();
			std::vector<const IOperand *>::reverse_iterator it2 = _stack.rbegin() + 1;

			if (((*it)->toString() != (*it2)->toString()) || ((*it)->getType() != (*it2)->getType()))
				throw std::runtime_error("Assert not equal");
			_stack.pop_back();
		}
	}
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
}

void		Vm::divi()
{
	IOperand const 		*left, *right, *rsl;

	right = *(_stack.rbegin());
	left = *(_stack.rbegin() + 1);
	rsl = *left / *right;

	_stack.pop_back();
	_stack.pop_back();
	_stack.push_back(rsl);
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
}

void		Vm::dump_stack()
{
	if (_stack.size() < 1)
		throw std::runtime_error("Can't dump, Stack is empty");
	else
	{
		for (std::vector<const IOperand *>::reverse_iterator it = _stack.rbegin() ; it != _stack.rend(); ++it)
			std::cout << (*it)->toString() << std::endl;
	}
}
