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
    Function object implementing min capabilities

    Computes the smallest of its parameter.

    @par semantic:
    For any given value @c x and @c y of type @c T:

    @code
    T r = min(x, y);
    @endcode

    is similar to:

    @code
    T r = (x < y) ? x : y;
    @endcode

    @par Note:

    With this definition min(x, @ref Nan) should return x...

    On some systems (namely for example vmx in simd mode) the intrinsic used returns Nan as soon x or y is a nan.
    So the real definition of our min function must add: but if y is Nan the result is system dependent.

    This can be corrected using the conformant_ decorator that ensures the standard behaviour at a cost.

    @see minnum, minnummag, minmag

  **/
  Value min(Value const & v0, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/min.hpp>
#include <boost/simd/function/simd/min.hpp>

#endif
