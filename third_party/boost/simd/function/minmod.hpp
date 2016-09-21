//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_MINMOD_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_MINMOD_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-arithmetic
    Function object implementing minmod capabilities

    Return the minimum of the two entries
    if they have the same sign, otherwise 0

    @par semantic:
    For any given value @c x,  @c y of type @c T:

    @code
    T r = minmod(x, y);
    @endcode

    is similar to:

    @code
    T r =  x*y > 0 ? min(x, y) : 0;
    @endcode

  **/
  Value minmod(Value const & x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/minmod.hpp>
#include <boost/simd/function/simd/minmod.hpp>

#endif
