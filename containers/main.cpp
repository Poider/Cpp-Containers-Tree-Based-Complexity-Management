#include <iostream>
#include "vector.hpp"
#include <vector>
#include <initializer_list>
#include <algorithm>
#include <iterator>
#include <list>
using namespace std;

// class inter{
    
//     public:int a;
//     inter(int a): a(a) {};
//     void print()
//     {
//         cout << this->a << endl;
//     };
//     const inter* operator->() const{ return this;}
//    inter operator+( int b)
//    {
//     this->a += b;
//    };
//     friend inter operator+(int b, inter a);
// };
//     //  inter operator+(inter a, int b)
//     //  {
//     //     return inter(a.a + b);
//     //  }
//      inter operator+(int b, inter a)
//      {
//         return inter(a.a + b);
//      }


    //    std::cout << "___" <<position << std::endl;
int main()
{
                        // std::vector<int>::iterator it3;
                        // std::vector<string>::iterator it4;
                        // it3 = it4;

    ft::vector<int> tt;
    
    ft::vector<int> a((size_t)3,3);
    // std::vector<int> b;
    ft::vector<int>::iterator it;
    it = a.begin();
    ft::vector<int>::iterator it1;
    it1 = it;
    cout << *it1;
    // it = 1 + it;
    // it++;
    // b.assign((size_t)10,1);
    // a.assign(b.begin(),b.end());
    // a.reserve(10);
    // a.push_back(1);
    // a.push_back(2);
    // a.push_back(3);
    // a.push_back(4);
    // a.push_back(5);
    // a.push_back(6);
    // a.pop_back();
    // it = a.begin();
    // for(;it != a.end();it++)
    //     std::cout << *it << std::endl;
    // ft::vector<int>::reverse_iterator Ritt = a.rbegin();
    // for(;Ritt!= a.rend();Ritt++)
    // std::cout << *(Ritt) << std::endl;

    // ft::vector<int> c(a);
    //  ft::vector<int> c;

    // ft::vector<int>::iterator itt = a.begin();
    // a.insert(a.end(),12);
    // a.insert(a.end(),(size_t)2,12);
    // a.erase(a.end() -2  );
    // a.erase(a.begin() + 1,a.end() -2);
    // a.resize(3);
    // a.clear();

    // c = a;
    // itt = c.begin();
    // for(;itt!= c.end();itt++)
    //     std::cout << *(itt) << std::endl;
    // /*Or */
    // for(;itt!= a.end();itt++)
    // std::cout << *(itt) << std::endl;

    // std::cout <<"size : " <<a.size()<< std::endl;
    // std::cout << a.capacity()<< std::endl;

    // std::cout << std::distance(a.begin() + 2, a.begin() + 3);
//     vector<int> a(3,1);
    
//     vector<int>::iterator itB = a.begin();
//     int b = 5;
//     int c = 4;
//     for(int i = 0;i < 5;i++)
//         {
//             itB = a.begin();
//             a.insert(itB,i);
//         }
//     itB = a.begin();

//     vector<int>::reverse_iterator itC = a.rbegin();
//     // for(;itC != a.rend();itC++)
//     //     cout << *itC << " ";
// //     cout << *(itC + 3) << "\n";
// //    for(;itB != a.end();itB++)
// //         cout << *itB << " ";

// itC+= 3;
// std :: cout << *itC << std::endl;


// if ((itC + 3) > itC)
// std::cout << "reverse comparison";

//     cout << endl;
//     itB = a.begin();
//     itB++;
//     cout << itB[7];


    // const inter test( inter(1) + 3);
    // int c = test->a;
    // test->a;
    // test.print();

}