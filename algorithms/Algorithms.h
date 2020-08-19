#ifndef __CPTEA_ALGORITHMS_INCLUDE
#define __CPTEA_ALGORITHMS_INCLUDE
#include <cstdint>
#endif

#ifndef __CPTEA_ALGORTIHMS_FUNC_DEF
#define __CPTEA_ALGORTIHMS_FUNC_DEF

#define LEq Asc
#define GEq Desc

#define Parent(i) (((i)-1) >> 1)
#define LChild(i) (1 + ((i) << 1))
#define RChild(i) ((1 + (i)) << 1)
#define InHeap(n, i) (((-1) < (i)) && ((i) < (n)))
#define LChildValid(n, i) InHeap(n, LChild(i))
#define RChildValid(n, i) InHeap(n, RChild(i))
#define Compare(PQ, i, j, order) (!order(PQ[j], PQ[i]) ? j : i)
#define ProperParent(PQ, n, i, order) (RChildValid(n, i) ? Compare(PQ, Compare(PQ, i, LChild(i), order), RChild(i), order) : (LChildValid(n, i) ? Compare(PQ, i, LChild(i), order) : i))

namespace cptea
{
    using size_type = std::int64_t;
    using position_type = std::int64_t;

    template <typename ElemType> bool Asc(const ElemType&, const ElemType&);
    template <typename ElemType> bool Desc(const ElemType&, const ElemType&);
    template <typename ElemType> void swap(ElemType&, ElemType&);
    template <typename ElemType> bool eq(const ElemType&, const ElemType&);

    template <typename ElemType>
    using Order = bool (*)(const ElemType&, const ElemType&);

    template <typename ElemType>
    position_type percolateDown(ElemType arr[], size_type len, position_type idx, cptea::Order<ElemType> order);

    template <typename ElemType>
    void heapify(ElemType arr[], size_type len, cptea::Order<ElemType> order);
}

#endif

#ifndef __CPTEA_ALGORTIHMS_CLASS_DEF
#define __CPTEA_ALGORTIHMS_CLASS_DEF
#endif

#ifndef __CPTEA_ALGORTIHMS_IMPL
#define __CPTEA_ALGORTIHMS_IMPL

template <typename ElemType>
void cptea::swap(ElemType& x, ElemType& y)
{
    ElemType temp = x;
    x = y;
    y = temp;
}

template<typename ElemType>
bool cptea::Asc(const ElemType& x, const ElemType& y)
{
    return x <= y;
}

template<typename ElemType>
bool cptea::Desc(const ElemType& x, const ElemType& y)
{
    return x >= y;
}

template<typename ElemType>
bool cptea::eq(const ElemType& x, const ElemType& y)
{
    return x == y;
}

template <typename ElemType>
cptea::position_type cptea::percolateDown(ElemType arr[], size_type len, position_type idx, cptea::Order<ElemType> order)
{
    size_type j;
    while (idx != (j = ProperParent(arr, len, idx, order)))
    {
        cptea::swap(arr[idx], arr[j]);
        idx = j;
    }
    return idx;
}

template <typename ElemType>
void cptea::heapify(ElemType arr[], size_type len, cptea::Order<ElemType> order)
{
    for (size_type i = (len >> 1) - 1; i >= 0; i--) cptea::percolateDown(arr, len, i, order);
}

#endif
