/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmartin <stmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 15:23:19 by stmartin          #+#    #+#             */
/*   Updated: 2018/04/14 17:39:09 by stmartin         ###   ########.fr       */
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
		// (void)_factory;
		// std::cout << "on creer operand " << value << " a une valeur type de " << _type << " nb = " << nb << std::endl;
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

		// std::cout << "le rsl dans divi " << left << " " << right << " " << rsl << std::endl;

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

		if (left == 0)
			throw std::runtime_error("Division by 0 not possible !");
		else if (_type == Float || rhs.getType() == Float || _type == Double || rhs.getType() == Double )
			throw std::runtime_error("Modulo use an invalid type !");

		rsl = left % right;
		if (rsl > std::numeric_limits<char>::max() || rsl < std::numeric_limits<char>::min())
			throw std::runtime_error("Int8 overflow !");
		else if (rsl > std::numeric_limits<short int>::max() || rsl < std::numeric_limits<short int>::min())
			throw std::runtime_error("Int16 overflow !");
		else if (rsl > std::numeric_limits<int>::max() || rsl < std::numeric_limits<int>::min())
			throw std::runtime_error("Int32 overflow !");
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
			throw std::runtime_error("Int8 overflow !");
	}

	void	limitInt16(double rsl) const
	{
		if (rsl > std::numeric_limits<short int>::max() || rsl < std::numeric_limits<short int>::min())
			throw std::runtime_error("Int16 overflow !");
	}

	void	limitInt32(double rsl) const
	{
		if (rsl > std::numeric_limits<int>::max() || rsl < std::numeric_limits<int>::min())
			throw std::runtime_error("Int32 overflow !");
	}

	void	limitFloat(double rsl) const
	{
		std::cout << rsl << std::endl;
		if (rsl != 0 && (rsl > std::numeric_limits<float>::max() || rsl < std::numeric_limits<float>::min()))
			throw std::runtime_error("Float overflow !");
	}

	void	limitDouble(double rsl) const
	{
		std::cout << rsl << std::endl;
		if (!(rsl <= std::numeric_limits<double>::max() && rsl >= std::numeric_limits<double>::min()))
			throw std::runtime_error("Double overflow !");
	}

private:

	eOperandType		_type;
	const Factory		*_factory;
	T					_nb;
	std::string			_str;
	std::map<eOperandType, void (Operand::*)(double) const> limit;

};

#endif
