/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmartin <stmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:50:04 by stmartin          #+#    #+#             */
/*   Updated: 2018/04/11 01:01:04 by stmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Factory.hpp"
#include "Operand.hpp"

Factory::Factory()
{
	create[Int8] = &Factory::createInt8;
	// create[Int16] = &Factory::createInt16;
	// create[Int32] = &Factory::createInt32;
	// create[Float] = &Factory::createFloat;
	// create[Double] = &Factory::createDouble;
}

Factory::Factory(Factory const & src)
{
	*this = src;
}

Factory::~Factory()
{ }

Factory		&Factory::operator=(Factory const & rhs)
{
	if (this != &rhs)
		*this = rhs;
	return *this;
}

IOperand const * Factory::createOperand( eOperandType type, std::string const & value ) const
{
	IOperand const* (Factory::*f)(std::string const & value) const;
	// std::cout << "on est la" << std::endl;
	f = create.at(type);
	return ((*this.*f)(value));
}

IOperand const * Factory::createInt8( std::string const & value ) const
{
		return (new Operand(value, Int8, this));
}

// IOperand const * Factory::createInt16( std::string const & value ) const
// {
    //
// }
//
// IOperand const * Factory::createInt32( std::string const & value ) const
// {
    //
// }
//
// IOperand const * Factory::createFloat( std::string const & value ) const
// {
    //
// }
//
// IOperand const * Factory::createDouble( std::string const & value ) const
// {
    //
// }
//
