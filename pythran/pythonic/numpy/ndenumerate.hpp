#ifndef PYTHONIC_NUMPY_NDENUMERATE_HPP
#define PYTHONIC_NUMPY_NDENUMERATE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/numpy_type.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            struct ndenumerate_iterator : std::iterator<std::random_access_iterator_tag, std::tuple<types::array<long, types::numpy_expr_to_ndarray<E>::N>, typename types::numpy_expr_to_ndarray<E>::type::dtype> > {
                long index;
                E const& expr;
                typename types::numpy_expr_to_ndarray<E>::type::dtype* iter;
                ndenumerate_iterator(){}
                ndenumerate_iterator(E const& expr, long first) : index(first), expr(expr), iter(expr.buffer) {
                }
                std::tuple<types::array<long, types::numpy_expr_to_ndarray<E>::N>, typename types::numpy_expr_to_ndarray<E>::type::dtype> operator*() {
                    types::array<long, types::numpy_expr_to_ndarray<E>::N> out;
                    auto shape = expr.shape();
                    constexpr long N = types::numpy_expr_to_ndarray<E>::N;
                    long mult = 1;
                    for(long j=N-1; j>0; j--) {
                        out[j] = (index/mult)%shape[j];
                        mult*=shape[j];
                    }
                    out[0] = index/mult;
                    return std::tuple<types::array<long, types::numpy_expr_to_ndarray<E>::N>, typename types::numpy_expr_to_ndarray<E>::type::dtype>(out, *iter);
                }
                ndenumerate_iterator& operator++() { ++index, ++iter ; return *this; }
                ndenumerate_iterator& operator+=(long n) { index+=n,iter+=n; return *this; }
                bool operator!=(ndenumerate_iterator const& other) { return index != other.index; }
                bool operator<(ndenumerate_iterator const& other) { return index < other.index; }
                long operator-(ndenumerate_iterator const& other) { return index - other.index; }

            };

        template<class E>
            struct _ndenumerate : ndenumerate_iterator<E> {
                typedef ndenumerate_iterator<E> iterator;
                E expr; // we need to keep one ref over the enumerated sequence alive
                iterator end_iter;

                _ndenumerate() {}
                _ndenumerate(E const &expr) :  ndenumerate_iterator<E>(expr, 0), expr(expr), end_iter(expr, expr.flat_size()) {}
                iterator & begin() { return *this; }
                iterator const & begin() const { return *this; }
                iterator end() const { return end_iter; }
            };

        template<class T, size_t N>
            _ndenumerate<types::ndarray<T,N>> ndenumerate(types::ndarray<T,N> const& expr) {
                return _ndenumerate<types::ndarray<T,N>>{expr};
            }
        NUMPY_EXPR_TO_NDARRAY0(ndenumerate);
        /*
        template<class E>
            _ndenumerate<typename types::numpy_expr_to_ndarray<E>::type> ndenumerate(E const& expr) {
                return _ndenumerate<typename types::numpy_expr_to_ndarray<E>::type>(expr);
            }
            */

        PROXY(pythonic::numpy, ndenumerate);

    }

}

#endif

