/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmartin <stmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:50:04 by stmartin          #+#    #+#             */
/*   Updated: 2018/04/14 16:14:05 by stmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Factory.hpp"
#include "Operand.hpp"

Factory::Factory()
{
	create[Int8] = &Factory::createInt8;
	create[Int16] = &Factory::createInt16;
	create[Int32] = &Factory::createInt32;
	create[Float] = &Factory::createFloat;
	create[Double] = &Factory::createDouble;
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
	f = create.at(type);
	return ((*this.*f)(value));
}

IOperand const * Factory::createInt8( std::string const & value ) const
{
	int min = std::numeric_limits<char>::min();
	int max = std::numeric_limits<char>::max();
	int int8 = std::stoi(value);
	if (int8 < min || int8 > max)
		throw std::overflow_error("Value is not a Int8 !");
	return (new Operand<short int>(value, Int8, this, int8));
}

IOperand const * Factory::createInt16( std::string const & value ) const
{
	int min = std::numeric_limits<short int>::min();
	int max = std::numeric_limits<short int>::max();
	int int16 = std::stoi(value);
	if (int16 < min || int16 > max)
		throw std::overflow_error("Value is not a Int16 !");
	return (new Operand<short int>(value, Int16, this, int16));
}

IOperand const * Factory::createInt32( std::string const & value ) const
{
	int min = std::numeric_limits<int>::min();
	int max = std::numeric_limits<int>::max();
	int int32 = std::stoi(value);
	if (int32 < min || int32 > max)
		throw std::overflow_error("Value is not a Int32 !");
	return (new Operand<int>(value, Int32, this, int32));
}

IOperand const * Factory::createFloat( std::string const & value ) const
{
	float minf = std::numeric_limits<float>::min();
	float maxf = std::numeric_limits<float>::max();
	float flt = std::stof(value);
	if ((flt < minf || flt > maxf) && flt != 0)
		throw std::overflow_error("Value is not a Float !");
	return (new Operand<float>(value, Float, this, flt));
}

IOperand const * Factory::createDouble( std::string const & value ) const
{
	double mind = std::numeric_limits<double>::min();
	double maxd = std::numeric_limits<double>::max();
	double dbl = std::stod(value);
	if ((dbl < mind || dbl > maxd) && dbl != 0)
		throw std::overflow_error("Value is not a Double !");
	return (new Operand<double>(value, Double, this, dbl));
}
