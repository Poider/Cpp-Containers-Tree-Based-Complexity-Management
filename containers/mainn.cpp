#include "iterator_traits.hpp"
#include <type_traits>
// #include <map>
#include "map.hpp"
using namespace std;
int main()
{
    // typedef  ft::iterator_traits<std::allocator<int>::pointer>::pointer a;
    // typedef  ft::iterator_traits<std::allocator<int>::const_pointer>::pointer b;

    // bool t = std::is_same<a,b>::value;
    // std::cout << t << std::endl;

    ft::map<int,int> m;
    m.insert(ft::make_pair(1,1));
    // m[20] = 13;
    // m[21] = 12;
    // m[22] = 15;
    // m[23] = 16;
    // auto x = it.operator->();
    // m.insert(make_pair(20,100));
    // m[20] = 100;
    ft::map<int,int>::iterator it = m.end();
    // it--;
    it--;
    
    cout << it->first <<  " " << it->second << endl;
}