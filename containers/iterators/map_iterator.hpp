/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 18:28:03 by mel-amma          #+#    #+#             */
/*   Updated: 2023/01/16 15:05:49 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//make it bidirectional
#ifndef _my_map_iterator
#define _my_map_iterator
#include <memory>
#include <algorithm>
#include <iterator>
#include <map>
#include "../utils/iterator_traits.hpp"
#include "../iterators/reverse_iterator_.hpp"
template <class T, class Allocator>
class map;

namespace ft{
template <class data_type ,typename map_ptr, class value_compare>
    class MapIterator
{
    public :
        typedef map_ptr                                                 iterator_type;
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
        template<class Key, class T, class Compare ,
        class Allocator >
            friend class map;
        MapIterator(iterator_type node_ptr,value_compare cmp,const iterator_type *root):node_ptr(node_ptr),root_d_ptr(root)   // send in comparator too
        {
            (void) cmp;
        };

        //>>>>>friends
        template <typename v_type,typename map_ptrX, class value_compareX>
            friend class MapIterator;
        template <typename rit>
            friend class reverse_iterator;
        // template <typename ss>
        //     friend class MapIterator;
    
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
        MapIterator(){};

        template <class v_type,typename s,class v>
        MapIterator(const MapIterator<v_type,s,v> &other) {
            this->node_ptr = other.base();
            this->root_d_ptr = other.root_base();
        };

        template <class v_type,typename s,class v>
        MapIterator<data_type,map_ptr,value_compare>& operator=(const MapIterator<v_type,s,v> &other)
        {
            this->node_ptr = other.base();
            this->root_d_ptr = other.root_base();
            return *this;
        };
        ~MapIterator(){};

        //increments
            MapIterator<data_type,map_ptr,value_compare>& operator++()//++x
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
            MapIterator<data_type,map_ptr,value_compare> operator++(int)//x++
            {
                MapIterator<data_type, map_ptr,value_compare> temp = *this;
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
            MapIterator<data_type,map_ptr,value_compare>& operator--()
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

            MapIterator<data_type, map_ptr,value_compare> operator--(int)
            {
                MapIterator<data_type,map_ptr,value_compare> temp = *this;
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

          
            // MapIterator<map_ptr> operator+(int a) const
            // {
            //     MapIterator<map_ptr>  temp;
            //     temp.node_ptr = node_ptr + a;
            //     return temp;
            // };
            // template <class iter>
            // friend MapIterator<iter> operator+(int a, const MapIterator<iter>& map);
            // MapIterator<map_ptr> operator-(int a)const
            // {
            //     MapIterator<map_ptr>  temp;
            //     temp.node_ptr = node_ptr - a;
            //     return temp;
            // };

            // difference_type operator-(MapIterator<map_ptr> other)const
            // {
            //     difference_type a;
                
            //     a = node_ptr - other.node_ptr;
            //     return a;
            // };

           
            // MapIterator& operator+=(int amount)
            // {
            //     node_ptr = node_ptr + amount;
            //     return *this;
            // };
            // MapIterator& operator-=(int amount)
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
             template <class v_type1, typename iterator1, class cmp1, class v_type2, typename iterator2, class cmp2>
            friend bool operator==(const MapIterator<v_type1, iterator1, cmp1> &it1, const MapIterator<v_type2,iterator2, cmp2> &it2);
            
            template <class v_type1 ,typename iterator1, class cmp1, class v_type2,typename iterator2, class cmp2>
            friend bool operator!=(const MapIterator<v_type1,iterator1, cmp1> &it1, const MapIterator<v_type2, iterator2, cmp2> &it2);

            // template <typename iterator1, typename iterator2>
            // friend bool operator>(const MapIterator<iterator1> &it1, const MapIterator<iterator2> &it2);

            // template <typename iterator1, typename iterator2>
            // friend bool operator>=(const MapIterator<iterator1> &it1, const MapIterator<iterator2> &it2);

            // template <typename iterator1, typename iterator2>
            // friend bool operator<(const MapIterator<iterator1> &it1, const MapIterator<iterator2> &it2);

            // template <typename iterator1, typename iterator2>
            // friend bool operator<=(const MapIterator<iterator1> &it1, const MapIterator<iterator2> &it2);
    };





template <class v_type,class map_ptr, class value_compare>
MapIterator<v_type, map_ptr,value_compare> operator+(int a, const MapIterator<v_type,map_ptr,value_compare>& iter)
{
    MapIterator<v_type,map_ptr,value_compare>  temp1;
    temp1 = iter.operator+(a);
    return (temp1);
};




//comparisons




template<class v_type1, typename iterator1, class cmp1, class v_type2,typename iterator2, class cmp2>
bool operator==(const MapIterator<v_type1,iterator1,cmp1> &it1,const MapIterator<v_type2,iterator2,cmp2> &it2)
{
    return (it1.node_ptr == it2.node_ptr);
};

template<class v_type1, typename iterator1, class cmp1, class v_type2, typename iterator2, class cmp2>
bool operator!=(const MapIterator<v_type1,iterator1, cmp1> &it1,const MapIterator<v_type2,iterator2, cmp2> &it2)
{
    return (it1.node_ptr != it2.node_ptr);
};

}
#endif