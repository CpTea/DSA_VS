#ifndef __STACK_INCLUDE
#define __STACK_INCLUDE
#include "vector.h"
#endif

#ifndef __STACK_DEF
#define __STACK_DEF

template <typename _Ty, typename Container = Vector<_Ty>>
class Stack : public Container
{
public:
    using value_type = typename Container::value_type;
    using pointer = typename Container::pointer;
    using const_pointer = typename Container::const_pointer;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;
    using size_type = typename Container::size_type;
    using position_type = typename Container::position_type;
    using init_list = typename Container::init_list;
    using order = typename Container::order;

public:
    void push(const_reference el);
    value_type pop();
    reference top() const;
};

#endif

#ifndef __STACK_IMPL
#define __STACK_IMPL

#endif

template<typename _Ty, typename Container>
inline void Stack<_Ty, Container>::push(const_reference el)
{
    Container::last(el);
}

template<typename _Ty, typename Container>
inline typename Stack<_Ty, Container>::value_type Stack<_Ty, Container>::pop()
{
    return Container::remove(Container::last());
}

template<typename _Ty, typename Container>
inline typename Stack<_Ty, Container>::reference Stack<_Ty, Container>::top() const
{
    return Container::operator[](Container::last());
}
