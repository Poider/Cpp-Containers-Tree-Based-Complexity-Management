#include <vector>
#include "vector.hpp"
#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))


int main()
{
     {
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");          // fill constructor
        // std::vector<std::string> v2;                         // empty constructor
        std::vector<std::string> v3(v1.begin(), v1.end());   // range constructor with normal iterators
        // std::vector<std::string> v4(v3);                     // copy constructor
        // std::vector<std::string> v5(v1.rbegin(), v1.rend()); // range constructor with reverse iterators
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string2");
        // ft::vector<std::string> ft_v2;
        ft::vector<std::string> ft_v3(ft_v1.begin(), ft_v1.end());
        // ft::vector<std::string> ft_v4(ft_v1);
        // ft::vector<std::string> ft_v5(ft_v1.rbegin(), ft_v1.rend());
        /*----------------------------------------------------*/
        std::cout << v3.capacity() << " " << ft_v3.capacity() << std::endl;
        // EQUAL(v1.capacity() == ft_v1.capacity() && v2.capacity() == ft_v2.capacity() && v3.capacity() == ft_v3.capacity() && v4.capacity() == ft_v4.capacity() && v5.capacity() == ft_v5.capacity());
    }
}