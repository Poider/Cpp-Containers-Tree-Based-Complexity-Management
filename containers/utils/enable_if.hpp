/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:59:25 by mel-amma          #+#    #+#             */
/*   Updated: 2023/01/16 14:45:57 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _enable_if
#define _enable_if

namespace ft{

template<bool B, class T = void>
struct enable_if {};
 
template<class T>
struct enable_if<true, T> 
{
     typedef T type;
};

}


#endif