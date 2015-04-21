#ifndef PYTHONIC_NUMPY_ARRAYEQUAL_HPP
#define PYTHONIC_NUMPY_ARRAYEQUAL_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/all.hpp"

namespace pythonic {

    namespace numpy {
        template<class U, class V>
            typename std::enable_if<types::has_shape<U>::value and types::has_shape<V>::value,bool>::type array_equal(U const& u, V const&v) {
                if(u.shape() == v.shape()) {
                    return all(u == v);
                }
                return false;
            }
        template<class U, class V>
            typename std::enable_if<types::has_shape<V>::value,bool>::type array_equal(types::list<U> const& u, V const&v) {
                return array_equal(typename types::numpy_expr_to_ndarray<types::list<U>>::type(u), v);
            }
        template<class U, class V>
            typename std::enable_if<types::has_shape<U>::value,bool>::type array_equal(U const& u, types::list<V> const&v) {
                return array_equal(u, typename types::numpy_expr_to_ndarray<types::list<V>>::type(v));
            }
        template<class U, class V>
            bool array_equal(types::list<U> const& u, types::list<V> const&v) {
                return array_equal(typename types::numpy_expr_to_ndarray<types::list<U>>::type(u), typename types::numpy_expr_to_ndarray<types::list<V>>::type(v));
            }

        PROXY(pythonic::numpy, array_equal);

    }

}

#endif

