# include <iostream>
#include <string>

class tt{
    int a;
    void print(){

    }
    friend class vv;
};

class vv{
public:
void printi()
{
    tt a;
    std::cout << a.a;
    a.print();
}

};
int main()
{
    tt test;
    vv test1;

    // test.print();
    test1.printi();
}