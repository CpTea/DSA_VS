#ifndef __VECTOR_INCLUDE
#define __VECTOR_INCLUDE
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
    template<class T, unsigned int cap>
    friend std::ostream& operator<<(std::ostream& os, const vector<T, cap>& vec);

public:
    // initialize
    vector(int size = 0, ElemType default_val = 0);
    vector(const ElemType arr[], int len) { clone(arr, 0, len); }
    vector(const ElemType arr[], int left, int right) { clone(arr, left, right); }
    vector(const vector& vec) { clone(vec.m_pData, 0, vec.m_size); }
    vector(const vector& vec, int left, int right) { clone(vec.m_pData, left, right); }
    vector(const List<ElemType>& li) { clone(li, 0, li.size()); }
    vector(const List<ElemType>& li, int left, int right) { clone(li, left, right); }
    ~vector() { delete[] m_pData; m_pData = nullptr; }

    // read only
    int size() const { return m_size; }
    bool empty() const { return !m_size; }
    int indexOf(const ElemType& el, int left, int right) const;
    int indexOf(const ElemType& el) const { return indexOf(el, 0, m_size); }
    int indexOfSorted(const ElemType& el) const { return indexOfSorted(el, 0, m_size); }
    int indexOfSorted(const ElemType& el, int left, int right) const { return binSearch(el, left, right); }
    void sort(int left, int right, int mode = 0);
    void shuffle(int left, int right);
    void deduplicate();
    void deduplicateBySorted();

    // write only
    ElemType& operator[](int index);
    const ElemType& operator[](int index) const;
    int remove(int left, int right);
    ElemType remove(int index);
    int insert(const ElemType& el, int index);
    int insert(const ElemType& el) { return insert(el, m_size); }
    void traverse(void (*)(ElemType&));
    template <typename T> void traverse(T&);

protected:
    void clone(const ElemType arr[], int left, int right);
    void clone(const List<ElemType>& li, int left, int right);
    void expand();
    void shrink();
    int  max(int left, int right);
    void merge(int left, int middle, int right);
    int  partition(int left, int right);

    void bubbleSort(int left, int right);
    void selectionSort(int left, int right);
    void mergeSort(int left, int right);
    void heapSort(int left, int right);
    void quickSort(int left, int right);
    void shellSort(int left, int right);

    int binSearch(const ElemType& el, int left, int right) const;

private:
    ElemType* m_pData;
    int m_size;
    unsigned int m_capacity;
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

template<class ElemType, int capacity>
inline int vector<ElemType, capacity>::indexOf(const ElemType& el, int left, int right) const
{
    while ((left < right--) && (el != m_pData[right]));
    return right;
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
    while (r < m_size) m_pData[left++] = m_pData[right++];
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
inline int vector<ElemType, capacity>::binSearch(const ElemType& el, int left, int right) const
{
    while (left < right) {
        int middle = (left + right) >> 1;
        (m_pData[middle] > el) ? right = middle : left = middle + 1;
    }
    return --left;
}

template<class T, unsigned int cap>
inline std::ostream& operator<<(std::ostream& os, const vector<T, cap>& vec)
{
    for (int idx = 0; idx < vec.m_size; idx++)
        os << vec.m_pData[idx] << '\t';
    return os << std::endl;
}

#endif
