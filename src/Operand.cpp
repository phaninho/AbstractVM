/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmartin <stmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 14:00:35 by stmartin          #+#    #+#             */
/*   Updated: 2018/04/09 11:45:08 by stmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operand.hpp"

Operand::Operand()
{ }

Operand::Operand( Operand const & src)
{
	*this = src;
}

Operand::~Operand()
{ }

virtual int getPrecision( void ) const
{

}

virtual eOperandType getType( void ) const
{
	
}

virtual IOperand const * operator+( Operand const & rhs ) const // Sum
{

}
virtual IOperand const * operator-( Operand const & rhs ) const // Difference
{

}

virtual IOperand const * operator*( Operand const & rhs ) const // Product
{

}

virtual IOperand const * operator/( Operand const & rhs ) const // Quotient
{

}

virtual IOperand const * operator%( Operand const & rhs ) const // Modulo
{

}
