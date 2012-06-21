#ifndef PYTHONIC_PARALLEL_H
#define PYTHONIC_PARALLEL_H
#include <iterator>

namespace pythonic {

    /* pmap */
    template <typename Operator, typename List0, typename... Iterators>
        auto _pmap(Operator& op, List0 const& seq, Iterators... iterators)
        -> core::list< decltype(op(seq.begin(), *iterators...)) >
        {
            auto n = std::distance(seq.begin(), seq.end());
            decltype(_pmap(op,seq, iterators...)) s(n);
#pragma omp parallel for
            for(decltype(n) i =0; i<n ;i++)
                s[i]= op(seq[i], *(iterators+i)...);
            return s;
        }

    template <typename Operator, typename List0, typename... ListN>
        auto pmap(Operator op, List0 const& seq, ListN const &... lists)
        -> decltype( _pmap(op, seq, lists.begin()...) )
        {
            return _pmap(op, seq, lists.begin()...);
        }

    PROXY(pythonic,pmap);
}
#endif
