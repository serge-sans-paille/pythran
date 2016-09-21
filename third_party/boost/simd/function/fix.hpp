//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_FIX_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_FIX_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-arithmetic
    Function object implementing fix capabilities

    Computes the truncation toward @ref Zero of its parameter.

    This is a convenience alias of @ref trunc
  **/
  Value fix(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/trunc.hpp>
#include <boost/simd/function/simd/fix.hpp>

#endif
