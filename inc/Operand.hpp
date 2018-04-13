/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmartin <stmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 15:23:19 by stmartin          #+#    #+#             */
/*   Updated: 2018/04/13 14:47:42 by stmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
#define OPERAND_HPP

#include <iostream>
#include <stack>
#include "IOperand.hpp"
#include "Factory.hpp"


template <typename T>

class Operand : public IOperand {

public:

	Operand();

	Operand(std::string const &value, eOperandType type, /*const Factory* factory,*/ T const & nb, std::string str):
	_type(type),
	// _factory(factory),
	_nb(nb),
	_str(str)
	{
		// (void)_factory;
		std::cout << "on creer operand " << value << " a une valeur type de " << _type << " nb = " << nb << std::endl;
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

	// virtual IOperand const * operator+( IOperand const & rhs ) const; // Sum
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
};

#endif
