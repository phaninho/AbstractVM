/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmartin <stmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 15:23:19 by stmartin          #+#    #+#             */
/*   Updated: 2018/04/09 11:50:31 by stmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
#define OPERAND_HPP

template <typename T>
class Operand : public IOperand {

public:

	Operand( void );
	Operand( Operand const & );
	virtual ~Operand( void );

	virtual int getPrecision( void ) const; // Precision of the type of the instance
	virtual eOperandType getType( void ) const; // Type of the instance

	virtual IOperand const * operator+( IOperand const & rhs ) const; // Sum
	virtual IOperand const * operator-( IOperand const & rhs ) const; // Difference
	virtual IOperand const * operator*( IOperand const & rhs ) const; // Product
	virtual IOperand const * operator/( IOperand const & rhs ) const; // Quotient
	virtual IOperand const * operator%( IOperand const & rhs ) const; // Modulo

 	virtual std::string const & toString( void ) const; // String representation of the instance

private:

	T					_tpl;
	eOperandType		_type;
	
};

#endif
