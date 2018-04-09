/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vm.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmartin <stmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:57:06 by stmartin          #+#    #+#             */
/*   Updated: 2018/04/09 20:13:25 by stmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_HPP
# define VM_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <map>

class Vm {

public:

	Vm( void );
	Vm( Vm const & src );
	virtual ~Vm();

	Vm &operator=( Vm const & rhs );

	void								run();
	void								run(char *av);
	const std::map<std::string, int>	createMap();

};


#endif
