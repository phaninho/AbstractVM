/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmartin <stmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 13:46:32 by stmartin          #+#    #+#             */
/*   Updated: 2018/04/16 20:13:56 by stmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "Operand.hpp"
#include "Vm.hpp"

typedef const	std::map<std::string, int> Map;

int		main(int ac, char **av)
{
	int i = 0;
	Vm vm;
	Map map = vm.createMap();
	try
	{
		// if (ac > 2)
			// throw std::invalid_argument("Too many arguments !");
		if (ac == 1)
			vm.run();
		else if (ac > 1)
		{
			while (++i < ac)
			{
				std::cout << av[i] << std::endl;
				vm.run(av[i]);
				vm.setVm();
			}
		}
	}
	catch (std::invalid_argument & e)
	{
		std::cout << e.what() << std::endl;
	}
}
