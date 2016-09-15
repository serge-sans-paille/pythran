//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_DEC_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_DEC_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!
  @ingroup group-arithmetic
  Function object implementing dec

  Decrements a value by 1.

  @par semantic:
  For any given value @c x of type @c T:

  @code
  T r = dec(x);
  @endcode

  is equivalent to:

  @code
  T r =  x-T(1);
  @endcode

  @par Decorators
    saturated_ ensures that saturated_(dec)(x) will never be strictly greater than x.

  @see minus

  **/
  Value dec(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/dec.hpp>
#include <boost/simd/function/simd/dec.hpp>

#endif
