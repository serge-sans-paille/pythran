//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ITRUNC_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ITRUNC_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-arithmetic
    Function object implementing itrunc capabilities

    Convert to integer by saturated truncation.

    This is an alias of saturated_(toint) (See @ref toint)

    @par Header <boost/simd/function/itrunc.hpp>

    @see ifix
  **/
  Value itrunc(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/itrunc.hpp>
#include <boost/simd/function/simd/itrunc.hpp>

#endif
