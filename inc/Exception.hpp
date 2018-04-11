/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmartin <stmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:16:35 by stmartin          #+#    #+#             */
/*   Updated: 2018/04/11 16:06:42 by stmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP

#include <stdexcept>

class LexicalSyntacticException : public std::runtime_error
{
	public:
		LexicalSyntacticException(char const *);
};

class BracketException : public std::runtime_error
{
	public:
		BracketException(char const *);
};

#endif
