/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmartin <stmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 13:46:32 by stmartin          #+#    #+#             */
/*   Updated: 2018/04/09 17:18:08 by stmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "Operand.hpp"
#include <iostream>
#include <map>
#include <iterator>

const std::map<std::string, int> createMap()
{
	std::map<std::string, int> m;

	m["Int8"] = 1;
	m["Int16"] = 2;
	m["Int32"] = 3;
	m["Float"] = 4;
	m["Double"] = 5;
	return m;
}

int		main(int ac, char **)
{
	const	std::map<std::string, int> map = createMap();

	if (map.find("Int8") != map.end())
		std::cout << map.at("Int8") << std::endl;
	try
	{
		if (ac > 2)
			throw std::invalid_argument("Too many arguments !");
		// else if (ac == 1)
		// 	//start reading standart input
		// else if (ac == 2)
			//start reading file
	}
	catch (std::invalid_argument & e)
	{
		std::cout << e.what() << std::endl;
	}
}
