/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:04:14 by mel-amma          #+#    #+#             */
/*   Updated: 2023/01/16 15:06:35 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../containers/stack.hpp"
#include "../containers/map.hpp"
#include "../containers/set.hpp"
#include "../containers/vector.hpp"




#define PRINT_LINE(msg, value)                                                                     \
    {                                                                                              \
        std::cout << msg << " " << (value) << std::endl;                                                        \
    }

#define PRINT_MSG(msg)                                                                             \
    {                                                                                              \
        std::cout << msg << std::endl;                                                                          \
    }

typedef ft::set<std::string> strset;
  
int main()
{
    std::size_t int_size = 64;                                                                     \
    std::size_t str_size = 32;  
    (void)int_size;                                                                                \
    (void)str_size;  
    
    std::string str_arr[32] = {                                                                    \
        "QExoqp0nICr0sXsHqty2", "naax9QcpJhvaL7DezsNQ", "25ZTtB6wbptfbxM8AvHB",                    \
        "tShYNtc0MkdjqLrOatgz", "7Z3kf1Qec0NnsLSEpbOt", "WhkSNrKJC966fvjZ2Or1",                    \
        "8vlxlFRRgW7yYj4GO7dt", "5sq1aoT8zP0HaHj3nFOK", "61Dv31GYZhkgjKCErpng",                    \
        "l0IIcWWHhOcPzoxEamQM", "bE1RYclskwXlhCm46YFs", "kXeoi5qz94JYPqSDTs79",                    \
        "TFsQP1dz8VVos9KzUpY0", "b3wYQR7An193gjgYuRj3", "xSmyNsnSJ47jLqrvbpyr",                    \
        "guAIP2Wq43Gf8VhHsyu5", "yT6c2loPebHovnq9BQog", "3qvU1xcVm2g1DKFDlqh4",                    \
        "L0q8RR9P41VD4sVjdnWl", "YdjESsIZM4b1oGQPjpBe", "l1ZVQbWKw7brHUSimJgq",                    \
        "xdn0cf4vqRzpfXWtl10G", "lYnZvpqaV0s8DowMZwzV", "8P1cyKrwJNLoJyvLjYqO",                    \
        "4MhOXNbAX23CEijO5cRT", "tHe3miAwCOVQbuoLaEP2", "l6uNLsc8fiLl3eWoG6j6",                    \
        "477xt6l0lph9ALQdr4HX", "D9UJNe4s8YF02LhrwOdl", "dLCisBNOdE8yugntu6cj",                    \
        "YvY4aQFHgAuagn4dFLO1", "eGR6Dtv7LW75qlV5Fkik"                                             \
    };            
                                                                                     \
    (void)str_arr;
     {
        strset m(str_arr, str_arr + 16);

        strset::iterator it = m.find("Hello");

        if (it != m.end()) {
            PRINT_LINE("find It:", *it);
        }

        it = m.find("guAIP2Wq43Gf8VhHsyu5");
        if (it != m.end()) {
            PRINT_LINE("find It:", *it);
        }

        m.insert(str_arr, str_arr + str_size);

        PRINT_LINE("size", m.size());
        PRINT_LINE("upper bound : ", *(m.upper_bound("as")));
        

        m.erase(m.begin());


        it = m.begin();
        std::advance(it, 10);

        m.erase(it, m.end());


        strset::size_type s = m.erase("1234");

        PRINT_LINE("S:", s);

        m.clear();


        it = m.insert(m.begin(), "");

        PRINT_LINE("Count:", m.count(""));


        m.insert(str_arr, str_arr + str_size);

        strset n(str_arr, str_arr + 10);

        m.swap(n);



        PRINT_LINE("Find:", m.find("hello") != m.end() ? *m.find("hello") : "End");

        PRINT_LINE("Find:", m.find("hello") != m.end() ? *m.find("hello") : "End");
    }

    {
        ft::set<int, std::less<int> > m;

        for (int i = 0; i < 15000; ++i) {
            m.insert(rand());
        }

        ft::set<int, std::less<int> >::iterator it = m.begin();
        ft::set<int, std::less<int> >::iterator end = m.begin();

        std::advance(it,300);
        std::advance(end,310);

        for(; it != end; it++)
        {
            PRINT_MSG(*it);
        }
        it--;
        --it;
        m.erase(it);

        it = m.begin();
        end = m.begin();
        std::advance(it,300);
        std::advance(end,310);
        
        PRINT_MSG("Set after erase 1 element");
        for(; it != end; it++)
        {
            PRINT_MSG(*it);
        }


        m.erase(m.begin(), m.end());
        PRINT_LINE("size after deletion of all :", m.size());


    }
}