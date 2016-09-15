//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SBITS_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SBITS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-ieee
    Function object implementing sbits capabilities

    Returns the signed integer value which has the bit pattern of the input

    @par Semantic:

    For every parameter @c x of type @c T

    @code
    auto r = sbits(x);
    @endcode

    is similar to:

    @code
    auto r = bitwise_cast<as_integer_t<T,signed>>(x);
    @endcode

  **/
  IntegerValue sbits(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/sbits.hpp>
#include <boost/simd/function/simd/sbits.hpp>

#endif
