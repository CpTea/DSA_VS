#ifndef __LIST_INCLUDE
#define __LIST_INCLUDE
#include "listnode.h"
#include <ostream>
#include <initializer_list>
#endif

#ifndef __LIST_DEF
#define __LIST_DEF

template <typename ElemType>
using iList = std::initializer_list<ElemType>;

template <typename ElemType>
class List
{
public:
    // initialize
    List();
    List(const List<ElemType>& li);
    List(const List<ElemType>& li, int begin, int len);
    List(ListNode<ElemType>* begin, int len);
    List(const iList<ElemType>& li);
    List(const iList<ElemType>& li, int left, int right);
    List(const ElemType arr[], int len);
    List(const ElemType arr[], int left, int right);
    ~List();
    template <typename T>
    friend std::ostream& operator<<(std::ostream& os, const List<T>& li);

    // read only
    ElemType& operator[](int ind) const;
    int size() const;
    bool empty() const;
    ListNode<ElemType>* first() const;
    ListNode<ElemType>* last() const;
    void valid(ListNode<ElemType>* pos) const;
    ListNode<ElemType>* max(ListNode<ElemType>* begin, int len) const;
    ListNode<ElemType>* max() const;
    ListNode<ElemType>* indexOf(const ElemType& el, ListNode<ElemType>* begin, int len) const;
    ListNode<ElemType>* indexOf(const ElemType& el) const;
    ListNode<ElemType>* indexOfSorted(const ElemType& el, ListNode<ElemType>* begin, int len) const;
    ListNode<ElemType>* indexOfSorted(const ElemType& el) const;

    // write only
    ListNode<ElemType>* before(const ElemType& el, ListNode<ElemType>* pos);
    ListNode<ElemType>* first(const ElemType& el);
    ListNode<ElemType>* after(const ElemType& el, ListNode<ElemType>* pos);
    ListNode<ElemType>* last(const ElemType& el);
    ElemType remove(ListNode<ElemType>* pos);

protected:
    void map(const ElemType arr[], int left, int right);
    void map(const iList<ElemType>& li, int left, int right);
    void clone(ListNode<ElemType>* begin, int len);
    void init(void);
    int clear(void);

private:
    int m_size;
    ListNode<ElemType>* m_pHead;
    ListNode<ElemType>* m_pTail;
};

#endif

#ifndef __LIST_IMPL
#define __LIST_IMPL

template<typename ElemType>
inline List<ElemType>::List() { init(); }

template<typename ElemType>
inline List<ElemType>::List(ListNode<ElemType>* begin, int len)
{
    clone(begin, len);
}

template<typename ElemType>
inline List<ElemType>::List(const iList<ElemType>& li)
{
    map(li, 0, (int)li.size());
}

template<typename ElemType>
inline List<ElemType>::List(const iList<ElemType>& li, int left, int right)
{
    map(li, left, right);
}

template<typename ElemType>
inline List<ElemType>::List(const ElemType arr[], int len)
{
    map(arr, 0, len);
}

template<typename ElemType>
inline List<ElemType>::List(const ElemType arr[], int left, int right)
{
    map(arr, left, right);
}

template<typename ElemType>
inline List<ElemType>::~List()
{
    clear();
    delete m_pHead;
    delete m_pTail;
    m_pHead = nullptr;
    m_pTail = nullptr;
}

template<typename ElemType>
inline ElemType& List<ElemType>::operator[](int ind) const
{
    ListNode<ElemType>* curr = first();
    while (ind--) curr = curr->rear;
    return curr->data;
}

template<typename ElemType>
inline int List<ElemType>::size() const
{
    return m_size;
}

template<typename ElemType>
inline bool List<ElemType>::empty() const
{
    return !m_size;
}

template<typename ElemType>
inline ListNode<ElemType>* List<ElemType>::first() const
{
    return m_pHead->rear;
}

template<typename ElemType>
inline ListNode<ElemType>* List<ElemType>::last() const
{
    return m_pTail->front;
}

template<typename ElemType>
inline void List<ElemType>::valid(ListNode<ElemType>* pos) const
{
    return pos && (pos != m_pHead) && (pos != m_pTail);
}

template<typename ElemType>
inline ListNode<ElemType>* List<ElemType>::max(ListNode<ElemType>* begin, int len) const
{
    ListNode<ElemType>* maximum = begin;
    for (ListNode<ElemType>* curr = begin; len > 1; len--)
    {
        curr = curr->rear;
        if (curr->data > maximum->data) maximum = curr;
    }
    return maximum;
}

template<typename ElemType>
inline ListNode<ElemType>* List<ElemType>::max() const
{
    return max(m_pHead->rear, m_size);
}

template<typename ElemType>
inline ListNode<ElemType>* List<ElemType>::indexOf(const ElemType& el, ListNode<ElemType>* begin, int len) const
{
    while (len--)
    {
        begin = begin->front;
        if (el == begin->data) return begin;
    }
    return nullptr;
}

template<typename ElemType>
inline ListNode<ElemType>* List<ElemType>::indexOf(const ElemType& el) const
{
    return indexOf(el, m_pTail, m_size);
}

template<typename ElemType>
inline ListNode<ElemType>* List<ElemType>::indexOfSorted(const ElemType& el, ListNode<ElemType>* begin, int len) const
{
    while ((el < (begin = begin->front)->data) && len--);
    return begin;
}

template<typename ElemType>
inline ListNode<ElemType>* List<ElemType>::indexOfSorted(const ElemType& el) const
{
    return indexOfSorted(el, m_pTail, m_size);
}

template<typename ElemType>
inline ListNode<ElemType>* List<ElemType>::before(const ElemType& el, ListNode<ElemType>* pos)
{
    m_size++;
    return pos->before(el);
}

template<typename ElemType>
inline ListNode<ElemType>* List<ElemType>::first(const ElemType& el)
{
    m_size++;
    return m_pHead->after(el);
}

template<typename ElemType>
inline ListNode<ElemType>* List<ElemType>::after(const ElemType& el, ListNode<ElemType>* pos)
{
    m_size++;
    return pos->after(el);
}

template<typename ElemType>
inline ListNode<ElemType>* List<ElemType>::last(const ElemType& el)
{
    m_size++;
    return m_pTail->before(el);
}

template<typename ElemType>
inline ElemType List<ElemType>::remove(ListNode<ElemType>* pos)
{
    ElemType data = pos->data;
    pos->front->rear = pos->rear;
    pos->rear->front = pos->front;
    delete pos;
    pos = nullptr;
    m_size--;
    return data;
}

template<typename ElemType>
inline void List<ElemType>::map(const ElemType arr[], int left, int right)
{
    init();
    while (left < right) last(arr[left++]);
}

template<typename ElemType>
inline void List<ElemType>::map(const iList<ElemType>& li, int left, int right)
{
    init();
    for (auto first = li.begin() + left, last = li.begin() + right; first != last; first++)
    {
        this->last(*first);
    }
}

template<typename ElemType>
inline void List<ElemType>::clone(ListNode<ElemType>* begin, int len)
{
    init();
    while (len--)
    {
        last(begin->data);
        begin = begin->rear;
    }
}

template<typename ElemType>
inline void List<ElemType>::init(void)
{
    m_pHead = new ListNode<ElemType>();
    m_pTail = new ListNode<ElemType>();
    m_pHead->rear = m_pTail;
    m_pTail->front = m_pHead;
    m_pHead->front = nullptr;
    m_pTail->rear = nullptr;
    m_size = 0;
}

template<typename ElemType>
inline int List<ElemType>::clear(void)
{
    int size = m_size;
    while (m_size) remove(m_pHead->rear);
    return size;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const List<T>& li)
{
    for (ListNode<T>* p = li.m_pHead->rear; p->rear != nullptr; p = p->rear)
        os << p->data << "\t ";
    os << std::endl;
    return os;
}

#endif
