#ifndef PYTHONIC_PARALLEL_H
#define PYTHONIC_PARALLEL_H
#include <iterator>

namespace pythonic {

    /* pmap */
    template <typename Operator, typename Sequence0, typename... Iterators>
        auto _pmap(Operator& op, Sequence0 const& seq, Iterators... iterators)
        -> sequence< decltype(op(seq.begin(), *iterators...)) >
        {
            auto n = std::distance(seq.begin(), seq.end());
            decltype(_pmap(op,seq, iterators...)) s(n);
#pragma omp parallel for
            for(decltype(n) i =0; i<n ;i++)
                s[i]= op(seq[i], *(iterators+i)...);
            return s;
        }

    template <typename Operator, typename Sequence0, typename... SequenceN>
        auto pmap(Operator op, Sequence0 const& seq, SequenceN const &... sequences)
        -> decltype( _pmap(op, seq, sequences.begin()...) )
        {
            return _pmap(op, seq, sequences.begin()...);
        }

    PROXY(pythonic,pmap);
}
#endif
