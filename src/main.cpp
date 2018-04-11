/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmartin <stmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 13:46:32 by stmartin          #+#    #+#             */
/*   Updated: 2018/04/11 15:15:37 by stmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "Operand.hpp"
#include "Vm.hpp"

typedef const	std::map<std::string, int> Map;

int		main(int ac, char **av)
{
	Vm vm;
	Map map = vm.createMap();

	try
	{
		if (ac > 2)
			throw std::invalid_argument("Too many arguments !");
		else if (ac == 1)
			vm.run();
		else if (ac == 2)
			vm.run(av[1]);
	}
	catch (std::invalid_argument & e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (std::runtime_error & e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}
