#ifndef _RED_BLACK //adding comp // changed new to use allocator instead for nodes (+ the use of that comp etc whenever u create a new node) //added size to change inside the insert// added so it would take a reference on a pointer and puts the address of the inserted node in it//change it so it dont change value of key if it already exist//added _default to delete to return if it didnt find// added a "bool" to tell if it deleted or not // : v_comp(key_compare()) added in  constructs by default//put right put left changes//added swap addresses
#define _RED_BLACK
#include <memory>

#define DELETION 0
#define INSERTION 1

#define BLACK 0
#define RED 1

//also keep in mind we return the root if we spot new root, otherwise we return 0 in insert and rotate balance and all

//keep in mind if tree is empty, create a new node, else insert (in map)

//change < to key_compare / value_compare


//in map check if theres root before inserting, or anything, if theresnt then make a new empty one

//this rbTree tree will work when class T is a pair
//do enable if to see if class T is a pair?
namespace ft{
template <class T, class key_compare ,class Allocator = std::allocator<T> >
struct rbTree{

    typedef typename Allocator::template rebind<ft::rbTree<T, key_compare, Allocator> >::other node_alloc_type;
    
    
    Allocator alloc;
    key_compare k_comp;
    bool color;
    T    *data;
    size_t height;
    rbTree *parent;
    rbTree *left;
    rbTree *right;

    rbTree(){
        data = 0;
        color = BLACK;
        height = 0;
        parent = 0;
        left = 0;
        right = 0;
    };

    rbTree(T data)
    {
        this->data = alloc.allocate(1);
        alloc.construct(this->data, data);
        color = BLACK;
        parent = 0;
        height = 1;
        left = 0;
        right = 0;
    };

    rbTree(const T& data, key_compare& k_comp, Allocator& alloc)
    {
        this->k_comp = k_comp;
        this->v_comp = v_comp;
        this->alloc = alloc;
        this->data = alloc.allocate(1);
        alloc.construct(this->data, data);
        
        color = BLACK;
        parent = 0;
        height = 1;
        left = 0;
        right = 0;
    };


    rbTree(const rbTree& other)
    {
        alloc = other.alloc;
        if(other.data)
        {
            this->data = alloc.allocate(1);
            alloc.construct(this->data, *(other.data));
        }
        parent = 0;
        left = 0;
        color = BLACK;
        height = 1;
        right = 0;
    };

    rbTree& operator=( const rbTree& other )//copies data from another, only if it exists
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

    ~rbTree() {
        if(data)
        {
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
        right = node_alloc.allocate(1);
        node_alloc.construct(right, avl(data,k_comp,v_comp,alloc));
        right->color = RED;
        right->height = 1;
        right->parent = this;
    };
    
    void put_right(T data)
    {
        left = node_alloc.allocate(1);
        node_alloc.construct(left,avl(data,k_comp,v_comp,alloc));
        left->height = 1;
        temp->color = RED;
        left->parent = this;
    };

    T* node_data()
    {
        return data;
    }
    void put_data(T data)
    {
        if (this->data)
            alloc.destroy(this->data);
        else
            this->data = alloc.allocate(1);
        alloc.construct(this->data, data);
    }
    rbTree *insert_node(T data, size_t &size, avl* & inserted)//use key compare or value compare here
    {
        rbTree* root = 0;
        rbTree* temp = 0;
        
        if(!this->data)// if no data
        {
            put_data(data);
            inserted = this;
        }
        else if(k_comp(data ,*(this->data)))//rest if no nodes it inserts
        {
            if(!left)
            {
                put_left(data);
                inserted = left;
                root = left->balance(INSERTION);
                if(height <= 1)
                    height++;
                
                temp = balance(INSERTION);
                if(temp)
                    root = temp;
            }
            else
            {
                root = left->insert_node(data, size, inserted);
                size_t l_height = 0;
                size_t r_height = 0;
                if(right)
                    r_height = right->height;
                if(left)//gotta add this cus in rb Im rotating from child so the right of this might not exist in some cases
                    l_height = left->height;
                height = std::max(l_height, r_height) + 1;
                temp = balance(INSERTION);
                if(temp)
                    root = temp;
            }
        }
        else if(k_comp(*(this->data) , data))
        {
            if(!right)
            {static int i = 0;
            
                put_right(data);
                inserted = right;
                i++;
               
                root = right->balance(INSERTION);
             
                if(height <= 1)
                    height++;
                 
                temp = balance(INSERTION);
              
                if(temp)
                    root = temp;
                
            }
            else
            { 
                root = right->insert_node(data,size, inserted);
                size_t r_height = 0;
                size_t l_height = 0;
                if(right)
                    r_height = right->height;
                if(left)
                    l_height = left->height;
                height = std::max(l_height, r_height) + 1;
                
                temp = balance(INSERTION);
                
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

    rbTree* insert(T data, size_t & size, avl* &inserted)//must be used in the root
    {
        // make it so if(parent doesnt exists then it does otherwise it wont)
        rbTree* root = insert_node(data,size, inserted);

        if(root)
        {
            return root;
        }
        else
            return this;
    }

    rbTree *find_node_key(first_type key) // use on the root ofc
    {
        rbTree *node = this;
        while (1)
        {
            if (node->data == key)
                break;
            if (k_comp(key, node->data))
            {
                if (node->left)
                    node = node->left;
                else
                    return NULL;
            }
            else
            {
                if (node->right)
                    node = node->right;
                else
                    return NULL;
            }
        }
        return node;
    }

    rbTree* balance(bool type)//if it catches parent it returns it otherwise it returns 0
    {//node is the child in the imbalance
        static int i = 0;
        i++;
        
        if(parent == NULL || parent->color == BLACK)
            return 0;
         
        //if parent is red and now the inserted is red
        if(color == RED)
        {
            rbTree* uncle = (parent->parent->right == parent)?parent->parent->left : parent->parent->right;
               
            if(uncle == NULL || uncle->color == BLACK)
            {
                //rotations and recolor;         
                rbTree* node = rotate(this);
                return node;
            }
            else
            {//uncle is red
                //recolor and if grandparent isnt root recolor em;
                uncle->color = !uncle->color;
                parent->color = !parent->color;
                if(parent->parent->parent != NULL)
                    parent->parent->color = !parent->parent->color;
                return 0;
            }
            //to find suitable roztations check this and its parent, are they left or right of their parent// by comparing their data
        }
        else
            return 0;//? so it dont touch change stuff(root) if its already balanced
    }

    rbTree *rotate(rbTree *child)
    {
        rbTree *root = 0;
        // recolor(,) two nodes changes their color
        rbTree *nodeRotate = child->parent->parent;
        if (k_comp( *(child->data) ,*(child->parent->data)))
        {//we in left of parent
            if(k_comp(*(child->parent->data), *(child->parent->parent->data)))
            {// LL
                std::cout << "LL" << std::endl;
                recolor(child->parent,child->parent->parent);
                root = right_rotate(nodeRotate);
            }
            else
            {// RL
                std::cout << "RL" << std::endl;
                recolor(child,child->parent->parent);
                root = right_rotate(nodeRotate->right);
                root = left_rotate(nodeRotate);
            }
        }
        else
        {//we in right of parent
            if(k_comp(*(child->parent->data), *(child->parent->parent->data)))
            {// LR
            
                std::cout << "LR" << std::endl;
                recolor(child,child->parent->parent);
                root = left_rotate(nodeRotate->left);
                root = right_rotate(nodeRotate);
            }
            else
            {// RR
                std::cout << "RR" << std::endl;
                recolor(child->parent,child->parent->parent);
                
                root = left_rotate(nodeRotate);
            }
            
        }
         return root;
    }

    void recolor(rbTree* Node1, rbTree* Node2)
    {
        Node1->color = !Node1->color;
        Node2->color = !Node2->color;
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
    rbTree* left_rotate(rbTree *z)
    {
        rbTree *root_parent = z->parent;

        rbTree *x = z->right;
        rbTree *T2 = x->left;
 
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

    rbTree* right_rotate(rbTree *z)
    {
        rbTree *root_parent = z->parent;

        rbTree *x = z->left;
        rbTree *T2 = x->right;
 
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



    //deletion

    void fix_height_till(rbTree *dis)
    {
        rbTree *current = this;
        bool flag = false;

        while (!flag && current)
        {
            size_t l_height = 0;
            size_t r_height = 0;

            if (current == dis)
                flag = true;
            if (current->left)
                l_height = current->left->height;
            if (current->right)
                r_height = current->right->height;
            current->height = std::max(l_height, r_height) + 1;
            current = current->parent;
        }
    }
    rbTree *sibling()
    {
        rbTree *node = (this == parent->left?parent->right:parent->left);
        return(node);
    }

    rbTree *delete_node(rbTree *root)//the child if it exists or parent if not, if none then 0
    {
        rbTree *ret_node;
        if (left && right)
        {
            // two children
            rbTree *min_max;
            {
                // get min right put it in its place
                rbTree *min = right;
                while (min->left)
                    min = min->left;
                min_max = min;
            }

            ret_node = min_max->parent; 
            rbTree *dis = this;
            swap_addresses(dis,min_max);
            dis = dis->delete_node();
            dis->fix_height_till(min_max);
        }

        else if (!left && !right)
        {
            // no children

            if (parent)
                (parent->left == this) ? parent->left = 0 : parent->right = 0;
            ret_node = parent;
            if(!ret_node)
            {
                //means we deleted root thats alone and no balancing needed
            }
            else if(color == BLACK)
                root = delete_fixup(0,root,ret_node);
            node_alloc.destroy(this);
            node_alloc.deallocate(this,1);;
        }

        else
        {
            // one child
            rbTree *child = (left != 0) ? left : right;
            child->parent = parent;
            if (parent)
                (parent->left == this) ? parent->left = child : parent->right = child;
            ret_node = child;
            // now delete this and its data
            bool clr = color;
            if(clr == BLACK && child->color == BLACK)
                delete_fixup(child,root,child->parent);//now check rotations
            else if(clr == BLACK || child->color == BLACK)
                child->color = BLACK;
            node_alloc.destroy(this);
            node_alloc.deallocate(this,1);
        }

        return ret_node;
        // shall return from where the balance should start, if no parent then returns 0 (tree empty)
    };



rbTree* find_delete(first_type key, rbTree* root, size_t &deleted, avl *_default) //use on the root ofc
{
    if(data == key)
    {
        //(if 0 is returned then the parent is null)
        //if no parent means the tree is empty now?
        deleted = 1;
        rbTree* node = delete_node(root);
        // if(node)
        //     node->balance(DELETION);
        //if it sends back 0 in recursivity then tree empty do nothin
        
        return node;//here keep going up the recursivity and if theres a node where no parent, you save that and send that back
    
    }

    //if it sends back 0 in recursivity then tree empty do nothin
    //or this that it didnt find the key
    else if(k_comp(key, data))
    {
        if(left)
        {
            rbTree* node = left->find_delete(key,root,deleted,_default);

            //fix height
            size_t l_height = 0;
            size_t r_height = 0;
            if(left)
                l_height = left->height;
            if(right)
                r_height = right->height;
            height = std::max(l_height, r_height) + 1;
            // balance(DELETION);
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
            rbTree* node = right->find_delete(key,root,deleted,_default);

            //fix height
            size_t l_height = 0;
            size_t r_height = 0;
            if(left)
                l_height = left->height;
            if(right)
                r_height = right->height;
            height = std::max(l_height, r_height) + 1;
            // balance(DELETION);
            if(!parent)//this wont segfault cus if it went through this then its not the one thats deleted
                node = this;
            return(node);
        }
        else
            return default;
    }
};

rbTree *delete_(first_type key, size_t &deleted, avl *_default) // you send the key apparently
{

    rbTree *root = this;
    while(root->parent)
        root = root->parent;
    root = find_delete(key, root, deleted, _default);
    if (root == 0)
        // tree is empty, return a new root null
        return NULL;
    else
    {
        while (root->parent)
        {
            //this so it goes back to parent, cus we track back if we passed by root and register and turn it back,
            // if we didnt pass by root and rotated and smth became root, meaning we wont passs by root, so maximum iterations this will mostly have is 1 I think
            root = root->parent;
        }
        return root;
    }
    // return the root sent back(either caught or when its same), in case root is deleted or smth,

}


rbTree* delete_fixup(rbTree *x, rbTree *root, rbTree *x_parent)
{
    bool clr = BLACK;
    while (x_parent != NULL && clr == BLACK)
    {
        if (x == x_parent->left)
        {
            rbTree *w = x_parent->right;
            // type 1
            if (w && w->color == RED)
            {
                w->color = BLACK;
                x_parent->color = RED;
                rbTree *tmp = 0;
                tmp = left_rotate(x_parent);
                if(tmp)
                    root = tmp;
                w = x_parent->right;
            }
            // type 2
            if (w && (!w->left || w->left->color == BLACK) && (!w->right || w->right->color == BLACK))
            {
                w->color = RED;
                x = x_parent;
                x_parent = x->parent;
                clr = x->color;
            }
            else
            {
                // type 3
                if (w && (!w->right || w->right->color == BLACK))
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    rbTree *tmp = 0;
                    tmp = right_rotate(w);
                    if(tmp)
                        root = tmp;
                    w = x_parent->right;
                }
                // type 4
                if(w)
                {
                    w->color = x_parent->color;
                    w->right->color = BLACK;
                }
                x_parent->color = BLACK;
                rbTree *tmp = 0;
                tmp = left_rotate(x_parent);
                if(tmp)
                    root = tmp;
                x = root;
                x_parent = x->parent;
                clr = x->color;
            }
        }
        else
        {
            rbTree *w = x_parent->left;
            // type 1
            if (w && w->color == RED)
            {
                w->color = BLACK;
                x_parent->color = RED;
                rbTree *tmp = 0;
                tmp = right_rotate(x_parent);
                if(tmp)
                    root = tmp;
                w = x_parent->left;
            }
            // type 2
            
            if (w && (!w->right || w->right->color == BLACK) && (!w->left || w->left->color == BLACK))
            {
                w->color = RED;
                x = x_parent;
                x_parent = x->parent;
                clr = x->color;
            }
            else
            {
                // type 3
                if (w && (!w->left ||w->left->color == BLACK))
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    rbTree *tmp = 0;
                    tmp = left_rotate(w);
                    if(tmp)
                        root = tmp;
                    w = x_parent->left;
                }
                // type 4
                if(w)
                {
                    w->color = x_parent->color;
                    w->left->color = BLACK;
                }
                
                x_parent->color = BLACK;
                rbTree *tmp = 0;
                tmp = right_rotate(x_parent);
                if(tmp)
                    root = tmp;
                x = root;         
                x_parent = x->parent;
                clr = x->color;
                
            }
        }
    }
    x->color = BLACK;
    return root;
}
};
};



#endif



