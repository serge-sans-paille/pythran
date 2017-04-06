//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SLIDE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SLIDE_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-swar
    This function object returns a vector extracted from the concatanation
    of `x` and `y` (resp. `x` and itself when only one argument is given).

    @par Header <boost/simd/function/slide.hpp>

    @par Semantic:

    Denote by `L` the common length of `x` and `y`.
    Let `c[i] = x[i]` and `c[i + L] = y[i]`.
    If N is positive then returns `(c[N], c[N + 1], ..., c[N + L - 1])`
    If `N + L - 1 >= 2L` then returns
    `(c[N], c[N + 1], ..., C[2L - 1], 0, ..., 0)`.

    If N is negative then

    @code
    Value r = slide<N>(x, y);
    @endcode

    is equivalent to

    @code
    Value r = slide<L - N>(x, y);
    @endcode

  **/
  ///@{
  template<std::size_t N> Value slide(Value const& x, Value const& y);
  template<std::size_t N> Value slide(Value const& x);
  ///@}
} }
#endif

#include <boost/simd/function/scalar/slide.hpp>
#include <boost/simd/function/simd/slide.hpp>

#endif
