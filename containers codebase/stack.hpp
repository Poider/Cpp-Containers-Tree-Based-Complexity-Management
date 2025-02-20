/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:01:27 by mel-amma          #+#    #+#             */
/*   Updated: 2023/01/16 15:03:51 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _my_stack
#define _my_stack

#include "../containers/vector.hpp"
namespace ft {
  template<class T, class Container = ft::vector<T> >
  class stack {
  public:

    typedef Container                                container_type;
    typedef typename container_type::value_type      value_type;
    typedef typename container_type::reference       reference;
    typedef typename container_type::const_reference const_reference;
    typedef typename container_type::size_type       size_type;
 
  protected:
    Container c;//
 
  public:
  // >>>> member funcs
    explicit stack( const Container& cont = Container() )
    {
      c = cont;
    };
    stack( const stack& other )
    {
      c = other.c;
    };
    ~stack()
    {
      
    };
    stack& operator=( const stack& other )
    {
        c = other.c;
        return (*this);
    };

    //>>access elements
    reference top()
    {
        return (c.back());
    };
    const_reference top() const
    {
        return (c.back());
    };

    //>>>>>>capacity
    bool empty() const
    {
        return(c.empty());
    };

    size_type size() const
    {
        return(c.size());
    };

    
    //>>>> modifiers
    void push( const value_type& value )
    {
        return (c.push_back(value));
    };

    void pop()
    {
        return(c.pop_back());
    };


    //>>>>>> nonmemeber funcs

    template <class TX, class ContainerX>
      friend bool operator==(const ft::stack<TX, ContainerX> &lhs, const ft::stack<TX, ContainerX> &rhs);
    
    template <class TX, class ContainerX>
      friend bool operator!=(const ft::stack<TX, ContainerX> &lhs, const ft::stack<TX, ContainerX> &rhs);
    
    template <class TX, class ContainerX>
      friend bool operator<(const ft::stack<TX, ContainerX> &lhs, const ft::stack<TX, ContainerX> &rhs);
    
    template <class TX, class ContainerX>
      friend bool operator<=(const ft::stack<TX, ContainerX> &lhs, const ft::stack<TX, ContainerX> &rhs);
    
    template <class TX, class ContainerX>
      friend bool operator>(const ft::stack<TX, ContainerX> &lhs, const ft::stack<TX, ContainerX> &rhs);
    
    template <class TX, class ContainerX>
      friend bool operator>=(const ft::stack<TX, ContainerX> &lhs, const ft::stack<TX, ContainerX> &rhs);
};

template <class TX, class ContainerX>
       bool operator==(const ft::stack<TX, ContainerX> &lhs, const ft::stack<TX, ContainerX> &rhs)
      {
        return (lhs.c == rhs.c);
      };
    
    template <class TX, class ContainerX>
       bool operator!=(const ft::stack<TX, ContainerX> &lhs, const ft::stack<TX, ContainerX> &rhs)
      {
        return (lhs.c != rhs.c);

      };
    
    template <class TX, class ContainerX>
       bool operator<(const ft::stack<TX, ContainerX> &lhs, const ft::stack<TX, ContainerX> &rhs)
      {
        return (lhs.c < rhs.c);

      };
    
    template <class TX, class ContainerX>
       bool operator<=(const ft::stack<TX, ContainerX> &lhs, const ft::stack<TX, ContainerX> &rhs)
      {
        return (lhs.c <= rhs.c);
      };
    
    template <class TX, class ContainerX>
       bool operator>(const ft::stack<TX, ContainerX> &lhs, const ft::stack<TX, ContainerX> &rhs)
      {
        return (lhs.c > rhs.c);
      };
    
    template <class TX, class ContainerX>
       bool operator>=(const ft::stack<TX, ContainerX> &lhs, const ft::stack<TX, ContainerX> &rhs)
      {
        return (lhs.c >= rhs.c);
      };


}
#endif