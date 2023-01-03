#include "stack.hpp"

int main()
{
    ft::stack<int> a;
    a.push(4);
    a.push(3);

    a.push(5);

    ft::stack<int> b(a);
    std::cout << b.size() << std::endl;
    std:: cout << b.top() << std::endl;
    system("leaks a.out");
}