#ifndef __QUEUE_INCLUDE
#define __QUEUE_INCLUDE
#include "list.h"
#endif

#ifndef __QUEUE_DEF
#define __QUEUE_DEF

template <class _Ty>
class Queue : public List<_Ty>
{
public:
    using value_type = typename List<_Ty>::value_type;
    using reference = typename List<_Ty>::reference;
    using const_reference = typename List<_Ty>::const_reference;

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
    List<_Ty>::last(el);
}

template<class _Ty>
inline typename Queue<_Ty>::value_type Queue<_Ty>::dequeue()
{
    return List<_Ty>::remove(List<_Ty>::first());
}

template<class _Ty>
inline typename Queue<_Ty>::reference Queue<_Ty>::front() const
{
    return List<_Ty>::operator[](List<_Ty>::first());
}

#endif
