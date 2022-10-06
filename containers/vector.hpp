#ifndef _my_vector
#define _my_vector

#include <memory>
#include <algorithm>
// #include <cstdlib>
namespace ft{
template <class T, class Allocator>
class vector;

template <typename vec>
    class ReverseVectorIterator
{
    public :
        typedef typename vec::value_type                 value_type;
        typedef typename std::ptrdiff_t                     difference_type;
        typedef typename vec::size_type                    size_type;
        typedef typename std::random_access_iterator_tag    iterator_category;
        typedef typename vec::value_type*                pointer;
        typedef const typename vec::value_type*          const_pointer;
        typedef typename vec::value_type&                reference;
        typedef const typename vec::value_type&          const_reference;
    private :
        pointer ptr;
        template <class T1, class Allocator1>
           friend class vector;
        ReverseVectorIterator(pointer ptr):ptr(ptr) 
        {};
    public :
        //default constructible only from forward iterator and ahead
        ReverseVectorIterator(){};
        ReverseVectorIterator(const ReverseVectorIterator<vec> &other): ptr(other.ptr) {};
        ReverseVectorIterator<vec>& operator=(const ReverseVectorIterator<vec> &other)
        {
            ptr = other.ptr;
            return *this;
        };
        ~ReverseVectorIterator(){};

        //increments
            ReverseVectorIterator<vec>& operator++()//++x
            {
                ptr--;
                return *this;
            };
            ReverseVectorIterator<vec> operator++(int)//x++
            {
                ReverseVectorIterator<vec> temp = *this;
                ptr--;
                return temp;
            };
            ReverseVectorIterator<vec>& operator--()
            {
                ptr++;
                return *this;
            };
            ReverseVectorIterator<vec>& operator--(int)
            {
                ReverseVectorIterator<vec> temp = *this;
                ptr++;
                return temp;
            };

            bool operator==(const ReverseVectorIterator<vec> &other)const
            {
                return(ptr == other.ptr);
            };
            bool operator!=(const ReverseVectorIterator<vec> &other)const
            {
                return(ptr != other.ptr);
            };
            ReverseVectorIterator<vec> operator+(int a)
            {
                ReverseVectorIterator<vec>  temp;
                temp.ptr = ptr - a;
                return temp;
            };
            friend ReverseVectorIterator<vec> operator+(int a, const ReverseVectorIterator<vec>& vector);
            ReverseVectorIterator<vec> operator-(int a)
            {
                ReverseVectorIterator<vec>  temp;
                temp.ptr = ptr + a;
                return temp;
            };

            difference_type operator-(ReverseVectorIterator<vec> other)
            {
                difference_type a;
                
                a = other.ptr - ptr;
                return a;
            };

            bool operator>(ReverseVectorIterator<vec> other) const
            {
                return (ptr < other.ptr);
            };
            bool operator>=(ReverseVectorIterator<vec> other) const
            {
                return (ptr <= other.ptr);
            };
            bool operator<(ReverseVectorIterator<vec> other) const
            {
                return (ptr > other.ptr);
            };
            bool operator<=(ReverseVectorIterator<vec> other) const
            {
                return (ptr >= other.ptr);
            };
            ReverseVectorIterator& operator+=(int amount)
            {
                ptr = ptr - amount;
                return *this;
            };
            ReverseVectorIterator& operator-=(int amount)
            {
                ptr = ptr + amount;
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
                return *(ptr - index);
            };
            const_reference operator[](int index)const
            {
                return *(ptr - index);
            };

        // multipass?
    };



template <typename vec>
    class VectorIterator
{
    public :
        typedef typename vec::value_type                 value_type;
        typedef typename std::ptrdiff_t                     difference_type;
        typedef typename vec::size_type                    size_type;
        typedef typename std::random_access_iterator_tag    iterator_category;
        typedef typename vec::value_type*                pointer;
        typedef const typename vec::value_type*          const_pointer;
        typedef typename vec::value_type&                reference;
        typedef const typename vec::value_type&          const_reference;
    private :
        pointer ptr;
        template <class T1, class Allocator1>
           friend class vector;
        VectorIterator(pointer ptr):ptr(ptr) 
        {};
    public :
        //default constructible only from forward iterator and ahead
        VectorIterator(){};
        VectorIterator(const VectorIterator<vec> &other): ptr(other.ptr) {};
        VectorIterator<vec>& operator=(const VectorIterator<vec> &other)
        {
            ptr = other.ptr;
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
            VectorIterator<vec>& operator--(int)
            {
                VectorIterator<vec> temp = *this;
                ptr--;
                return temp;
            };

            bool operator==(const VectorIterator<vec> &other)const
            {
                return(ptr == other.ptr);
            };
            bool operator!=(const VectorIterator<vec> &other)const
            {
                return(ptr != other.ptr);
            };
            VectorIterator<vec> operator+(int a)
            {
                VectorIterator<vec>  temp;
                temp.ptr = ptr + a;
                return temp;
            };
            friend VectorIterator<vec> operator+(int a, const VectorIterator<vec>& vector);
            VectorIterator<vec> operator-(int a)
            {
                VectorIterator<vec>  temp;
                temp.ptr = ptr - a;
                return temp;
            };

            difference_type operator-(VectorIterator<vec> other)
            {
                difference_type a;
                
                a = ptr - other.ptr;
                return a;
            };

            bool operator>(VectorIterator<vec> other) const
            {
                return (ptr > other.ptr);
            };
            bool operator>=(VectorIterator<vec> other) const
            {
                return (ptr >= other.ptr);
            };
            bool operator<(VectorIterator<vec> other) const
            {
                return (ptr < other.ptr);
            };
            bool operator<=(VectorIterator<vec> other) const
            {
                return (ptr <= other.ptr);
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
    };



template <class T, class Allocator = std::allocator<T> >
class vector
{

public:
    typedef T                                        value_type;//
    typedef Allocator                                allocator_type;//
    typedef typename allocator_type::reference       reference;//value_type&
    typedef typename allocator_type::const_reference const_reference;//const value_type&
    typedef VectorIterator<vector>                 iterator;//LegacyRandomAccessIterator and LegacyContiguousIterator to value_type 
    typedef const VectorIterator<vector>                    const_iterator; //LegacyRandomAccessIterator and LegacyContiguousIterator to const value_type 
    typedef typename allocator_type::size_type       size_type;//std::size_t  
    typedef typename allocator_type::difference_type difference_type;// usually std::ptrdiff_t
    typedef typename allocator_type::pointer         pointer;//Allocator::pointer 
    typedef typename allocator_type::const_pointer   const_pointer;//Allocator::const_pointer 
    typedef  ReverseVectorIterator<vector>         reverse_iterator;//std::reverse_iterator<iterator>
    typedef const ReverseVectorIterator<vector>   const_reverse_iterator;//	std::reverse_iterator<const_iterator>


    
    // >>>>> member funcs 
    vector()
    {
        allocator_type my_alloc;
        container = my_alloc.allocate(0);
        _size = 0;
        _capacity = 0;
    };

    explicit vector(const Allocator &alloc)
    {
        container = alloc.allocate(0);
        _size = 0;
        _capacity = 0;
    };

    explicit vector(size_type count,
                    const T &value = T(),
                    const Allocator &alloc = Allocator())
                    {
                        _size = count;
                        _capacity = count;
                        container = alloc.allocate(count);
                        for(size_type i = 0; i < count; ++i)
                            alloc.construct(container + i, value);
                    };

    template <class InputIt>
    vector(InputIt first, InputIt last,
           const Allocator &alloc = Allocator())
           {
                size_type s = std::distance(first,last);
                container = alloc.allocate(s);
                for(size_type i = 0; i < s; ++i)
                {
                    container[i] = *first;
                    first++;
                }
           };

    vector(const vector &other)
    {
        allocator_type alloc;
        _size = other._size;
        _capacity = other._capacity;
        container = alloc.allocate(_capacity);
        for(size_type i = 0; i < _capacity; ++i)
        {
            container[i] = other._container[i];
        }
    };

    ~vector()
    {
        allocator_type alloc;
        if(_capacity)
        {
            for(size_type i = 0; i < _size; ++i)
                alloc.destroy(container + i);
            alloc.deallocate(container, _capacity);
        }
    };

    vector& operator=( const vector& other )
    {
        allocator_type alloc;
        if(_capacity)
        {
            for(size_type i = 0; i < _size; ++i)
                alloc.destroy(container + i);
            alloc.deallocate(container, _capacity);
        }
        _size = other._size;
        _capacity = other._capacity;
        container = alloc.allocate(_capacity);
        for(size_type i = 0; i < _capacity; ++i)
        {
            container[i] = other._container[i];
        }
    };

    void assign( size_type count, const T& value )
    {
        allocator_type alloc;
        
        if(count < 0)
            throw std::length_error("vector");

        for(size_type i = 0; i < _size; ++i)
            alloc.destroy(container + i);
        _size = 0;

        if(count > _capacity)
        {
            alloc.deallocate(container, _capacity);
            container = alloc.allocate(count);
            _capacity = count;
        }
        _size = count;
        for(size_type i = 0; i < _size; ++i)
            alloc.construct(&container[i],value);
    };

    template <class InputIt>
    void assign(InputIt first, InputIt last)
    {
        size_type count = std::distance(first,last);
        if(count < 0)
            throw std::length_error("vector");
        allocator_type alloc;

        for(size_type i = 0; i < _size; ++i)
            alloc.destroy(container + i);
        _size = 0;
        
        if(count > _capacity)
        {
            alloc.deallocate(container, _capacity);
            container = alloc.allocate(count);
            _capacity = count;
        }
        
        _size = count;
        for(size_type i = 0; i < _size; ++i)
        {
            alloc.construct(&container[i],*first);
            first++;
        }
    };

    allocator_type get_allocator() const
    {
        allocator_type alloc;
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
        iterator it = iterator(container);
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
        reverse_iterator it = reverse_iterator(container + _size - 1);
        return it;
    };
    const_reverse_iterator rbegin() const
    {
        reverse_iterator it = reverse_iterator(container + _size - 1);
        return it;
    };
    reverse_iterator rend()
    {
        reverse_iterator it = reverse_iterator(container  - 1);
        return it;
    };
    const_reverse_iterator rend() const
    {
        reverse_iterator it = reverse_iterator(container  - 1);
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
        allocator_type alloc;

        return (alloc.max_size());
    };

    void reserve( size_type new_cap )
    {
        if(new_cap > max_size())
            throw std::length_error("vector");
        if(_capacity < new_cap)
        {
            allocator_type alloc;
            size_type temp_capacity = _capacity;
            _capacity = new_cap;
            T *temp_container = container;
            container = alloc.allocate(_capacity);
            for (size_type i = 0; i < _size; ++i)
                alloc.construct(container + i, temp_container[i]);
            if (temp_capacity)
            {
                for (size_type i = 0; i < _size; ++i)
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
        allocator_type alloc;
        for (size_type i = 0; i < _size; ++i)
        {
            alloc.destroy(container + i);
        }
        alloc.deallocate(container, _capacity);
        _size = 0;
        alloc.allocate(_capacity);
    };

    iterator insert(const_iterator pos, const T &value)
    {
        allocator_type alloc;
        iterator first = begin();
        size_type position = std::distance(begin(),pos);
    
        //iterator pos should be above size or return exception
        if(pos > end() || pos < begin())
            throw std::overflow_error("Container overflow");

        _size++;
        //reallocate if capacity < (new size) oldsize + (1 or count);
        if(_size > _capacity)
            double_up(_capacity * 2);
        for(size_type i = _size; i > position; i--)
            container[i] = container[i - 1];
        alloc.construct(container + position, value); 
        return(iterator(container + position));
    };// while() double_up(); if theres a range of stuff added

    iterator insert(const_iterator pos, size_type count, const T &value)
    {
        allocator_type alloc;
        iterator first = begin();
        size_type position = std::distance(begin(), pos);
        //iterator pos should be above size or return exception
        if(pos > end() || pos < begin())
            throw std::overflow_error("Container overflow");
               
        if(count <= 0)
            return pos;
        _size = _size + count;
        //reallocate if capacity < (new size) oldsize + (1 or count);
        while(_size > _capacity)
            double_up(_capacity * 2);
        for(size_type i = _size; i > position; i--)
            container[i] = container[i - count];
        //construct it in each position
        for(size_type i = 0; i < count; i++)
            alloc.construct(container + position + i, value); 
         
        return(iterator(container + position));
    };

    // constexpr iterator insert(const_iterator pos, size_type count, const T &value);

    template <class InputIt>
        iterator insert(const_iterator pos, InputIt first, InputIt last)
        {
            allocator_type alloc;
            size_type position = std::distance(begin(), pos);
            size_type count = std::distance(first, last);
            //iterator pos should be above size or return exception
            if(pos > end() || pos < begin())
                throw std::overflow_error("Container overflow");
            if(count <= 0)
                return pos;
            _size = _size + count;
            //reallocate if capacity < (new size) oldsize + (1 or count);
            while(_size > _capacity)
                double_up(_capacity * 2);
            for(size_type i = _size; i > position; i--)
                container[i] = container[i - count];
            //construct it in each position
            for(size_type i = 0; i < count; i++)
            {
                alloc.construct(container + position + i, *first); 
                first++;
            }
            return(iterator(container + position));
        };

    iterator erase( iterator pos )
    {
        size_type position = std::distance(begin(), pos);
 
        allocator_type alloc;
        
        if(pos < end())
        {
            alloc.destroy(container + position);
            for(size_type i = position; i < _size; i++)
                container[i] = container[i + 1];
            _size--;
            return pos;
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
            allocator_type alloc;
            for(size_type i = 0; i < count; i++)
                alloc.destroy(container + first_pos + i);
            for(size_type i = 0; i < count; i++)
                container[first_pos + i] = container[first_pos + i + count];
            _size -= count;
            return first;
        }
        else
            throw std::overflow_error("container overflow");
    };
    void push_back( const T& value )
    {
        Allocator alloc;
        if(_size + 1 > _capacity)
            double_up(_capacity * 2);
        alloc.construct(container + _size, value);
        _size++;
    };
    
    void pop_back()
    {
        Allocator alloc;
        alloc.destroy(&container[_size - 1]);
        _size--;
    };

    void resize( size_type count, T value = T() )
    {
        //if count < 0
        Allocator alloc;
        
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

    // template<class inputIterator>
    // size_t _distance(inputIterator first, inputIterator second)
    // {
    //     size_t distance = 0;
    //     Allocator alloc;

    //     while(first != second)
    //     {
    //         if(distance > alloc.max_size())
    //             throw std::out_of_range(""
    //     } 
    // }

    void double_up(size_type new_cap)
    {
        Allocator alloc;
        size_type temp_capacity = _capacity;
        _capacity = new_cap;
        T* temp_container = container;
        container = alloc.allocate(_capacity);
        for( size_type i = 0; i < _size; ++i )
            alloc.construct(container + i, temp_container[i]);
        if(temp_capacity)
        {
            for(size_type i = 0; i < _size; ++i)
                alloc.destroy(temp_container + i);
            alloc.deallocate(temp_container, temp_capacity);
        }    
    };
    //  >>>>> nonmember funcs
     template< class T1, class Alloc >
    friend bool operator==( const std::vector<T1,Alloc>& lhs,
                    const std::vector<T1,Alloc>& rhs );
    template< class T1, class Alloc >
    friend bool operator!=( const std::vector<T1,Alloc>& lhs,
                    const std::vector<T1,Alloc>& rhs );
    template< class T1, class Alloc >
    friend bool operator<( const std::vector<T1,Alloc>& lhs,
                    const std::vector<T1,Alloc>& rhs );
    template< class T1, class Alloc >
    friend bool operator<=( const std::vector<T1,Alloc>& lhs,
                    const std::vector<T1,Alloc>& rhs );
    template< class T1, class Alloc >
    friend bool operator>( const std::vector<T1,Alloc>& lhs,
                    const std::vector<T1,Alloc>& rhs );
    template< class T1, class Alloc >
    friend bool operator>=( const std::vector<T1,Alloc>& lhs,
                    const std::vector<T1,Alloc>& rhs );

    template< class T1, class Alloc >
        friend void swap( std::vector<T1,Alloc>& lhs,
                std::vector<T1,Alloc>& rhs );
};


template <class vec>
VectorIterator<vec> operator+(int a, const VectorIterator<vec>& vector)
{
    VectorIterator<vec>  temp;
    temp = vector.operator+(a);
    return (temp);
};


template <class vec>
ReverseVectorIterator<vec> operator+(int a, const ReverseVectorIterator<vec>& vector)
{
    ReverseVectorIterator<vec>  temp;
    temp = vector.operator+(a);
    return (temp);
};


 template< class T1, class Alloc >
        bool operator==( const std::vector<T1,Alloc>& lhs,
                    const std::vector<T1,Alloc>& rhs )
                    {
                        if( lhs.size() != rhs.size() )
                            return false;
                        for( size_t i = 0; i < lhs.size(); ++i )
                            if(lhs.container[i] != rhs.container[i])
                                return false;
                        return true;
                    };
    template< class T1, class Alloc >
        bool operator!=( const std::vector<T1,Alloc>& lhs,
                    const std::vector<T1,Alloc>& rhs )
                    {
                        return (!(lhs == rhs));
                    };

    template< class T1, class Alloc >
        bool operator<( const std::vector<T1,Alloc>& lhs,
                    const std::vector<T1,Alloc>& rhs )
                    {
                        return (std::lexicographical_compare(lhs.begin(),lhs.end(),rhs.begin(),rhs.end()));
                    };

    template< class T1, class Alloc >
        bool operator>( const std::vector<T1,Alloc>& lhs,
                    const std::vector<T1,Alloc>& rhs )
                    {
                        return (rhs < lhs);
                    };

    template< class T1, class Alloc >
        bool operator<=( const std::vector<T1,Alloc>& lhs,
                    const std::vector<T1,Alloc>& rhs )
                    {
                        return (!(lhs > rhs));
                    };
                    
    template< class T1, class Alloc >
        bool operator>=( const std::vector<T1,Alloc>& lhs,
                    const std::vector<T1,Alloc>& rhs )
                    {
                        return (!(lhs < rhs));
                    };

    template< class T1, class Alloc >
            void swap( std::vector<T1,Alloc>& lhs,
                std::vector<T1,Alloc>& rhs )
                {
                    lhs.swap(rhs);
                };
/*
lexicographical comparison:
Two ranges are compared element by element.
The first mismatching element defines which range is lexicographically less or greater than the other.
If one range is a prefix of another, the shorter range is lexicographically less than the other.
If two ranges have equivalent elements and are of the same length, then the ranges are lexicographically equal.
An empty range is lexicographically less than any non-empty range.
Two empty ranges are lexicographically equal.*/
};
#endif