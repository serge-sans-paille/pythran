#ifndef PYTHONIC_TYPES_NUMPY_FEXPR_HPP
#define PYTHONIC_TYPES_NUMPY_FEXPR_HPP

#include "pythonic/types/nditerator.hpp"

namespace pythonic {

    namespace types {

        /* Expression template for numpy expressions - filter
         */
        template<class Arg, class F>
            struct numpy_fexpr {
                static constexpr size_t value = 1;
                typedef typename std::remove_reference<Arg>::type::dtype value_type;
                typedef typename std::remove_reference<Arg>::type::dtype dtype;

                typedef nditerator<numpy_fexpr> iterator;
                typedef const_nditerator<numpy_fexpr> const_iterator;

                typename assignable<typename std::remove_reference<Arg>::type>::type arg;
                array<long, value> shape;
                utils::shared_ref<raw_array<long>> indices;
                long *buffer;

                numpy_fexpr() {}
                numpy_fexpr(numpy_fexpr const&) = default;
                numpy_fexpr(numpy_fexpr&&) = default;

                template<class FIter, class O>
                void _copy_mask(FIter fiter, FIter fend, O& out, long &index, utils::int_<1>) {
                    for(; fiter!=fend; ++fiter, ++index)
                        if(*fiter) {
                            *out++ = index;
                        }
                }
                template<class FIter, class O, size_t N>
                void _copy_mask(FIter fiter, FIter fend, O& out, long & index, utils::int_<N>) {
                    for(; fiter != fend; ++fiter) {
                        _copy_mask((*fiter).begin(), (*fiter).end(), out, index, utils::int_<N-1>());
                    }
                }

                numpy_fexpr(Arg const &arg, F const& filter) : arg(arg), indices(arg.size()), buffer(indices->data)
                {
                    auto iter = buffer;
                    long index = 0;
                    _copy_mask(filter.begin(), filter.end(), iter, index, utils::int_<Arg::value>());
                    shape[0] = { iter - buffer };
                }

                template<class E>
                typename std::enable_if<is_iterable<E>::value, numpy_fexpr&>::type
                operator=(E const& expr) {
                    std::copy(expr.begin(), expr.end(), begin());
                    return *this;
                }
                template<class E>
                typename std::enable_if<not is_iterable<E>::value, numpy_fexpr&>::type
                operator=(E const& expr) {
                    std::fill(begin(), end(), expr);
                    return *this;
                }
                numpy_fexpr& operator=(numpy_fexpr const& expr) {
                    std::copy(expr.begin(), expr.end(), begin());
                    return *this;
                }

                const_iterator begin() const { return const_iterator(*this, 0); }
                const_iterator end() const { return const_iterator(*this, shape[0]); }

                iterator begin() { return iterator(*this, 0); }
                iterator end() { return iterator(*this, shape[0]); }


                dtype fast(long i) const
                {
                    return *(arg.fbegin() + buffer[i]);
                }
                dtype& fast(long i)
                {
                    return *(arg.fbegin() + buffer[i]);
                }
                auto operator[](long i) const -> decltype(this->fast(i))
                {
                    if(i<0) i += shape[0];
                    return fast(i);
                }
                auto operator[](long i) -> decltype(this->fast(i))
                {
                    if(i<0) i += shape[0];
                    return fast(i);
                }
                long size() const { return shape[0]; }
            };

    }
}

#endif

