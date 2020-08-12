﻿#ifndef __LISTNODE_INCLUDE
#define __LISTNODE_INCLUDE
#endif

#ifndef __LISTNODE_DEF
#define __LISTNODE_DEF

template <typename ElemType>
class ListNode
{
public:
    ElemType data;
    ListNode<ElemType>* front;
    ListNode<ElemType>* rear;

public:
    ListNode();
    ListNode(ElemType el, ListNode<ElemType>* front = nullptr, ListNode<ElemType>* rear = nullptr);
    ListNode<ElemType>* before(const ElemType& el);
    ListNode<ElemType>* after(const ElemType& el);
};

#endif

#ifndef __LISTNODE_IMPL
#define __LISTNODE_IMPL

template<typename ElemType>
inline ListNode<ElemType>::ListNode() { }

template<typename ElemType>
inline ListNode<ElemType>::ListNode(ElemType el, ListNode<ElemType>* front, ListNode<ElemType>* rear)
{
    this->data = el;
    this->front = front;
    this->rear = rear;
}

template<typename ElemType>
inline ListNode<ElemType>* ListNode<ElemType>::before(const ElemType& el)
{
    ListNode<ElemType>* pNode = new ListNode(el, front, this);
    front->rear = pNode;
    front = pNode;
    return pNode;
}

template<typename ElemType>
inline ListNode<ElemType>* ListNode<ElemType>::after(const ElemType& el)
{
    ListNode<ElemType>* pNode = new ListNode(el, this, rear);
    rear->front = pNode;
    rear = pNode;
    return pNode;
}


#endif