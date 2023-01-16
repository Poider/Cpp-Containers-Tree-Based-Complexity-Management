/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 18:27:56 by mel-amma          #+#    #+#             */
/*   Updated: 2023/01/16 15:05:49 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//make it bidirectional
#ifndef _my_set_iterator
#define _my_set_iterator
#include <memory>
#include <algorithm>
#include <iterator>
#include "../utils/iterator_traits.hpp"
#include "../iterators/reverse_iterator_.hpp"
template <class T, class Allocator>
class set;

namespace ft{
template <class data_type ,typename set_ptr>
    class setIterator
{
    public :
        typedef set_ptr                                                 iterator_type;
        typedef typename iterator_traits<data_type*, std::bidirectional_iterator_tag>::value_type           value_type;
        typedef typename iterator_traits<data_type*, std::bidirectional_iterator_tag>::difference_type      difference_type;
        typedef typename std::size_t                                size_type;
        typedef typename iterator_traits<data_type*, std::bidirectional_iterator_tag>::iterator_category    iterator_category;
        typedef typename iterator_traits<data_type*, std::bidirectional_iterator_tag>::pointer                pointer;
        typedef const  pointer          const_pointer;
        typedef typename iterator_traits<data_type*, std::bidirectional_iterator_tag>::reference              reference;
        typedef const  reference          const_reference;
    private :
        iterator_type node_ptr;
        const iterator_type* root_d_ptr;
        template<class Key,class Compare ,
        class Allocator >
            friend class set;
        setIterator(iterator_type node_ptr,const iterator_type *root):node_ptr(node_ptr),root_d_ptr(root)   // send in comparator too
        {
        };

        //>>>>>friends
        template <typename v_type,typename set_ptrX>
            friend class setIterator;
        template <typename rit>
            friend class reverse_iterator;
        // template <typename ss>
        //     friend class setIterator;
    
        const iterator_type* root_base() const
        {
            return root_d_ptr;
        };
    public :
        iterator_type base() const
        {
            return node_ptr;
        };
        //default constructible only from forward iterator and ahead
        setIterator(){};

        template <class v_type,typename s>
        setIterator(const setIterator<v_type,s> &other) {
            this->node_ptr = other.base();
            this->root_d_ptr = other.root_base();
        };

        template <class v_type,typename s>
        setIterator<data_type,set_ptr>& operator=(const setIterator<v_type,s> &other)
        {
            this->node_ptr = other.base();
            this->root_d_ptr = other.root_base();
            return *this;
        };
        ~setIterator(){};

        //increments
            setIterator<data_type,set_ptr>& operator++()//++x
            {
                if(node_ptr == nullptr)
                {
                    node_ptr = *root_d_ptr;
                    while(node_ptr->left)
                        node_ptr = node_ptr->left;
                }
                else
                {
                    if (node_ptr->right) 
                    {
                        node_ptr = node_ptr->right;
                        while (node_ptr->left)
                            node_ptr = node_ptr->left;
                    }
                    else
                    {
                        while (node_ptr->parent && node_ptr->parent->right == node_ptr)
                            node_ptr = node_ptr->parent;
                        node_ptr = node_ptr->parent;
                    }
                }
                return *this;
            };
            setIterator<data_type,set_ptr> operator++(int)//x++
            {
                setIterator<data_type, set_ptr> temp = *this;
                if(node_ptr == nullptr)
                {
                    node_ptr = *root_d_ptr;
                    while(node_ptr->left)
                        node_ptr = node_ptr->left;
                }
                else
                {
                    if (node_ptr->right) 
                    {
                        node_ptr = node_ptr->right;
                        while (node_ptr->left)
                            node_ptr = node_ptr->left;
                    }
                    else
                    {
                        while (node_ptr->parent && node_ptr->parent->right == node_ptr)
                            node_ptr = node_ptr->parent;
                        node_ptr = node_ptr->parent;
                    }
                }
                return temp;
            };
            setIterator<data_type,set_ptr>& operator--()
            {
                if(node_ptr == nullptr)
                {
                    node_ptr = *root_d_ptr;
                    while(node_ptr->right)
                        node_ptr = node_ptr->right;
                }
                else
                {
                    if (node_ptr->left) 
                    {
                        node_ptr = node_ptr->left;
                        while (node_ptr->right)
                            node_ptr = node_ptr->right;
                    }
                    else
                    {
                        while (node_ptr->parent && node_ptr->parent->left == node_ptr)
                            node_ptr = node_ptr->parent;
                        node_ptr = node_ptr->parent;
                    }
                }
                return *this;
            };

            setIterator<data_type, set_ptr> operator--(int)
            {
                setIterator<data_type,set_ptr> temp = *this;
                if(node_ptr == nullptr)
                {
                    node_ptr = *root_d_ptr;
                    while(node_ptr->right)
                        node_ptr = node_ptr->right;
                }
                else
                {
                    if (node_ptr->left) 
                    {
                        node_ptr = node_ptr->left;
                        while (node_ptr->right)
                            node_ptr = node_ptr->right;
                    }
                    else
                    {
                        while (node_ptr->parent && node_ptr->parent->left == node_ptr)
                            node_ptr = node_ptr->parent;
                        node_ptr = node_ptr->parent;
                    }
                }
                return (temp);
            };

          
            // setIterator<set_ptr> operator+(int a) const
            // {
            //     setIterator<set_ptr>  temp;
            //     temp.node_ptr = node_ptr + a;
            //     return temp;
            // };
            // template <class iter>
            // friend setIterator<iter> operator+(int a, const setIterator<iter>& set);
            // setIterator<set_ptr> operator-(int a)const
            // {
            //     setIterator<set_ptr>  temp;
            //     temp.node_ptr = node_ptr - a;
            //     return temp;
            // };

            // difference_type operator-(setIterator<set_ptr> other)const
            // {
            //     difference_type a;
                
            //     a = node_ptr - other.node_ptr;
            //     return a;
            // };

           
            // setIterator& operator+=(int amount)
            // {
            //     node_ptr = node_ptr + amount;
            //     return *this;
            // };
            // setIterator& operator-=(int amount)
            // {
            //     node_ptr = node_ptr - amount;
            //     return *this;
            // };
            
            /*
            //operator * -> const op const for lvalue
            //operator * -> not const for rvalue
            */
            const_pointer operator->() const
            {
                return node_ptr->data;
            };
            const_reference operator*() const
            {
                return *(node_ptr->data);
            };
            pointer operator->()
            {
                return node_ptr->data;
            };
            reference operator*()
            {
                return *(node_ptr->data);
            };

            /**
             * @explanation
             * 
             [] is the node_ptr + number * hops
             op [] const op const // for read only in const objs
             op [] not const for writing
            */
            // reference operator[](int index)
            // {
            //     return *(node_ptr + index);
            // };
            // const_reference operator[](int index)const
            // {
            //     return *(node_ptr + index);
            // };

        // multipass?
             template <class v_type1, typename iterator1,  class v_type2, typename iterator2>
            friend bool operator==(const setIterator<v_type1, iterator1> &it1, const setIterator<v_type2,iterator2> &it2);
            
            template <class v_type1 ,typename iterator1, class v_type2,typename iterator2>
            friend bool operator!=(const setIterator<v_type1,iterator1> &it1, const setIterator<v_type2, iterator2> &it2);

            // template <typename iterator1, typename iterator2>
            // friend bool operator>(const setIterator<iterator1> &it1, const setIterator<iterator2> &it2);

            // template <typename iterator1, typename iterator2>
            // friend bool operator>=(const setIterator<iterator1> &it1, const setIterator<iterator2> &it2);

            // template <typename iterator1, typename iterator2>
            // friend bool operator<(const setIterator<iterator1> &it1, const setIterator<iterator2> &it2);

            // template <typename iterator1, typename iterator2>
            // friend bool operator<=(const setIterator<iterator1> &it1, const setIterator<iterator2> &it2);
    };





template <class v_type,class set_ptr>
setIterator<v_type, set_ptr> operator+(int a, const setIterator<v_type,set_ptr>& iter)
{
    setIterator<v_type,set_ptr>  temp1;
    temp1 = iter.operator+(a);
    return (temp1);
};




//comparisons




template<class v_type1, typename iterator1, class v_type2,typename iterator2>
bool operator==(const setIterator<v_type1,iterator1> &it1,const setIterator<v_type2,iterator2> &it2)
{
    return (it1.node_ptr == it2.node_ptr);
};

template<class v_type1, typename iterator1,  class v_type2, typename iterator2>
bool operator!=(const setIterator<v_type1,iterator1> &it1,const setIterator<v_type2,iterator2> &it2)
{
    return (it1.node_ptr != it2.node_ptr);
};

}
#endif