#ifndef _my_vector
#define _my_vector

#include <memory>
#include <algorithm>
// #include <cstdlib>
//namespace


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
            friend VectorIterator<vector> operator-(int a,const VectorIterator<vector>& vec);

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
            VectorIterator& operator+=(int amount);
            VectorIterator& operator-=(int amount);
            
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
    typedef std::reverse_iterator<iterator>          reverse_iterator;//std::reverse_iterator<iterator>
    typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;//	std::reverse_iterator<const_iterator>


    
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
 /*!!*/                 _size = count;
/*!!*/                  _capacity = count;
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
                    container[i] = first[i];
           };

    vector(const vector &other)
    {
        Allocator alloc;
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
        Allocator alloc;
        if(_capacity)
        {
            for(size_t i = 0; i < _size; ++i)
                alloc.destruct(container + i);
            alloc.dealocate(container, _capacity);
        }
    };

    vector& operator=( const vector& other )
    {
        Allocator alloc;
        if(_capacity)
        {
            for(size_t i = 0; i < _size; ++i)
                alloc.destruct(container + i);
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
        
    };

    template <class InputIt>
    void assign(InputIt first, InputIt last);

    allocator_type get_allocator() const;
    
    // >>>>> element access
    reference at( size_type pos );
    const_reference at( size_type pos ) const;
    reference operator[]( size_type pos );
    const_reference operator[]( size_type pos ) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    T* data();
    const T* data() const;

    // >>>>> iterators
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;

    // >>>>> capacity
    bool empty() const;
    size_type size() const;
    size_type max_size() const;
    void reserve( size_type new_cap );
    size_type capacity() const;

    // >>>>> modifiers
    void clear();

    iterator insert(const_iterator pos, const T &value);

    iterator insert(const_iterator pos, size_type count, const T &value);

    constexpr iterator insert(const_iterator pos, size_type count, const T &value);

    template <class InputIt>
        iterator insert(const_iterator pos, InputIt first, InputIt last);

    iterator erase( iterator pos );
    iterator erase( iterator first, iterator last );
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
        container = alloc.allocate(_capacity)
        for( size_t i = 0; i < _size; ++i )
            alloc.construct(container + i, temp_container[i]);
        if(temp_capacity)
        {
            for(size_t i = 0; i < _size; ++i)
                alloc.destruct(temp_container + i);
            alloc.dealocate(temp_container, temp_capacity);
        }    
    };
};

template <class vector>
VectorIterator<vector> operator-(int a,const VectorIterator<vector>& vec)
{
    VectorIterator<vector>  temp;
    temp = vec.operator-(a);
    return (temp);
};
template <class vector>
VectorIterator<vector> operator+(int a, const VectorIterator<vector>& vec)
{
    VectorIterator<vector>  temp;
    temp = vec.operator+(a);
    return (temp);
};


#endif