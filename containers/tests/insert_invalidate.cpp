#include <vector>
#include <iostream>

using namespace std;

int main()
{
    allocator<int> alloc;
    vector<int> numbers(2,2);

    numbers.reserve(5);
    // cout << *(numbers.end() + 1);
    // throw std::overflow_error("overflow");
    vector<int>::iterator end = numbers.end();
    vector<int>::iterator it = numbers.begin();
    vector<int>::iterator itest = it + 1;
    // numbers.insert(numbers.end()  + 1, 4);
    cout << std::distance(it,it);
    // cout << *itest;
    // cout << *end;
    // for(;it!=numbers.end();it++)
    // {
    //     cout << *it << " ";
    // }

    // if((numbers.end() + 3) > end)
    // cout << "bigger";
}

//iterator pos should be above size or return exception
//reallocate if capacity < size + 1;