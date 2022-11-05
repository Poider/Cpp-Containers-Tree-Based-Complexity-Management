#include <vector>
#include <iostream>

using namespace std;
int main()
{
    vector<int> a;
    vector<int> b;
    // a.pop_back();
    a.reserve(7);
    a.assign(7,3);
    cout << a.capacity() << std::endl;
    a.resize(8);
    a.at(100);
    // a.push_back(12);
    // vector<int>::iterator it = a.begin();
    // cout << distance(a.begin(),it) << endl;
    cout << a.size() << std::endl;

}