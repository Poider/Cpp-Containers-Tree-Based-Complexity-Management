/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:59:05 by mel-amma          #+#    #+#             */
/*   Updated: 2023/01/16 14:45:40 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _AVL
#define _AVL
#include <memory>
#include <iostream>

#include <algorithm>
#define DELETION 0
#define INSERTION 1
//change < to key_compare / value_compare


//in map check if theres root before inserting, or anything, if theresnt then make a new empty one

//this avl tree will work when class T is a pair
//do enable if to see if class T is a pair?
namespace ft{
template <class T,class key_compare = std::less<typename T::first_type>,class value_compare = std::less<T> ,class Allocator = std::allocator<T> >
struct avl{
    //update height whenever you insert or delete
    // typedef typename Allocator::template rebind<ft::avl<T, key_compare, value_compare, Allocator> >::other node_alloc_type;
    typedef typename Allocator::template rebind<ft::avl<T, key_compare, value_compare, Allocator> >::other node_alloc_type;

    typedef typename T::first_type first_type;
    typedef T data_type;
    node_alloc_type node_alloc;
    Allocator alloc;
    key_compare k_comp;
    value_compare v_comp;
    T    *data;
    size_t height;
    avl *parent;
    avl *left;
    avl *right;

    avl() : v_comp(key_compare())
    {
        data = 0;
        height = 0;
        parent = 0;
        left = 0;
        right = 0;
    };

    avl(const T& data) : v_comp(key_compare())
    {
        this->data = alloc.allocate(1);
        alloc.construct(this->data, data);
        parent = 0;
        height = 1;
        left = 0;
        right = 0;
    };

    avl(const T& data, key_compare& k_comp, value_compare& v_comp,Allocator& alloc) : v_comp(k_comp)
    {
        this->k_comp = k_comp;
        this->v_comp = v_comp;
        this->alloc = alloc;
        this->data = alloc.allocate(1);
        alloc.construct(this->data, data);
        
        parent = 0;
        height = 1;
        left = 0;
        right = 0;
    };

    avl(const avl& other) : v_comp(other.k_comp)
    {
        alloc = other.alloc;
        if(other.data)
        {
            this->data = alloc.allocate(1);
            alloc.construct(this->data, *(other.data));
        }
        // std::cout << data << std::endl;

        alloc = other.alloc;
        v_comp = other.v_comp;
        k_comp = other.k_comp;
        parent = 0;
        left = 0;
        height = 1;
        right = 0;
    };

    avl& operator=( const avl& other )//copies data from another, only if it exists
    {
        if(other.data)
        {
            if(data)
            {
                alloc.destroy(data);
                alloc.deallocate(data,1);
            }
            alloc = other.alloc;
            v_comp = other.v_comp;
            k_comp = other.k_comp;
            this->data = alloc.allocate(1);
            alloc.construct(this->data, *(other.data));
        }
        return *this;
    };


    ~avl() {
        if(data)
        {
        // std::cout << node->data->first << std::endl;

            alloc.destroy(data);
            alloc.deallocate(data,1);
        }
    };
    
      void fill_node(avl* node1 , avl* node2)
    {
        node1->left = node2->left;
        node1->right = node2->right;
        node1->parent = node2->parent;
        node1->height = node2->height;
        if (node2 ->left != NULL)
            node2 ->left->parent = node1;
        if (node2 ->right != NULL)
            node2 ->right->parent = node1;
    }

   void swap_addresses(avl* node1, avl* node2) 
   {
        avl tmp;
        tmp.left = node1->left;
        tmp.right = node1->right;
        tmp.parent = node1->parent;
        tmp.height = node1->height;
        if (node2->parent->left == node2)
            node2->parent->left = node1;
        else
            node2->parent->right = node1;
        fill_node(node1, node2);
        if (tmp.parent == NULL)
        {}
        else if (tmp.parent->left == node1)
            tmp.parent->left = node2;
        else
            tmp.parent->right = node2;
        fill_node(node2, &tmp);
        if (node1 ->parent == node1)
        {
            node1 ->parent = node2;
            node2 ->right = node1;
            node2->parent = tmp.parent;
        }
   
    }
//these put new node at a null node
    void put_left(T data)
    {
        left = node_alloc.allocate(1);
        node_alloc.construct(left,avl(data,k_comp,v_comp,alloc));
        left->height = 1;
        left->parent = this;
    };
    
    void put_right(T data)
    {
        right = node_alloc.allocate(1);
        node_alloc.construct(right, avl(data,k_comp,v_comp,alloc));

        right->height = 1;

        right->parent = this;

        // std::cout << this->data << std::endl;

    };

    T* node_data()
    {
        return data;
    }

    
//use balance on each level as it goes up (checks diff between height of right and of left)
//while tryna insert ++ height of each node passed by?
    avl *insert_node(T data, size_t &size, avl* & inserted)//use key compare or value compare here
    {
        avl* root = 0;
        avl* temp = 0;
        if(!this->data)// if no data
        {
            put_data(data);
            inserted = this;
        }
        else if(v_comp(data, *(this->data)))//rest if no nodes it inserts
        {
            if(!left)
            {
                put_left(data);
                inserted = left;
                if(height <= 1)
                    height++;
                root = balance(data, INSERTION);
            }
            else
            {
                root = left->insert_node(data,size,inserted);
                size_t l_height = left->height;
                size_t r_height = 0;
                if(right)
                    r_height = right->height;
                height = std::max(l_height, r_height) + 1;
                temp = balance(data, INSERTION);
                if(temp)
                    root = temp;
            }
        }
        else if(v_comp(*(this->data), data))
        {
            if(!right)
            {
                put_right(data);
                inserted = right;
                if(height <= 1)
                    height++;
                root = balance(data, INSERTION);
            }
            else
            {
                root = right->insert_node(data,size,inserted);
                size_t r_height = right->height;
                size_t l_height = 0;
                if(left)
                    l_height = left->height;
                height = std::max(l_height, r_height) + 1;
                temp = balance(data, INSERTION); 
                if(temp)
                    root = temp;
            }
        }
        else
        {
            //if same key? change old data
            size--;
            inserted = this;
            // alloc.destroy(this->data);
            // alloc.construct(this->data, data);
        }
        return root;
    };

    avl* insert(T data, size_t & size, avl* &inserted)//must be used in the root
    {
        // make it so if(parent doesnt exists then it does otherwise it wont)
        avl* root = insert_node(data,size,inserted);
        if(root)
            return root;
        else
            return this;
    }

    avl* balance(T data_static, bool type)
    {
        avl* root = 0;
        int l_height = 0;
        int r_height = 0;
        
        if(left)
            l_height = left->height;
        if(right)
            r_height = right->height;


        //check height diff of current node to see if its unbalanced
        int diff = l_height - r_height;

        if(abs(diff) < 2)
            return 0;
        
        //where theres unbalance you send 3 nodes to the appropriate rotate
        T *data = &data_static;
        if(diff < 0)
        {
            
            //right subtree is imbalanced
            if(type == DELETION)
            {
                int l_height2 = 0;
                int r_height2 = 0;

                if(right->left)
                    l_height2 = right->left->height;
                if(right->right)
                    r_height2 = right->right->height;
                int diff2 = l_height2 - r_height2;
                data  = (diff2 < 0)? right->right->data : right->left->data;
            }



            if(v_comp(*data, *(right->data)))
            {

                // std::cout << "RL" << std::endl;
                root = right_rotate(this->right);
                root = left_rotate(this);
            }
            else
            {
                // std::cout << "RR" << std::endl;
                root = left_rotate(this);

            }
        }
        else
        {
            //left subtree is imbalanced
            if(type == DELETION)
            {
                int l_height2 = 0;
                int r_height2 = 0;

                if(left->left)
                    l_height2 = left->left->height;
                if(left->right)
                    r_height2 = left->right->height;
                int diff2 = l_height2 - r_height2;
                data  = (diff2 < 0)? left->right->data : left->left->data;
            }

            if(v_comp(*data, *(left->data)))
            {
                // std::cout << "LL" << std::endl;
                root = right_rotate(this);
            }
            else
            {
                // std::cout << "LR" << std::endl;
                root = left_rotate(this->left);
                root = right_rotate(this);
            }
        }
        return root;
    }

 
    

/*
     z                            x
    / \                          /  \ 
  T1   x      Left Rotate(z)   z      y
     /  \   - - - - - - - ->  / \    / \
    T2   y                  T1  T2  T3  T4
        /  \
       T3   T4*/
//the parent is where theres unbalance      
//return the head to put in their parent left or right
    avl* left_rotate(avl *z)
    {
        avl *root_parent = z->parent;

        avl *x = z->right;
        avl *T2 = x->left;
 
        //finding if z is left or right of its parent
        if(root_parent)
        {
            if(z == root_parent->left)
                root_parent->left = x;
                //parent child and child of parent
            else
                root_parent->right = x;
        }
        x->parent = root_parent;
        // Perform rotation
        x->left = z;
        z->parent = x;
        z->right = T2;
        if(T2)
            T2->parent = z;
        // Update heights //protect against segfault
        size_t l_height = 0;
        size_t r_height = 0;
        {
            if(z->left)
                l_height = z->left->height;
            if(z->right)
                r_height = z->right->height;
        }
        z->height = std::max(l_height, r_height) + 1;

        l_height = 0;
        r_height = 0;
        {
            if(x->left)
                l_height = x->left->height;
            if(x->right)
                r_height = x->right->height;
        }
        x->height = std::max(l_height, r_height) + 1;
         //if its the root now it returns it otherwise nothing
        if(x->parent)
            return 0;
        return x;
    };

/*
       z                           x
     /   \                        /  \ 
    x    T4  Right Rotate(z)    y      z
   /  \      - - - - - - - ->  / \    / \
  y    T2                    T1  T3 T2  T4
 / \
T1   T3*/

    avl* right_rotate(avl *z)
    {
        avl *root_parent = z->parent;

        avl *x = z->left;
        avl *T2 = x->right;
 
        //finding if z is left or right of its parent
        if(root_parent)
        {
            if(z == root_parent->left)
                root_parent->left = x;
                //parent child and child of parent
            else
                root_parent->right = x;
        }
        x->parent = root_parent;

        // Perform rotation
        x->right = z;
        z->parent = x;
        z->left = T2;
        if(T2)
            T2->parent = z;

        // Update heights
        size_t l_height = 0;
        size_t r_height = 0;
        {
            if(z->left)
                l_height = z->left->height;
            if(z->right)
                r_height = z->right->height;
        }
        z->height = std::max(l_height, r_height) + 1;
        
        l_height = 0;
        r_height = 0;
        {
            if(x->left)
                l_height = x->left->height;
            if(x->right)
                r_height = x->right->height;
        }
        x->height = std::max(l_height, r_height) + 1;
        //if its the root now it returns it otherwise nothing
        if(x->parent)
            return 0;
        return x;
    };

    avl* _left()
    {
        return left;
    }

    avl * _right()
    {
        return right;
    }

    void put_data(T data)
    {
        if(this->data)
            alloc.destroy(this->data);
        else
            this->data = alloc.allocate(1);
        alloc.construct(this->data,data);
    }



//deletion
//maybe will also return root like insert


void fix_height_till(avl *dis)
{
    avl *current = this;
    bool flag = false;
    
    while(!flag && current)
    {
        size_t l_height = 0;
        size_t r_height = 0;

        if(current == dis)
            flag = true;
        if(current->left)
            l_height = current->left->height;
        if(current->right)
            r_height = current->right->height;
        current->height = std::max(l_height, r_height) + 1;
        current = current->parent;
        
    }
}



//find node that you try deleting then update height with the recursivity after deletion and then also balance
avl* delete_node()
// update height after deleting that node // starting from parent of the deleted node
{
    avl *ret_node;
    if(left && right)
    {
        //two children
        //maybe do the opposite and take from the highest to maybe not do rotations
        avl* min_max;
        // if(left->height > right->height)
        {
            //get min right put it in its place
            avl* min = right;
            while(min->left)
                min = min->left;
            min_max = min;
        }
        // else{
        //     //get max left put it in its place
        //     avl* max = left;
        //     while(max->right)
        //         max = max->right;
        //     min_max = max;
        // }
        
        ret_node = min_max->parent; // from where balance
        // alloc.destroy(this->data);
        // alloc.construct(this->data, *(min_max->data));
        // then delete that node //send it to this delete_node
        avl *dis = this;
        swap_addresses(dis,min_max);
        dis = dis->delete_node();
        dis->fix_height_till(min_max);
    }

    else if(!left && !right)
    {
        //no children
        if(parent)
            (parent->left == this)? parent->left = 0 : parent->right = 0;
        ret_node = parent;
        node_alloc.destroy(this);
        node_alloc.deallocate(this,1);
        // delete this;
       
    }

    else
    {
        // one child
        avl *child = (left != 0)? left : right;
        child->parent = parent;
        if(parent)
            (parent->left == this)? parent->left = child : parent->right = child;
        ret_node = child;
        //now delete this and its data
        node_alloc.destroy(this);
        node_alloc.deallocate(this,1);
        // delete this;
    }

    return ret_node;
    //shall return from where the balance should start, if no parent then returns 0 (tree empty)
    
};

avl* find_node_key(first_type key) //use on the root ofc
{
    avl *node = this;
    while(1)
    {
        if(node->data->first == key)
            break;
        if(k_comp(key, node->data->first))
        {
            if(node->left)
                node = node->left;
            else
                return NULL;
        }
        else 
        {
            if(node->right)
                node = node->right;
            else
                return NULL;
        }
    }
    return node;
}



avl* find_delete(const first_type key, size_t &deleted, avl *_default) //use on the root ofc
{
    if(data->first == key)
    {
        //(if 0 is returned then the parent is null)
        //if no parent means the tree is empty now?
            // std::cout << "here22" << std::endl;
        deleted = 1;
        avl* node = delete_node();
        T d;
        if(node)
        node->balance(d,DELETION);
        //if it sends back 0 in recursivity then tree empty do nothin
        return node;//here keep going up the recursivity and if theres a node where no parent, you save that and send that back
    
    }

    //if it sends back 0 in recursivity then tree empty do nothin
    //or this that it didnt find the key
    else if(k_comp(key, data->first))
    {
        if(left)
        {
            avl* node = left->find_delete(key,deleted,_default);

            //fix height
            size_t l_height = 0;
            size_t r_height = 0;
            if(left)
                l_height = left->height;
            if(right)
                r_height = right->height;
            height = std::max(l_height, r_height) + 1;
            T d;
            balance(d,DELETION);
            if(!parent)
                node = this;
            return(node);
        }
        else
            return _default;
    }
    else
    {
        if(right)
        {
            avl* node = right->find_delete(key, deleted,_default);

            //fix height
            size_t l_height = 0;
            size_t r_height = 0;
            if(left)
                l_height = left->height;
            if(right)
                r_height = right->height;
            height = std::max(l_height, r_height) + 1;
            T d;
            balance(d,DELETION);
            if(!parent)//this wont segfault cus if it went through this then its not the one thats deleted
                node = this;
            return(node);
        }
        else
            return _default;
    }
}

avl* delete_(const first_type key, size_t &deleted)// you send the key apparently
{
    avl *root = find_delete(key,deleted,this);
    if(root == 0)
        //tree is empty, return a new root null
        return NULL;
    else
    {//if root returned the  its caught or still the same
        while(root->parent)
        {
            // std::cout << "sup" << std::endl;
            root = root->parent;
        }
        return root;
    }
    //return the root sent back, in case root is deleted or smth,
    
}
template <class TX,class key_compareX ,class value_compareX,class AllocatorX>
    friend bool operator==(avl<TX, key_compareX, value_compareX,AllocatorX > &a, avl<TX, key_compareX, value_compareX,AllocatorX > &b);

template <class TX,class key_compareX ,class value_compareX,class AllocatorX>
    friend bool operator!=(avl<TX, key_compareX, value_compareX,AllocatorX > &a, avl<TX, key_compareX, value_compareX,AllocatorX > &b);
};

template <class TX,class key_compareX ,class value_compareX,class AllocatorX>
    bool operator==(avl<TX, key_compareX, value_compareX,AllocatorX > &a, avl<TX, key_compareX, value_compareX,AllocatorX > &b)
    {
        if(a.data->first == b.data->first && a.data->second == b.data->second)
            return true;
        return false;
    };

template <class TX,class key_compareX ,class value_compareX,class AllocatorX>
    bool operator!=(avl<TX, key_compareX, value_compareX,AllocatorX > &a, avl<TX, key_compareX, value_compareX,AllocatorX > &b)
    {
        return !(a == b);
    };


}

// template <class T, class key_compare ,class value_compare ,class Allocator>
//         std::ostream& operator<<(std::ostream& os, const ft::avl<T,value_compare,Allocator>& p)
//         {
//             if(p.data == 0)
//                 os << "null data";
//             else
//                 os << p.data->first << "/" << p.data->second;
//             return os;
//         }
// template <class T, class key_compare ,class value_compare ,class Allocator>
//         std::ostream& operator<<(std::ostream& os, const ft::avl<T,value_compare,Allocator> *p)
//         {
//             if(p == 0)
//                 os << "null";
//             else if(p->data == 0)
//                 os << "null data";
//             else
//             os << p->data->first << "/" << p->data->second;
//             return os;
//         }

#endif