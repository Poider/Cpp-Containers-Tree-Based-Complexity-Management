#include <iostream>

using namespace std;

struct test{
    int a;
    char b;
    string c;
    test(){};
};

int main()
{
    test *testing;
    testing = new test[3];

    testing[0].a = 0;
    testing[0].b = 'a';
    testing[0].c = "sup";

    testing[1].a = 1;
    testing[1].b = 'b';
    testing[1].c = "duck";
    
    testing[2].a = 3;
    testing[2].b = 'c';
    testing[2].c = "cuck";

    testing = testing + 2;
    // testing = testing + 1;
    cout << testing->a;

    // delete[] testing;

}