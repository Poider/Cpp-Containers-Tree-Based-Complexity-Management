/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:59:37 by mel-amma          #+#    #+#             */
/*   Updated: 2023/01/17 14:13:56 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _my_map__
#define _my_map__

#include <utility>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
// #include <map>
#include "../utils/pair.hpp"
#include <functional>
#include "../trees/avl_tree.hpp"
#include "../iterators/map_iterator.hpp"
#include "../utils/compare.hpp"
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
    typedef MapIterator<const value_type , avl<value_type, key_compare, value_compare, allocator_type>*, value_compare>                   const_iterator;//LegacyBidirectionalIterator to const value_type
    typedef ft::reverse_iterator<iterator>          reverse_iterator;//	std::reverse_iterator<iterator>
    typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;//std::reverse_iterator<const_iterator>



    private:
    typedef avl<value_type, key_compare, value_compare, allocator_type> node_type;
    typedef typename Allocator ::template rebind<ft::avl<value_type, key_compare, value_compare, Allocator> >::other node_alloc_type;

    
    node_type *root;//
    node_type *_max;//make getters for these
    node_type *_min;//
    size_type _size;//
    key_compare _comp;
    value_compare _v_comp;
    allocator_type alloc;
    node_alloc_type node_alloc;
    //compare wrapper>> make a pair compare that'll compare keys of the pair


            //>>>tree clone using reference
    // void tree_clone(const node_type *& root,const node_type *& copy, node_alloc_type& node_alloc, key_compare &_comp, value_compare _v_comp, allocator_type alloc) const
    // {
    //     if (!root)
    //     {
    //         copy = 0;
    //         return;
    //     }

    //     // Allocate a new node using the provided node allocator
    //     node_type* new_node = node_alloc.allocate(1);

    //     // Construct the new node by copying the values from the original node
    //     node_alloc.construct(new_node, *root);

    //     // Recursively clone the left and right subtrees
    //     tree_clone_on_go(root->left, new_node->left, node_alloc, _comp, _v_comp, alloc);
    //     tree_clone_on_go(root->right, new_node->right, node_alloc, _comp, _v_comp, alloc);

    //     // Set the copy pointer to point to the new node
    //     copy = new_node;
    // };


    node_type *tree_clone_on_go(const node_type *root, node_alloc_type& node_alloc, key_compare &_comp, value_compare _v_comp, allocator_type alloc) const
    {
        //make it so last new root makes parent NULL of root
        if (root == nullptr)
            return nullptr;
        node_type *new_root = node_alloc.allocate(1);
        node_alloc.construct(new_root, node_type(*(root->data),_comp,_v_comp,alloc));
        
        new_root->left = tree_clone_on_go(root->left, node_alloc, _comp, _v_comp, alloc);
        if(new_root->left)
            new_root->left->parent = new_root;
        new_root->right = tree_clone_on_go(root->right, node_alloc, _comp, _v_comp, alloc);//parents
        if(new_root->right)
            new_root->right->parent = new_root;
        return new_root;
    };

    node_type *tree_clone(const node_type *root, node_alloc_type& node_alloc, key_compare &_comp, value_compare _v_comp, allocator_type alloc) const
    {
       node_type *new_root = tree_clone_on_go(root,node_alloc,_comp,_v_comp,alloc);
       new_root->parent = 0;
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
                 const Allocator &alloc = Allocator()): _v_comp(comp)
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
                const Allocator &alloc = Allocator(), typename ft::enable_if<!ft::is_integral< InputIt >::value,InputIt >::type* = nullptr) : _v_comp(_comp)
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
        _size = 0;
        *this = other;
    };

    ~map(){
        clear();
    };
    
    map& operator=( const map& other )
    {
        clear();
        _size = other.size();
        _comp = other._comp;
        alloc = other.alloc;
        
        _min = 0;
        _max = 0;
        root = 0;
        _v_comp = other._v_comp;
        if(_size)
        {
            root = other.tree_clone(other.root, node_alloc, _comp, _v_comp, alloc);
            _min = root;
            while(_min->left)
                _min = _min->left;
            _max = root;
            while(_max->right)
                _max = _max->right;
        }
        return *this;
    };

    allocator_type get_allocator() const
    {
        return alloc;
    };

//>>>>> element access
    T& at( const Key& key )
    {
        node_type *tmp = 0;
        if(root)
            tmp = root->find_node_key(key);
        if(!tmp || !root)
            throw std::out_of_range("no element with that key found");
        return (tmp->data->second);
    };

    const T& at( const Key& key ) const
    {
        node_type *tmp = 0;
        if(root)
            tmp = root->find_node_key(key);
        if(!tmp || !root)
            throw std::out_of_range("no element with that key found");
        return (tmp->data->second);
    };

    T& operator[]( const Key& key )
    {
        node_type *tmp = 0;
        if(root)
            tmp = root->find_node_key(key);
        if(!tmp)
            return insert(ft::make_pair(key ,mapped_type())).first->second;
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
    reverse_iterator rbegin()
    {
        return reverse_iterator(iterator(nullptr,_v_comp,&root));
    };
    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(const_iterator(nullptr,_v_comp,&root));
    };
    reverse_iterator rend()
    {
        return reverse_iterator(iterator(_min,_v_comp,&root));
    };
    const_reverse_iterator rend() const
    {
        return const_reverse_iterator(const_iterator(_min,_v_comp,&root));
    };

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
        if(_size == 0)
            return;
        burn_tree(root);
        root = 0;
        _min = 0;
        _max = 0;
        _size = 0;
    };

    ft::pair<iterator, bool> insert( const value_type& value )
    {
        bool is_inserted = true;
        size_type save = _size;
        _size++;
        node_type *node = 0;// returns node inserted here
        if(!root)
        {
            root = node_alloc.allocate(1);
            node_alloc.construct(root, node_type(value,_comp,_v_comp,alloc));
            node = root;
        }
        else
            root = root->insert(value,_size,node);
        //if size got decremented > not inserted
        if(save == _size)
            is_inserted = false;
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
        return (insert(value).first);
    };

//enable if
    template< class InputIt >
        void insert( InputIt first, InputIt last ,typename ft::enable_if<!ft::is_integral< InputIt >::value,InputIt >::type* = nullptr)
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
            iterator tmp = first;
            tmp++;
            erase(first->first);
            first = tmp;
        }
    };
    size_type erase( const Key& key )
    {
        size_type deleted = 0;
        if(_size > 0)
        {
            
            iterator tmp1(_min,_v_comp,&root);
            iterator tmp2(_max,_v_comp,&root);
            
            if(_min->data->first == key)
                tmp1++;
            if(_max->data->first == key)
                tmp2--;

            root = root->delete_(key,deleted);
            
            if(deleted)
            {
                _size--;
                _min = tmp1.base();
                _max = tmp2.base();
            
            }
            
        }
        return deleted;
    };
    void swap( map& other )
    {
        node_type *root_tmp = root;
        node_type *_max_tmp = _max;
        node_type *_min_tmp = _min;
        size_type _size_tmp = _size;
        key_compare _comp_tmp = _comp;
        value_compare _v_comp_tmp = _v_comp;
        allocator_type alloc_tmp = alloc;
        node_alloc_type node_alloc_tmp = node_alloc;

        root = other.root;
        _max = other._max;
        _min = other._min;
        _size = other._size;
        _comp = other._comp;
        _v_comp = other._v_comp;
        alloc = other.alloc;
        node_alloc = other.node_alloc;

        other.root = root_tmp;
        other._max = _max_tmp;
        other._min = _min_tmp;
        other._size = _size_tmp;
        other._comp = _comp_tmp;
        other._v_comp = _v_comp_tmp;
        other.alloc = alloc_tmp;
        other.node_alloc = node_alloc_tmp;
    };

//>>>>>> lookup
    size_type count( const Key& key ) const
    {
        node_type *tmp = 0;
        if(root)
            tmp = root->find_node_key(key);
        if(!tmp || !root)
            return 0;
        return 1;
    };
    iterator find( const Key& key )
    {
        node_type *tmp = 0;
        if(root)
            tmp = root->find_node_key(key);
        if(!tmp || !root)
            end();
        return iterator(tmp,_v_comp,&root);
    };
    const_iterator find( const Key& key ) const
    {
        node_type *tmp = 0;
        if(root)
            tmp = root->find_node_key(key);
        if(!tmp || !root)
            end();
        return const_iterator(tmp,_v_comp,&root);
    };
    ft::pair<iterator,iterator> equal_range( const Key& key )
    {
        return (ft::make_pair(lower_bound(key),upper_bound(key)));
    };
    ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
    {
        return (ft::make_pair(lower_bound(key),upper_bound(key)));
    };

    private:




node_type* lower_b(node_type* root, const Key& key) const
{
    if (!root)
        return nullptr; // meaning none bigger than the key found

    if (root->data->first == key)
        return root;

    else if (_comp(key, root->data->first))
    {
        // check left tree
        node_type* left = lower_b(root->left, key);
        if (left)
            return left;
        return root;
    }
    else
    {
        // check right tree
        return lower_b(root->right, key);
    }
}

node_type* upper_b(node_type* root, const Key& key) const
{
   if (!root)
        return nullptr; // meaning none bigger than the key found

   if (_comp(key, root->data->first))
    {
        // check left tree
        node_type* left = upper_b(root->left, key);
        if (left)
            return left;
        return root;
    }
    else
    {
        // check right tree
        return upper_b(root->right, key);
    }
}

    public:
    iterator lower_bound( const Key& key )
    {
        node_type* lowerbound = lower_b(root, key);
        return iterator(lowerbound,_v_comp,&root);
    };

    

    const_iterator lower_bound( const Key& key ) const
    {
        node_type* lowerbound = lower_b(root, key);
        return const_iterator(lowerbound,_v_comp,&root);
    };
    iterator upper_bound( const Key& key )
    {
        node_type* upperbound = upper_b(root, key);
        return iterator(upperbound,_v_comp,&root);
    };
    const_iterator upper_bound( const Key& key ) const
    {
        node_type* upperbound = upper_b(root, key);
        return const_iterator(upperbound,_v_comp,&root);
    };


//>>>>> observers
    key_compare key_comp() const
    {
        return _comp;
    };
    ft::map<Key, T, Compare ,
        Allocator>::value_compare value_comp() const
    {
        return _v_comp;
    };



template <class KeyX, class TX, class CompareX,
              class AllocatorX>
    friend bool operator==(const map<KeyX, TX, CompareX, AllocatorX> &lhs,
                    const map<KeyX, TX, CompareX, AllocatorX> &rhs);
template <class KeyX, class TX, class CompareX,
              class AllocatorX>
    friend bool operator!=(const map<KeyX, TX, CompareX, AllocatorX> &lhs,
                    const map<KeyX, TX, CompareX, AllocatorX> &rhs);
template <class KeyX, class TX, class CompareX,
              class AllocatorX>
    friend bool operator<(const map<KeyX, TX, CompareX, AllocatorX> &lhs,
                    const map<KeyX, TX, CompareX, AllocatorX> &rhs);
template <class KeyX, class TX, class CompareX,
              class AllocatorX>
    friend bool operator<=(const map<KeyX, TX, CompareX, AllocatorX> &lhs,
                    const map<KeyX, TX, CompareX, AllocatorX> &rhs);
template <class KeyX, class TX, class CompareX,
              class AllocatorX>
    friend bool operator>(const map<KeyX, TX, CompareX, AllocatorX> &lhs,
                    const map<KeyX, TX, CompareX, AllocatorX> &rhs);
template <class KeyX, class TX, class CompareX,
              class AllocatorX>
    friend bool operator>=(const map<KeyX, TX, CompareX, AllocatorX> &lhs,
                    const map<KeyX, TX, CompareX, AllocatorX> &rhs);


    template <class KeyX, class TX, class CompareX,
              class AllocatorX>
    void swap(map<KeyX, TX, CompareX, AllocatorX> &lhs,
                    map<KeyX, TX, CompareX, AllocatorX> &rhs);

    //end
  };

  template <class KeyX, class TX, class CompareX,
            class AllocatorX>
        void swap(map<KeyX, TX, CompareX, AllocatorX> &lhs,
                    map<KeyX, TX, CompareX, AllocatorX> &rhs)
        {
          lhs.swap(rhs);
        };


    template <class KeyX, class TX, class CompareX,
              class AllocatorX>
    bool operator==(const map<KeyX, TX, CompareX, AllocatorX> &lhs,
                    const map<KeyX, TX, CompareX, AllocatorX> &rhs)
                    {
                        if( lhs.size() != rhs.size() )
                            return false;
                       
                        typename ft::map<KeyX, TX, CompareX, AllocatorX>::iterator it1 = lhs.begin();
                        typename ft::map<KeyX, TX, CompareX, AllocatorX>::iterator it2 = rhs.begin();

                        for( size_t i = 0; i < lhs.size(); i++ )
                        {
                            if(it1->first != it2->first || it1->second != it2->second)
                                return false;
                            it1++;
                            it2++;
                        }
                        return true;
                    };


    template <class KeyX, class TX, class CompareX,
                  class AllocatorX>
        bool operator!=(const map<KeyX, TX, CompareX, AllocatorX> &lhs,
                        const map<KeyX, TX, CompareX, AllocatorX> &rhs)
                        {
                            return (!(lhs == rhs));
                        };


    template <class KeyX, class TX, class CompareX,
                  class AllocatorX>
        bool operator<(const map<KeyX, TX, CompareX, AllocatorX> &lhs,
                        const map<KeyX, TX, CompareX, AllocatorX> &rhs)
                        {
                            return (ft::lexicographical_compare(lhs.begin(),lhs.end(),rhs.begin(),rhs.end()));
                        };


    template <class KeyX, class TX, class CompareX,
                  class AllocatorX>
        bool operator<=(const map<KeyX, TX, CompareX, AllocatorX> &lhs,
                        const map<KeyX, TX, CompareX, AllocatorX> &rhs)
                        {
                         return (!(lhs > rhs));

                        };


    template <class KeyX, class TX, class CompareX,
                  class AllocatorX>
        bool operator>(const map<KeyX, TX, CompareX, AllocatorX> &lhs,
                        const map<KeyX, TX, CompareX, AllocatorX> &rhs)
                        {
                        return (rhs < lhs);

                        };


    template <class KeyX, class TX, class CompareX,
                  class AllocatorX>
        bool operator>=(const map<KeyX, TX, CompareX, AllocatorX> &lhs,
                        const map<KeyX, TX, CompareX, AllocatorX> &rhs)
                        {
                        return (!(lhs < rhs));

                        };


}
#endif