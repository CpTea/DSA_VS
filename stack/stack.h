#ifndef __STACK_INCLUDE
#define __STACK_INCLUDE
#include "vector.h"
#endif

#ifndef __STACK_DEF
#define __STACK_DEF

template <typename _Ty, typename Container = Vector<_Ty>>
class Stack : public Container
{
private:
    using self_type = Stack;
    using super_type = Container;
public:
    using value_type = typename super_type::value_type;
    using pointer = typename super_type::pointer;
    using const_pointer = typename super_type::const_pointer;
    using reference = typename super_type::reference;
    using const_reference = typename super_type::const_reference;
    using size_type = typename super_type::size_type;
    using position_type = typename super_type::position_type;
    using init_list = typename super_type::init_list;
    using order = typename super_type::order;

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
    super_type::last(el);
}

template<typename _Ty, typename Container>
inline typename Stack<_Ty, Container>::value_type Stack<_Ty, Container>::pop()
{
    return super_type::remove(super_type::last());
}

template<typename _Ty, typename Container>
inline typename Stack<_Ty, Container>::reference Stack<_Ty, Container>::top() const
{
    return super_type::operator[](super_type::last());
}
