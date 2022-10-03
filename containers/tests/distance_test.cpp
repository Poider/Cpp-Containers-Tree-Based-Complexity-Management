#include <iostream>
#include <vector>

int main()
{
    // std::vector<int> a;
    // std::vector<int>::iterator it1 = a.begin();
    // a.insert(it1,1);
    // it1 = a.begin();
    // a.insert(it1,2);

    // std::vector<int> b(a.begin(), a.end());

    // std::vector<int>::iterator it = b.begin();
    // for(;it!= b.end();it++)
    // {
    //     std::cout << *it;
    // }
    std::vector<int> a(10);
    a.insert(a.begin(),1);
    std::cout << a.capacity();

}