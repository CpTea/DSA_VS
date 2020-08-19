#ifndef __LIST_INCLUDE
#define __LIST_INCLUDE
#include "listnode.h"
#include "Algorithms.h"
#include <ostream>
#include <initializer_list>
#endif

#ifndef __LIST_DEF
#define __LIST_DEF

template <typename _Ty>
class List
{
public:
    using value_type = _Ty;
    using node = ListNode<value_type>;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = typename value_type&;
    using const_reference = const value_type&;
    using const_ref = const reference;
    using size_type = int64_t;
    using position_type = node*;
    using init_list = const std::initializer_list<value_type>&;
    using order = cptea::Order<value_type>;

public:
    // initialize
    List();
    List(const List& li);
    List(const List& li, size_type begin, size_type len);
    List(position_type begin, size_type len);
    List(init_list li);
    List(init_list li, size_type left, size_type right);
    List(const_pointer arr, size_type len);
    List(const_pointer arr, size_type left, size_type right);
    ~List();
    template <typename T>
    friend std::ostream& operator<<(std::ostream& os, const List<T>& li);

    // read only
    reference operator[](size_type ind) const;
    reference operator[](position_type ind) const;
    size_type size() const;
    bool empty() const;
    position_type first() const;
    position_type last() const;
    bool valid(position_type pos) const;
    position_type max(position_type begin, size_type len) const;
    position_type max() const;
    position_type min(position_type begin, size_type len) const;
    position_type min() const;
    position_type indexOf(const_reference el, position_type begin, size_type len) const;
    position_type indexOf(const_reference el) const;
    position_type indexOfSorted(const_reference el, position_type begin, size_type len, order ord = cptea::Asc) const;
    position_type indexOfSorted(const_reference el, order ord = cptea::Asc) const;

    // write only
    position_type before(const_reference el, position_type pos);
    position_type first(const_reference el);
    position_type after(const_reference el, position_type pos);
    position_type last(const_reference el);
    value_type remove(position_type pos);

    void sort(position_type begin, size_type len, order ord = cptea::Asc, int method = -1);
    void sort(order ord = cptea::Asc, int method = -1);
    size_type deduplicate();
    size_type deduplicateBySorted();
    void reverse();
    void traverse(void (*handle)(reference));
    template <typename T> void traverse(T& handle);

protected:
    void map(const_pointer arr, size_type left, size_type right);
    void map(init_list li, size_type left, size_type right);
    void clone(position_type begin, size_type len);
    void init(void);
    size_type clear(void);
    position_type extremum(position_type begin, size_type len, order ord) const;
    void merge(position_type& begin1, size_type len1, List& li, position_type begin2, size_type len2, order ord = cptea::Asc);
    void mergeSort(position_type& begin, size_type len, order ord = cptea::Asc);
    void selectionSort(position_type begin, size_type len, order ord = cptea::Asc);
    void insertionSort(position_type begin, size_type len, order ord = cptea::Asc);

private:
    size_type m_size;
    position_type m_pHead;
    position_type m_pTail;
};

#endif

#ifndef __LIST_IMPL
#define __LIST_IMPL

template<typename _Ty>
inline List<_Ty>::List() { init(); }

template<typename _Ty>
inline List<_Ty>::List(const List& li)
{
    clone(li.first, li.m_size);
}

template<typename _Ty>
inline List<_Ty>::List(const List& li, size_type begin, size_type len)
{
    position_type curr = li.first();
    while (begin-- > 0) curr = curr->rear;
    clone(curr, len);
}

template<typename _Ty>
inline List<_Ty>::List(position_type begin, size_type len)
{
    clone(begin, len);
}

template<typename _Ty>
inline List<_Ty>::List(init_list li)
{
    map(li, 0, (size_type)li.size());
}

template<typename _Ty>
inline List<_Ty>::List(init_list li, size_type left, size_type right)
{
    map(li, left, right);
}

template<typename _Ty>
inline List<_Ty>::List(const_pointer arr, size_type len)
{
    map(arr, 0, len);
}

template<typename _Ty>
inline List<_Ty>::List(const_pointer arr, size_type left, size_type right)
{
    map(arr, left, right);
}

template<typename _Ty>
inline List<_Ty>::~List()
{
    clear();
    delete m_pHead;
    delete m_pTail;
    m_pHead = nullptr;
    m_pTail = nullptr;
}

template<typename _Ty>
inline typename List<_Ty>::reference List<_Ty>::operator[](size_type ind) const
{
    position_type curr = first();
    while (ind--) curr = curr->rear;
    return curr->data;
}

template<typename _Ty>
inline typename List<_Ty>::reference List<_Ty>::operator[](position_type ind) const
{
    return ind->data;
}

template<typename _Ty>
inline typename List<_Ty>::size_type List<_Ty>::size() const
{
    return m_size;
}

template<typename _Ty>
inline bool List<_Ty>::empty() const
{
    return m_size > 0;
}

template<typename _Ty>
inline typename List<_Ty>::position_type List<_Ty>::first() const
{
    return m_pHead->rear;
}

template<typename _Ty>
inline typename List<_Ty>::position_type List<_Ty>::last() const
{
    return m_pTail->front;
}

template<typename _Ty>
inline bool List<_Ty>::valid(position_type pos) const
{
    return pos && (pos != m_pHead) && (pos != m_pTail);
}

template<typename _Ty>
inline typename List<_Ty>::position_type List<_Ty>::max(position_type begin, size_type len) const
{
    return extremum(begin, len, cptea::Asc);
}

template<typename _Ty>
inline typename List<_Ty>::position_type List<_Ty>::max() const
{
    return max(m_pHead->rear, m_size);
}

template<typename _Ty>
inline typename List<_Ty>::position_type List<_Ty>::min(position_type begin, size_type len) const
{
    return extremum(begin, len, cptea::Desc);
}

template<typename _Ty>
inline typename List<_Ty>::position_type List<_Ty>::min() const
{
    return min(m_pHead->rear, m_size);
}

template<typename _Ty>
inline typename List<_Ty>::position_type List<_Ty>::indexOf(const_reference el, position_type begin, size_type len) const
{
    while (len--)
    {
        begin = begin->front;
        if (el == begin->data) return begin;
    }
    return nullptr;
}

template<typename _Ty>
inline typename List<_Ty>::position_type List<_Ty>::indexOf(const_reference el) const
{
    return indexOf(el, m_pTail, m_size);
}

template<typename _Ty>
inline typename List<_Ty>::position_type List<_Ty>::indexOfSorted(const_reference el, position_type begin, size_type len, order ord) const
{
    while (!ord((begin = begin->front)->data, el) && len--);
    return begin;
}

template<typename _Ty>
inline typename List<_Ty>::position_type List<_Ty>::indexOfSorted(const_reference el, order ord) const
{
    return indexOfSorted(el, m_pTail, m_size, ord);
}

template<typename _Ty>
inline typename List<_Ty>::position_type List<_Ty>::before(const_reference el, position_type pos)
{
    m_size++;
    return pos->before(el);
}

template<typename _Ty>
inline typename List<_Ty>::position_type List<_Ty>::first(const_reference el)
{
    m_size++;
    return m_pHead->after(el);
}

template<typename _Ty>
inline typename List<_Ty>::position_type List<_Ty>::after(const_reference el, position_type pos)
{
    m_size++;
    return pos->after(el);
}

template<typename _Ty>
inline typename List<_Ty>::position_type List<_Ty>::last(const_reference el)
{
    m_size++;
    return m_pTail->before(el);
}

template<typename _Ty>
inline typename List<_Ty>::value_type List<_Ty>::remove(position_type pos)
{
    value_type data = pos->data;
    pos->front->rear = pos->rear;
    pos->rear->front = pos->front;
    delete pos;
    pos = nullptr;
    m_size--;
    return data;
}

template<typename _Ty>
inline void List<_Ty>::sort(position_type begin, size_type len, order ord, int method)
{
    switch (method)
    {
    case 0:
        return mergeSort(begin, len, ord);
    case 1:
        return selectionSort(begin, len, ord);
    case 2:
        return insertionSort(begin, len, ord);
    default:
        return mergeSort(begin, len, ord);
    }
}

template<typename _Ty>
inline void List<_Ty>::sort(order ord, int method)
{
    return sort(m_pHead->rear, m_size, ord, method);
}

template<typename _Ty>
inline typename List<_Ty>::size_type List<_Ty>::deduplicate()
{
    size_type size = m_size;
    position_type curr = first();
    for (size_type i = 0; curr != m_pTail; curr = curr->rear)
        if (position_type delElem = indexOf(curr->data, curr, i)) remove(delElem);
        else i++;
    return size - m_size;
}

template<typename _Ty>
inline typename List<_Ty>::size_type List<_Ty>::deduplicateBySorted()
{
    if (m_size < 2) return 0;
    size_type size = m_size;
    position_type curr = first();
    position_type p;
    while (m_pTail != (p = curr->rear))
        if (curr->data != p->data) curr = p;
        else remove(p);
    return size - m_size;
}

template<typename _Ty>
inline void List<_Ty>::reverse()
{
    position_type p = m_pHead;
    position_type q = m_pTail;
    for (size_type i = 1; i < m_size; i += 2)
        cptea::swap((p = p->rear)->data, (q = q->front)->data);
}

template<typename _Ty>
inline void List<_Ty>::traverse(void(*handle)(reference))
{
    for (position_type curr = m_pHead->rear; curr != m_pTail; curr = curr->rear)
        handle(curr->data);
}

template<typename _Ty> template<typename T>
inline void List<_Ty>::traverse(T& handle)
{
    for (position_type curr = m_pHead->rear; curr != m_pTail; curr = curr->rear)
        handle(curr->data);
}

template<typename _Ty>
inline void List<_Ty>::map(const_pointer arr, size_type left, size_type right)
{
    init();
    while (left < right) last(arr[left++]);
}

template<typename _Ty>
inline void List<_Ty>::map(init_list li, size_type left, size_type right)
{
    init();
    for (auto first = li.begin() + left, last = li.begin() + right;
        first != last;
        first++)
    {
        this->last(*first);
    }
}

template<typename _Ty>
inline void List<_Ty>::clone(position_type begin, size_type len)
{
    init();
    while (len--)
    {
        last(begin->data);
        begin = begin->rear;
    }
}

template<typename _Ty>
inline void List<_Ty>::init(void)
{
    m_pHead = new node;
    m_pTail = new node;
    m_pHead->rear = m_pTail;
    m_pTail->front = m_pHead;
    m_pHead->front = nullptr;
    m_pTail->rear = nullptr;
    m_size = 0;
}

template<typename _Ty>
inline typename List<_Ty>::size_type List<_Ty>::clear(void)
{
    size_type size = m_size;
    while (m_size) remove(m_pHead->rear);
    return size;
}

template<typename _Ty>
inline typename List<_Ty>::position_type List<_Ty>::extremum(position_type begin, size_type len, order ord) const
{
    position_type extr = begin;
    for (position_type curr = begin; len > 1; len--)
    {
        curr = curr->rear;
        if (!ord(curr->data, extr->data)) extr = curr;
    }
    return extr;
}

template<typename _Ty>
inline void List<_Ty>::merge(position_type& begin1, size_type len1, List& li, position_type begin2, size_type len2, order ord)
{
    position_type curr = begin1->front;
    while (0 < len2)
    {
        if ((0 < len1) && ord(begin1->data, begin2->data))
        {
            if (begin2 == (begin1 = begin1->rear)) break;
            len1--;
        }
        else
        {
            before(li.remove((begin2 = begin2->rear)->front), begin1);
            len2--;
        }
    }
    begin1 = curr->rear;
}

template<typename _Ty>
inline void List<_Ty>::mergeSort(position_type& begin, size_type len, order ord)
{
    if (len < 2) return;
    size_type mid = len >> 1;
    position_type curr = begin;
    for (size_type i = 0; i < mid; i++) curr = curr->rear;
    mergeSort(begin, mid, ord);
    mergeSort(curr, len - mid, ord);
    merge(begin, mid, *this, curr, len - mid, ord);
}

template<typename _Ty>
inline void List<_Ty>::selectionSort(position_type begin, size_type len, order ord)
{
    ListNode<_Ty>* head = begin->front;
    position_type tail = begin;
    for (size_type i = 0; i < len; i++) tail = tail->rear;
    while (1 < len)
    {
        position_type extr = extremum(head->rear, len, ord);
        before(remove(extr), tail);
        tail = tail->front;
        len--;
    }
}

template<typename _Ty>
inline void List<_Ty>::insertionSort(position_type begin, size_type len, order ord)
{
    for (size_type r = 0; r < len; r++)
    {
        after(begin->data, indexOfSorted(begin->data, begin, r, ord));
        begin = begin->rear;
        remove(begin->front);
    }
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const List<T>& li)
{
    for (auto p = li.m_pHead->rear; p->rear != nullptr; p = p->rear)
        os << p->data << "\t ";
    os << std::endl;
    return os;
}


#endif
