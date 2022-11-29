#include <iostream>
#include "avl_tree.hpp"
#include "pair.hpp"

using namespace ft;
int main()
{
    {
        avl< pair<int,std::string> ,int,int > root;
        // root.put_data(make_pair(0,"root"));
        // root.put_left(make_pair(1,"lol"));
        // root.put_right(make_pair(2,"lel"));

        // std::cout << root.right << std::endl;
        // avl< pair<int,std::string> ,int,int > node;
        // node = root;
        // std::cout << node.left << std::endl;

        root.insert(make_pair(1,"root"));
        root.insert(make_pair(2,"root"));
        root.insert(make_pair(3,"root"));
        // root.insert(make_pair(4,"root"));
        // root.insert(make_pair(5,"root"));

        std::cout << root.right << std::endl;

    }
    // system("leaks a.out");
}