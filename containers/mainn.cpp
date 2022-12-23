#include "iterator_traits.hpp"
#include <type_traits>
#include <map>
using namespace std;
int main()
{
    // typedef  ft::iterator_traits<std::allocator<int>::pointer>::pointer a;
    // typedef  ft::iterator_traits<std::allocator<int>::const_pointer>::pointer b;

    // bool t = std::is_same<a,b>::value;
    // std::cout << t << std::endl;

    std::map<int,int> m;
    m[20] = 13;
    std::map<int,int>::iterator it = m.begin();
    auto x = it.operator->();
}