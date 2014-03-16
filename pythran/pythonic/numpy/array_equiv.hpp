#ifndef PYTHONIC_NUMPY_ARRAYEQUIV_HPP
#define PYTHONIC_NUMPY_ARRAYEQUIV_HPP

#include "pythonic/numpy/array_equal.hpp"
#include "pythonic/numpy/asarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class U, class V>
            typename std::enable_if<types::has_shape<U>::value and types::has_shape<V>::value,bool>::type array_equiv(U const& u, V const&v) {
                if(u.shape == v.shape) {
                    return array_equal(u,v);
                }
                else if(u.size() > v.size()) {
                    return array_equiv(v,u);
                }
                else if(v.size()%u.size() ==0) {
                    auto uu = asarray(u);
                    auto vv = asarray(v);
                    for(auto vi = vv.fbegin(), ve = vv.fend(); vi != ve;)
                        for(auto ui = uu.fbegin(), ue = uu.fend(); ui != ue; ++ui, ++vi)
                            if(*ui != *vi)
                                return false;
                    return true;
                }
                return false;
            }
        template<class U, class V>
            typename std::enable_if<types::has_shape<V>::value,bool>::type array_equiv(types::list<U> const& u, V const&v) {
                return array_equiv(typename types::numpy_expr_to_ndarray<types::list<U>>::type(u), v);
            }
        template<class U, class V>
            typename std::enable_if<types::has_shape<U>::value,bool>::type array_equiv(U const& u, types::list<V> const&v) {
                return array_equiv(u, typename types::numpy_expr_to_ndarray<types::list<V>>::type(v));
            }
        template<class U, class V>
            bool array_equiv(types::list<U> const& u, types::list<V> const&v) {
                return array_equiv(typename types::numpy_expr_to_ndarray<types::list<U>>::type(u), typename types::numpy_expr_to_ndarray<types::list<V>>::type(v));
            }

        PROXY(pythonic::numpy, array_equiv);

    }

}

#endif

