#include <iostream>
#include <list>


int main()
{
    std::list a{1,2,3};
    std::list<int>::iterator it;

    it = a.begin();
    it++;
    // for(;it!=a.end();it++)
    // std::cout << *it<<std::endl;

    if(it > a.begin())
    std::cout << "on";
    else
    std::cout << "off";
}