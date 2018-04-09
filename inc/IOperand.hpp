/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmartin <stmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 13:55:09 by stmartin          #+#    #+#             */
/*   Updated: 2018/04/09 17:26:32 by stmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_HPP
#define IOPERAND_HPP

enum 	eOperandType
{
	Int8, 	//int8_t
	Int16,	//int16_t
	Int32,	//int32_t
	Float,	//float
	Double	//double
};

class 	IOperand {

public:
	virtual int getPrecision( void ) const = 0;
	virtual eOperandType getType( void ) const = 0;
	virtual IOperand const * operator+( IOperand const & rhs ) const = 0; // Sum
	virtual IOperand const * operator-( IOperand const & rhs ) const = 0; // Difference
	virtual IOperand const * operator*( IOperand const & rhs ) const = 0; // Product
	virtual IOperand const * operator/( IOperand const & rhs ) const = 0; // Quotient
	virtual IOperand const * operator%( IOperand const & rhs ) const = 0; // Modulo
  // Precision of the type of the instance
  // Type of the instance

 	virtual std::string const & toString( void ) const = 0; // String representation of the instance

	virtual ~IOperand( void ) {}
	
};

#endif
