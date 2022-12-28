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
{
    ft::map<std::string,std::string> m;
    m["h"] = "a";
    m["s"] = "b";
    // m.erase("s");
    // ft::map<std::string,std::string> st(m);
    // std::string s = st.at("s");
    // std::cout << s << std::endl;
    // ft::map<int,int> v;

    // m.insert(ft::make_pair("h","a"));
    // m.insert(ft::make_pair("s","b"));

    // m[20] = 13;
    // m[21] = 12;
    // m[22] = 15;
    // m[23] = 16;
    // auto x = it.operator->();
    // m.insert(make_pair(20,100));
    // m[20] = 100;
    ft::map<std::string,std::string>::const_iterator it = m.begin();
    // it--;
    // it--;
    // v = m;
    // it = v.end();
    // it --;
    // cout << (m.begin()->first) << std::endl;
    // cout << m.begin()->first <<  " " << m.begin()->second << endl;
    while(it != m.end())
    {
        std::cout << it->first << " " << it->second << std::endl;
        it++;
    }
}

// system("leaks a.out");
}