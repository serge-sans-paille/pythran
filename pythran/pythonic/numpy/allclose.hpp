#ifndef PYTHONIC_NUMPY_ALLCLOSE_HPP
#define PYTHONIC_NUMPY_ALLCLOSE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/abs.hpp"
#include "pythonic/numpy/isfinite.hpp"

namespace pythonic {

    namespace numpy {
        template<class I0, class I1>
            bool _allclose(I0 begin, I0 end, I1 ibegin, double rtol, double atol, utils::int_<1>)
            {
                for(; begin != end; ++begin, ++ibegin) {
                    auto u = *begin;
                    auto v = *ibegin;
                    if(((!proxy::isfinite()(u) || !proxy::isfinite()(v)) && u != v) ||  // Infinite and NaN cases
                        proxy::abs()(u-v) > (atol + rtol * proxy::abs()(v))) {
                        return false;
                    }
                }
                return true;
            }
        template<class I0, class I1, size_t N>
            bool _allclose(I0 begin, I0 end, I1 ibegin,  double rtol, double atol, utils::int_<N>)
            {
                for(; begin != end; ++begin, ++ibegin)
                    if(not _allclose((*begin).begin(), (*begin).end(), (*ibegin).begin(), rtol, atol, utils::int_<N - 1>()))
                        return false;
                return true;
            }
        template<class U, class V>
            bool allclose(U const& u, V const& v, double rtol=1e-5, double atol=1e-8) {
                return _allclose(u.begin(), u.end(), v.begin(), rtol, atol, utils::int_<types::numpy_expr_to_ndarray<U>::N>());
            }

        PROXY(pythonic::numpy, allclose);

    }

}

#endif

