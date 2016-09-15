//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_HYPOT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_HYPOT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-arithmetic
    Function object implementing hypot capabilities

    Computes \f$(x^2 + y^2)^{1/2}\f$

    @par semantic:
    For any given value @c x,  @c y of floating type @c T:

    @code
    T r = hypot(x, y);
    @endcode

    The code is similar to:

    @code
    T r = sqrt(sqr(x)+sqr(y));
    @endcode

    @par Note

    - Provision are made to avoid overflow as possible and to compute
    @c hypot accurately.

    - If these considerations can be put aside, use the decorator fast_.

    @par Decorators

    std_,  fast_ for floating entries

  **/
  Value hypot(Option const& o, Value const& x, Value const& y);

  //@overload
  Value hypot(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/hypot.hpp>
#include <boost/simd/function/scalar/hypot.hpp>
#include <boost/simd/function/simd/hypot.hpp>

#endif
