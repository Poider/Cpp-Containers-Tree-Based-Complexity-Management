#include <iostream>

int main()
{
    size_t _size = 5;
    size_t position = 2;
    int container[5] = {1,2,3,4,5};
    for(size_t i = _size; i > position; i--)
        container[i] = container[i - 1];
    container[position] = -1;

    for(size_t i = 0 ; i < _size; i++)
        std::cout << container[i] << " ";
}