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
        height = 1;
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


//these put new node at a null node
    void put_left(T data)
    {
        avl *temp = new avl();
        temp->data = alloc.allocate(1);
        temp->height = 1;
        alloc.construct(temp->data, data);
        temp->parent = this;
        left = temp;
    };
    
    void put_right(T data)
    {
        avl *temp = new avl();
        temp->data = alloc.allocate(1);
        temp->height = 1;

        alloc.construct(temp->data, data);
        temp->parent = this;
        right = temp;
    };

    T* node_data()
    {
        return data;
    }

    
//use balance on each level as it goes up (checks diff between height of right and of left)
//while tryna insert ++ height of each node passed by?
    avl *insert_node(T data)//use key compare or value compare here
    {
        avl* root = 0;
        avl* temp = 0;
        if(!this->data)// if no data
        {
            put_data(data);
        }
        else if(*(this->data) > data)//rest if no nodes it inserts
        {
            if(!left)
            {
                put_left(data);
                if(height <= 1)
                    height++;
                root = balance(data);
            }
            else
            {
                root = left->insert_node(data);
                size_t l_height = left->height;
                size_t r_height = 0;
                if(right)
                    r_height = right->height;
                height = std::max(l_height, r_height) + 1;
                temp = balance(data);
                if(temp)
                    root = temp;
            }
        }
        else if(*(this->data) < data)
        {
            if(!right)
            {
                put_right(data);
                if(height <= 1)
                    height++;
                root = balance(data);
            }
            else
            {
                root = right->insert_node(data);
                size_t r_height = right->height;
                size_t l_height = 0;
                if(left)
                    l_height = left->height;
                height = std::max(l_height, r_height) + 1;
                temp = balance(data);
                if(temp)
                    root = temp;
            }
        }
        else
        {
            //if same key? change old data
            alloc.destroy(this->data);
            alloc.construct(this->data, data);
        }
        return root;
    };

    avl* insert(T data)//must be used in the root
    {
        // make it so if(parent doesnt exists then it does otherwise it wont)
        avl* root = insert_node(data);
        if(root)
            return root;
        else
            return this;
    }

    avl* balance(T data)//segfault cus I touch a parent that shouldnt be touched?
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

        if(diff < 0)
        {
            //right subtree is imbalanced
            if(data < *(right->data))
            {

                std::cout << "RL" << std::endl;
                root = right_rotate(this->right);
                root = left_rotate(this);
            }
            else
            {
                std::cout << "RR" << std::endl;
                root = left_rotate(this);

            }
        }
        else
        {
            //left subtree is imbalanced
            if(data < *(left->data))
            {
                std::cout << "LL" << std::endl;
                root = right_rotate(this);
            }
            else
            {
                std::cout << "LR" << std::endl;
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