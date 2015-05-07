#ifndef PYTHONIC_NUMPY_NDENUMERATE_HPP
#define PYTHONIC_NUMPY_NDENUMERATE_HPP

#include "pythonic/include/numpy/ndenumerate.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/numpy_type.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            ndenumerate_iterator<E>::ndenumerate_iterator()
            {}

        template<class E>
            ndenumerate_iterator<E>::ndenumerate_iterator(E const& expr, long first) :
                index(first),
                expr(expr),
                iter(expr.buffer)
            {}

        template<class E>
            std::tuple<types::array<long, types::numpy_expr_to_ndarray<E>::N>,
                       typename types::numpy_expr_to_ndarray<E>::type::dtype>
            ndenumerate_iterator<E>::operator*()
            {
                constexpr long N = types::numpy_expr_to_ndarray<E>::N;
                types::array<long, N> out;
                auto&& shape = expr.shape();
                long mult = 1;
                for(long j=N-1; j>0; j--)
                {
                    out[j] = (index/mult)%shape[j];
                    mult*=shape[j];
                }
                out[0] = index/mult;
                return std::tuple<types::array<long, types::numpy_expr_to_ndarray<E>::N>,
                                  typename types::numpy_expr_to_ndarray<E>::type::dtype>(out, *iter);
            }

        template<class E>
            ndenumerate_iterator<E>& ndenumerate_iterator<E>::operator++()
            {
                ++index, ++iter;
                return *this;
            }

        template<class E>
            ndenumerate_iterator<E>& ndenumerate_iterator<E>::operator+=(long n)
            {
                index+=n, iter+=n;
                return *this;
            }

        template<class E>
            bool ndenumerate_iterator<E>::operator!=(ndenumerate_iterator<E> const& other)
            {
                return index != other.index;
            }

        template<class E>
            bool ndenumerate_iterator<E>::operator<(ndenumerate_iterator<E> const& other)
            {
                return index < other.index;
            }

        template<class E>
            long ndenumerate_iterator<E>::operator-(ndenumerate_iterator<E> const& other)
            {
                return index - other.index;
            }

        template<class E>
            _ndenumerate<E>::_ndenumerate()
            {}

        template<class E>
            _ndenumerate<E>::_ndenumerate(E const &expr) :
                ndenumerate_iterator<E>(expr, 0),
                expr(expr),
                end_iter(expr, expr.flat_size())
            {}

        template<class E>
            typename _ndenumerate<E>::iterator & _ndenumerate<E>::begin()
            {
                return *this;
            }

        template<class E>
            typename _ndenumerate<E>::iterator const & _ndenumerate<E>::begin() const
            {
                return *this;
            }

        template<class E>
            typename _ndenumerate<E>::iterator _ndenumerate<E>::end() const
            {
                return end_iter;
            }

        template<class T, size_t N>
            _ndenumerate<types::ndarray<T,N>> ndenumerate(types::ndarray<T,N> const& expr)
            {
                return {expr};
            }

        NUMPY_EXPR_TO_NDARRAY0_IMPL(ndenumerate);
        PROXY_IMPL(pythonic::numpy, ndenumerate);

    }

}

#endif
