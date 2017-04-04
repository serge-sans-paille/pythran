//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_MAX_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_MAX_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-arithmetic
    This function object computes the largest of its parameter.


    @par Header <boost/simd/function/max.hpp>

    @par Notes
    For any given value @c x and @c y of type @c T:

    Using `max(x, y)` is similar to `(x > y) ? x : y` which is the standard behaviour.

    With this definition max(x, @ref Nan) should return x...

    On some systems the intrinsic used returns Nan as soon x or y is a nan.
    So the real definition of our max function must add: but if y is Nan the result is system dependent.

    This can be corrected using the pedantic_ decorator that ensures the standard behaviour at a cost.

    @par Decorators

     - pedantic_ ensures the standard behaviour.
     - std_ call std::max.

    @see min,  maxnum, maxnummag, maxmag

    @par Example:

      @snippet max.cpp max

    @par Possible output:

      @snippet max.txt max

  **/
  Value max(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/max.hpp>
#include <boost/simd/function/simd/max.hpp>

#endif
