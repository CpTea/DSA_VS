#ifndef __VECTOR_INCLUDE
#define __VECTOR_INCLUDE
#include "Algorithms.h"
#include <ostream>
#include <initializer_list>
#endif

#ifndef __VECTOR_DEF
#define __VECTOR_DEF

typedef int64_t size_type;

template <typename _Ty, size_type capacity = 5>
class Vector
{
private:
    using self_type = Vector;
public:
    using value_type = _Ty;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_type;
    using position_type = int64_t;
    using init_list = const std::initializer_list<value_type>&;
    using order = cptea::Order<value_type>;

public:
    // initialize
    Vector(size_type size = 0, value_type default_val = 0);
    Vector(const_pointer arr, size_type len);
    Vector(const_pointer arr, position_type left, position_type right);
    Vector(const self_type& vec);
    Vector(const self_type& vec, position_type left, position_type right);
    Vector(init_list li);
    Vector(init_list li, position_type left, position_type right);
    ~Vector();

    // read only
    size_type size() const;
    bool empty() const;
    position_type indexOf(const_reference el, position_type left, position_type right) const;
    position_type indexOf(const_reference el) const;
    position_type indexOfSorted(const_reference el, order ord = cptea::Asc) const;
    position_type indexOfSorted(const_reference el, position_type left, position_type right, order ord = cptea::Asc) const;
    position_type last() const;
    reference operator[](position_type index) const;
    template<class T, int cap>
    friend std::ostream& operator<<(std::ostream& os, const Vector<T, cap>& vec);

    // write only
    size_type remove(position_type left, position_type right);
    value_type remove(position_type index);
    position_type after(const_reference el, position_type index);
    position_type last(const_reference el);
    void sort(position_type left, position_type right, order ord = cptea::Asc, int method = -1);
    void sort(order ord = cptea::Asc, int method = -1);
    void shuffle(position_type left, position_type right);
    void shuffle();
    size_type deduplicate();
    size_type deduplicateBySorted();
    void traverse(void (*handle)(reference));
    template <typename T> void traverse(T& handle);

protected:
    void clone(const_pointer arr, position_type left, position_type right);
    void clone(init_list li, position_type left, position_type right);
    void expand();
    void shrink();
    position_type  extremum(position_type left, position_type right, order ord);
    position_type  min(position_type left, position_type right);
    position_type  max(position_type left, position_type right);
    void merge(position_type left, position_type middle, position_type right, order ord);
    position_type  partition(position_type left, position_type right, order ord);
    position_type binSearch(const_reference el, position_type left, position_type right, order ord) const;
    void bubbleSort(position_type left, position_type right, order ord);
    void selectionSort(position_type left, position_type right, order ord);
    void mergeSort(position_type left, position_type right, order ord);
    void heapSort(position_type left, position_type right, order ord);
    void quickSort(position_type left, position_type right, order ord);
    void shellSort(position_type left, position_type right, order ord);

private:
    pointer m_pData;
    size_type m_size;
    size_type m_capacity;
};

#endif

#ifndef __VECTOR_IMPL
#define __VECTOR_IMPL

template<typename _Ty, size_type capacity>
inline Vector<_Ty, capacity>::Vector(size_type size, value_type default_val)
{
    m_pData = new value_type[m_capacity = capacity];
    if (size > capacity) size = capacity;
    for (m_size = 0; m_size < size; m_pData[m_size++] = default_val);
}

template<typename _Ty, size_type capacity>
inline Vector<_Ty, capacity>::Vector(const_pointer arr, size_type len)
{
    clone(arr, 0, len);
}

template<typename _Ty, size_type capacity>
inline Vector<_Ty, capacity>::Vector(const_pointer arr, position_type left, position_type right)
{
    clone(arr, left, right);
}

template<typename _Ty, size_type capacity>
inline Vector<_Ty, capacity>::Vector(const self_type& vec)
{
    clone(vec.m_pData, 0, vec.m_size);
}

template<typename _Ty, size_type capacity>
inline Vector<_Ty, capacity>::Vector(const self_type& vec, position_type left, position_type right)
{
    clone(vec.m_pData, left, right);
}

template<typename _Ty, size_type capacity>
inline Vector<_Ty, capacity>::Vector(init_list li)
{
    clone(li, 0, (size_type)li.size());
}

template<typename _Ty, size_type capacity>
inline Vector<_Ty, capacity>::Vector(init_list li, position_type left, position_type right)
{
    clone(li, left, right);
}

template<typename _Ty, size_type capacity>
inline Vector<_Ty, capacity>::~Vector()
{
    delete[] m_pData;
    m_pData = nullptr;
}

template<typename _Ty, size_type capacity>
inline size_type Vector<_Ty, capacity>::size() const
{
    return m_size;
}

template<typename _Ty, size_type capacity>
inline bool Vector<_Ty, capacity>::empty() const
{
    return m_size > 0;
}

template<typename _Ty, size_type capacity>
inline typename Vector<_Ty, capacity>::position_type Vector<_Ty, capacity>::indexOf(const_reference el, position_type left, position_type right) const
{
    while ((left < right--) && (el != m_pData[right]));
    return right;
}

template<typename _Ty, size_type capacity>
inline typename Vector<_Ty, capacity>::position_type Vector<_Ty, capacity>::indexOf(const_reference el) const
{
    return indexOf(el, 0, m_size);
}

template<typename _Ty, size_type capacity>
inline typename Vector<_Ty, capacity>::position_type Vector<_Ty, capacity>::indexOfSorted(const_reference el, order ord) const
{
    return indexOfSorted(el, 0, m_size, ord);
}

template<typename _Ty, size_type capacity>
inline typename Vector<_Ty, capacity>::position_type Vector<_Ty, capacity>::indexOfSorted(const_reference el, position_type left, position_type right, order ord) const
{
    return binSearch(el, left, right, ord);
}

template<typename _Ty, size_type capacity>
inline typename Vector<_Ty, capacity>::position_type Vector<_Ty, capacity>::last() const
{
    return m_size - 1;
}

template<typename _Ty, size_type capacity>
inline typename Vector<_Ty, capacity>::reference Vector<_Ty, capacity>::operator[](position_type index) const
{
    return m_pData[index];
}

template<typename _Ty, size_type capacity>
inline typename Vector<_Ty, capacity>::size_type Vector<_Ty, capacity>::remove(position_type left, position_type right)
{
    if (left == right) return 0;
    while (right < m_size) m_pData[left++] = m_pData[right++];
    m_size = left;
    shrink();
    return right - left;
}

template<typename _Ty, size_type capacity>
inline typename Vector<_Ty, capacity>::value_type Vector<_Ty, capacity>::remove(position_type index)
{
    value_type el = m_pData[index];
    remove(index, index + 1);
    return el;
}

template<typename _Ty, size_type capacity>
inline typename Vector<_Ty, capacity>::position_type Vector<_Ty, capacity>::after(const_reference el, position_type index)
{
    expand();
    for (size_type i = m_size; i > index; i--) m_pData[i] = m_pData[i - 1];
    m_pData[index] = el;
    m_size++;
    return index;
}

template<typename _Ty, size_type capacity>
inline typename Vector<_Ty, capacity>::position_type Vector<_Ty, capacity>::last(const_reference el)
{
    return after(el, m_size);
}

template<typename _Ty, size_type capacity>
inline void Vector<_Ty, capacity>::sort(position_type left, position_type right, order ord, int method)
{
    switch (method)
    {
    case 0: return bubbleSort(left, right, ord);
    case 1: return selectionSort(left, right, ord);
    case 2: return mergeSort(left, right, ord);
    case 3: return heapSort(left, right, ord);
    case 4: return quickSort(left, right, ord);
    case 5:return shellSort(left, right, ord);
    default:  return quickSort(left, right, ord);
    }
}

template<typename _Ty, size_type capacity>
inline void Vector<_Ty, capacity>::sort(order ord, int method)
{
    return sort(0, m_size, ord, method);
}

template<typename _Ty, size_type capacity>
inline void Vector<_Ty, capacity>::shuffle(position_type left, position_type right)
{
    pointer p = m_pData + left;
    for (size_type i = right - left; i > 0; i--) cptea::swap(p[i - 1], p[rand() % i]);
}

template<typename _Ty, size_type capacity>
inline void Vector<_Ty, capacity>::shuffle()
{
    return shuffle(0, m_size);
}

template<typename _Ty, size_type capacity>
inline typename Vector<_Ty, capacity>::size_type Vector<_Ty, capacity>::deduplicate()
{
    size_type size = m_size;
    size_type i = 1;
    while (i < m_size)
        if (indexOf(m_pData[i], 0, i) < 0) i++;
        else remove(i);
    return size - m_size;
}

template<typename _Ty, size_type capacity>
inline typename Vector<_Ty, capacity>::size_type Vector<_Ty, capacity>::deduplicateBySorted()
{
    size_type i = 0, j = 0;
    while (++j < m_size)
        if (m_pData[i] != m_pData[j]) m_pData[++i] = m_pData[j];
    m_size = ++i;
    shrink();
    return j - i;
}

template<typename _Ty, size_type capacity>
inline void Vector<_Ty, capacity>::traverse(void(*handle)(reference))
{
    for (size_type i = 0; i < m_size; i++) handle(m_pData[i]);
}

template<typename _Ty, size_type capacity>
template<typename T>
inline void Vector<_Ty, capacity>::traverse(T& handle)
{
    for (size_type i = 0; i < m_size; i++) handle(m_pData[i]);
}

template<typename _Ty, size_type capacity>
inline void Vector<_Ty, capacity>::clone(const_pointer arr, position_type left, position_type right)
{
    m_pData = new value_type[m_capacity = 2 * (right - left)];
    for (m_size = 0; left < right; m_pData[m_size++] = arr[left++]);
}

template<typename _Ty, size_type capacity>
inline void Vector<_Ty, capacity>::clone(init_list li, position_type left, position_type right)
{
    m_pData = new value_type[m_capacity = 2 * (right - left)];
    m_size = 0;
    for (auto first = li.begin() + left, last = li.begin() + right; first != last; *(m_pData + m_size++) = *first++);
}

template<typename _Ty, size_type capacity>
inline void Vector<_Ty, capacity>::expand()
{
    if (m_size < m_capacity) return;
    if (m_capacity < capacity) m_capacity = capacity;
    pointer pTemp = m_pData;
    m_pData = new value_type[m_capacity <<= 1];
    for (size_type i = 0; i < m_size; i++) m_pData[i] = pTemp[i];
    delete[] pTemp;
}

template<typename _Ty, size_type capacity>
inline void Vector<_Ty, capacity>::shrink()
{
    if (m_capacity < capacity << 1) return;
    if (m_size << 2 > m_capacity) return;
    if (m_capacity < capacity) m_capacity = capacity;
    pointer pTemp = m_pData;
    m_pData = new value_type[m_capacity >>= 1];
    for (size_type i = 0; i < m_size; i++) *(m_pData + i) = *(pTemp + i);
    delete[] pTemp;
}

template<typename _Ty, size_type capacity>
inline typename Vector<_Ty, capacity>::position_type Vector<_Ty, capacity>::extremum(position_type left, position_type right, order ord)
{
    size_type extr = right;
    while (left < right--)
        if (!ord(m_pData[right], m_pData[extr])) extr = right;
    return extr;
}

template<typename _Ty, size_type capacity>
inline typename Vector<_Ty, capacity>::position_type Vector<_Ty, capacity>::min(position_type left, position_type right)
{
    return extremum(left, right, cptea::Asc);
}

template<typename _Ty, size_type capacity>
inline typename Vector<_Ty, capacity>::position_type Vector<_Ty, capacity>::max(position_type left, position_type right)
{
    return extremum(left, right, cptea::Desc);
}

template<typename _Ty, size_type capacity>
inline void Vector<_Ty, capacity>::merge(position_type left, position_type middle, position_type right, order ord)
{
    pointer pLeft = m_pData + left;
    size_type lenLeft = middle - left;
    pointer pTemp = new value_type[lenLeft];
    for (size_type i = 0; i < lenLeft; i++) pTemp[i] = pLeft[i];
    size_type lenRight = right - middle;
    pointer pRight = m_pData + middle;
    for (size_type i = 0, j = 0, k = 0; j < lenLeft; )
        pLeft[i++] = (lenRight <= k || ord(pTemp[j], pRight[k])) ? pTemp[j++] : pRight[k++];
    delete[] pTemp;
}

template<typename _Ty, size_type capacity>
inline typename Vector<_Ty, capacity>::position_type Vector<_Ty, capacity>::partition(position_type left, position_type right, order ord)
{
    cptea::swap(m_pData[left], m_pData[left + rand() % (right - left)]);
    value_type pivot = m_pData[left];
    size_type m = left;
    for (size_type k = left + 1; k < right; k++)
        if (!ord(pivot, m_pData[k])) cptea::swap(m_pData[++m], m_pData[k]);
    cptea::swap(m_pData[left], m_pData[m]);
    return m;
}

template<typename _Ty, size_type capacity>
inline typename Vector<_Ty, capacity>::position_type Vector<_Ty, capacity>::binSearch(const_reference el, position_type left, position_type right, order ord) const
{
    while (left < right)
    {
        position_type middle = (left + right) >> 1;
        (!ord(m_pData[middle], el)) ? right = middle : left = middle + 1;
    }
    return --left;
}

template<typename _Ty, size_type capacity>
inline void Vector<_Ty, capacity>::bubbleSort(position_type left, position_type right, order ord)
{
    for (size_type last = --right; left < right; right = last)
        for (size_type i = last = left; i < right; i++)
            if (!ord(m_pData[i], m_pData[i + 1]))
                cptea::swap(m_pData[last = i], m_pData[i + 1]);
}

template<typename _Ty, size_type capacity>
inline void Vector<_Ty, capacity>::selectionSort(position_type left, position_type right, order ord)
{
    while (left < --right) cptea::swap(m_pData[extremum(left, right, ord)], m_pData[right]);
}

template<typename _Ty, size_type capacity>
inline void Vector<_Ty, capacity>::mergeSort(position_type left, position_type right, order ord)
{
    if (right - left < 2) return;
    position_type middle = (left + right) >> 1;
    mergeSort(left, middle, ord);
    mergeSort(middle, right, ord);
    merge(left, middle, right, ord);
}

template<typename _Ty, size_type capacity>
inline void Vector<_Ty, capacity>::heapSort(position_type left, position_type right, order ord)
{
    pointer p = m_pData + left;
    size_type n = right - left;
    cptea::heapify(p, n, ord);
    while (0 < --n)
    {
        cptea::swap(p[0], p[n]);
        cptea::percolateDown(p, n, 0, ord);
    }
}

template<typename _Ty, size_type capacity>
inline void Vector<_Ty, capacity>::quickSort(position_type left, position_type right, order ord)
{
    if (right - left < 2) return;
    position_type middle = partition(left, right, ord);
    quickSort(left, middle, ord);
    quickSort(middle + 1, right, ord);
}

template<typename _Ty, size_type capacity>
inline void Vector<_Ty, capacity>::shellSort(position_type left, position_type right, order ord)
{
    for (size_type d = 0x3FFFFFFF; 0 < d; d >>= 1)
    {
        for (size_type j = left + d; j < right; j++)
        {
            value_type x = m_pData[j];
            size_type i = j - d;
            while (left <= i && !ord(m_pData[i], x))
            {
                m_pData[i + d] = m_pData[i];
                i -= d;
            }
            m_pData[i + d] = x;
        }
    }
}

template<class T, int cap>
inline std::ostream& operator<<(std::ostream& os, const Vector<T, cap>& vec)
{
    for (int idx = 0; idx < vec.m_size; idx++)
        os << vec.m_pData[idx] << "\t ";
    return os << std::endl;
}

#endif
