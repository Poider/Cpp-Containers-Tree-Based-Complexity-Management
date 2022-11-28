#include <iostream>
using namespace std;

struct test
{
    int *a;
    struct test *next;
    test(){
        a = new int();
    }
    void add(int s){
        struct test tt;
    // no
        next = &tt;
    }
    ~test() {
        cout << "destructor called" << endl;
    }
};

int main()
{
    test t;
    
}