#include <iostream>
#include "red_black.hpp"
#include "pair.hpp"

using namespace ft;

#include <iostream>
#include <vector>
#include <queue>

#include <iostream>
#include <string>

#define BLACK 0
#define RED 1
template<class T>
void print_tree_X(const ft::rbTree<T,int,int>* root, int indent=0) {
  if (!root) return;

  std::cout << std::string(indent, ' ') << root->data->first << std::endl;
  if (root->left) {
    std::cout << std::string(indent, ' ') << "└── " << root->left->data->first<< std::endl;
    print_tree_X(root->left, indent + 4);
  }
  if (root->right) {
    std::cout << std::string(indent, ' ') << "└── " << root->right->data->first << std::endl;
    print_tree_X(root->right, indent + 4);
  }
}


template<class T>
void printTree(ft::rbTree<T,int,int>* root) {
    if (root == NULL) {
        return;
    }

    std::queue<ft::rbTree<T,int,int>*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();
        std::vector<ft::rbTree<T,int,int> *> level;

        for (int i = 0; i < size; i++) {
            ft::rbTree<T,int,int>* node = q.front();
            q.pop();
            level.push_back(node);

            if (node->left != NULL) {
                q.push(node->left);
            }

            if (node->right != NULL) {
                q.push(node->right);
            }
        }

        for (int i = 0; i < level.size(); i++) {
            std::string s = (level[i]->color == BLACK)?"B":"R";
            std::cout << level[i]->data->first <<"("   << s<< ")";
            if (i < level.size() - 1) {
                std::cout << " /";
            }
        }
        std::cout << std::endl;

        for (int i = 0; i < level.size(); i++) {
            if (i > 0) {
                std::cout << "  ";
            }
            if (i < level.size() - 1) {
                std::cout << "\\ ";
            }
        }
        std::cout << std::endl;
    }
}



// template<class T>
// void print(rbTree<T,int,int>* node) {
//   if (node == nullptr) return;

//   // Print the left subtree
//   print(node->left);

//   // Print the current node
//   std::cout << node << " ";

//   // Print the right subtree
//   print(node->right);
// }

int main()
{
    {
        ft::rbTree< pair<int,std::string> ,int,int > *root = new ft::rbTree< pair<int,std::string> ,int,int >();
        // root.put_data(make_pair(0,"root"));
        // root.put_left(make_pair(1,"lol"));
        // root.put_right(make_pair(2,"lel"));

        // std::cout << root.right << std::endl;
        // rbTree< pair<int,std::string> ,int,int > node;
        // node = root;
        // std::cout << node.left << std::endl;


        // if(make_pair(15,"rooty") < make_pair(18,"rooty"))
        //     std::cout << "yes\n";


        root = root->insert(make_pair(10,"rooty"));
        root = root->insert(make_pair(18,"rooty"));
        root = root->insert(make_pair(7,"rooty"));
        root = root->insert(make_pair(15,"rooty"));
        root = root->insert(make_pair(16,"rooty"));
        root = root->insert(make_pair(30,"rooty"));
        root = root->insert(make_pair(25,"rooty"));
        root = root->insert(make_pair(40,"rooty"));
        root = root->insert(make_pair(60,"rooty"));
        root = root->insert(make_pair(2,"rooty"));
        root = root->insert(make_pair(1,"rooty"));
        root = root->insert(make_pair(70,"rooty"));
        // root = root->insert(make_pair(9,"rooty"));
        // root = root->insert(make_pair(19,"rooty"));

        // root = root->find_node_key(14);
        root = root->delete_(70);
        
        printTree(root);
        // std::cout << root->find_node_key(13)->parent<< std::endl;
        // print(root);
    }
    // system("leaks a.out");
}
//check parent management of delete
//check height management after delete


//in fix height, balance after so for the minmax case, else balance normally through recursivity
