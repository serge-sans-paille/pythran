#ifndef PYTHONIC_NUMPY_INTERSECT1D_HPP
#define PYTHONIC_NUMPY_INTERSECT1D_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/combined.hpp"
#include "pythonic/numpy/asarray.hpp"

#include <algorithm>

namespace pythonic {

    namespace numpy {
        template<class E, class F>
            types::ndarray<typename __combined<typename types::numpy_expr_to_ndarray<E>::T,
                                               typename types::numpy_expr_to_ndarray<F>::T
                                              >::type,
                           1>
            intersect1d(E const& e, F const& f)
            {
                typedef typename __combined<typename types::numpy_expr_to_ndarray<E>::T,
                                            typename types::numpy_expr_to_ndarray<F>::T
                                           >::type T;
                auto ae = asarray(e);
                auto af = asarray(f);
                std::set<T> sae(ae.fbegin(), ae.fend());
                std::set<T> found;
                types::list<T> lout(0);
                lout.reserve(sae.size());
                for(auto iter = af.fbegin(), end = af.fend(); iter != end; ++iter)
                {
                    auto curr = *iter;
                    if(sae.find(curr) != sae.end() and found.find(curr) == found.end()) {
                        found.insert(curr);
                        lout.push_back(curr);
                    }
                }
                std::sort(lout.begin(), lout.end());
                return types::ndarray<T, 1> (lout);
            }

        PROXY(pythonic::numpy, intersect1d);

    }

}

#endif

