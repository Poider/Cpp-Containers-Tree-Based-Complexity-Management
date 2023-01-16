#include <iostream>
#include <vector>

using namespace std;
int main()
{
    // vector<int> vec = vector<int>();

    // cout << vec.size() << endl;

    allocator<int> alloc;
    int *a;
    int c = 1;
    int b = c;
    a = alloc.allocate(1);
    alloc.construct(a,3);
    cout << *a;
}