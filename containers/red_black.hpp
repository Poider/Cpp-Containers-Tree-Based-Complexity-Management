#ifndef _RED_BLACK
#define _RED_BLACK
#include <memory>

#define DELETION 0
#define INSERTION 1

#define BLACK 0
#define RED 1

//keep in mind if tree is empty, create a new node, else insert (in map)

//change < to key_compare / value_compare


//in map check if theres root before inserting, or anything, if theresnt then make a new empty one

//this rbTree tree will work when class T is a pair
//do enable if to see if class T is a pair?
namespace ft{
template <class T, class key_compare ,class value_compare ,class Allocator = std::allocator<T> >
struct rbTree{
    //update height whenever you insert or delete
    typedef typename T::first_type first_type;


    //add static for both a var of root and a var of sentinel, sentinel is an object and root is a ptr

    Allocator alloc;
    key_compare k_comp;
    value_compare v_comp;
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


//these put new node at a null node
    void put_left(T data)
    {
        rbTree *temp = new rbTree();
        temp->data = alloc.allocate(1);
        temp->height = 1;
        temp->color = RED;
        alloc.construct(temp->data, data);
        temp->parent = this;
        left = temp;
    };
    
    void put_right(T data)
    {
        rbTree *temp = new rbTree();
        temp->data = alloc.allocate(1);
        temp->height = 1;

        alloc.construct(temp->data, data);
        temp->color = RED;
        temp->parent = this;
        right = temp;
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
    rbTree *insert_node(T data)//use key compare or value compare here
    {
        rbTree* root = 0;
        rbTree* temp = 0;
        
        if(!this->data)// if no data
        {
            put_data(data);
        }
        else if(*(this->data) > data)//rest if no nodes it inserts
        {
            if(!left)
            {
                put_left(data);
                root = left->balance(INSERTION);
                if(height <= 1)
                    height++;
                
                temp = balance(INSERTION);
                if(temp)
                    root = temp;
            }
            else
            {
                root = left->insert_node(data);
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
        else if(*(this->data) < data)
        {
            if(!right)
            {static int i = 0;
            
                put_right(data);
                i++;
               
                root = right->balance(INSERTION);
             
                if(height <= 1)
                    height++;
                 
                temp = balance(INSERTION);
              
                if(temp)
                    root = temp;
                
                // if(i == 2)
                // {
                //     std::cout << right;
                //     exit(1);
                // }
            }
            else
            { 
                root = right->insert_node(data);
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
            alloc.destroy(this->data);
            alloc.construct(this->data, data);
        }
        
        return root;
    };

    rbTree* insert(T data)//must be used in the root
    {
        // make it so if(parent doesnt exists then it does otherwise it wont)
        rbTree* root = insert_node(data);

        if(root)
        {
            // std::cout << root->data->first << std::endl;
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
            if (node->data->first == key)
                break;
            if (key < node->data->first)
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
                // std::cout << "here" << std::endl;
                
                rbTree* node = rotate(this);
                // if(i == 8)
                // {
                //     std::cout << node->data->first << std::endl;
                //     exit(1);
                // }
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
        if (*(child->parent->data) > *(child->data))
        {//we in left of parent
            if(*(child->parent->parent->data) > *(child->parent->data))
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
            if(*(child->parent->parent->data) > *(child->parent->data))
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


};
};



#endif



// void fix_red_black_tree_after_insertion(Tree& T, Node* p) {
//     while (p->color == RED) {
//         if (p == p->parent->left) {  // is p's parent a left child?
//             Node* y = p->parent->parent->right;  // y is p's uncle
//             if (y->color == RED) {  // are p's parent and uncle both red?
//                 // case 1: p's parent and uncle are both red
//                 p->parent->color = BLACK;
//                 y->color = BLACK;
//                 p->parent->parent->color = RED;
//                 p = p->parent->parent;
//             } else {
//                 if (p == p->parent->right) {
//                     // case 2: p is a right child and uncle is black
//                     p = p->parent;
//                     left_rotate(T, p);
//                 }
//                 // case 3: p is a left child and uncle is black
//                 p->parent->color = BLACK;
//                 p->parent->parent->color = RED;
//                 right_rotate(T, p->parent->parent);
//             }
//         } else {  // same as above, but with left and right exchanged
//             Node* y = p->parent->parent->left;
//             if (y->color == RED) {
//                 p->parent->color = BLACK;
//                 y->color = BLACK;
//                 p->parent->parent->color = RED;
//                 p = p->parent->parent;
//             } else {
//                 if (p == p->parent->left) {
//                     p = p->parent;
//                     right_rotate(T, p);
//                 }
//                 p->parent->color = BLACK;
//                 p->parent->parent->color = RED;
//                 left_rotate(T, p->parent->parent);
//             }
//         }
//     }
//     T.root->color = BLACK;
// }




// // Here is a modified version of the red-black tree insertion fixup function that does not use the T.root member to access the root of the tree. Instead, the function takes the root of the tree as an additional argument and keeps a reference to it in a local variable. This allows the function to operate on any subtree of the red-black tree, not just the entire tree.
// Node* fix_red_black_tree_after_insertion(Tree& T, Node* root, Node* p) {
//     //p meaning its parent is red
//     Node* new_root = root;
//     while (p->color == RED) {
//         if (p == p->parent->left) {  // is p's parent a left child?
//             Node* y = p->parent->parent->right;  // y is p's uncle
//             if (y->color == RED) {  // are p's parent and uncle both red?
//                 // case 1: p's parent and uncle are both red
//                 p->parent->color = BLACK;
//                 y->color = BLACK;
//                 p->parent->parent->color = RED;
//                 p = p->parent->parent;
//             } else {
//                 if (p == p->parent->right) {
//                     // case 2: p is a right child and uncle is black
//                     p = p->parent;
//                     left_rotate(T, p);
//                 }
//                 // case 3: p is a left child and uncle is black
//                 p->parent->color = BLACK;
//                 p->parent->parent->color = RED;
//                 right_rotate(T, p->parent->parent);
//             }
//         } else {  // same as above, but with left and right exchanged
//             Node* y = p->parent->parent->left;
//             if (y->color == RED) {
//                 p->parent->color = BLACK;
//                 y->color = BLACK;
//                 p->parent->parent->color = RED;
//                 p = p->parent->parent;
//             } else {
//                 if (p == p->parent->left) {
//                     p = p->parent;
//                     right_rotate(T, p);
//                 }
//                 p->parent->color = BLACK;
//                 p->parent->parent->color = RED;
//                 left_rotate(T, p->parent->parent);
//             }
//         }
//         new_root = p;
//     }
//     root->color = BLACK;
//     return new_root;
// }

// // In this version of the function, the first argument is still the Tree object, but the second argument is the root of the subtree where the insertion took place, and the third argument is the newly inserted node. The function keeps track of the new root of the subtree in the new_root variable and returns it at the end. Note that we still use the T object to call the left_rotate and right_rotate functions, as these functions need to modify the tree object.