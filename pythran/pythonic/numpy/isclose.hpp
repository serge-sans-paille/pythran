#ifndef PYTHONIC_NUMPY_ISCLOSE_HPP
#define PYTHONIC_NUMPY_ISCLOSE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/is_finite.hpp>

// nt2 does not handle bool specialization, which is indeed a corner case...
namespace nt2 {
  constexpr bool is_finite(bool) { return true;}
  constexpr bool is_nan(bool) { return false;}
}

namespace pythonic {

    namespace numpy {
        template<class I0, class I1, class O>
            void _isclose(I0 begin, I0 end, I1 ibegin, O obegin, double rtol, double atol, bool equal_nan, utils::int_<1>)
            {
                for(; begin != end; ++begin, ++ibegin, ++obegin) {
                    auto u = *begin;
                    auto v = *ibegin;
                    if (nt2::is_finite(u) && nt2::is_finite(v))
                        *obegin = std::abs(u-v) <= (atol + rtol * std::abs(v));
                    else if(nt2::is_nan(u) && nt2::is_nan(v))
                        *obegin = equal_nan;
                    else
                        *obegin = (u == v);
                }
            }

        template<class I0, class I1, class O, size_t N>
            void _isclose(I0 begin, I0 end, I1 ibegin, O obegin,  double rtol, double atol, bool equal_nan, utils::int_<N>)
            {
                for(; begin != end; ++begin, ++ibegin, ++obegin)
                    _isclose((*begin).begin(), (*begin).end(), (*ibegin).begin(), (*obegin).begin(), rtol, atol, equal_nan, utils::int_<N - 1>());
            }


        // Same size arrays TODO broadcasted cases
        template<class U, class V>
            typename std::enable_if<types::numpy_expr_to_ndarray<U>::N == types::numpy_expr_to_ndarray<V>::N,
                                    types::ndarray<bool, types::numpy_expr_to_ndarray<V>::N>
                                   >::type
            isclose(U const& u, V const& v, double rtol=1e-5, double atol=1e-8, bool equal_nan=false) {
                types::ndarray<bool, types::numpy_expr_to_ndarray<U>::N> out(u.shape, false);
                _isclose(u.begin(), u.end(), v.begin(), out.begin(), rtol, atol, equal_nan, utils::int_<types::numpy_expr_to_ndarray<U>::N>());
                return out;
            }

        PROXY(pythonic::numpy, isclose);

    }

}

#endif

