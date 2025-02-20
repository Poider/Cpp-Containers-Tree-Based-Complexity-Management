#include <iostream>
#include <string>

using namespace std;

struct test{
    typedef test abc;
    int s;
};

template<typename T>
class testy
{
    int *numb;
    public:
    typedef const typename test::abc& inter;
    testy(int num) : numb(new int(num)) {};
    inter ret()
    {
        test *a = new test;
        a->s = 12;
        return (*a);
    }

};

int main(int argc, char **argv)
{
    int a;
    testy<int> aa(21);

    cout << aa.ret().s;
    // n = 12;
    // cout << aa.ret() << endl;

}