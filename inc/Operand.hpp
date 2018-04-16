/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmartin <stmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 15:23:19 by stmartin          #+#    #+#             */
/*   Updated: 2018/04/16 21:47:14 by stmartin         ###   ########.fr       */
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

	Operand(std::string const &value, eOperandType type, const Factory* factory, T const & nb):
	_type(type),
	_factory(factory),
	_nb(nb),
	_str(value)
	{
		limit[Int8] = &Operand::limitInt8;
		limit[Int16] = &Operand::limitInt16;
		limit[Int32] = &Operand::limitInt32;
		limit[Float] = &Operand::limitFloat;
		limit[Double] = &Operand::limitDouble;
	}

	Operand( Operand const & src);

	~Operand( void )
	{ }

	Operand &        operator=( Operand const & rhs );


	virtual int getPrecision( void ) const // Precision of the type of the instance
	{
		return _type;
	}

	virtual eOperandType getType( void ) const // Type of the instance
	{
		return _type;
	}

	virtual IOperand const * operator+( IOperand const & rhs ) const // Sum
	{
		double left = this->_nb;
		double right = std::stod(rhs.toString());
		double rsl;
		std::stringstream	ss;
		void (Operand::*fc)(double rsl) const;
		eOperandType type = _type >= rhs.getType() ? _type : rhs.getType();

		rsl = left + right;
		fc = limit.at(type);
		(*this.*fc)(rsl);
		ss << left + right;
		return _factory->createOperand(type, ss.str());
	}

	virtual IOperand const * operator-( IOperand const & rhs ) const // Difference
	{
		double left = this->_nb;
		double right = std::stod(rhs.toString());
		double rsl;
		std::stringstream	ss;
		void (Operand::*fc)(double rsl) const;
		eOperandType type = _type >= rhs.getType() ? _type : rhs.getType();

		rsl = left - right;
		fc = limit.at(type);
		(*this.*fc)(rsl);
		ss << left - right;
		return _factory->createOperand(type, ss.str());
	}

	virtual IOperand const * operator*( IOperand const & rhs ) const // Product
	{
		double left = this->_nb;
		double right = std::stod(rhs.toString());
		double rsl;
		std::stringstream	ss;
		void (Operand::*fc)(double rsl) const;
		eOperandType type = _type >= rhs.getType() ? _type : rhs.getType();

		rsl = left * right;
		fc = limit.at(type);
		(*this.*fc)(rsl);
		ss << left * right;
		return _factory->createOperand(type, ss.str());
	}

	virtual IOperand const * operator/( IOperand const & rhs ) const // Quotient
	{
		double left = this->_nb;
		double right = std::stod(rhs.toString());
		double rsl;
		std::stringstream	ss;
		void (Operand::*fc)(double rsl) const;
		eOperandType type = _type >= rhs.getType() ? _type : rhs.getType();

		if (right == 0)
			throw std::runtime_error("Division by 0 not possible !");
		rsl = left / left;

		fc = limit.at(type);
		(*this.*fc)(rsl);
		ss << left / right;
		return _factory->createOperand(type, ss.str());
	}

	virtual IOperand const * operator%( IOperand const & rhs ) const // Modulo
	{
		int left = this->_nb;
		int right = std::stoi(rhs.toString());
		int rsl;
		std::stringstream	ss;
		eOperandType type = _type >= rhs.getType() ? _type : rhs.getType();

		if (right == 0)
			throw std::runtime_error("\033[1;34mModulo by 0 not possible !\033[0m");
		else if (_type == Float || rhs.getType() == Float || _type == Double || rhs.getType() == Double )
			throw std::runtime_error("\033[1;34mModulo use an invalid type !\033[0m");

		rsl = left % right;
		if (rsl > std::numeric_limits<char>::max() || rsl < std::numeric_limits<char>::min())
			throw std::runtime_error("\033[1;36mInt8 overflow !\033[0m");
		else if (rsl > std::numeric_limits<short int>::max() || rsl < std::numeric_limits<short int>::min())
			throw std::runtime_error("\033[1;36mInt16 overflow !\033[0m");
		else if (rsl > std::numeric_limits<int>::max() || rsl < std::numeric_limits<int>::min())
			throw std::runtime_error("\033[1;36mInt32 overflow !\033[0m");
		ss << left % right;
		return _factory->createOperand(type, ss.str());
	}

	virtual std::string const & toString( void ) const // String representation of the instance
	{
		return _str;
	}


	//////////	check limits ///////////////////


	void	limitInt8(double rsl) const
	{
		if (rsl > std::numeric_limits<char>::max() || rsl < std::numeric_limits<char>::min())
			throw std::runtime_error("\033[1;36mInt8 overflow !\033[0m");
	}

	void	limitInt16(double rsl) const
	{
		if (rsl > std::numeric_limits<short int>::max() || rsl < std::numeric_limits<short int>::min())
			throw std::runtime_error("\033[1;36mInt16 overflow !\033[0m");
	}

	void	limitInt32(double rsl) const
	{
		if (rsl > std::numeric_limits<int>::max() || rsl < std::numeric_limits<int>::min())
			throw std::runtime_error("\033[1;36mInt32 overflow !\033[0m");
	}

	void	limitFloat(double rsl) const
	{
		if (rsl != 0 && (rsl > std::numeric_limits<float>::max() || rsl < -std::numeric_limits<float>::max()))
			throw std::runtime_error("\033[1;36mFloat overflow !\033[0m");
	}

	void	limitDouble(double rsl) const
	{
		if (rsl != 0 && (rsl > std::numeric_limits<double>::max() && rsl < -std::numeric_limits<double>::max()))
			throw std::runtime_error("\033[1;36mDouble overflow !\033[0m");
	}

private:

	eOperandType		_type;
	const Factory		*_factory;
	T					_nb;
	std::string			_str;
	std::map<eOperandType, void (Operand::*)(double) const> limit;

};

#endif
