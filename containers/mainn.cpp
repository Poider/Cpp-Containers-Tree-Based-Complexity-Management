#include "iterator_traits.hpp"
#include <type_traits>
// #include <map>
#include "map.hpp"
#include <set>
using namespace std;
    void init_array_int_str(ft::pair<int, std::string>* arr, std::size_t size)
{
    std::string x[64] = { "CBCId4lUU6oYms60JkNr", "V5sbXjlqYRAV1C1LgJbt", "TPcK94z2htaoK5hWpR1j",
                          "WA1JMsjadjyjQjJLxVkE", "aDhJUsH7AVnKLfzQGcPC", "DPpRIm6G9C5CWSWYLwnt",
                          "aKyxvwuxzUAksmm7s8o3", "d8NpBFRFI87WxlYiRzJB", "5RDlRrY8OFBkqtlD5R33",
                          "W4dsiGdNWranxT1qbPt9", "uUxBDNzk3Tpg1bIow0uf", "FiKAXgTFhhPhmRkfXci9",
                          "02Fxrj1KnMufOpH1gbxw", "hSV7LrNPzTKHS6h7BRW6", "YzIjmI4i4Fum1gzs9QFy",
                          "6jjGwGu20C7dXFRgdCU8", "bej1zTuyCJGa0b4KXgQO", "ckkK36lt3kBVH1PYvbib",
                          "Gs9kLamEeSWqM9ORSlzF", "oJTGXtRpq4rz6IBt2Gc2", "6XSQM096yPnzWqydO7Fl",
                          "Kw91n77jigS09IQEYFw0", "K0Qj3EOV96U6xbBDMkaP", "i0b4NYygRb7ZuT3HOE61",
                          "C6KyCaoRm5MncGCjjP0I", "6xxl5c88m0Rq5CkTPsTU", "xtZ16NJzNU4IEnzsily8",
                          "2ofwuG2e80JGsK8VdB6r", "UjhRe94EahPlXuBbIV0q", "be5WTfjjKVBU8cezAjH8",
                          "zOWJPAQLV4wgVGJTC0uV", "nuqgXoNhZpL8uMvbDcT7", "HdCk0Gm8Gn3eqcVYxcYD",
                          "PuIS5xPbBpGe3MHG7SNm", "ZY6finqJMbHpB6dKlenn", "VJfBTOFj9reLm3iGU2Fs",
                          "UFWOX8UzTSzSAGMvGRIC", "cZfcw5yVwFprkH2v3FQO", "V34DSjjaiDianUKjRFCj",
                          "j7SHtomH6GvAY8y0nL9E", "3z82NvciqTwWW2Lp7MET", "S1BDCdeUHLIVB6I8zaIc",
                          "OkuQPNHq0AnYY9Pemxpn", "yH5J2tI4oQzVsPBB226z", "aafwp6lvuOxv5JkUBUlA",
                          "RjRwqlQ0hnxYnglid2x3", "3RBzhOIHFtRtZBHNlCVv", "lttYCjRWSXYKeyIgvpJv",
                          "6KhIc7LvaTTwklmmbjBO", "IDlAqFCEdFTJcVW36RsY", "pDGkqtvKVRReq19BFVwN",
                          "88UJAeNtrlAwEu4BGiSb", "eFN5bxsWa4dAnvZdzToE", "B3cqY0IqO2IH2yGMnX7e",
                          "BRcU6oFTAC8IWuiSrTEa", "dtBZVLQMx9MBw1eak8SB", "zM2XVrazn2fXAsRHDc16",
                          "qqlM2sERpGhcZJAv3qPR", "4Lru0dOIQpWGYlcx9oyn", "HSH0O0igQruyLC1FmQVs",
                          "mXHcnXiXhKJwJ0BUSpje", "sXhbSe7MQHhvJ9XQcrrX", "aTejup4iQw70n78erKEB",
                          "1IRLC9sfQI5AzDYeotLd" };

    for (std::size_t i = 0; i < size; ++i) {
        arr[i] = ft::make_pair(rand(), x[i]);
    }
}
int main()
{
    // typedef  ft::iterator_traits<std::allocator<int>::pointer>::pointer a;
    // typedef  ft::iterator_traits<std::allocator<int>::const_pointer>::pointer b;

    // bool t = std::is_same<a,b>::value;
    // std::cout << t << std::endl;
{

    
    // m["h"] = "a";
    // m["s"] = "b";
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
    ft::pair<int, std::string> intstr_arr[64];                                              \
    init_array_int_str(intstr_arr, 64);
    ft::map<int,std::string> m(intstr_arr, intstr_arr + 25);
    ft::map<int,std::string> ss;
    ft::map<int,std::string>::iterator it = m.begin();
    it = m.end();
    it--;
    if(ss == m)
        std::cout <<"hi";

    std::set<int> a;
    std::set<int>::iterator itrr;
    auto x = itrr.operator->();
    if(a != a)
    ;
    // ft::map<int,std::string>::reverse_iterator itr = m.rbegin();
    //  for (itr = m.rbegin(); itr != m.rend(); ++itr) {
        
    //        std::cout << itr->first<< std::endl;
    //     }
    //     ++itr;
    // std::cout << itr->first  << std::endl;
    // std::cout << it->first  << std::endl;

    // for (it = m.begin(); it != m.end(); it = m.begin()) 
    // {
   
    //         m.erase(it);
    //     // ft::map<int,std::string>::iterator it1 = m.begin();
    //     // while(it1 != m.end())
    //     // {
    //     //     std::cout << it1->first << " " << it1->second << std::endl;
    //     //     it1++;
    //     // }
    //     // std::cout << " " << std::endl;
    // }
    // it--;
    // it--;
    // v = m;
    // it = v.end();
    // it --;
    // cout << (m.begin()->first) << std::endl;
    // cout << m.begin()->first <<  " " << m.begin()->second << endl;
    // it = m.begin();
    // while(it != m.end())
    // {
    //     std::cout << it->first << " " << it->second << std::endl;
    //     it++;
    // }


}

// system("leaks a.out");
}