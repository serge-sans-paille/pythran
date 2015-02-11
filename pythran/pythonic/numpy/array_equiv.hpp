#ifndef PYTHONIC_NUMPY_ARRAYEQUIV_HPP
#define PYTHONIC_NUMPY_ARRAYEQUIV_HPP

#include "pythonic/numpy/array_equal.hpp"
#include "pythonic/numpy/asarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class I0, class U>
            bool _array_equiv(I0 vbegin, I0 vend, U const& uu);

        template<class U, class V>
            typename std::enable_if<types::numpy_expr_to_ndarray<U>::N == types::numpy_expr_to_ndarray<V>::N, bool>::type
            array_equiv(U const& u, V const &v) {
                return array_equal(u, v);
            }

        template<class U, class V>
            typename std::enable_if<types::numpy_expr_to_ndarray<U>::N < types::numpy_expr_to_ndarray<V>::N, bool>::type
            array_equiv(U const& u, V const &v) {
                if(v.flat_size() % u.flat_size() == 0) {
                    // requires allocation for u' as it is used multiple times.
                    return _array_equiv(v.begin(), v.end(), asarray(u));
                }
                return false;
            }

        template<class U, class V>
            typename std::enable_if<(types::numpy_expr_to_ndarray<U>::N > types::numpy_expr_to_ndarray<V>::N), bool>::type
            array_equiv(U const& u, V const &v) {
                    return array_equiv(v,u);
            }

        template<class I0, class U>
            bool _array_equiv(I0 vbegin, I0 vend, U const& uu)
            {
                for(; vbegin != vend; ++vbegin){
                    if(not array_equiv(uu, *vbegin))
                        return false;
                }
                return true;
            }


        PROXY(pythonic::numpy, array_equiv);

    }

}

#endif

