#ifndef __QUEUE_INCLUDE
#define __QUEUE_INCLUDE
#include "list.h"
#endif

#ifndef __QUEUE_DEF
#define __QUEUE_DEF

template <class _Ty>
class Queue : public List<_Ty>
{
private:
    using self_type = Queue;
    using super_type = List<_Ty>;
public:
    using value_type = typename super_type::value_type;
    using reference = typename super_type::reference;
    using const_reference = typename super_type::const_reference;

public:
    void enqueue(const_reference el);
    value_type dequeue();
    reference front() const;
};

#endif

#ifndef __QUEUE_IMPL
#define __QUEUE_IMPL

template<class _Ty>
inline void Queue<_Ty>::enqueue(const_reference el)
{
    super_type::last(el);
}

template<class _Ty>
inline typename Queue<_Ty>::value_type Queue<_Ty>::dequeue()
{
    return super_type::remove(super_type::first());
}

template<class _Ty>
inline typename Queue<_Ty>::reference Queue<_Ty>::front() const
{
    return super_type::operator[](super_type::first());
}

#endif
