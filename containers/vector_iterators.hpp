/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterators.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 12:49:00 by mel-amma          #+#    #+#             */
/*   Updated: 2022/11/16 13:45:46 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef _my_vector_iter
#define _my_vector_iter
#include <memory>
#include <algorithm>
#include <iterator>
#include "iterator_traits.hpp"
template <class T, class Allocator>
class vector;

namespace ft{
template <typename vec>
    class VectorIterator
{
    public :
        typedef vec                                                 iterator_type;
        typedef typename iterator_traits<vec>::value_type           value_type;
        typedef typename iterator_traits<vec>::difference_type      difference_type;
        typedef typename std::size_t                                size_type;
        typedef typename iterator_traits<vec>::iterator_category    iterator_category;
        typedef typename iterator_traits<vec>::pointer                pointer;
        typedef const  pointer          const_pointer;
        typedef typename iterator_traits<vec>::reference              reference;
        typedef const  reference          const_reference;
    private :
        pointer ptr;
        template <class T1, class Allocator1>
           friend class vector;
        VectorIterator(pointer ptr):ptr(ptr) 
        {};

        //>>>>>friends
        template <typename it>
            friend class VectorIterator;
        template <typename rit>
            friend class ReverseVectorIterator;
        // template <typename ss>
        //     friend class VectorIterator;
    public :
        pointer base() const
        {
            return ptr;
        };
        //default constructible only from forward iterator and ahead
        VectorIterator(){};

        template <typename s>
        VectorIterator(const VectorIterator<s> &other) {
            this->ptr = other.base();
        };

        template <typename s>
        VectorIterator<vec>& operator=(const VectorIterator<s> &other)
        {
            this->ptr = other.base();
            return *this;
        };
        ~VectorIterator(){};

        //increments
            VectorIterator<vec>& operator++()//++x
            {
                ptr++;
                return *this;
            };
            VectorIterator<vec> operator++(int)//x++
            {
                VectorIterator<vec> temp = *this;
                ptr++;
                return temp;
            };
            VectorIterator<vec>& operator--()
            {
                ptr--;
                return *this;
            };
            VectorIterator<vec> operator--(int)
            {
                VectorIterator<vec> temp =*this;
                ptr--;
                return (temp);
            };

          
            VectorIterator<vec> operator+(int a) const
            {
                VectorIterator<vec>  temp;
                temp.ptr = ptr + a;
                return temp;
            };
            template <class iter>
            friend VectorIterator<iter> operator+(int a, const VectorIterator<iter>& vector);
            VectorIterator<vec> operator-(int a)const
            {
                VectorIterator<vec>  temp;
                temp.ptr = ptr - a;
                return temp;
            };

            difference_type operator-(VectorIterator<vec> other)const
            {
                difference_type a;
                
                a = ptr - other.ptr;
                return a;
            };

           
            VectorIterator& operator+=(int amount)
            {
                ptr = ptr + amount;
                return *this;
            };
            VectorIterator& operator-=(int amount)
            {
                ptr = ptr - amount;
                return *this;
            };
            
            /*
            //operator * -> const op const for lvalue
            //operator * -> not const for rvalue
            */
            const_pointer operator->() const
            {
                return ptr;
            };
            const_reference operator*() const
            {
                return *ptr;
            };
            pointer operator->()
            {
                return ptr;
            };
            reference operator*()
            {
                return *ptr;
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
                return *(ptr + index);
            };
            const_reference operator[](int index)const
            {
                return *(ptr + index);
            };

        // multipass?
             template <typename iterator1, typename iterator2>
            friend bool operator==(const VectorIterator<iterator1> &it1, const VectorIterator<iterator2> &it2);
            
            template <typename iterator1, typename iterator2>
            friend bool operator!=(const VectorIterator<iterator1> &it1, const VectorIterator<iterator2> &it2);

            template <typename iterator1, typename iterator2>
            friend bool operator>(const VectorIterator<iterator1> &it1, const VectorIterator<iterator2> &it2);

            template <typename iterator1, typename iterator2>
            friend bool operator>=(const VectorIterator<iterator1> &it1, const VectorIterator<iterator2> &it2);

            template <typename iterator1, typename iterator2>
            friend bool operator<(const VectorIterator<iterator1> &it1, const VectorIterator<iterator2> &it2);

            template <typename iterator1, typename iterator2>
            friend bool operator<=(const VectorIterator<iterator1> &it1, const VectorIterator<iterator2> &it2);
    };


template <typename iterator>
    class ReverseVectorIterator
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
        template <class T1, class Allocator1>
           friend class vector;
        ReverseVectorIterator(pointer ptr) 
        {
            it = VectorIterator<pointer>(ptr);
        };


        //>>>>>friends 
        template <typename it>
            friend class VectorIterator;
        template <typename rit>
            friend class ReverseVectorIterator;
    public :
        iterator_type base() const
        {
            return it;
        };
        //default constructible only from forward iterator and ahead
        ReverseVectorIterator(){};

        template <typename s>
            ReverseVectorIterator(const ReverseVectorIterator<s> &other) {
            it = other.base();
        };
        
        template <typename s>
            ReverseVectorIterator<iterator>& operator=(const ReverseVectorIterator<s> &other)
        {
            it =  other.base();
            return *this;
        };

        ~ReverseVectorIterator(){};

        //increments
            ReverseVectorIterator<iterator>& operator++()//++x
            {
                it--;
                return *this;
            };
            ReverseVectorIterator<iterator> operator++(int)//x++
            {
                ReverseVectorIterator<iterator> temp = *this;
                it--;
                return temp;
            };
            ReverseVectorIterator<iterator>& operator--()
            {
                it++;
                return *this;
            };
            ReverseVectorIterator<iterator> operator--(int)
            {
                ReverseVectorIterator<iterator> temp = *this;
                it++;
                return temp;
            };

           
            ReverseVectorIterator<iterator> operator+(int a)const
            {
                ReverseVectorIterator<iterator>  temp;
                temp.it = it - a;
                return temp;
            };
            template <class iter>
            friend ReverseVectorIterator<iter> operator+(int a, const ReverseVectorIterator<iter>& vector);
            ReverseVectorIterator<iterator> operator-(int a)const
            {
                ReverseVectorIterator<iterator>  temp;
                temp.it = it + a;
                return temp;
            };

            difference_type operator-(ReverseVectorIterator<iterator> other)const
            {
                difference_type a;
                
                a = other.it - it;
                return a;
            };

           
            ReverseVectorIterator& operator+=(int amount)
            {
                it = it - amount;
                return *this;
            };
            ReverseVectorIterator& operator-=(int amount)
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
                return it.operator->();
            };
            const_reference operator*() const
            {
                ReverseVectorIterator<iterator>  temp = it;
                --temp;
                return temp.operator*();
            };
            pointer operator->()
            {
                return it.operator->();
            };
            reference operator*()
            {
                ReverseVectorIterator<iterator>  temp = it;
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
                return *(it.base() - index);
            };
            const_reference operator[](int index)const
            {
                return *(it.base() - index);
            };

        // multipass?
            template <typename iterator1, typename iterator2>
            friend bool operator==(const ReverseVectorIterator<iterator1> &it1, const ReverseVectorIterator<iterator2> &it2);
            
            template <typename iterator1, typename iterator2>
            friend bool operator!=(const ReverseVectorIterator<iterator1> &it1, const ReverseVectorIterator<iterator2> &it2);

            template <typename iterator1, typename iterator2>
            friend bool operator>(const ReverseVectorIterator<iterator1> &it1, const ReverseVectorIterator<iterator2> &it2);

            template <typename iterator1, typename iterator2>
            friend bool operator>=(const ReverseVectorIterator<iterator1> &it1, const ReverseVectorIterator<iterator2> &it2);

            template <typename iterator1, typename iterator2>
            friend bool operator<(const ReverseVectorIterator<iterator1> &it1, const ReverseVectorIterator<iterator2> &it2);

            template <typename iterator1, typename iterator2>
            friend bool operator<=(const ReverseVectorIterator<iterator1> &it1, const ReverseVectorIterator<iterator2> &it2);
    };




template <class vec>
VectorIterator<vec> operator+(int a, const VectorIterator<vec>& iter)
{
    VectorIterator<vec>  temp1;
    temp1 = iter.operator+(a);
    return (temp1);
};


template <class iterator>
ReverseVectorIterator<iterator> operator+(int a, const ReverseVectorIterator<iterator>& iter)
{
    ReverseVectorIterator<iterator>  temp;
    temp = iter.operator+(a);
    return (temp);
};

//comparisons

template<typename iterator1,typename iterator2>
bool operator==(const ReverseVectorIterator<iterator1> &it1,const ReverseVectorIterator<iterator2> &it2)
{
    return (it1 == it2);
};

template<typename iterator1,typename iterator2>
bool operator!=(const ReverseVectorIterator<iterator1> &it1,const ReverseVectorIterator<iterator2> &it2)
{
    return (it1 != it2);
};

template<typename iterator1,typename iterator2>
bool operator>(const VectorIterator<iterator1> &it1,const VectorIterator<iterator2> &it2)
{
    return (it1.ptr > it2.ptr);
};

template<typename iterator1,typename iterator2>
bool operator>=(const VectorIterator<iterator1> &it1,const VectorIterator<iterator2> &it2)
{
    return (it1.ptr >= it2.ptr);
};

template<typename iterator1,typename iterator2>
bool operator<(const VectorIterator<iterator1> &it1,const VectorIterator<iterator2> &it2)
{
    return (it1.ptr < it2.ptr);
};

template<typename iterator1,typename iterator2>
bool operator<=(const VectorIterator<iterator1> &it1,const VectorIterator<iterator2> &it2)
{
    return (it1.ptr <= it2.ptr);
};

template<typename iterator1,typename iterator2>
bool operator>(const ReverseVectorIterator<iterator1> &it1,const ReverseVectorIterator<iterator2> &it2)
            {
                return (it1 < it2);
                   
            };
template<typename iterator1,typename iterator2>         
bool operator>=(const ReverseVectorIterator<iterator1> &it1,const ReverseVectorIterator<iterator2> &it2)
{
    return (it1 <= it2);
};

template<typename iterator1,typename iterator2>
bool operator<(const ReverseVectorIterator<iterator1> &it1,const ReverseVectorIterator<iterator2> &it2)
{
    return (it1 > it2);
};

template<typename iterator1,typename iterator2>
bool operator<=(const ReverseVectorIterator<iterator1> &it1,const ReverseVectorIterator<iterator2> &it2)
{
    return (it1 >= it2);
};

template<typename iterator1,typename iterator2>
bool operator==(const VectorIterator<iterator1> &it1,const VectorIterator<iterator2> &it2)
{
    return (it1.ptr == it2.ptr);
};

template<typename iterator1,typename iterator2>
bool operator!=(const VectorIterator<iterator1> &it1,const VectorIterator<iterator2> &it2)
{
    return (it1.ptr != it2.ptr);
};

}
#endif