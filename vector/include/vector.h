#ifndef __VECTOR_INCLUDE
#define __VECTOR_INCLUDE
#include "Algorithms.h"
#include <ostream>
#include <initializer_list>
#endif

#ifndef __VECTOR_DEF
#define __VECTOR_DEF

template <typename ElemType>
using List = std::initializer_list<ElemType>;

template <typename ElemType, int capacity = 5>
class vector
{
    using Order = cptea::Order<ElemType>;

    template<class T, int cap>
    friend std::ostream& operator<<(std::ostream& os, const vector<T, cap>& vec);

public:
    // initialize
    vector(int size = 0, ElemType default_val = 0);
    vector(const ElemType arr[], int len);
    vector(const ElemType arr[], int left, int right);
    vector(const vector& vec);
    vector(const vector& vec, int left, int right);
    vector(const List<ElemType>& li);
    vector(const List<ElemType>& li, int left, int right);
    ~vector();

    // read only
    int size() const;
    bool empty() const;
    int indexOf(const ElemType& el, int left, int right) const;
    int indexOf(const ElemType& el) const;
    int indexOfSorted(const ElemType& el, Order order = cptea::Asc) const;
    int indexOfSorted(const ElemType& el, int left, int right, Order order = cptea::Asc) const;
    void sort(int left, int right, Order order = cptea::Asc, int method = -1);
    void sort(Order order = cptea::Asc, int method = -1);
    void shuffle(int left, int right);
    void shuffle();
    int deduplicate();
    int deduplicateBySorted();

    // write only
    ElemType& operator[](int index);
    const ElemType& operator[](int index) const;
    int remove(int left, int right);
    ElemType remove(int index);
    int insert(const ElemType& el, int index);
    int insert(const ElemType& el);
    void traverse(void (*handle)(ElemType&));
    template <typename T> void traverse(T& handle);

protected:
    void clone(const ElemType arr[], int left, int right);
    void clone(const List<ElemType>& li, int left, int right);
    void expand();
    void shrink();
    int  extremum(int left, int right, Order order);
    int  min(int left, int right);
    int  max(int left, int right);
    void merge(int left, int middle, int right, Order order);
    int  partition(int left, int right, Order order);
    int binSearch(const ElemType& el, int left, int right, Order order) const;

    void bubbleSort(int left, int right, Order order);
    void selectionSort(int left, int right, Order order);
    void mergeSort(int left, int right, Order order);
    void heapSort(int left, int right, Order order);
    void quickSort(int left, int right, Order order);
    void shellSort(int left, int right, Order order);

private:
    ElemType* m_pData;
    int m_size;
    int m_capacity;
};

#endif

#ifndef __VECTOR_IMPL
#define __VECTOR_IMPL

template<class ElemType, int capacity>
inline vector<ElemType, capacity>::vector(int size, ElemType default_val)
{
    m_pData = new ElemType[m_capacity = capacity];
    if (size > capacity) size = capacity;
    for (m_size = 0; m_size < size; m_pData[m_size++] = default_val);
}

template<typename ElemType, int capacity>
inline vector<ElemType, capacity>::vector(const ElemType arr[], int len)
{
    clone(arr, 0, len);
}

template<typename ElemType, int capacity>
inline vector<ElemType, capacity>::vector(const ElemType arr[], int left, int right)
{
    clone(arr, left, right);
}

template<typename ElemType, int capacity>
inline vector<ElemType, capacity>::vector(const vector& vec)
{
    clone(vec.m_pData, 0, vec.m_size);
}

template<typename ElemType, int capacity>
inline vector<ElemType, capacity>::vector(const vector& vec, int left, int right)
{
    clone(vec.m_pData, left, right);
}

template<typename ElemType, int capacity>
inline vector<ElemType, capacity>::vector(const List<ElemType>& li)
{
    clone(li, 0, (int)li.size());
}

template<typename ElemType, int capacity>
inline vector<ElemType, capacity>::vector(const List<ElemType>& li, int left, int right)
{
    clone(li, left, right);
}

template<typename ElemType, int capacity>
inline vector<ElemType, capacity>::~vector()
{
    delete[] m_pData;
    m_pData = nullptr;
}

template<typename ElemType, int capacity>
inline int vector<ElemType, capacity>::size() const
{
    return m_size;
}

template<typename ElemType, int capacity>
inline bool vector<ElemType, capacity>::empty() const
{
    return !m_size;
}

template<class ElemType, int capacity>
inline int vector<ElemType, capacity>::indexOf(const ElemType& el, int left, int right) const
{
    while ((left < right--) && (el != m_pData[right]));
    return right;
}

template<typename ElemType, int capacity>
inline int vector<ElemType, capacity>::indexOf(const ElemType& el) const
{
    return indexOf(el, 0, m_size);
}

template<typename ElemType, int capacity>
inline int vector<ElemType, capacity>::indexOfSorted(const ElemType& el, Order order) const
{
    return indexOfSorted(el, 0, m_size, order);
}

template<typename ElemType, int capacity>
inline int vector<ElemType, capacity>::indexOfSorted(const ElemType& el, int left, int right, Order order) const
{
    return binSearch(el, left, right, order);
}

template<typename ElemType, int capacity>
inline void vector<ElemType, capacity>::sort(int left, int right, Order order, int method)
{
    switch (method)
    {
    case 0: return bubbleSort(left, right, order);
    case 1: return selectionSort(left, right, order);
    case 2: return mergeSort(left, right, order);
    case 3: return heapSort(left, right, order);
    case 4: return quickSort(left, right, order);
    case 5:return shellSort(left, right, order);
    default:  return quickSort(left, right, order);
    }
}

template<typename ElemType, int capacity>
inline void vector<ElemType, capacity>::sort(Order order, int method)
{
    return sort(0, m_size, order, method);
}

template<typename ElemType, int capacity>
inline void vector<ElemType, capacity>::shuffle(int left, int right)
{
    ElemType* p = m_pData + left;
    for (int i = right - left; i > 0; i--) cptea::swap(p[i - 1], p[rand() % i]);
}

template<typename ElemType, int capacity>
inline void vector<ElemType, capacity>::shuffle()
{
    return shuffle(0, m_size);
}

template<typename ElemType, int capacity>
inline int vector<ElemType, capacity>::deduplicate()
{
    int oldSize = m_size;
    int i = 1;
    while (i < m_size)
        if (indexOf(m_pData[i], 0, i) < 0) i++;
        else remove(i);
    return oldSize - m_size;
}

template<typename ElemType, int capacity>
inline int vector<ElemType, capacity>::deduplicateBySorted()
{
    int i = 0, j = 0;
    while (++j < m_size)
        if (m_pData[i] != m_pData[j]) m_pData[++i] = m_pData[j];
    m_size = ++i;
    shrink();
    return j - i;
}

template<typename ElemType, int capacity>
inline ElemType& vector<ElemType, capacity>::operator[](int index)
{
    return m_pData[index];
}

template<typename ElemType, int capacity>
inline const ElemType& vector<ElemType, capacity>::operator[](int index) const
{
    return m_pData[index];
}

template<typename ElemType, int capacity>
inline int vector<ElemType, capacity>::remove(int left, int right)
{
    if (left == right) return 0;
    while (right < m_size) m_pData[left++] = m_pData[right++];
    m_size = left;
    shrink();
    return right - left;
}

template<typename ElemType, int capacity>
inline ElemType vector<ElemType, capacity>::remove(int index)
{
    ElemType el = m_pData[index];
    remove(index, index + 1);
    return el;
}

template<typename ElemType, int capacity>
inline int vector<ElemType, capacity>::insert(const ElemType& el, int index)
{
    expand();
    for (int i = m_size; i > index; i--) m_pData[i] = m_pData[i - 1];
    m_pData[index] = el;
    m_size++;
    return index;
}

template<typename ElemType, int capacity>
inline int vector<ElemType, capacity>::insert(const ElemType& el)
{
    return insert(el, m_size);
}

template<typename ElemType, int capacity>
inline void vector<ElemType, capacity>::traverse(void(*handle)(ElemType&))
{
    for (int i = 0; i < m_size; i++) handle(m_pData[i]);
}

template<typename ElemType, int capacity>
template<typename T>
inline void vector<ElemType, capacity>::traverse(T& handle)
{
    for (int i = 0; i < m_size; i++) handle(m_pData[i]);
}

template<class ElemType, int capacity>
inline void vector<ElemType, capacity>::clone(const ElemType arr[], int left, int right)
{
    m_pData = new ElemType[m_capacity = 2 * (right - left)];
    for (m_size = 0; left < right; m_pData[m_size++] = arr[left++]);
}

template<class ElemType, int capacity>
inline void vector<ElemType, capacity>::clone(const List<ElemType>& li, int left, int right)
{
    m_pData = new ElemType[m_capacity = 2 * (right - left)];
    m_size = 0;
    for (auto first = li.begin() + left, last = li.begin() + right; first != last; *(m_pData + m_size++) = *first++);
}

template<typename ElemType, int capacity>
inline void vector<ElemType, capacity>::expand()
{
    if (m_size < m_capacity) return;
    if (m_capacity < capacity) m_capacity = capacity;
    ElemType* pTemp = m_pData;
    m_pData = new ElemType[m_capacity <<= 1];
    for (int i = 0; i < m_size; i++) m_pData[i] = pTemp[i];
    delete[] pTemp;
}

template<typename ElemType, int capacity>
inline void vector<ElemType, capacity>::shrink()
{
    if (m_capacity < capacity << 1) return;
    if (m_size << 2 > m_capacity) return;
    if (m_capacity < capacity) m_capacity = capacity;
    ElemType* pTemp = m_pData;
    m_pData = new ElemType[m_capacity >>= 1];
    for (int i = 0; i < m_size; i++) *(m_pData + i) = *(pTemp + i);
    delete[] pTemp;
}

template<typename ElemType, int capacity>
inline int vector<ElemType, capacity>::extremum(int left, int right, Order order)
{
    int maximum = right;
    while (left < right--)
        if (!order(m_pData[right], m_pData[maximum])) maximum = right;
    return maximum;
}

template<typename ElemType, int capacity>
inline int vector<ElemType, capacity>::min(int left, int right)
{
    extremum(left, right, cptea::Asc);
}

template<typename ElemType, int capacity>
inline int vector<ElemType, capacity>::max(int left, int right)
{
    extremum(left, right, cptea::Desc);
}

template<typename ElemType, int capacity>
inline void vector<ElemType, capacity>::merge(int left, int middle, int right, Order order)
{
    ElemType* pLeft = m_pData + left;
    int lenLeft = middle - left;
    ElemType* pTemp = new ElemType[lenLeft];
    for (int i = 0; i < lenLeft; i++) pTemp[i] = pLeft[i];
    int lenRight = right - middle;
    ElemType* pRight = m_pData + middle;
    for (int i = 0, j = 0, k = 0; j < lenLeft; )
        pLeft[i++] = (lenRight <= k || order(pTemp[j], pRight[k])) ? pTemp[j++] : pRight[k++];
    delete[] pTemp;
}

template<typename ElemType, int capacity>
inline int vector<ElemType, capacity>::partition(int left, int right, Order order)
{
    cptea::swap(m_pData[left], m_pData[left + rand() % (right - left)]);
    ElemType   pivot = m_pData[left];
    int m = left;
    for (int k = left + 1; k < right; k++)
        if (!order(pivot, m_pData[k])) cptea::swap(m_pData[++m], m_pData[k]);
    cptea::swap(m_pData[left], m_pData[m]);
    return m;
}

template<typename ElemType, int capacity>
inline int vector<ElemType, capacity>::binSearch(const ElemType& el, int left, int right, Order order) const
{
    while (left < right)
    {
        int middle = (left + right) >> 1;
        (!order(m_pData[middle], el)) ? right = middle : left = middle + 1;
    }
    return --left;
}

template<typename ElemType, int capacity>
inline void vector<ElemType, capacity>::bubbleSort(int left, int right, Order order)
{
    for (int last = --right; left < right; right = last)
        for (int i = last = left; i < right; i++)
            if (!order(m_pData[i], m_pData[i + 1]))
                cptea::swap(m_pData[last = i], m_pData[i + 1]);
}

template<typename ElemType, int capacity>
inline void vector<ElemType, capacity>::selectionSort(int left, int right, Order order)
{
    while (left < --right) cptea::swap(m_pData[extremum(left, right, order)], m_pData[right]);
}

template<typename ElemType, int capacity>
inline void vector<ElemType, capacity>::mergeSort(int left, int right, Order order)
{
    if (right - left < 2) return;
    int middle = (left + right) >> 1;
    mergeSort(left, middle, order);
    mergeSort(middle, right, order);
    merge(left, middle, right, order);
}

template<typename ElemType, int capacity>
inline void vector<ElemType, capacity>::heapSort(int left, int right, Order order)
{
    ElemType* p = m_pData + left;
    int n = right - left;
    cptea::heapify(p, n, order);
    while (0 < --n)
    {
        cptea::swap(p[0], p[n]);
        cptea::percolateDown(p, n, 0, order);
    }
}

template<typename ElemType, int capacity>
inline void vector<ElemType, capacity>::quickSort(int left, int right, Order order)
{
    if (right - left < 2) return;
    int middle = partition(left, right, order);
    quickSort(left, middle, order);
    quickSort(middle + 1, right, order);
}

template<typename ElemType, int capacity>
inline void vector<ElemType, capacity>::shellSort(int left, int right, Order order)
{
    for (int d = 0x3FFFFFFF; 0 < d; d >>= 1)
        for (int j = left + d; j < right; j++)
        {
            ElemType   x = m_pData[j];
            int i = j - d;
            while (left <= i && !order(m_pData[i], x))
            {
                m_pData[i + d] = m_pData[i];
                i -= d;
            }
            m_pData[i + d] = x;
        }
}

template<class T, int cap>
inline std::ostream& operator<<(std::ostream& os, const vector<T, cap>& vec)
{
    for (int idx = 0; idx < vec.m_size; idx++)
        os << vec.m_pData[idx] << "\t ";
    return os << std::endl;
}

#endif
