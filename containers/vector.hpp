#ifndef _my_vector
#define _my_vector

#include <memory>
// #include <cstdlib>
//namespace


template <typename vector>
    class VectorIterator
{
    public :
        typedef typename vector::value_type                     value_type;
        typedef typename std::ptrdiff_t                         difference_type;
        typedef typename std::random_access_iterator_tag        iterator_category;
        typedef typename value_type*                            pointer;
        typedef typename value_type&                            reference;

    private :
        pointer ptr;

    public :
        VectorIterator();//default constructible only from forward iterator and ahead
        VectorIterator(const VectorIterator<vector> &other);
        VectorIterator<vector>& operator=(const VectorIterator<vector> &other);
        ~VectorIterator();

        //increments
            VectorIterator<vector>& operator++();
            VectorIterator<vector>& operator++(int);
            VectorIterator<vector>& operator--();
            VectorIterator<vector>& operator--(int);

            bool operator==(const VectorIterator<vector> &other)const;
            bool operator!=(const VectorIterator<vector> &other)const;
            friend VectorIterator<vector> operator+(const VectorIterator& vec, int a);
            friend VectorIterator<vector> operator+(int a, const VectorIterator& vec);
            friend VectorIterator<vector> operator-(const VectorIterator& vec, int a);
            friend VectorIterator<vector> operator-(int a,const VectorIterator& vec);

            bool operator>(VectorIterator<vector> other) const;
            bool operator>=(VectorIterator<vector> other) const;
            bool operator<(VectorIterator<vector> other) const;
            bool operator<=(VectorIterator<vector> other) const;
            VectorIterator& operator+=(int amount);
            VectorIterator& operator-=(int amount);
      
        // * -> rvalue (const I guess?)
        // * -> lvalue (only for mutable) *a = t;
        // multipass?
        //a[n]
        //a[n] with const, returns const refrence
    };



template <class T, class Allocator = std::allocator<T> >
class Vector
{
    std::random_access_iterator_tag
public:
    typedef T                                        value_type;//
    typedef Allocator                                allocator_type;//
    typedef typename allocator_type::reference       reference;//value_type&
    typedef typename allocator_type::const_reference const_reference;//const value_type&
    typedef implementation-defined                   iterator;/LegacyRandomAccessIterator and LegacyContiguousIterator to value_type */
    typedef implementation-defined                   const_iterator; /*LegacyRandomAccessIterator and LegacyContiguousIterator to const value_type */
    typedef typename allocator_type::size_type       size_type;//std::size_t   
    typedef typename allocator_type::difference_type difference_type;// usually std::ptrdiff_t
    typedef typename allocator_type::pointer         pointer;//Allocator::pointer 
    typedef typename allocator_type::const_pointer   const_pointer;//Allocator::const_pointer 
    typedef std::reverse_iterator<iterator>          reverse_iterator;//std::reverse_iterator<iterator>
    typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;//	std::reverse_iterator<const_iterator>


    
    // >>>>> member funcs 
    vector();

    explicit vector(const Allocator &alloc);

    explicit vector(size_type count,
                    const T &value = T(),
                    const Allocator &alloc = Allocator());

    template <class InputIt>
    vector(InputIt first, InputIt last,
           const Allocator &alloc = Allocator());

    vector(const vector &other);

    ~vector();

    vector& operator=( const vector& other );

    void assign( size_type count, const T& value );

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
    template< class T, class Alloc >
    bool operator==( const std::vector<T,Alloc>& lhs,
                    const std::vector<T,Alloc>& rhs );
    template< class T, class Alloc >
    bool operator!=( const std::vector<T,Alloc>& lhs,
                    const std::vector<T,Alloc>& rhs );
    template< class T, class Alloc >
    bool operator<( const std::vector<T,Alloc>& lhs,
                    const std::vector<T,Alloc>& rhs );
    template< class T, class Alloc >
    bool operator<=( const std::vector<T,Alloc>& lhs,
                    const std::vector<T,Alloc>& rhs );
    template< class T, class Alloc >
    bool operator>( const std::vector<T,Alloc>& lhs,
                    const std::vector<T,Alloc>& rhs );
    template< class T, class Alloc >
    bool operator>=( const std::vector<T,Alloc>& lhs,
                    const std::vector<T,Alloc>& rhs );

    template< class T, class Alloc >
        void swap( std::vector<T,Alloc>& lhs,
                std::vector<T,Alloc>& rhs );
};





#endif