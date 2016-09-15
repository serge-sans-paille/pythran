//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_CUMPROD_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_CUMPROD_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-reduction
    Function object implementing cumprod capabilities

    Computes the cumulated product of the vector elements

    Take care that overflow is very easy to get here especially for integral types.
    cumprod of char and unsigned char almost always overflow in SIMD !

    @par semantic:
    For any given vector @c x of type @c T:

    @code
    T r = cumprod(x);
    @endcode

    is similar to:

    @code
    auto r = x;
    for(int i=1;i < T::static_size; ++i)
      r[i] *= r[i-1];
    @endcode

  **/
  Value cumprod(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/cumprod.hpp>
#include <boost/simd/function/simd/cumprod.hpp>

#endif
