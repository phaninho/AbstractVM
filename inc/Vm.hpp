/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vm.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmartin <stmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:57:06 by stmartin          #+#    #+#             */
/*   Updated: 2018/04/16 16:26:24 by stmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_HPP
# define VM_HPP

#include <fstream>
#include <regex>
#include <sstream>
#include "Factory.hpp"
#include "Exception.hpp"

enum eAsmArgs
{
	PUSH,
	POP,
	DUMP,
	ASSERT,
	ADD,
	SUB,
	MUL,
	DIV,
	MOD,
	PRINT,
	EXIT
};

class Vm {

public:

	Vm( void );
	Vm( Vm const & src );
	virtual ~Vm();

	Vm &operator=( Vm const & rhs );

	void								run();
	void								run(char *av);
	const std::map<std::string, int>	createMap();
	void								read_args(std::string av);
	bool								check_word(std::string buf,size_t s);
	void								check_stack();
	void								check_operand(std::string const & buf, size_t pos);
	void								chooseType(std::string const & buf, size_t t);
	void								check_bracket(std::string const &, size_t start);
	void								check_for_print();
	void								checkInteger(std::string const &value);
	void								checkDecimal(std::string const &value);
	void								castValue(std::string const & nb);
	void								add();
	void								sub();
	void								mul();
	void								divi();
	void								mod();
	void								dump_stack();

private:

	bool								_end;
	eOperandType						_type;
	std::string							_value;
	Factory								*_factory;
	std::vector<IOperand const *>		_stack;
	eAsmArgs							_asmArg;
	bool								_exit;
};


#endif
