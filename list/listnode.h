#ifndef __LISTNODE_INCLUDE
#define __LISTNODE_INCLUDE
#include <ostream>
#endif

#ifndef __LISTNODE_DEF
#define __LISTNODE_DEF

template <typename _Ty>
class ListNode
{
private:
    using self_type = ListNode;
public:
    using value_type = _Ty;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using position_type = self_type*;

public:
    value_type data;
    position_type front;
    position_type rear;

public:
    ListNode();
    ListNode(value_type el, position_type front = nullptr, position_type rear = nullptr);
    position_type before(const_reference el);
    position_type after(const_reference el);
};

#endif

#ifndef __LISTNODE_IMPL
#define __LISTNODE_IMPL

template<typename _Ty>
inline ListNode<_Ty>::ListNode() : data(NULL), front(nullptr), rear(nullptr) { }

template<typename _Ty>
inline ListNode<_Ty>::ListNode(value_type el, position_type front, position_type rear)
{
    this->data = el;
    this->front = front;
    this->rear = rear;
}

template<typename _Ty>
inline ListNode<_Ty>* ListNode<_Ty>::before(const_reference el)
{
    position_type pNode = new ListNode(el, front, this);
    front->rear = pNode;
    front = pNode;
    return pNode;
}

template<typename _Ty>
inline ListNode<_Ty>* ListNode<_Ty>::after(const_reference el)
{
    position_type pNode = new ListNode(el, this, rear);
    rear->front = pNode;
    rear = pNode;
    return pNode;
}

#endif
