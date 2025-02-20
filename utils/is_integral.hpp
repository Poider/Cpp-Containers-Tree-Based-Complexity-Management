/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:59:13 by mel-amma          #+#    #+#             */
/*   Updated: 2023/01/17 13:46:24 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _is_integral
#define _is_integral

//you can send a value of some type or a parameter or a type, through templates
namespace ft{


template< class T, T V >
struct base_integral
{
    const static T value = V;
};



typedef  base_integral<bool, true> true_type;
typedef  base_integral<bool, false> false_type;

template<typename T>
struct is_integral : false_type{};


template<typename T>
struct is_integral<const T> : is_integral<T> {};

template<typename T>
struct is_integral<volatile T> : is_integral<T> {};

template<typename T>
struct is_integral<const volatile T> : is_integral<T> {};


template<>
struct is_integral<int> : true_type{};

template<>
struct is_integral<unsigned int> : true_type{};


template<>
struct is_integral<signed char> : true_type{};


template<>
struct is_integral<bool> : true_type{};

template<>
struct is_integral<char> : true_type{};


template<>
struct is_integral<unsigned char> : true_type{};

template<>
struct is_integral<char16_t> : true_type{};

template<>
struct is_integral<char32_t> : true_type{};

template<>
struct is_integral<wchar_t> : true_type{};

template<>
struct is_integral<short> : true_type{};

template<>
struct is_integral<unsigned short int> : true_type{};



template<>
struct is_integral<long> : true_type{};


template<>
struct is_integral<unsigned long> : true_type{};


template<>
struct is_integral<long long> : true_type{};



template<>
struct is_integral<unsigned long long> : true_type{};

}
#endif