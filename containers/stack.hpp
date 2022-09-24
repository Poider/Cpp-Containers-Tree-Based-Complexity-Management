#ifndef _my_stack
#define _my_stack

#include <deque>
#include <stack>
namespace std {
  template<class T, class Container = deque<T>>
  class stack {
  public:

    typedef Container                                container_type;
    typedef typename container_type::value_type      value_type;
    typedef typename container_type::reference       reference;
    typedef typename container_type::const_reference const_reference;
    typedef typename container_type::size_type       size_type;
 
  protected:
    Container c;//
 
  public:
  // >>>> member funcs
    explicit stack( const Container& cont = Container() );
    stack( const stack& other )0;
    ~stack();
    stack& operator=( const stack& other );

    //>>access elements
    reference top();
    const_reference top() const;

    //>>>>>>capacity
    bool empty() const;
    size_type size() const;
    
    //>>>> modifiers
    void push( const value_type& value );
    void pop();

    //>>>>>> nonmemeber funcs

    template <class T, class Container>
      bool operator==(const std::stack<T, Container> &lhs, const std::stack<T, Container> &rhs);
    
    template <class T, class Container>
      bool operator!=(const std::stack<T, Container> &lhs, const std::stack<T, Container> &rhs);
    
    template <class T, class Container>
      bool operator<(const std::stack<T, Container> &lhs, const std::stack<T, Container> &rhs);
    
    template <class T, class Container>
      bool operator<=(const std::stack<T, Container> &lhs, const std::stack<T, Container> &rhs);
    
    template <class T, class Container>
      bool operator>(const std::stack<T, Container> &lhs, const std::stack<T, Container> &rhs);
    
    template <class T, class Container>
      bool operator>=(const std::stack<T, Container> &lhs, const std::stack<T, Container> &rhs);
};
}
#endif