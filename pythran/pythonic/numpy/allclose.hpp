#ifndef PYTHONIC_NUMPY_ALLCLOSE_HPP
#define PYTHONIC_NUMPY_ALLCLOSE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/is_nan.hpp>

namespace pythonic {

    namespace numpy {
        template<class I0, class I1>
            void _allclose(I0 begin, I0 end, I1 ibegin, bool& close,  double rtol, double atol, utils::int_<1>)
            {
                for(; begin != end; ++begin, ++ibegin) {
                    auto u = *begin;
                    auto v = *ibegin;
                    if(nt2::is_nan(v) || nt2::is_nan(u) || std::abs(u-v) > (atol + rtol * std::abs(v))) {
                        close = false;
                        return;
                    }
                }
            }
        template<class I0, class I1, size_t N>
            void _allclose(I0 begin, I0 end, I1 ibegin, bool& close,  double rtol, double atol, utils::int_<N>)
            {
                for(; close and begin != end; ++begin, ++ibegin)
                    _allclose((*begin).begin(), (*begin).end(), (*ibegin).begin(), close, rtol, atol, utils::int_<N - 1>());
            }
        template<class U, class V>
            bool allclose(U const& u, V const& v, double rtol=1e-5, double atol=1e-8) {
                bool close = true;
                _allclose(u.begin(), u.end(), v.begin(), close, rtol, atol, utils::int_<types::numpy_expr_to_ndarray<U>::N>());
                return close;
            }

        PROXY(pythonic::numpy, allclose);

    }

}

#endif

