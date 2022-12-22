#ifndef _my_map
#define _my_map
#include <utility>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <map>
#include "pair.hpp"
#include <functional>
#include "avl_tree.hpp"
#include "map_iterator.hpp"
namespace ft {
  
  template<class Key, class T, class Compare = std::less<Key>,
           class Allocator = std::allocator< pair <const Key, T> > >
  class map {
    // types
    public:
    // types:
    typedef Key                                      key_type;//
    typedef T                                        mapped_type;//
    typedef ft::pair<const key_type, mapped_type>        value_type;//
    typedef Compare                                  key_compare;//
    typedef Allocator                                allocator_type;//
    typedef typename allocator_type::reference       reference;//value_type&
    typedef typename allocator_type::const_reference const_reference;//const value_type&
    typedef typename allocator_type::pointer         pointer;//	 Allocator::pointer 
    typedef typename allocator_type::const_pointer   const_pointer;//Allocator::const_pointer 
    typedef typename allocator_type::size_type       size_type;//std::size_t
    typedef typename allocator_type::difference_type difference_type;//std::ptrdiff_t

    typedef MapIterator<pointer>                   iterator;//LegacyBidirectionalIterator to value_type
    typedef MapIterator<const_pointer>                   const_iterator;//LegacyBidirectionalIterator to const value_type
    typedef ft::reverse_iterator<iterator>          reverse_iterator;//	std::reverse_iterator<iterator>
    typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;//std::reverse_iterator<const_iterator>
    
    //makes the key compare work on pairs
    class value_compare: public binary_function<value_type, value_type, bool>
    {
        friend class map;

        protected:
            Compare comp;

            value_compare(Compare c) : comp(c)/
            {};

        public:
        bool operator()(const value_type& x, const value_type& y) const 
        {
            return comp(x.first, y.first);
        }
    };

    private:
    typedef avl<value_type, key_compare, value_compare, allocator_type> node_type;
    node_type *root;
    node_type *last;
    size_type _size;
    key_compare _comp;
    allocator_type alloc;

    //compare wrapper>> make a pair compare that'll compare keys of the pair

    public:
//>>>>> member funcs
    map()
    {
        root = NULL;
        last = NULL;
        _size = 0;
    };

    explicit map(const Compare &comp,
                 const Allocator &alloc = Allocator())
                 {
                     root = NULL;
                     last = NULL;
                     _size = 0;
                     _comp = comp;
                     this->alloc = alloc;
                 };

    template <class InputIt>
        map(InputIt first, InputIt last,
                const Compare &comp = Compare(),
                const Allocator &alloc = Allocator())
                {
                    //insert node by node
                };
    map(const map &other)
    {
        _size;
        _comp;
        alloc;
        //insert range from other begin to other end?
        //root; copy the others deep copy
    };

    ~map();
    map& operator=( const map& other );
    allocator_type get_allocator() const;

//>>>>> element access
    T& at( const Key& key );
    const T& at( const Key& key ) const;
    T& operator[]( const Key& key );

//>>>>> iterators
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;

//>>>>>> capacity
    bool empty() const
    {
        return(size == 0);
    };
    size_type size() const
    {
        return(size);
    };
    size_type max_size() const
    {
        size_type s = alloc.max_size();
        if(s > PTRDIFF_MAX)
            s = PTRDIFF_MAX; 
        return (s);
    };


//>>>>>>> modifiers
    void clear();
    std::pair<iterator, bool> insert( const value_type& value );
    iterator insert( iterator hint, const value_type& value );

    template< class InputIt >
        void insert( InputIt first, InputIt last );

    iterator erase( iterator pos );
    iterator erase( iterator first, iterator last );
    size_type erase( const Key& key );
    void swap( map& other );

//>>>>>> lookup
    size_type count( const Key& key ) const;
    iterator find( const Key& key );
    const_iterator find( const Key& key ) const;
    std::pair<iterator,iterator> equal_range( const Key& key );
    std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;
    iterator lower_bound( const Key& key );
    const_iterator lower_bound( const Key& key ) const;
    iterator upper_bound( const Key& key );
    const_iterator upper_bound( const Key& key ) const;


//>>>>> observers
    key_compare key_comp() const;
    ft::map::value_compare value_comp() const;


template< class Key, class T, class Compare, class Alloc >
    bool operator==( const std::map<Key,T,Compare,Alloc>& lhs,
                    const std::map<Key,T,Compare,Alloc>& rhs );
template< class Key, class T, class Compare, class Alloc >
    bool operator!=( const std::map<Key,T,Compare,Alloc>& lhs,
                    const std::map<Key,T,Compare,Alloc>& rhs );
template< class Key, class T, class Compare, class Alloc >
    bool operator<( const std::map<Key,T,Compare,Alloc>& lhs,
                    const std::map<Key,T,Compare,Alloc>& rhs );
template< class Key, class T, class Compare, class Alloc >
    bool operator<=( const std::map<Key,T,Compare,Alloc>& lhs,
                    const std::map<Key,T,Compare,Alloc>& rhs );
template< class Key, class T, class Compare, class Alloc >
    bool operator>( const std::map<Key,T,Compare,Alloc>& lhs,
                    const std::map<Key,T,Compare,Alloc>& rhs );
template< class Key, class T, class Compare, class Alloc >
    bool operator>=( const std::map<Key,T,Compare,Alloc>& lhs,
                    const std::map<Key,T,Compare,Alloc>& rhs );


template< class Key, class T, class Compare, class Alloc >
    void swap( std::map<Key,T,Compare,Alloc>& lhs,
              std::map<Key,T,Compare,Alloc>& rhs );
};
}

#endif