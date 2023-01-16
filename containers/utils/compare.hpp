/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:59:22 by mel-amma          #+#    #+#             */
/*   Updated: 2023/01/16 15:05:18 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _lexicographical_compare
#define _lexicographical_compare
#include "../utils/enable_if.hpp"
#include "../utils/is_integral.hpp"
#include <utility>
namespace ft{

template< class InputIt1, class InputIt2 >
bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                              InputIt2 first2, InputIt2 last2 )
{
    while(first1 != last1 && first2 != last2)
    {
        if(*first1 == *first2)
        {
            first1++;
            first2++;
            continue;
        }
        else
            return *first1 < *first2; 
    }
    if(first2 == last2 && first1 == last1)
        return false;
    else if(first1 == last1)
        return true;
    else 
        return false;
};

template <class _InputIterator1, class _InputIterator2, class _Compare>
bool lexicographical_compare(_InputIterator1 __first1, _InputIterator1 __last1,
                        _InputIterator2 __first2, _InputIterator2 __last2, _Compare __comp);

}
#endif