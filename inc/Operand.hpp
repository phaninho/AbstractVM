/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmartin <stmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 15:23:19 by stmartin          #+#    #+#             */
/*   Updated: 2018/04/13 19:57:45 by stmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
#define OPERAND_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include "IOperand.hpp"
#include "Factory.hpp"


template <typename T>

class Operand : public IOperand {

public:

	Operand();

	Operand(std::string const &value, eOperandType type, /*const Factory* factory,*/ T const & nb):
	_type(type),
	// _factory(factory),
	_nb(nb),
	_str(value)
	{
		limit[Int8] = &Operand::limitInt8;
		// limit[Int16] = &Operand::limitInt16;
		// limit[Int32] = &Operand::limitInt32;
		// limit[Float] = &Operand::limitFloat;
		// limit[Double] = &Operand::limitDouble;
		// (void)_factory;
		// std::cout << "on creer operand " << value << " a une valeur type de " << _type << " nb = " << nb << std::endl;
	}

	Operand( Operand const & src);

	~Operand( void )
	{ }

	Operand &        operator=( Operand const & rhs );


	virtual int getPrecision( void ) const // Precision of the type of the instance
	{
		int precision = 0;

		if (_type == Float)
			precision = 2;
		else if (_type == Double)
			precision = 7;
		return precision;
	}

	virtual eOperandType getType( void ) const // Type of the instance
	{
		return _type;
	}

	virtual IOperand const * operator+( IOperand const & rhs ) const // Sum
	{
		double left = this->_nb;
		double right = std::stod(rhs.toString());
		std::stringstream	ss;

		if (this->_type >= rhs.getType())
		{
			void (Operand::*fc)(double left, double right) const;
			fc = limit.at(_type);
			(*this.*fc)(left, right);
		}
		// else
		// {
        //
		// }
		// if (this->_type == Int8)
		// {
		// 	if (left + right > std::numeric_limits<char>::max() || left + right < std::numeric_limits<char>::min())
		// 		throw std::runtime_error("Int8 overflow !");
		// 	else
		// 	{
				ss << left + right;
				return new Operand<short>(ss.str() , Int8, left + right);
		// 	}
		// }
		// else if (this->_type == Int16)
		// {
		// 	if (left + right > std::numeric_limits<short int>::max() || left + right < std::numeric_limits<short int>::min())
		// 		throw std::runtime_error("Int16 overflow !");
		// 	else
		// 	{
		// 		ss << left + right;
		// 		return new Operand<short>(ss.str() , Int16, left + right);
		// 	}
		// }
		// else if (this->_type == Int32)
		// {
		// 	if (left + right > std::numeric_limits<int>::max() || left + right < std::numeric_limits<int>::min())
		// 		throw std::runtime_error("Int32 overflow !");
		// 	else
		// 	{
		// 		ss << left + right;
		// 		return new Operand<int>(ss.str() , Int32, left + right);
		// 	}
		// }
		// else if (this->_type == Float)
		// {
		// 	if (left + right > std::numeric_limits<float>::max() || left + right < std::numeric_limits<float>::min())
		// 		throw std::runtime_error("float overflow !");
		// 	else
		// 	{
		// 		ss << left + right;
		// 		return new Operand<float>(ss.str() , Float, left + right);
		// 	}
		// }
		// else if (this->_type == Double)
		// {
		// 	if (left + right > std::numeric_limits<double>::max() || left + right < std::numeric_limits<double>::min())
		// 		throw std::runtime_error("double overflow !");
		// 	else
		// 	{
		// 		ss << left + right;
		// 		return new Operand<double>(ss.str() , Double, left + right);
		// 	}
		// }
		// throw std::runtime_error("Wrong Type");
	}

	void	limitInt8(double left, double right) const
	{
		if (left + right > std::numeric_limits<char>::max() || left + right < std::numeric_limits<char>::min())
			throw std::runtime_error("Int8 overflow !");
	}
	// virtual IOperand const * operator-( IOperand const & rhs ) const; // Difference
	// virtual IOperand const * operator*( IOperand const & rhs ) const; // Product
	// virtual IOperand const * operator/( IOperand const & rhs ) const; // Quotient
	// virtual IOperand const * operator%( IOperand const & rhs ) const; // Modulo

	virtual std::string const & toString( void ) const // String representation of the instance
	{
		return _str;
	}

private:

	eOperandType		_type;
	// const Factory		*_factory;
	T					_nb;
	std::string			_str;
	std::map<eOperandType, void (Operand::*)(double, double) const> limit;

};

#endif
