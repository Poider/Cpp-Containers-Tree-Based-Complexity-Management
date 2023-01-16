#include <vector>
#include <iostream>

int main()
{

    // std::vector<int> lines(3,1);
    // std::vector<int>::iterator it = lines.begin();
    // std::vector<int>::iterator ende = lines.end();
    // lines.clear();
    // lines.assign(4,2);
    // std::cout << *it;
    // std::cout << lines[0] << std::endl;
    // for(; it != ende; it++)
    // {
    //     std::cout << *it << std::endl;
    // }

    using namespace std;

    allocator<string> alloc;
    string *str = alloc.allocate(3);
    alloc.construct(str,"hi");
    alloc.construct(str + 1,"hii");
    alloc.construct(str + 2,"hiii");
    alloc.destroy(str);
    cout << str[0];

}