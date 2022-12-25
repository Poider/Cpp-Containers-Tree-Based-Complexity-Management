#ifndef _my_map__
#define _my_map__

#include <utility>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
// #include <map>
#include "pair.hpp"
#include <functional>
#include "avl_tree.hpp"
#include "map_iterator.hpp"
namespace ft{
  
    //updating min / max values
        // if(!_min || _v_comp(node,_min))
        //     _min = node;
        // if(!_max || _v_comp(_max,node))
        //     _max = node;



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
    class value_compare: public std::binary_function<value_type, value_type, bool>
    {
        template<class KeyX, class TX, class CompareX ,
        class AllocatorX >
            friend class map;
            template <class TX,class key_compareX,class value_compareX ,class AllocatorX >
                friend struct avl;
        protected:
            Compare comp;

            value_compare(Compare c) : comp(c)
            {};

        public:
        bool operator()(const value_type& x, const value_type& y) const 
        {
            return comp(x.first, y.first);
        }
    };
    
    typedef MapIterator<value_type ,avl<value_type, key_compare, value_compare, allocator_type>*, value_compare>      iterator;//LegacyBidirectionalIterator to value_type
    typedef MapIterator<value_type ,const avl<value_type, key_compare, value_compare, allocator_type>*, value_compare>                   const_iterator;//LegacyBidirectionalIterator to const value_type
    typedef ft::reverse_iterator<iterator>          reverse_iterator;//	std::reverse_iterator<iterator>
    typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;//std::reverse_iterator<const_iterator>



    private:
    typedef avl<value_type, key_compare, value_compare, allocator_type> node_type;
    node_type *root;//
    node_type *_max;//make getters for these
    node_type *_min;//
    size_type _size;//
    key_compare _comp;
    value_compare _v_comp;
    allocator_type alloc;
    std::allocator<ft::avl<value_type, key_compare, value_compare, Allocator> > node_alloc;
    //compare wrapper>> make a pair compare that'll compare keys of the pair
    node_type *tree_clone(const node_type *root) const
    {
        if (root == nullptr)
            return nullptr;
        node_type *new_root = this->node_alloc.allocate(1);
        this->node_alloc.construct(new_root, node_type(root->value,_comp,_v_comp,alloc));
        new_root->left = clone_tree(root->left);
        new_root->right = clone_tree(root->right);
        return new_root;
    };

    void burn_tree(node_type *node)
    {
        if (node == nullptr) return;
        burn_tree(node->left);
        burn_tree(node->right);
        node_alloc.destroy(node);
        node_alloc.deallocate(node,1);
    }

    public:
//>>>>> member funcs
    map(): _v_comp(_comp)
    {
        root = NULL;
        _max = NULL;
        _min = NULL;
        _size = 0;
    };


//when alloc changes and comp or smth, update it in root one, cus it makes the calls, unless youll do a call from another one thats not root then update its things then do the operation
// make it change vcomps etc on stuff that wont work with the root (thatll be called by another node thats not root), otherwise just change it in root
//if you copy or smth, make if root then root -> comp alloc change
    explicit map(const Compare &comp,
                 const Allocator &alloc = Allocator()): _v_comp(_comp)
                 {
                     root = NULL;
                     _max = NULL;
                     _min = NULL;
                     _size = 0;
                     _comp = comp;
                     _v_comp = value_compare(_comp);//I redo it cus if comp change I need it to re declare the comp in that class var
                     this->alloc = alloc;
                 };
    //enable_if
    template <class InputIt>
        map(InputIt first, InputIt last,
                const Compare &comp = Compare(),
                const Allocator &alloc = Allocator()) : _v_comp(_comp)
                {
                    root = NULL;
                    _max = NULL;
                    _min = NULL;
                    _size = 0;
                    _comp = comp;
                    _v_comp = value_compare(_comp);
                    this->alloc = alloc;
                    insert(first, last);
                    //line 76
                    //insert node by node
                };
    map(const map &other): _v_comp(_comp)
    {
        *this = other;
    };

    ~map(){
        clear();
    };
    
    map& operator=( const map& other )
    {
        _size = other.size();
        _comp = other._comp;
        alloc = other.alloc;
        _v_comp = other._v_comp;
        root = other.tree_clone(other.root);
        _min = root;
        while(_min->left)
            _min = _min->left;
        while(_max->right)
            _max = _max->right;
        
        return *this;
    };

    allocator_type get_allocator() const
    {
        return alloc;
    };

//>>>>> element access
    T& at( const Key& key )
    {
        node_type *tmp = root->find_node_key(key);
        if(!tmp)
            throw std::out_of_range("no element with that key found");
        return (*tmp);
    };

    const T& at( const Key& key ) const
    {
        node_type *tmp = root->find_node_key(key);
        if(!tmp)
            throw std::out_of_range("no element with that key found");
        return (*tmp);
    };

    T& operator[]( const Key& key )
    {
        node_type *tmp = root->find_node_key(key);
        if(!tmp)
            return insert(make_pair(key ,mapped_type())).first->second;
        return tmp->data->second;
    };
//>>>>> iterators
    iterator begin()
    {
        return iterator(_min,_v_comp,&root);
    };
    const_iterator begin() const
    {
        return const_iterator(_min,_v_comp,&root);
    };
    iterator end()
    {
        return iterator(nullptr,_v_comp,&root);
    };
    const_iterator end() const
    {
        return const_iterator(nullptr,_v_comp,&root);
    };
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;

//>>>>>> capacity
    bool empty() const
    {
        return(_size == 0);
    };
    size_type size() const
    {
        return(_size);
    };
    size_type max_size() const
    {
        size_type s = alloc.max_size();
        if(s > PTRDIFF_MAX)
            s = PTRDIFF_MAX; 
        return (s);
    };


//>>>>>>> modifiers
    void clear()
    {
          root->burn_tree();
    };

    ft::pair<iterator, bool> insert( const value_type& value )
    {
        bool is_inserted = true;
        _size++;
        node_type *node = 0;// returns node inserted here
        if(!root)
        {
            root = node_alloc.allocate(1);
            node_alloc.construct(root, node_type(value,_comp,_v_comp,alloc));
            node = root;
        }
        else if((node = root->find_node_key(value.first)))
        {
            is_inserted = false;
        }
        else
        {
            root = root->insert(value,_size,node);
        }
        //updating min / max values
        if(!_min || _v_comp(*(node->data),*(_min->data)))
            _min = node;
        if(!_max || _v_comp(*(_max->data),*(node->data)))
            _max = node;
            //Returns a pair consisting of an iterator to the inserted element (or to the element that prevented the insertion) and a bool denoting whether the insertion took place.

        return ft::make_pair(iterator(node,_v_comp,&root),is_inserted);
    };

    iterator insert( iterator hint, const value_type& value )
    {
        (void) hint;
        return (insert(value)->first);
    };

//enable if
    template< class InputIt >
        void insert( InputIt first, InputIt last )
    {
        while(first != last)
        {
            insert(*first);
            first++;
        }
    };
    void erase( iterator pos )
    {
        erase(pos->first);
    };
    void erase( iterator first, iterator last )
    {
        while(first != last)
        {
            erase(first->first);
            first++;
        }
    };
    size_type erase( const Key& key )
    {
        size_type deleted = 0;
        root = root->delete_key(key);
        return deleted;
    };
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
    // key_compare key_comp() const;
    // ft::map::value_compare value_comp() const;


// template< class Key, class T, class Compare, class Alloc >
//     bool operator==( const std::map<Key,T,Compare,Alloc>& lhs,
//                     const std::map<Key,T,Compare,Alloc>& rhs );
// template< class Key, class T, class Compare, class Alloc >
//     bool operator!=( const std::map<Key,T,Compare,Alloc>& lhs,
//                     const std::map<Key,T,Compare,Alloc>& rhs );
// template< class Key, class T, class Compare, class Alloc >
//     bool operator<( const std::map<Key,T,Compare,Alloc>& lhs,
//                     const std::map<Key,T,Compare,Alloc>& rhs );
// template< class Key, class T, class Compare, class Alloc >
//     bool operator<=( const std::map<Key,T,Compare,Alloc>& lhs,
//                     const std::map<Key,T,Compare,Alloc>& rhs );
// template< class Key, class T, class Compare, class Alloc >
//     bool operator>( const std::map<Key,T,Compare,Alloc>& lhs,
//                     const std::map<Key,T,Compare,Alloc>& rhs );
// template< class Key, class T, class Compare, class Alloc >
//     bool operator>=( const std::map<Key,T,Compare,Alloc>& lhs,
//                     const std::map<Key,T,Compare,Alloc>& rhs );


// template< class Key, class T, class Compare, class Alloc >
//     void swap( std::map<Key,T,Compare,Alloc>& lhs,
//               std::map<Key,T,Compare,Alloc>& rhs );
};
}

#endif