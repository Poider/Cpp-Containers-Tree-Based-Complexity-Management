#include <iostream>
#include "avl_tree.hpp"
#include "pair.hpp"

using namespace ft;

#include <iostream>
#include <vector>
#include <queue>

#include <iostream>
#include <string>


template<class T>
void print_tree_X(const avl<T,int,int>* root, int indent=0) {
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
void printTree(avl<T,int,int>* root) {
    if (root == NULL) {
        return;
    }

    std::queue<avl<T,int,int>*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();
        std::vector<avl<T,int,int> *> level;

        for (int i = 0; i < size; i++) {
            avl<T,int,int>* node = q.front();
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
            std::cout << level[i]->data->first <<"("   <<level[i]->height<<")";
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
// void print(avl<T,int,int>* node) {
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
        avl< pair<int,std::string> ,int,int > *root = new avl< ft::pair<int,std::string> ,int,int >();
        // root.put_data(make_pair(0,"root"));
        // root.put_left(make_pair(1,"lol"));
        // root.put_right(make_pair(2,"lel"));

        // std::cout << root.right << std::endl;
        // avl< pair<int,std::string> ,int,int > node;
        // node = root;
        // std::cout << node.left << std::endl;

        root = root->insert(make_pair(20,"rooty"));
        root = root->insert(make_pair(14,"rooty"));
        root = root->insert(make_pair(23,"rooty"));
        root = root->insert(make_pair(11,"rooty"));
        root = root->insert(make_pair(17,"rooty"));
        root = root->insert(make_pair(22,"rooty"));
        root = root->insert(make_pair(25,"rooty"));
        root = root->insert(make_pair(10,"rooty"));
        root = root->insert(make_pair(13,"rooty"));
        root = root->insert(make_pair(16,"rooty"));
        root = root->insert(make_pair(18,"rooty"));
        root = root->insert(make_pair(26,"rooty"));
        root = root->insert(make_pair(9,"rooty"));
        root = root->insert(make_pair(19,"rooty"));

        root = root->delete_(14);
        root = root->delete_(155);
        printTree(root);
        // std::cout << root->find_node_key(13)->parent<< std::endl;
        // print(root);
    }
    // system("leaks a.out");
}
//check parent management of delete
//check height management after delete


//in fix height, balance after so for the minmax case, else balance normally through recursivity
