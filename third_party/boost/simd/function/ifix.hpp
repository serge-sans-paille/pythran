//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IFIX_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IFIX_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-arithmetic
    Function object implementing ifix capabilities

    Convert to integer by saturated truncation.

    This is a convenience alias of @ref saturated_(toint)
  **/
  Value ifix(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/ifix.hpp>
#include <boost/simd/function/simd/ifix.hpp>

#endif
