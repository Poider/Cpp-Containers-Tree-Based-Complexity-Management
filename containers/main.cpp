#include <iostream>
#include <vector>
#include <initializer_list>
using namespace std;
class inter{
    int a;
    public:
    inter(int a): a(a) {};
    void print()
    {
        cout << this->a << endl;
    };
    friend inter operator+(inter a, int b);
    friend inter operator+(int b, inter a);
};
     inter operator+(inter a, int b)
     {
        return inter(a.a + b);
     }
     inter operator+(int b, inter a)
     {
        return inter(a.a + b);
     }

int main()
{
    // allocator<int> myalloc;

    // vector<int> a(10,1);
    
    // vector<int>::iterator itB = a.begin();
    // int b = 5;
    // int c = 4;
    // a.insert(itB,3);
    // itB = a.begin(); 
    // itB++;
    // // cout << itB;
    // a.insert(itB,4);
    // // a.insert(itB++,b);
    // // a.insert(itB++,b);
    // vector<int>::iterator it = a.end();
    // it--;
    // for(;it!= a.begin();it--)
    // cout << *it;
    // cout << *it;
    // //will segfault cus vector will re allocate each time so that ptr is freed already

    // inter test(1);

    inter test = 3 + inter(1);
    test.print();

}