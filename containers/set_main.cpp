#include "iterator_traits.hpp"
#include <type_traits>
// #include <map>
#include "set.hpp"

    


int main()
{
    // std::string str_arr[32] = {                                                                    \
    //     "QExoqp0nICr0sXsHqty2", "naax9QcpJhvaL7DezsNQ", "25ZTtB6wbptfbxM8AvHB",                    \
    //     "tShYNtc0MkdjqLrOatgz", "7Z3kf1Qec0NnsLSEpbOt", "WhkSNrKJC966fvjZ2Or1",                    \
    //     "8vlxlFRRgW7yYj4GO7dt", "5sq1aoT8zP0HaHj3nFOK", "61Dv31GYZhkgjKCErpng",                    \
    //     "l0IIcWWHhOcPzoxEamQM", "bE1RYclskwXlhCm46YFs", "kXeoi5qz94JYPqSDTs79",                    \
    //     "TFsQP1dz8VVos9KzUpY0", "b3wYQR7An193gjgYuRj3", "xSmyNsnSJ47jLqrvbpyr",                    \
    //     "guAIP2Wq43Gf8VhHsyu5", "yT6c2loPebHovnq9BQog", "3qvU1xcVm2g1DKFDlqh4",                    \
    //     "L0q8RR9P41VD4sVjdnWl", "YdjESsIZM4b1oGQPjpBe", "l1ZVQbWKw7brHUSimJgq",                    \
    //     "xdn0cf4vqRzpfXWtl10G", "lYnZvpqaV0s8DowMZwzV", "8P1cyKrwJNLoJyvLjYqO",                    \
    //     "4MhOXNbAX23CEijO5cRT", "tHe3miAwCOVQbuoLaEP2", "l6uNLsc8fiLl3eWoG6j6",                    \
    //     "477xt6l0lph9ALQdr4HX", "D9UJNe4s8YF02LhrwOdl", "dLCisBNOdE8yugntu6cj",                    \
    //     "YvY4aQFHgAuagn4dFLO1", "eGR6Dtv7LW75qlV5Fkik"                                             \
    // };     
    // ft::set<std::string> a(str_arr,str_arr+ 2);
    // ft::set<std::string> b;

    // a.insert(4);
    // ft::set<std::string>::iterator it = a.begin();
    // b = a;
    // std::cout << *it << std::endl;
    // it = b.begin();
    // std::cout << *it << std::endl;

        ft::set<int> m;
        m.insert(23);
        m.insert(25);
        m.insert(1);
        m.insert(2);
        m.insert(3);
        m.insert(75);
        m.insert(30);
        m.insert(-22);
        m.insert(-23);
        m.insert(0);
        size_t size = m.erase(2);

}