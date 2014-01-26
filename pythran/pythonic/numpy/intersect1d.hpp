#ifndef PYTHONIC_NUMPY_INTERSECT1D_HPP
#define PYTHONIC_NUMPY_INTERSECT1D_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/asarray.hpp"

#include <algorithm>

namespace pythonic {

    namespace numpy {
        template<class E, class F>
            types::ndarray<
            decltype(std::declval<typename types::numpy_expr_to_ndarray<E>::type::dtype>()
                    +
                    std::declval<typename types::numpy_expr_to_ndarray<F>::type::dtype>()),
            1>
                intersect1d(E const& e, F const& f)
                {
                    typedef decltype(std::declval<typename types::numpy_expr_to_ndarray<E>::type::dtype>()
                            +
                            std::declval<typename types::numpy_expr_to_ndarray<F>::type::dtype>()) T;
                    auto ae = asarray(e);
                    auto af = asarray(f);
                    std::set<T> sae(ae.buffer, ae.buffer + ae.size());
                    std::set<T> found;
                    types::list<T> lout(0);
                    lout.reserve(sae.size());
                    for(long i=0, n = af.size(); i<n; ++i)
                        if(sae.find(af.at(i)) != sae.end() and found.find(af.at(i)) == found.end()) {
                            found.insert(af.at(i));
                            lout.push_back(af.at(i));
                        }
                    std::sort(lout.begin(), lout.end());
                    return types::ndarray<T, 1> (lout);
                }

        PROXY(pythonic::numpy, intersect1d);

    }

}

#endif

