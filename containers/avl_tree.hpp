#ifndef _AVL
#define _AVL
#include <memory>



namespace ft{
template <class T, class key_compare ,class value_compare ,class Allocator = std::allocator<T> >
struct avl{
    //update height whenever you insert or delete

    Allocator alloc;
    key_compare k_comp;
    value_compare v_comp;
    T    *data;
    size_t height;
    avl *parent;
    avl *left;
    avl *right;

    avl(){
        data = 0;
        height = 0;
        parent = 0;
        left = 0;
        right = 0;
    };

    avl(T data)
    {
        this->data = alloc.allocate(1);
        alloc.construct(this->data, data);
        parent = 0;
        height = 0;
        left = 0;
        right = 0;
    };

    avl(const avl& other)
    {
        alloc = other.alloc;
        if(other.data)
        {
            this->data = alloc.allocate(1);
            alloc.construct(this->data, *(other.data));
        }
        parent = 0;
        left = 0;
        height = 0;
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
            
            this->data = alloc.allocate(1);
            alloc.construct(this->data, *(other.data));
        }
        return *this;
    };

    void burn_tree()
    {
        //only if theres parent free (so you dont delete root node cus its on stack)
        //recursive? each node, send delete right and left?
        // or delete with a traversal algorithm
    };

    ~avl() {
        if(data)
        {
            alloc.destroy(data);
            alloc.deallocate(data,1);
        }
    };

//update height
//these put new node at a null node
    void put_left(T data)
    {
        avl *temp = new avl();
        temp->data = alloc.allocate(1);
        alloc.construct(temp->data, data);
        temp->parent = this;
        left = temp;
    };
    
    void put_right(T data)
    {
        avl *temp = new avl();
        temp->data = alloc.allocate(1);
        alloc.construct(temp->data, data);
        temp->parent = this;
        right = temp;
    };

    T* node_data()
    {
        return data;
    }

    // //each insert it should calculate O(n)? so no, cus insert is log(n)
    // size_t node_height() //use when insert or delete to update heights (either on all tree or on the stuff that will change?(think of logic))
    // {
    //     if(!left && !right)
    //         return 0;
    //     size_t left_height = 0;
    //     size_t right_height = 0;
    //     if(left)
    //     {
    //         left_height = 1 + left->node_height();
    //         left->height = left_height;
    //     }
    //     if(right)
    //     {
    //         right_height = 1 + right->node_height();
    //         right->height = right_height;
    //     }

    //     return(std::max(left_height, right_height));
    // }


//use balance on each level as it goes up (checks diff between height of right and of left)
//while tryna insert ++ height of each node passed by?
    bool insert_node(T data)//use key compare or value compare here
    {
        if(!this->data)// if no data
        {
            put_data(data);
            return 0;
        }
        else if(*(this->data) > data)//rest if no nodes it inserts
        {
            if(!left)
            {
                put_left(data);
                height++;
                return 1;
            }
            else
            {
                bool incr = left->insert_node(data);
                height += incr;
                return incr;
            }
        }
        else if(*(this->data) < data)
        {
            if(!right)
            {
                put_right(data);
                height++;
                return 1;
            }
            else
            {
                bool incr = right->insert_node(data);
                height += incr;
                return incr;
            }
        }
        else
        {
            //if same key? change old data
            alloc.destroy(this->data);
            alloc.construct(this->data, data);
            return 0;
        }
    };

    void insert(T data)
    {
        insert_node(data);
        balance();//from this node you go up till you find unbalance
    }

    void balance()
    {
        size_t l_height,r_height;

        //check height diff of current node to see if its unbalanced

        //where theres unbalance you send 3 nodes to the appropriate rotate
    }

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
};

}

template <class T, class key_compare ,class value_compare ,class Allocator>
        std::ostream& operator<<(std::ostream& os, const ft::avl<T,key_compare,value_compare,Allocator>& p)
        {
            if(p.data == 0)
                os << "null data";
            else
                os << p.data->first << "/" << p.data->second;
            return os;
        }
template <class T, class key_compare ,class value_compare ,class Allocator>
        std::ostream& operator<<(std::ostream& os, const ft::avl<T,key_compare,value_compare,Allocator> *p)
        {
            if(p == 0)
                os << "null";
            else if(p->data == 0)
                os << "null data";
            else
            os << p->data->first << "/" << p->data->second;
            return os;
        }

#endif