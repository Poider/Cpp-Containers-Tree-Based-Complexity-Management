/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:04:14 by mel-amma          #+#    #+#             */
/*   Updated: 2023/01/16 15:29:08 by mel-amma         ###   ########.fr       */
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


#define PRINT_PAIR_REF(p)                                                                          \
    {                                                                                              \
        PRINT_LINE("Key:", (p).first);                                                             \
        PRINT_LINE("Value:", (p).second);                                                          \
    }

#define PRINT_BOUND(b, end)                                                                        \
    {                                                                                              \
        if (b != end) {                                                                            \
            PRINT_PAIR_REF(*b);                                                                    \
        } else {                                                                                   \
            PRINT_MSG("End iterator");                                                             \
        }                                                                                          \
        std::cout << std::endl;                                                                    \
    }

#define PRINT_EQ_RANGE(p, end)                                                                     \
    {                                                                                              \
        std::cout << "--------------------------------\n";                                         \
        PRINT_BOUND(p.first, end);                                                                 \
        PRINT_BOUND(p.second, end);                                                                \
    }

typedef ft::map<std::string, std::string, std::less<std::string> > strmap;


template <typename T>
void init_array_int_str(ft::pair<int, std::string>* arr, std::size_t size)
{
    std::string x[64] = { "CBCId4lUU6oYms60JkNr", "V5sbXjlqYRAV1C1LgJbt", "TPcK94z2htaoK5hWpR1j",
                          "WA1JMsjadjyjQjJLxVkE", "aDhJUsH7AVnKLfzQGcPC", "DPpRIm6G9C5CWSWYLwnt",
                          "aKyxvwuxzUAksmm7s8o3", "d8NpBFRFI87WxlYiRzJB", "5RDlRrY8OFBkqtlD5R33",
                          "W4dsiGdNWranxT1qbPt9", "uUxBDNzk3Tpg1bIow0uf", "FiKAXgTFhhPhmRkfXci9",
                          "02Fxrj1KnMufOpH1gbxw", "hSV7LrNPzTKHS6h7BRW6", "YzIjmI4i4Fum1gzs9QFy",
                          "6jjGwGu20C7dXFRgdCU8", "bej1zTuyCJGa0b4KXgQO", "ckkK36lt3kBVH1PYvbib",
                          "Gs9kLamEeSWqM9ORSlzF", "oJTGXtRpq4rz6IBt2Gc2", "6XSQM096yPnzWqydO7Fl",
                          "Kw91n77jigS09IQEYFw0", "K0Qj3EOV96U6xbBDMkaP", "i0b4NYygRb7ZuT3HOE61",
                          "C6KyCaoRm5MncGCjjP0I", "6xxl5c88m0Rq5CkTPsTU", "xtZ16NJzNU4IEnzsily8",
                          "2ofwuG2e80JGsK8VdB6r", "UjhRe94EahPlXuBbIV0q", "be5WTfjjKVBU8cezAjH8",
                          "zOWJPAQLV4wgVGJTC0uV", "nuqgXoNhZpL8uMvbDcT7", "HdCk0Gm8Gn3eqcVYxcYD",
                          "PuIS5xPbBpGe3MHG7SNm", "ZY6finqJMbHpB6dKlenn", "VJfBTOFj9reLm3iGU2Fs",
                          "UFWOX8UzTSzSAGMvGRIC", "cZfcw5yVwFprkH2v3FQO", "V34DSjjaiDianUKjRFCj",
                          "j7SHtomH6GvAY8y0nL9E", "3z82NvciqTwWW2Lp7MET", "S1BDCdeUHLIVB6I8zaIc",
                          "OkuQPNHq0AnYY9Pemxpn", "yH5J2tI4oQzVsPBB226z", "aafwp6lvuOxv5JkUBUlA",
                          "RjRwqlQ0hnxYnglid2x3", "3RBzhOIHFtRtZBHNlCVv", "lttYCjRWSXYKeyIgvpJv",
                          "6KhIc7LvaTTwklmmbjBO", "IDlAqFCEdFTJcVW36RsY", "pDGkqtvKVRReq19BFVwN",
                          "88UJAeNtrlAwEu4BGiSb", "eFN5bxsWa4dAnvZdzToE", "B3cqY0IqO2IH2yGMnX7e",
                          "BRcU6oFTAC8IWuiSrTEa", "dtBZVLQMx9MBw1eak8SB", "zM2XVrazn2fXAsRHDc16",
                          "qqlM2sERpGhcZJAv3qPR", "4Lru0dOIQpWGYlcx9oyn", "HSH0O0igQruyLC1FmQVs",
                          "mXHcnXiXhKJwJ0BUSpje", "sXhbSe7MQHhvJ9XQcrrX", "aTejup4iQw70n78erKEB",
                          "1IRLC9sfQI5AzDYeotLd" };

    for (std::size_t i = 0; i < size; ++i) {
        arr[i] = ft::make_pair(rand(), x[i]);
    }
}


template <typename T>
void init_array_str_str(ft::pair<std::string, std::string>* arr, std::size_t size)
{
    std::string x[32] = { "RxWAUMME3GtF9Zbv3a4M", "WC96vs7Z6I6TfdGxObUg", "2beuhrfBZvjdkmfqV9yn",
                          "AuIhF3lUgwT0OMy8DuUx", "dVW2KAL06gB4s7rEf508", "jnsp7MGfl5wZNZVfQSvp",
                          "p26Kfhz0Iof6rJDy27vc", "bnWXfp2eexq7MPpcmRSI", "tMEU0L6RNvqDAaV6HN0e",
                          "POcbaPteUMFfltrwdu7r", "epDGhJZoKoL4i1HO67XS", "o83N1RTIeOafqBfqeAYh",
                          "aYRtwuDT8k7k7iIfTrtU", "fEPXIREoFGKXqnNKySG5", "QrqmIbVVIQzf8WKBxiga",
                          "k5NSg0Dq0b9ewfrhYdy7", "Tf9dsqBADfMeWVQGG3Zk", "dS2LouElpUXsXNCClr4B",
                          "tsvf3JaWNg5JlSDZs1Dm", "oWurB8fBAIBQq1ZnlFiR", "8YllXP80XunEXhqnjkZc",
                          "Spt36tVcEkIFjwogWli0", "c25H1u6DF9RVdagn81DA", "AjWfT7TlXgzSKOywpoTH",
                          "ZwTg8WNnmXOJKdW6ZeJv", "E9aYpoCXd1kbSWhdLOnf", "QN1iAuoSNQ5WvHeSeSSL",
                          "7g5wfNllowIaqMUVjywr", "b38gJrosdk9xEQ2K8Gbu", "KdVdRVLHJg9Bazc4cpM7",
                          "COJeGmQEzjXwqKCAnd6J", "2k6XCpXEkP7QoST6uYoy" };

    std::string y[32] = { "TZ3QuE3ZNUbFrEpQhgcY", "BX2lyPzOWRIznb34T5OT", "v7lPrSeDokdBIUXR9QGh",
                          "nAQxkuEYL5k1Er7FspKu", "r8T4oZaWBI1m7sPBEDz3", "pdxM9tJrYZskZla7L7yM",
                          "dIIx6eKTfygu24SNKa32", "tw04BOo705mdWxuDciNO", "q94icFprhKrrFXLvjEN3",
                          "uM25BWUl14NTlTwFsNIv", "2oTV9fXUESLQqzvsPFmd", "W6ASLRzrlOggx5b7CtYN",
                          "bz4BQ7rLU203RNwwmbMK", "jfWgRPiuy1P3NGDPWmbe", "PgtdYLdGuneYEUgMA8SB",
                          "eaaFugCSOOU5my4y4SkG", "gGd4FiUEJwgvhOCSHu9g", "9K0ZhqlbyDCJXYXHoEIN",
                          "VTmk8m7rbEGl8ntGpTCQ", "eRJ98PUF2tSMX6zpDOi4", "wFMJIDAbjYnJkxMxkAtL",
                          "JCOXV4iPcIt72DcNnbuY", "LsnOUrHHD2FNFH5DMvbc", "YVPp2jPqK3jmif7yY14r",
                          "JBMhRRtLY3QX3x1ZVDCs", "Uwo5PD2RLMx5ByW9Rscq", "O4Q6DPBJHOelMtBKc9GQ",
                          "Bq0H2eqnuCYqyj9F5Lkn", "P2fJf0TYN92iUXkwELjG", "f656ltXlumpc7YyPVjan",
                          "YQfr76LAA1xKokfq8HpL", "6utvLeZ9t0IM4OkdfAQ2" };

    for (std::size_t i = 0; i < size; ++i) {
        arr[i] = ft::make_pair(x[i], y[i]);
    }
}


int main()
{
    
    std::size_t intstr_size = 64;                                                                  \
    std::size_t strstr_size = 32; 
    ft::pair<int, std::string> intstr_arr[64];                                              \
    init_array_int_str<void>(intstr_arr, 64);                                                      \
    ft::pair<std::string, std::string> strstr_arr[32];                                      \
    init_array_str_str<void>(strstr_arr, 32);                                                                 \
    (void)intstr_arr;                                                                              \
    (void)strstr_arr;                                                                              \
    (void)intstr_size;                                                                             \
    (void)strstr_size;



   {
        strmap m(strstr_arr, strstr_arr + 16);

        strmap::iterator it = m.find("Hello");

        if (it != m.end()) {
            PRINT_PAIR_REF(*it);
        }

        try {
            std::string& ref = m.at("World!");

            PRINT_LINE("Val:", ref);
        } catch (std::out_of_range& e) {
            PRINT_MSG("Exception");
        }
     
        m.insert(strstr_arr, strstr_arr + strstr_size);

        PRINT_LINE("size", m.size());
        PRINT_LINE("upper bound : ", (m.upper_bound("as"))->first);
        

        m.erase(m.begin());


        it = m.begin();
        std::advance(it, 10);

        m.erase(it, m.end());


        strmap::size_type s = m.erase("1234");

        PRINT_LINE("S:", s);

        m.clear();


        it = m.insert(m.begin(), ft::make_pair("",""));

        PRINT_LINE("Count:", m.count(""));


        m.insert(strstr_arr, strstr_arr + strstr_size);

        strmap n(strstr_arr, strstr_arr + 10);

        m.swap(n);



        PRINT_LINE("Find:", m.find("hello") != m.end() ? m.find("hello")->first : "End");

        PRINT_LINE("Find:", m.find("hello") != m.end() ? m.find("hello")->first : "End");



        
    }

    {
        ft::map<int, int, std::less<int> >
            m;

        for (int i = 0; i < 50000; ++i) {
            m.insert(ft::make_pair(rand(), rand()));
        }
        ft::map<int,int, std::less<int> >::iterator it = m.begin();
        ft::map<int,int, std::less<int> >::iterator end = m.begin();
        std::advance(it,300);
        std::advance(end,310);

        for(; it != end; it++)
        {
            PRINT_MSG(it->first);
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
            PRINT_MSG(it->first);
        }


        m.erase(m.begin(), m.end());
        PRINT_LINE("size after deletion of all :", m.size());
    }

     
}