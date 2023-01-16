/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator_.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 14:56:14 by mel-amma          #+#    #+#             */
/*   Updated: 2023/01/16 15:04:14 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _reverse_iterator_
#define _reverse_iterator_

#include "../utils/iterator_traits.hpp"

namespace ft{


template <typename iterator>
    class reverse_iterator
{
    public :
        typedef iterator                                                     iterator_type;
        typedef typename std::size_t                          size_type;
        typedef typename iterator_traits<iterator>::value_type                          value_type;
        typedef typename iterator_traits<iterator>::difference_type                     difference_type;
        typedef typename iterator_traits<iterator>::iterator_category    iterator_category;
        typedef typename iterator_traits<iterator>::pointer                pointer;
        typedef const typename iterator_traits<iterator>::pointer          const_pointer;
        typedef typename iterator_traits<iterator>::reference               reference;
        typedef const typename iterator_traits<iterator>::reference            const_reference;
    private :
        // pointer ptr;
        iterator_type it;
        template<class Key, class T, class Compare ,
        class Allocator >
            friend class map;
        
        template <class T1, class Allocator1>
           friend class vector;
        

        template<class Key, class Compare ,
           class Allocator >
           friend class set;
        


        //>>>>>friends 
        template <typename v_type,typename map_ptrX, class value_compareX>
            friend class MapIterator;
        template <typename rit>
            friend class reverse_iterator;
    public :
        reverse_iterator(const iterator_type& it) 
        {
            this->it = it;
        };
        
        iterator_type base() const
        {
            return it;
        };
        //default constructible only from forward iterator and ahead
        reverse_iterator(){};

        template <typename s>
            reverse_iterator(const reverse_iterator<s> &other) {
            it = other.base();
        };
        
        template <typename s>
            reverse_iterator<iterator>& operator=(const reverse_iterator<s> &other)
        {
            it =  other.base();
            return *this;
        };

        ~reverse_iterator(){};

        //increments
            reverse_iterator<iterator>& operator++()//++x
            {
                it--;
                return *this;
            };
            reverse_iterator<iterator> operator++(int)//x++
            {
                reverse_iterator<iterator> temp = *this;
                it--;
                return temp;
            };
            reverse_iterator<iterator>& operator--()
            {
                it++;
                return *this;
            };
            reverse_iterator<iterator> operator--(int)
            {
                reverse_iterator<iterator> temp = *this;
                it++;
                return temp;
            };

           
            reverse_iterator<iterator> operator+(int a)const
            {
                reverse_iterator<iterator>  temp;
                temp.it = it - a;
                return temp;
            };
            template <class iter>
            friend reverse_iterator<iter> operator+(int a, const reverse_iterator<iter>& map);
            reverse_iterator<iterator> operator-(int a)const
            {
                reverse_iterator<iterator>  temp;
                temp.it = it + a;
                return temp;
            };

            difference_type operator-(reverse_iterator<iterator> other)const
            {
                difference_type a;
                
                a = other.it - it;
                return a;
            };

           
            reverse_iterator& operator+=(int amount)
            {
                it = it - amount;
                return *this;
            };
            reverse_iterator& operator-=(int amount)
            {
                it = it + amount;
                return *this;
            };
            
            /*
            //operator * -> const op const for lvalue
            //operator * -> not const for rvalue
            */
            const_pointer operator->() const
            {
                iterator_type  temp = it;
                --temp;
                return temp.operator->();
            };
            const_reference operator*() const
            {
                iterator_type  temp = it;
                --temp;
                return temp.operator*();
            };
            pointer operator->()
            {
                iterator_type  temp = it;
                --temp;
                return temp.operator->();
            };
            reference operator*()
            {
                iterator_type  temp = it;
                --temp;
                return temp.operator*();
            };

            /**
             * @explanation
             * 
             [] is the ptr + number * hops
             op [] const op const // for read only in const objs
             op [] not const for writing
            */
            reference operator[](int index)
            {
                return *(it - index - 1);
            };
            const_reference operator[](int index)const
            {
                return *(it - index - 1);
            };

        // multipass?
            template <typename iterator1, typename iterator2>
            friend bool operator==(const reverse_iterator<iterator1> &it1, const reverse_iterator<iterator2> &it2);
            
            template <typename iterator1, typename iterator2>
            friend bool operator!=(const reverse_iterator<iterator1> &it1, const reverse_iterator<iterator2> &it2);

            template <typename iterator1, typename iterator2>
            friend bool operator>(const reverse_iterator<iterator1> &it1, const reverse_iterator<iterator2> &it2);

            template <typename iterator1, typename iterator2>
            friend bool operator>=(const reverse_iterator<iterator1> &it1, const reverse_iterator<iterator2> &it2);

            template <typename iterator1, typename iterator2>
            friend bool operator<(const reverse_iterator<iterator1> &it1, const reverse_iterator<iterator2> &it2);

            template <typename iterator1, typename iterator2>
            friend bool operator<=(const reverse_iterator<iterator1> &it1, const reverse_iterator<iterator2> &it2);
    };

template<typename iterator1,typename iterator2>
bool operator==(const reverse_iterator<iterator1> &it1,const reverse_iterator<iterator2> &it2)
{
    return (it1.it == it2.it);
};

template<typename iterator1,typename iterator2>
bool operator!=(const reverse_iterator<iterator1> &it1,const reverse_iterator<iterator2> &it2)
{
    return (it1.it != it2.it);
};

template<typename iterator1,typename iterator2>
bool operator>(const reverse_iterator<iterator1> &it1,const reverse_iterator<iterator2> &it2)
            {
                return (it1.it < it2.it);
                   
            };
template<typename iterator1,typename iterator2>         
bool operator>=(const reverse_iterator<iterator1> &it1,const reverse_iterator<iterator2> &it2)
{
    return (it1.it <= it2.it);
};

template<typename iterator1,typename iterator2>
bool operator<(const reverse_iterator<iterator1> &it1,const reverse_iterator<iterator2> &it2)
{
    return (it1.it > it2.it);
};

template<typename iterator1,typename iterator2>
bool operator<=(const reverse_iterator<iterator1> &it1,const reverse_iterator<iterator2> &it2)
{
    return (it1.it >= it2.it);
};

template <class iterator>
reverse_iterator<iterator> operator+(int a, const reverse_iterator<iterator>& iter)
{
    reverse_iterator<iterator>  temp;
    temp = iter.operator+(a);
    return (temp);
};


}
#endif