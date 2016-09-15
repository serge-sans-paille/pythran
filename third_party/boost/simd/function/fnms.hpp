//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_FNMS_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_FNMS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-arithmetic
    Function object implementing fnms capabilities

    Computes the fused substract-multiply of three value.

    @par semantic:
    For any given value @c x,  @c y,  @c z of type @c T:

    @code
    T r = fnms(x, y, z);
    @endcode

    The code is similar to:

    @code
    T r = -(x*y-s);
    @endcode

    @par Note:

    fnms can be called with the same modalities as @ref fma
    and can use the decorator conformant_ to ensure the correct
    one rounding, no intermediate overflow  behaviour

    @see  fms, fma, fnma

  **/
  Value fnms(Value const& v0, Value const& v1, Value const& v2);
} }
#endif

#include <boost/simd/function/scalar/fnms.hpp>
#include <boost/simd/function/simd/fnms.hpp>

#endif
