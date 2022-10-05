#ifndef _my_vector
#define _my_vector

#include <memory>
#include <algorithm>
// #include <cstdlib>
//namespace


template <typename vector>
    class ReverseVectorIterator
{
    public :
        typedef typename vector::value_type                 value_type;
        typedef typename std::ptrdiff_t                     difference_type;
        typedef typename std::random_access_iterator_tag    iterator_category;
        typedef typename vector::value_type*                pointer;
        typedef const typename vector::value_type*          const_pointer;
        typedef typename vector::value_type&                reference;
        typedef const typename vector::value_type&          const_reference;
    private :
        pointer ptr;
        friend class vector;
        VectorIterator(pointer ptr):ptr(ptr) 
        {};
    public :
        //default constructible only from forward iterator and ahead
        ReverseVectorIterator(){};
        ReverseVectorIterator(const ReverseVectorIterator<vector> &other): ptr(other.ptr) {};
        ReverseVectorIterator<vector>& operator=(const ReverseVectorIterator<vector> &other)
        {
            ptr = other.ptr;
            return *this;
        };
        ~ReverseVectorIterator(){};

        //increments
            ReverseVectorIterator<vector>& operator++()//++x
            {
                ptr--;
                return *this;
            };
            ReverseVectorIterator<vector> operator++(int)//x++
            {
                ReverseVectorIterator<vector> temp = *this;
                ptr--;
                return temp;
            };
            ReverseVectorIterator<vector>& operator--()
            {
                ptr++;
                return *this;
            };
            ReverseVectorIterator<vector>& operator--(int)
            {
                ReverseVectorIterator<vector> temp = *this;
                ptr++;
                return temp;
            };

            bool operator==(const ReverseVectorIterator<vector> &other)const
            {
                return(ptr == other.ptr);
            };
            bool operator!=(const ReverseVectorIterator<vector> &other)const
            {
                return(ptr != other.ptr);
            };
            ReverseVectorIterator<vector> operator+(int a)
            {
                ReverseVectorIterator<vector>  temp;
                temp.ptr = ptr - a;
                return temp;
            };
            friend ReverseVectorIterator<vector> operator+(int a, const ReverseVectorIterator<vector>& vec);
            ReverseVectorIterator<vector> operator-(int a)
            {
                ReverseVectorIterator<vector>  temp;
                temp.ptr = ptr + a;
                return temp;
            };

            difference_type operator-(ReverseVectorIterator<vector> other)
            {
                difference_type a;
                
                a = other.ptr - ptr;
                return a;
            };

            bool operator>(ReverseVectorIterator<vector> other) const
            {
                return (ptr < other.ptr);
            };
            bool operator>=(ReverseVectorIterator<vector> other) const
            {
                return (ptr <= other.ptr);
            };
            bool operator<(ReverseVectorIterator<vector> other) const
            {
                return (ptr > other.ptr);
            };
            bool operator<=(ReverseVectorIterator<vector> other) const
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



template <typename vector>
    class VectorIterator
{
    public :
        typedef typename vector::value_type                 value_type;
        typedef typename std::ptrdiff_t                     difference_type;
        typedef typename std::random_access_iterator_tag    iterator_category;
        typedef typename vector::value_type*                pointer;
        typedef const typename vector::value_type*          const_pointer;
        typedef typename vector::value_type&                reference;
        typedef const typename vector::value_type&          const_reference;
    private :
        pointer ptr;
        friend class vector;
        VectorIterator(pointer ptr):ptr(ptr) 
        {};
    public :
        //default constructible only from forward iterator and ahead
        VectorIterator(){};
        VectorIterator(const VectorIterator<vector> &other): ptr(other.ptr) {};
        VectorIterator<vector>& operator=(const VectorIterator<vector> &other)
        {
            ptr = other.ptr;
            return *this;
        };
        ~VectorIterator(){};

        //increments
            VectorIterator<vector>& operator++()//++x
            {
                ptr++;
                return *this;
            };
            VectorIterator<vector> operator++(int)//x++
            {
                VectorIterator<vector> temp = *this;
                ptr++;
                return temp;
            };
            VectorIterator<vector>& operator--()
            {
                ptr--;
                return *this;
            };
            VectorIterator<vector>& operator--(int)
            {
                VectorIterator<vector> temp = *this;
                ptr--;
                return temp;
            };

            bool operator==(const VectorIterator<vector> &other)const
            {
                return(ptr == other.ptr);
            };
            bool operator!=(const VectorIterator<vector> &other)const
            {
                return(ptr != other.ptr);
            };
            VectorIterator<vector> operator+(int a)
            {
                VectorIterator<vector>  temp;
                temp.ptr = ptr + a;
                return temp;
            };
            friend VectorIterator<vector> operator+(int a, const VectorIterator<vector>& vec);
            VectorIterator<vector> operator-(int a)
            {
                VectorIterator<vector>  temp;
                temp.ptr = ptr - a;
                return temp;
            };

            difference_type operator-(VectorIterator<vector> other)
            {
                difference_type a;
                
                a = other.ptr - ptr;
                return a;
            };

            bool operator>(VectorIterator<vector> other) const
            {
                return (ptr > other.ptr);
            };
            bool operator>=(VectorIterator<vector> other) const
            {
                return (ptr >= other.ptr);
            };
            bool operator<(VectorIterator<vector> other) const
            {
                return (ptr < other.ptr);
            };
            bool operator<=(VectorIterator<vector> other) const
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
    typedef VectorIterator<T>                 iterator;//LegacyRandomAccessIterator and LegacyContiguousIterator to value_type 
    typedef const VectorIterator<T>                    const_iterator; //LegacyRandomAccessIterator and LegacyContiguousIterator to const value_type 
    typedef typename allocator_type::size_type       size_type;//std::size_t   
    typedef typename allocator_type::difference_type difference_type;// usually std::ptrdiff_t
    typedef typename allocator_type::pointer         pointer;//Allocator::pointer 
    typedef typename allocator_type::const_pointer   const_pointer;//Allocator::const_pointer 
    typedef  ReverseVectorIterator<T>         reverse_iterator;//std::reverse_iterator<iterator>
    typedef const ReverseVectorIterator<T>   const_reverse_iterator;//	std::reverse_iterator<const_iterator>


    
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
                        for(size_t i = 0; i < count; ++i)
                            alloc.construct(container + i, value);
                    };

    template <class InputIt>
    vector(InputIt first, InputIt last,
           const Allocator &alloc = Allocator())
           {
                size_t s = std::distance(first,last);
                container = alloc.allocate(s);
                for(size_t i = 0; i < s; ++i)
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
        for(size_t i = 0; i < _capacity; ++i)
        {
            container[i] = other._container[i];
        }
    };

    ~vector()
    {
        allocator_type alloc;
        if(_capacity)
        {
            for(size_t i = 0; i < _size; ++i)
                alloc.destroy(container + i);
            alloc.dealocate(container, _capacity);
        }
    };

    vector& operator=( const vector& other )
    {
        allocator_type alloc;
        if(_capacity)
        {
            for(size_t i = 0; i < _size; ++i)
                alloc.destroy(container + i);
            alloc.dealocate(container, _capacity);
        }
        _size = other._size;
        _capacity = other._capacity;
        container = alloc.allocate(_capacity);
        for(size_t i = 0; i < _capacity; ++i)
        {
            container[i] = other._container[i];
        }
    };

    void assign( size_type count, const T& value )
    {
        allocator_type alloc;
        
        if(count < 0)
            throw std::length_error("vector");

        for(size_t i = 0; i < _size; ++i)
            alloc.destroy(container[i]);
        _size = 0;

        if(count > _capacity)
        {
            alloc.dealocate(container, _capacity);
            container = alloc.allocate(count);
            _capacity = count;
        }
        _size = count;
        for(size_t i = 0; i < _size; ++i)
            alloc.construct(container[i],value);
    };

    template <class InputIt>
    void assign(InputIt first, InputIt last)
    {
        size_t count = std::distance(first,last);
        if(count < 0)
            throw std::length_error("vector");
        allocator_type alloc;

        for(size_t i = 0; i < _size; ++i)
            alloc.destroy(container[i]);
        _size = 0;
        
        if(count > _capacity)
        {
            alloc.dealocate(container, _capacity);
            container = alloc.allocate(count);
            _capacity = count;
        }
        
        _size = count;
        for(size_t i = 0; i < _size; ++i)
        {
            alloc.construct(container[i],*first);
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
            throw std::out_of_range;
        return container[pos];
    };
    const_reference at( size_type pos ) const
    {
        if(pos >= _size)
            throw std::out_of_range;
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
            throw std::length_error();
        if(_capacity < new_cap)
        {
            allocator_type alloc;
            size_t temp_capacity = _capacity;
            _capacity = new_cap;
            T *temp_container = container;
            container = alloc.allocate(_capacity);
            for (size_t i = 0; i < _size; ++i)
                alloc.construct(container + i, temp_container[i]);
            if (temp_capacity)
            {
                for (size_t i = 0; i < _size; ++i)
                    alloc.destroy(temp_container + i);
                alloc.dealocate(temp_container, temp_capacity);
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
        for (size_t i = 0; i < _size; ++i)
        {
            alloc.destroy(container + i);
        }
        alloc.dealocate(container, _capacity);
        _size = 0;
        alloc.allocate(_capacity);
    };

    iterator insert(const_iterator pos, const T &value)
    {
        allocator_type alloc;
        iterator first = begin();
        size_t position = std::distance(begin());
    
        //iterator pos should be above size or return exception
        if(pos > end() || pos < begin())
            throw std::overflow_error("Container overflow");

        _size++;
        //reallocate if capacity < (new size) oldsize + (1 or count);
        if(_size > _capacity)
            double_up();
        for(size_t i = _size; i > position; i--)
            container[i] = container[i - 1];
        alloc.construct(container + position, value); 
        return(iterator(container + position));
    };// while() double_up(); if theres a range of stuff added

    iterator insert(const_iterator pos, size_type count, const T &value)
    {
        allocator_type alloc;
        iterator first = begin();
        size_t position = std::distance(begin(), pos);
    
        //iterator pos should be above size or return exception
        if(pos > end() || pos < begin())
            throw std::overflow_error("Container overflow");
        if(count >= 0)
            return pos;
        _size = _size + count;
        //reallocate if capacity < (new size) oldsize + (1 or count);
        while(_size > _capacity)
            double_up();
        for(size_t i = _size; i > position; i--)
            container[i] = container[i - count];
        //construct it in each position
        for(size_t i = 0; i < count; i++)
            alloc.construct(container + position + i, value); 
        return(iterator(container + position));
    };

    // constexpr iterator insert(const_iterator pos, size_type count, const T &value);

    template <class InputIt>
        iterator insert(const_iterator pos, InputIt first, InputIt last)
        {
            allocator_type alloc;
            iterator first = begin();
            size_t position = std::distance(begin(), pos);
            size_t count = std::distance(first, last);
            //iterator pos should be above size or return exception
            if(pos > end() || pos < begin())
                throw std::overflow_error("Container overflow");
            if(count >= 0)
                return pos;
            _size = _size + count;
            //reallocate if capacity < (new size) oldsize + (1 or count);
            while(_size > _capacity)
                double_up();
            for(size_t i = _size; i > position; i--)
                container[i] = container[i - count];
            //construct it in each position
            for(size_t i = 0; i < count; i++)
            {
                alloc.construct(container + position + i, *first); 
                first++;
            }
            return(iterator(container + position));
        };

    iterator erase( iterator pos )
    {
        size_t position = std::distance(begin(), pos);
        allocator_type alloc;
        
        if(pos < end())
        {
            alloc.destroy(container + position);
            for(size_t i = 0; i < _size; i++)
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
            size_t first_pos = std::distance(begin(),first);
            size_t second_pos = std::distance(begin(),last);
            size_t count = second_pos - first_pos;
            allocator_type alloc;
            for(size_t i = 0; i < count; i++)
                alloc.destroy(container + first_pos + i);
            for(size_t i = 0; i < count; i++)
                container[first_pos + i] = container[first_pos + i + count];
            _size -= count;
            return first;
        }
        else
            throw std::overflow_error("container overflow");
    };
    void push_back( const T& value );
    void pop_back();
    void resize( size_type count, T value = T() );
    void swap( vector& other );

    //  >>>>> nonmember funcs
    // template< class T, class Alloc >
    // bool operator==( const std::vector<T,Alloc>& lhs,
    //                 const std::vector<T,Alloc>& rhs );
    // template< class T, class Alloc >
    // bool operator!=( const std::vector<T,Alloc>& lhs,
    //                 const std::vector<T,Alloc>& rhs );
    // template< class T, class Alloc >
    // bool operator<( const std::vector<T,Alloc>& lhs,
    //                 const std::vector<T,Alloc>& rhs );
    // template< class T, class Alloc >
    // bool operator<=( const std::vector<T,Alloc>& lhs,
    //                 const std::vector<T,Alloc>& rhs );
    // template< class T, class Alloc >
    // bool operator>( const std::vector<T,Alloc>& lhs,
    //                 const std::vector<T,Alloc>& rhs );
    // template< class T, class Alloc >
    // bool operator>=( const std::vector<T,Alloc>& lhs,
    //                 const std::vector<T,Alloc>& rhs );

    // template< class T, class Alloc >
    //     void swap( std::vector<T,Alloc>& lhs,
    //             std::vector<T,Alloc>& rhs );

    private:
    T *container;
    size_t _size;
    size_t _capacity;

    void double_up()
    {
        Allocator alloc;
        size_t temp_capacity = _capacity;
        _capacity = _capacity * 2;
        T* temp_container = container;
        container = alloc.allocate(_capacity);
        for( size_t i = 0; i < _size; ++i )
            alloc.construct(container + i, temp_container[i]);
        if(temp_capacity)
        {
            for(size_t i = 0; i < _size; ++i)
                alloc.destroy(temp_container + i);
            alloc.dealocate(temp_container, temp_capacity);
        }    
    };
};


template <class vector>
VectorIterator<vector> operator+(int a, const VectorIterator<vector>& vec)
{
    VectorIterator<vector>  temp;
    temp = vec.operator+(a);
    return (temp);
};


template <class vector>
ReverseVectorIterator<vector> operator+(int a, const ReverseVectorIterator<vector>& vec)
{
    ReverseVectorIterator<vector>  temp;
    temp = vec.operator+(a);
    return (temp);
};


#endif