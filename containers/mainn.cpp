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
    m[21] = 12;
    m[22] = 15;
    m[23] = 16;
    // auto x = it.operator->();
    // m.insert(make_pair(20,100));
    m[20] = 100;
    std::map<int,int>::iterator it = m.begin();
    cout << it->first <<  " " << it->second << endl;
}