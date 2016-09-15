//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_CONJ_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_CONJ_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-arithmetic
    Function object implementing conj capabilities

    Computes the complex conjugate of its parameter

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = conj(x);
    @endcode

    for a real parameter, this is equivalent to:

    @code
    T r = x
    @endcode

    This function is the restriction to real numbers of the complex conj(ugation).

  **/
  Value conj(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/conj.hpp>

#include <boost/simd/function/simd/conj.hpp>

#endif
