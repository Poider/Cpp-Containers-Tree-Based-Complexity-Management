#include <iostream>

using namespace std;

struct s
{
    string a;
    int b;
};

struct s1
{
    char a;
    string *b;
};

int main()
{
    string *newS = new string("hii");
    s t;
    t.a = "test";
    t.b = 44;
    s1 t1;
    t1.a = 'a';
    t1.b = newS;

    s1 *t2 = reinterpret_cast<s1 *> (&t);
    std::cout << t2->a << " " << *(t2->b) << std::endl;

}