#include <vector>
#include <iostream>

using namespace std;
int main()
{
    vector<int> a;
    vector<int> b;
    a.reserve(10);
    a.assign(7,3);
    vector<int>::iterator it = a.erase( a.begin()+3, a.end());
    cout << distance(a.begin(),it) << endl;
    // vector<int>::iterator it = a.begin();
    // b.assign(a.begin(), a.begin());
    // cout << b.size();
    // cout << *it << endl;
    // a.assign(6,4);
    // cout << a.capacity() <<endl;
    // cout << *it;
    // a.erase(it +1, it );
    // cout << 
}