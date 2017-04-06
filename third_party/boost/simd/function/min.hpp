//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_MIN_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_MIN_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-arithmetic
    This function object computes the smallest of its parameter.


    @par Header <boost/simd/function/min.hpp>

    @par Notes
    For any given value @c x and @c y of type @c T:

    Using `min(x, y)` is similar to `(x <  y) ? x : y` which is the standard behaviour.

    With this definition min(x, @ref Nan) should return x...

    On some systems the intrinsic used returns Nan as soon x or y is a nan.
    So the real definition of our min function must add: but if y is Nan the result is system dependent.

    This can be corrected using the pedantic_ decorator that ensures the standard behaviour at a cost.

    @par Decorators

     - pedantic_ ensures the standard behaviour.
     - std_ call std::min.

    @see min,  minnum, minnummag, minmag, minmod

    @par Example:

      @snippet min.cpp min

    @par Possible output:

      @snippet min.txt min

  **/
  Value min(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/min.hpp>
#include <boost/simd/function/simd/min.hpp>

#endif
