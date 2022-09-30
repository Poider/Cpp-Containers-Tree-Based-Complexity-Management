#include <iostream>
#include <vector>
#include <initializer_list>
using namespace std;
class inter{
    
    public:int a;
    inter(int a): a(a) {};
    void print()
    {
        cout << this->a << endl;
    };
    const inter* operator->() const{ return this;}
   inter operator+( int b)
   {
    this->a += b;
   };
    friend inter operator+(int b, inter a);
};
    //  inter operator+(inter a, int b)
    //  {
    //     return inter(a.a + b);
    //  }
     inter operator+(int b, inter a)
     {
        return inter(a.a + b);
     }



int main()
{
    allocator<int> myalloc;

    vector<int> a(3,1);
    
    vector<int>::iterator itB = a.begin();
    int b = 5;
    int c = 4;
    for(int i = 0;i < 5;i++)
        {
            itB = a.begin();
            a.insert(itB,i);
        }
    itB = a.begin();
   for(;itB != a.end();itB++)
        cout << *itB << " ";
    cout << endl;
    itB = a.begin();
    itB++;
    cout << itB[7];


    // inter test(1);
    inter test( inter(1) + 3);
    // int c = test->a;

    // test.print();

}