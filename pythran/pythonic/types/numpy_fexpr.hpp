#ifndef PYTHONIC_TYPES_NUMPY_FEXPR_HPP
#define PYTHONIC_TYPES_NUMPY_FEXPR_HPP

#include "pythonic/types/nditerator.hpp"
#include "pythonic/types/numexpr_to_ndarray.hpp"

namespace pythonic {

    namespace types {

        /* Expression template for numpy expressions - filter
         */
        template<class Arg, class F>
            // numpy_fexpr is a wrapper around a ndarray. It stores raw indices of values
            // where filters information is True so that we can jump to the correct value 
            // in the ndarray buffer in O(1)
            struct numpy_fexpr {
                static const bool is_vectorizable = false;
                static const bool is_strided = true;
                //TODO accept multidimensionnal filtered expression
                //>>> a = numpy.arange(2*3*4).reshape(2,3,4)
                //array([[[ 0,  1,  2,  3],
                //        [ 4,  5,  6,  7],
                //        [ 8,  9, 10, 11]],
                //       [[12, 13, 14, 15],
                //        [16, 17, 18, 19],
                //        [20, 21, 22, 23]]])
                //>>> a[[0,1],[0,1], [0, 0]]
                //array([ 0, 16])
                static constexpr size_t value = 1;
                typedef typename std::remove_reference<Arg>::type::dtype value_type;
                typedef typename std::remove_reference<Arg>::type::dtype dtype;

                typedef nditerator<numpy_fexpr> iterator;
                typedef const_nditerator<numpy_fexpr> const_iterator;

                typename assignable<typename std::remove_reference<Arg>::type>::type arg;
                array<long, value> _shape;
                array<long, value> const& shape() const { return _shape; }
                utils::shared_ref<raw_array<long>> indices;
                long *buffer;

                numpy_fexpr() = default;
                numpy_fexpr(numpy_fexpr const&) = default;
                numpy_fexpr(numpy_fexpr&&) = default;
                numpy_fexpr(Arg const &arg, F const& filter) : arg(arg), indices(arg.flat_size()), buffer(indices->data)
                {
                    auto iter = buffer;
                    long index = 0;
                    _copy_mask(filter.begin(), filter.end(), iter, index, utils::int_<std::remove_reference<typename std::remove_cv<Arg>::type>::type::value>());
                    _shape[0] = { iter - buffer };
                }

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
                template<class E>
                numpy_fexpr& operator+=(E const& expr) {
                    return *(this) = *this + expr;
                }
                template<class E>
                numpy_fexpr& operator-=(E const& expr) {
                    return *(this) = *this - expr;
                }
                template<class E>
                numpy_fexpr& operator*=(E const& expr) {
                    return *(this) = *this * expr;
                }
                template<class E>
                numpy_fexpr& operator/=(E const& expr) {
                    return *(this) = *this / expr;
                }
                template<class E>
                numpy_fexpr& operator&=(E const& expr) {
                    return *(this) = *this & expr;
                }
                template<class E>
                numpy_fexpr& operator|=(E const& expr) {
                    return *(this) = *this | expr;
                }
                template<class E>
                numpy_fexpr& operator>>=(E const& expr) {
                    return *(this) = *this >> expr;
                }
                template<class E>
                numpy_fexpr& operator<<=(E const& expr) {
                    return *(this) = *this << expr;
                }

                const_iterator begin() const { return const_iterator(*this, 0); }
                const_iterator end() const { return const_iterator(*this, _shape[0]); }

                iterator begin() { return iterator(*this, 0); }
                iterator end() { return iterator(*this, _shape[0]); }


                dtype fast(long i) const
                {
                    return *(arg.fbegin() + buffer[i]);
                }
                dtype& fast(long i)
                {
                    return *(arg.fbegin() + buffer[i]);
                }
#ifdef USE_BOOST_SIMD
                template<class I> // template to prevent automatic instantiation when the type is not vectorizable
                void load(I) const {
                  static_assert(I::this_should_never_happen, "this is *not* vectorizable");
                }
#endif
                auto operator[](long i) const -> decltype(this->fast(i))
                {
                    if(i<0) i += _shape[0];
                    return fast(i);
                }
                auto operator[](long i) -> decltype(this->fast(i))
                {
                    if(i<0) i += _shape[0];
                    return fast(i);
                }
                template<class E>
                    typename std::enable_if<is_numexpr_arg<E>::value, numpy_fexpr<numpy_fexpr, E>>::type
                    fast(E const& expr) const {
                        return numpy_fexpr<numpy_fexpr, E>(*this, expr);
                    }
                template<class E>
                    typename std::enable_if<is_numexpr_arg<E>::value, numpy_fexpr<numpy_fexpr, E>>::type
                    operator[](E const& expr) const {
                        return fast(expr);
                    }
                long flat_size() const { return _shape[0]; }
            };

    }

    template<class Arg, class F>
        struct assignable<types::numpy_fexpr<Arg, F>>
        {
            typedef typename types::numpy_expr_to_ndarray<types::numpy_fexpr<Arg, F>>::type type;
        };
    template<class Arg, class F>
        struct lazy<types::numpy_fexpr<Arg,F>>
        {
            typedef types::numpy_fexpr<typename lazy<Arg>::type, typename lazy<F>::type> type;
        };
}

#endif

