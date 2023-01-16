/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:59:29 by mel-amma          #+#    #+#             */
/*   Updated: 2023/01/16 14:46:06 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef _iterator_traits__
#define _iterator_traits__

#include <iostream>
#include <algorithm>
#include <vector>

//do I gotta define iterator_traits? or just put it in the thing?

namespace ft{


template<class Iterator, class Category = std::random_access_iterator_tag>
struct iterator_traits
{
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
    typedef typename Iterator::iterator_category iterator_category;
};

template<class T, class Category>
struct iterator_traits<T*, Category>
{
    typedef ptrdiff_t difference_type;//
    typedef T value_type;//
    typedef T* pointer;//
    typedef T& reference;
    typedef Category iterator_category;
};

template<class T, class Category>
struct iterator_traits<const T*, Category>
{
    typedef std::ptrdiff_t                  difference_type;
    typedef T                               value_type;
    typedef const T                         *pointer;
    typedef const T&                        reference;
    typedef Category iterator_category;
};







template<class Category, class T, class Distance = ptrdiff_t,
         class Pointer = T*, class Reference = T&>
struct iterator
{
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;
};


}

#endif