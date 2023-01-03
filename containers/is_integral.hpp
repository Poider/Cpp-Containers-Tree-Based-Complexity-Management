#ifndef _is_integral
#define _is_integral

//you can send a value of some type or a parameter or a type, through templates
namespace ft{


template< class T, T V >
struct base_integral
{
    const static T value = V;
};

typedef  base_integral<bool, true> true_type;
typedef  base_integral<bool, false> false_type;

template<typename T>
struct is_integral : false_type{};

template<>
struct is_integral<int> : true_type{};

template<>
struct is_integral<unsigned int> : true_type{};





template<>
struct is_integral<bool> : true_type{};

template<>
struct is_integral<char> : true_type{};

template<>
struct is_integral<signed char> : true_type{};


template<>
struct is_integral<unsigned char> : true_type{};

template<>
struct is_integral<char16_t> : true_type{};

template<>
struct is_integral<char32_t> : true_type{};

template<>
struct is_integral<wchar_t> : true_type{};

template<>
struct is_integral<short> : true_type{};

template<>
struct is_integral<unsigned short int> : true_type{};



template<>
struct is_integral<long> : true_type{};


template<>
struct is_integral<unsigned long> : true_type{};


template<>
struct is_integral<long long> : true_type{};

}
#endif