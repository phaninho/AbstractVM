/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmartin <stmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 13:46:32 by stmartin          #+#    #+#             */
/*   Updated: 2018/04/16 21:20:36 by stmartin         ###   ########.fr       */
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

	if (ac == 1)
		vm.run();
	else if (ac > 1)
	{
		while (++i < ac)
		{
			std::cout << "\033[1;32mbold Execute "<< av[i] << " :\033[0m" << std::endl;
			vm.run(av[i]);
			vm.setVm();
		}
	}
}


//Bonus
//ecriture scientifique
//multi files
//couleurs
//verif complete
