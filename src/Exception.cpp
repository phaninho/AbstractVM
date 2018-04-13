/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmartin <stmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:21:13 by stmartin          #+#    #+#             */
/*   Updated: 2018/04/13 10:16:53 by stmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Exception.hpp"


LexicalSyntacticException::LexicalSyntacticException(char const * what):
std::runtime_error(what)
{ }

BracketException::BracketException(char const * what):
std::runtime_error(what)
{ }
