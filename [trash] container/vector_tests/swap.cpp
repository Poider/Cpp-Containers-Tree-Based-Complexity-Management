#include <vector>
#include <iostream>

using namespace std;
int main()
{
    std::vector<int> a(3,5);
    std::vector<int> b(3,9);
    a == b;
    std::vector<int>::iterator it = a.begin();
    a.swap(b);
    std::vector<int>::iterator it1 = a.begin();
    cout << *it <<  "\n" << *it1 << "\n"; 
}