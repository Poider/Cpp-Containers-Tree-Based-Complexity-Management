/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 12:49:07 by mel-amma          #+#    #+#             */
/*   Updated: 2022/11/23 15:17:05 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _my_vector
#define _my_vector
#include <memory>
#include <algorithm>
#include <iterator>
#include "iterator_traits.hpp"
#include "vector_iterators.hpp"
// #include <cstdlib>
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "compare.hpp"
namespace ft{


template <class T, class Allocator = std::allocator<T> >
class vector
{

public:
    typedef T                                        value_type;//
    typedef Allocator                                allocator_type;//
    typedef typename allocator_type::reference       reference;//value_type&
    typedef typename allocator_type::const_reference const_reference;//const value_type&
    typedef typename allocator_type::size_type       size_type;//std::size_t  
    typedef typename allocator_type::difference_type difference_type;// usually std::ptrdiff_t
    typedef typename allocator_type::pointer         pointer;//Allocator::pointer 
    typedef typename allocator_type::const_pointer   const_pointer;//Allocator::const_pointer 
    typedef VectorIterator<pointer>                 iterator;//LegacyRandomAccessIterator and LegacyContiguousIterator to value_type 
    typedef VectorIterator<const_pointer>                    const_iterator; //LegacyRandomAccessIterator and LegacyContiguousIterator to const value_type 
    typedef  ReverseVectorIterator<iterator>         reverse_iterator;//std::reverse_iterator<iterator>
    typedef  ReverseVectorIterator<const_iterator>   const_reverse_iterator;//	std::reverse_iterator<const_iterator>


    // >>>>> member funcs 
    vector()
    {
        // container = nullptr;
        _size = 0;
        _capacity = 0;
    };

    explicit vector(const Allocator &alloc)
    {
        this->alloc = alloc;
        // container = nullptr;
        _size = 0;
        _capacity = 0;
    };
    

    explicit vector(size_type count,
                    const T &value = T(),
                    const Allocator &alloc = Allocator())
                    {
                        this->alloc = alloc;
                        _size = 0;
                        _capacity = 0;
                        if(count <= 0)
                        return;
                        if(count < max_size())
                        {
                            _size = count;
                            _capacity = count;
                            container = this->alloc.allocate(count);
                            for(size_type i = 0; i < count; i++)
                                this->alloc.construct(container + i, value);
                        }
                        else throw std::length_error("Length exception");
                    };

    template <class InputIt>
    vector(InputIt first, InputIt last,
           const Allocator &alloc = Allocator(), typename std::enable_if<!std::is_integral< InputIt >::value,InputIt >::type* = nullptr)
           {
                // size_type s = (size_type)std::distance(first,last);
                this->alloc= alloc;
                _size = 0;
                _capacity = 0;
                while(first != last)
                {
                    push_back(*first);
                    first++;
                }
                // if(s <= 0)
                //     return;
                // if(s < max_size())
                // {
                //     container = this->alloc.allocate(s);
                //     for(size_type i = 0; i < s; i++)
                //     {
                //         this->alloc.construct(container + i, *first);
                //         first++;
                //     }
                //     _size = s;
                //     _capacity = s;
                // }
                // else throw std::length_error("Length exception");
           };

    vector(const vector &other)
    {
        _size = other._size;
        _capacity = other._capacity;
        if(_capacity)
        {
            container = alloc.allocate(_capacity);
            for(size_type i = 0; i < _capacity; i++)
            {
                alloc.construct(container + i,other.container[i]);
            }
        }
    };

    ~vector()
    {
        if(_capacity)
        {
            for(size_type i = 0; i < _size; i++)
                alloc.destroy(container + i);
            alloc.deallocate(container, _capacity);
        }
    };

    vector& operator=( const vector& other )
    {
        if(_capacity)
        {
            for(size_type i = 0; i < _size; i++)
                alloc.destroy(container + i);
            alloc.deallocate(container, _capacity);
        }
        _size = other._size;
        _capacity = other._capacity;
        container = alloc.allocate(_capacity);
        for(size_type i = 0; i < _capacity; i++)
        {
            container[i] = other.container[i];
        }
        return *this;
    };

    void assign( size_type count, const T& value )
    {
        
        if(count < 0)
            throw std::length_error("vector");

        for(size_type i = 0; i < _size; i++)
            alloc.destroy(container + i);
        _size = 0;

        if(count > _capacity)
        {
            alloc.deallocate(container, _capacity);
            container = alloc.allocate(count);
            _capacity = count;
        }
        _size = count;
        for(size_type i = 0; i < _size; i++)
            alloc.construct(&container[i],value);
    };

    template <class InputIt >
    void assign(InputIt first,typename std::enable_if<!std::is_integral< InputIt >::value,InputIt >::type last)
    {
        size_type count = std::distance(first,last);
        if(count < 0)
            throw std::length_error("vector");

        for(size_type i = 0; i < _size; i++)
            alloc.destroy(container + i);
        _size = 0;
        
        if(count > _capacity)
        {
            alloc.deallocate(container, _capacity);
            container = alloc.allocate(count);
            _capacity = count;
        }
        
        _size = count;
        for(size_type i = 0; i < _size; i++)
        {
            alloc.construct(&container[i],*first);
            first++;
        }
    };

    allocator_type get_allocator() const
    {
        return alloc;
    };
    
    // >>>>> element access
    reference at( size_type pos )
    {
        if(pos >= _size)
            throw std::out_of_range("vector");
        return container[pos];
    };
    const_reference at( size_type pos ) const
    {
        if(pos >= _size)
            throw std::out_of_range("vector");;
        return container[pos];
    };
    reference operator[]( size_type pos )
    {
        return container[pos];
    };
    const_reference operator[]( size_type pos ) const
    {
        return container[pos];
    };
    reference front()
    {
        return container[0];
    };
    const_reference front() const
    {
        return container[0];
    };

    reference back()
    {
        return container[_size - 1];
    };
    const_reference back() const
    {
        return container[_size - 1];
    };
    T* data()
    {
        if(_size)
            return 0;
        return container;
    };
    const T* data() const
    {
        if(_size)
            return 0;
        return container;
    };


    // >>>>> iterators
    iterator begin()
    {
        iterator it = iterator(container);
        return it;
    };
    const_iterator begin() const
    {
        const_iterator it = const_iterator(container);
        return it;
    };
    iterator end()
    {
        iterator it = iterator(container + _size);
        return it;
    };
    const_iterator end() const
    {
        iterator it = iterator(container + _size);
        return it;
    };
    reverse_iterator rbegin()
    {
        reverse_iterator it = reverse_iterator(container + _size);
        return it;
    };
    const_reverse_iterator rbegin() const
    {
        reverse_iterator it = reverse_iterator(container + _size);
        return it;
    };
    reverse_iterator rend()
    {
        reverse_iterator it = reverse_iterator(container);
        return it;
    };
    const_reverse_iterator rend() const
    {
        reverse_iterator it = reverse_iterator(container);
        return it;
    };

    // >>>>> capacity
    bool empty() const
    {
        if(_size == 0)
            return true;
        return false;
    };

    size_type size() const
    {
        return _size;
    };

    size_type max_size() const
    {
        return (alloc.max_size());
    };

    void reserve( size_type new_cap )
    {
        if(new_cap > max_size())
            throw std::length_error("vector");
        if(_capacity < new_cap)
        {
            size_type temp_capacity = _capacity;
            _capacity = new_cap;
            T *temp_container = container;
            container = alloc.allocate(_capacity);
            for (size_type i = 0; i < _size; i++)
                alloc.construct(container + i, temp_container[i]);
            if (temp_capacity)
            {
                for (size_type i = 0; i < _size; i++)
                    alloc.destroy(temp_container + i);
                alloc.deallocate(temp_container, temp_capacity);
            }
        }
    
    };
    size_type capacity() const
    {
        return _capacity;
    };

    // >>>>> modifiers
    void clear()
    {
        for (size_type i = 0; i < _size; i++)
        {
            alloc.destroy(container + i);
        }
        if(_capacity)
        alloc.deallocate(container, _capacity);
        _size = 0;
        if(_capacity)
        alloc.allocate(_capacity);
    };

    iterator insert(const_iterator pos, const T &value)
    {
        const_iterator first = begin();
        size_type position = std::distance(first,pos);
    
        //iterator pos should be above size or return exception
        if(pos > end() || pos < begin())
            return (iterator(container + position));

        
       
        
        //reallocate if capacity < (new size) oldsize + (1 or count);
       
        if(_size + 1 > _capacity)
            double_up(_capacity * 2);
        _size++;
        alloc.construct(container + _size - 1, container[_size - 2]); 
        for(size_type i = _size - 1; i > position; i--)
            container[i] = container[i - 1];
            
        container[position] = value;
        return(iterator(container + position));
    };// while() double_up(); if theres a range of stuff added

    iterator insert(const_iterator pos, size_type count, const T &value)
    {
            const_iterator beg = begin();
            size_type position = std::distance(beg, pos);
            iterator _pos = iterator(container + position);
            

            //iterator pos should be above size or return exception
            if(pos > end() || pos < begin())
                throw std::overflow_error("Container overflow");
            if(count + _size > max_size())
                throw std::length_error("length exception");
            if(count <= 0)
                return iterator(container + position);
            //reallocate if capacity < (new size) oldsize + (1 or count);
            while(_size + count > _capacity)
                double_up(_capacity * 2);

            for(size_type i = 0; i < count ; i++)
                alloc.construct(container + _size + i, value);
            _size = _size + count;
            
            for(size_type i = _size  ; i  > position + count; i--)
                container[i - 1] = container[i - count - 1];

            //construct it in each position
            for(size_type i = 0; i < count; i++)
            {
                container[position + i] =  value;
            }
            return(iterator(container + position));
    };

        template <class InputIt>
        iterator insert(const_iterator pos, InputIt first, InputIt last, typename ft::enable_if<std::__is_input_iterator<InputIt>::value &&
                                 !std::__is_forward_iterator<InputIt>::value ,
                                 InputIt>::type* = nullptr)
        {
            const_iterator beg = begin();
            size_type position = std::distance(beg, pos);
            iterator _pos = iterator(container + position);

            //iterator pos should be above size or return exception
            if(pos > end() || pos < begin())
                throw std::overflow_error("Container overflow");
            //reallocate if capacity < (new size) oldsize + (1 or count);

            while(first != last)
            {
                if(_size + 1 > _capacity)
                    double_up(_capacity * 2);
                _size++;
                alloc.construct(container + _size - 1, *first);
                
                
                for(size_type i = _size  ; i  > position + 1; i--)
                    container[i - 1] = container[i - 2];
              
                container[position] =  *first;
                  
                position++;
                first++;
            }
            return(iterator(container + position));
        };



    template <class InputIt>
        iterator insert(const_iterator pos, InputIt first, typename std::enable_if<!std::is_integral< InputIt >::value,InputIt >::type last)
        {
            //if(is_input_it) do smth else
            const_iterator beg = begin();
            size_type position = std::distance(beg, pos);
            iterator _pos = iterator(container + position);
            size_type count = std::distance(first, last);

            //iterator pos should be above size or return exception
            if(pos > end() || pos < begin())
                throw std::overflow_error("Container overflow");
            if(count <= 0)
                return iterator(container + position);
            //reallocate if capacity < (new size) oldsize + (1 or count);
            while(_size + count > _capacity)
                double_up(_capacity * 2);

            for(size_type i = 0; i < count ; i++)
                alloc.construct(container + _size + i, *first);
            _size = _size + count;
            
            for(size_type i = _size  ; i  > position + count; i--)
                container[i - 1] = container[i - count - 1];

            //construct it in each position
            for(size_type i = 0; first != last; i++)
            {
                container[position + i] =  *first;
                first++;
            }
            return(iterator(container + position));
        };

    iterator erase( iterator pos )
    {
        size_type position = std::distance(begin(), pos);

        if(pos < end())
        {
            for(size_type i = position; i < _size - 1; i++)
                container[i] = container[i + 1];
            _size--;
            alloc.destroy(container + _size);
            return iterator(container + position);
        }
        else
            throw std::overflow_error("container overflow");
    };

    iterator erase( iterator first, iterator last )
    {
        if(first == last)
            return last;
        if(first < last)
        {
            size_type first_pos = std::distance(begin(),first);
            size_type second_pos = std::distance(begin(),last);
            size_type count = second_pos - first_pos;
            // std::cout << first_pos << " . "<< second_pos << std::endl;
            for(size_type i = first_pos; count + i < _size; i++)
                container[i] = container[count + i];
       
            for(size_type i = _size ;  i > _size - count; i--)
            {//hard to undestand bug when you put i = size - 1  and container + i/instead of container + i -1
                alloc.destroy(container + i - 1);
            }
            _size -= count;
            return first;
        }
        else
            throw std::overflow_error("container overflow");
    };
    void push_back( const T& value )
    {
        if(_size + 1 > _capacity)
            double_up(_capacity * 2);
        _size++;
        alloc.construct(container + _size - 1, value);
       
    };
    
    void pop_back()
    {
        alloc.destroy(&container[_size - 1]);
        _size--;
    };

    void resize( size_type count, T value = T() )
    {
        //if count < 0
        
        if(count <= _size)
        {
            for(size_type i = count; i < _size; i++)
            {
                alloc.destroy(container + i);  
            }
            _size = count;
        }
        else
        {
            while(count > _capacity)
                double_up(_capacity * 2);
            for(size_type i = _size; i < _size + count; i++)
            {
                alloc.construct(&container[i], value);
            }
            _size += count;
        }
    };
    void swap( vector& other )
    {
        T *temp = container;
        size_type temp_cap = _capacity;
        size_type temp_size = _size;

        container = other.container;
        _capacity = other._capacity;
        _size = other._size;

        other.container = temp;
        other._capacity = temp_cap;
        other._size = temp_size;
    };


    private:
    T *container;
    size_type _size;
    size_type _capacity;
    allocator_type alloc;
    // template<class inputIterator>
    // size_t _distance(inputIterator first, inputIterator second)
    // {
    //     size_t distance = 0;

    //     while(first != second)
    //     {
    //         if(distance > alloc.max_size())
    //             throw std::out_of_range(""
    //     } 
    // }

    void double_up(size_type new_cap)
    {
        size_type temp_capacity = _capacity;
        _capacity = new_cap;
        T* temp_container = container;
        if(!_capacity)
            _capacity++;
        container = alloc.allocate(_capacity);
        for( size_type i = 0; i < _size; i++ )
            alloc.construct(container + i, temp_container[i]);
        if(temp_capacity)
        {
            for(size_type i = 0; i < _size; i++)
                alloc.destroy(temp_container + i);
            alloc.deallocate(temp_container, temp_capacity);
        }
    };

};




 template< class T1, class Alloc >
        bool operator==( const ft::vector<T1,Alloc>& lhs,
                    const ft::vector<T1,Alloc>& rhs )
                    {
                        if( lhs.size() != rhs.size() )
                            return false;
                        for( size_t i = 0; i < lhs.size(); i++ )
                            if(lhs[i] != rhs[i])
                                return false;
                        return true;
                    };
    template< class T1, class Alloc >
        bool operator!=( const ft::vector<T1,Alloc>& lhs,
                    const ft::vector<T1,Alloc>& rhs )
                    {
                        return (!(lhs == rhs));
                    };

    template< class T1, class Alloc >
        bool operator<( const ft::vector<T1,Alloc>& lhs,
                    const ft::vector<T1,Alloc>& rhs )
                    {
                        return (ft::lexicographical_compare(lhs.begin(),lhs.end(),rhs.begin(),rhs.end()));
                    };

    template< class T1, class Alloc >
        bool operator>( const ft::vector<T1,Alloc>& lhs,
                    const ft::vector<T1,Alloc>& rhs )
                    {
                        return (rhs < lhs);
                    };

    template< class T1, class Alloc >
        bool operator<=( const ft::vector<T1,Alloc>& lhs,
                    const ft::vector<T1,Alloc>& rhs )
                    {
                        return (!(lhs > rhs));
                    };
                    
    template< class T1, class Alloc >
        bool operator>=( const ft::vector<T1,Alloc>& lhs,
                    const ft::vector<T1,Alloc>& rhs )
                    {
                        return (!(lhs < rhs));
                    };

    template< class T1, class Alloc >
            void swap( ft::vector<T1,Alloc>& lhs,
                ft::vector<T1,Alloc>& rhs )
                {
                    lhs.swap(rhs);
                };
/*
lexicographical comparison:
Two ranges are compared element by element.
The first mismatching element de
es which range is lexicographically less or greater than the other.
If one range is a prefix of another, the shorter range is lexicographically less than the other.
If two ranges have equivalent elements and are of the same length, then the ranges are lexicographically equal.
An empty range is lexicographically less than any non-empty range.
Two empty ranges are lexicographically equal.*/
};
#endif