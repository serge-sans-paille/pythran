//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_REM_PIO2_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_REM_PIO2_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-trigonometric
    Function object implementing rem_pio2 capabilities

    Computes the remainder modulo \f$\pi/2\f$.

    @par Semantic:

    For every parameter of floating type T

    @code
    T r;
    as_integer<T> n;
    std::tie(n, r) = rem_pio2(x);
    @endcode

    is similar to:

    @code
    as_integer<T> n = div(inearbyint, x, Pio_2<T>());
    T r =  remainder(x, Pio_2<T>());
    @endcode

  **/
  std::pair<IntegerValue, Value> rem_pio2(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/rem_pio2.hpp>
#include <boost/simd/function/simd/rem_pio2.hpp>

#endif
