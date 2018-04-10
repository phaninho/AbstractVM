/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vm.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmartin <stmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:59:38 by stmartin          #+#    #+#             */
/*   Updated: 2018/04/10 19:19:00 by stmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vm.hpp"

Vm::Vm( void ):
_end(0)
{ }

Vm::Vm( Vm const & src )
{
	*this = src;
}

Vm::~Vm()
{ }

Vm 				&Vm::operator=( Vm const & rhs )
{
	if (this != &rhs)
		*this = rhs;
	return *this;
}

void	Vm::run()
{
	std::string buf;
	// int end = 0;

    while (!_end)
    {
    	if (!std::getline(std::cin, buf))
    		break;
		read_args(buf);
	}
}


void				Vm::run(char *av)
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

void						Vm::read_args(std::string buf)
{
	size_t pos;

	if ((pos = buf.find(";;")) == 0)
		_end = 1;
	else if ((pos = buf.find(";")) == 0)
		;
	else if ((pos = buf.find("push")) == 0)
		check_operand(buf, PUSH, 3);
}

void						Vm::check_operand(std::string const &buf, eAsmArgs n, size_t start)
{
	size_t pos;

	if (n == 0 && (pos = buf.find(" ")) == start + 1)
		std::cout << pos << std::endl;
	else if (n == 0 && pos != start + 1)
		throw std::runtime_error("Wrong instruction format !");
}
