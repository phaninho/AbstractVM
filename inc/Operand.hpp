/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmartin <stmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 15:23:19 by stmartin          #+#    #+#             */
/*   Updated: 2018/04/11 01:02:20 by stmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
#define OPERAND_HPP

#include <iostream>
#include "IOperand.hpp"
#include "Factory.hpp"


// template <typename T>

class Operand : public IOperand {

public:

	Operand();

	Operand(std::string const &value, eOperandType type, const Factory* factory):
	_type(type),
	_Factory(factory)
	{
		(void)_Factory;
		std::cout << "on creer operand " << value << " a une valeur type de " << _type << std::endl;
	}

	Operand( Operand const & src);

	~Operand( void )
	{
		std::cout << "on detruit operand " << _type << std::endl;
	}

	Operand &        operator=( Operand const & rhs );


	// virtual int getPrecision( void ) const; // Precision of the type of the instance
	// virtual eOperandType getType( void ) const; // Type of the instance
    //
	// virtual IOperand const * operator+( IOperand const & rhs ) const; // Sum
	// virtual IOperand const * operator-( IOperand const & rhs ) const; // Difference
	// virtual IOperand const * operator*( IOperand const & rhs ) const; // Product
	// virtual IOperand const * operator/( IOperand const & rhs ) const; // Quotient
	// virtual IOperand const * operator%( IOperand const & rhs ) const; // Modulo
    //
 	// virtual std::string const & toString( void ) const; // String representation of the instance

private:

	eOperandType		_type;
	const Factory		*_Factory;
};

#endif
