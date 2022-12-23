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
    //iterator send it other shit than this
   
    
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
    
    typedef MapIterator<avl<value_type, key_compare, value_compare, allocator_type>*, value_compare>      iterator;//LegacyBidirectionalIterator to value_type
    typedef MapIterator<const avl<value_type, key_compare, value_compare, allocator_type>*, value_compare>                   const_iterator;//LegacyBidirectionalIterator to const value_type
    typedef ft::reverse_iterator<iterator>          reverse_iterator;//	std::reverse_iterator<iterator>
    typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;//std::reverse_iterator<const_iterator>



    private:
    typedef avl<value_type, key_compare, value_compare, allocator_type> node_type;
    node_type *root;//
    node_type *max;//make getters for these
    node_type *min;//
    size_type _size;//
    key_compare _comp;
    value_compare _v_comp;
    allocator_type alloc;
    std::allocator<ft::avl<T, key_compare, value_compare, Allocator> > node_alloc;
    //compare wrapper>> make a pair compare that'll compare keys of the pair

    public:
//>>>>> member funcs
    map()
    {
        root = NULL;
        max = NULL;
        min = NULL;
        _size = 0;
    };


//when alloc changes and comp or smth, update it in root one, cus it makes the calls, unless youll do a call from another one thats not root then update its things then do the operation
// make it change vcomps etc on stuff that wont work with the root, otherwise just change it in root
//if you copy or smth, make if root then root -> comp alloc change
    explicit map(const Compare &comp,
                 const Allocator &alloc = Allocator())
                 {
                     root = NULL;
                     max = NULL;
                     min = NULL;
                     _size = 0;
                     _comp = comp;
                     _v_comp = value_compare();//I redo it cus if comp change I need it to re declare the comp in that class var
                     this->alloc = alloc;
                 };

    template <class InputIt>
        map(InputIt first, InputIt last,
                const Compare &comp = Compare(),
                const Allocator &alloc = Allocator())
                {
                    //line 76
                    //insert node by node
                };
    map(const map &other)
    {
        *this = other;
        //insert range from other begin to other end?
        //root; copy the others deep copy
    };

    ~map(){
        if(root)
        {
            //recursive or iterativly delete its children then
            //delete root
        }
    };

    map& operator=( const map& other )
    {
        _size = other.size();
        _comp = other._comp;
        alloc = other._alloc;
        //insert all the other nodes
        //max / min, when you insert the max and min of other in this, make that address in min max here
    };

    allocator_type get_allocator() const
    {
        return alloc;
    };

//>>>>> element access
    T& at( const Key& key )
    {
        node_type *tmp = root->find_node_key(key)
        if(!tmp)
            throw std::out_of_range("no element with that key found");
        return (*tmp);
    };

    const T& at( const Key& key ) const
    {
        node_type *tmp = root->find_node_key(key)
        if(!tmp)
            throw std::out_of_range("no element with that key found");
        return (*tmp);
    };

    T& operator[]( const Key& key );
    {
        node_type *tmp = root->find_node_key(key)
        if(!tmp)
        {
            tmp = insert(make_pair(k,mapped_type()));
            //idk what tmp type but basically insert and bring back reference to the second one?


        }
    }
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

    std::pair<iterator, bool> insert( const value_type& value )
    {
        _size++;
        if(!root)
        {
            root = node_alloc.allocate(1);
            node_alloc.construct(root, avl(value,_comp,_v_comp,alloc));
        }
        else
        {
            root = root.insert(value,_size);
        }
    };
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