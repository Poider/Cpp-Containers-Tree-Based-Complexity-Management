#include <vector>
#include <iostream>

int main()
{
    std::vector<int> vec(5);
    std::allocator<int> alloc;
    std::cout << vec.max_size() << std::endl;
    std::cout << vec.max_size() << std::endl;
    alloc.max_size();
}