//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IFNOT_PLUS_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IFNOT_PLUS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-boolean
    This function object conditionally returns  @c x (respectively @c x+y)
    if @c c is @ref True (respectively  @ref False)


    @par Header <boost/simd/function/ifnot_plus.hpp>

    @par Example:

      @snippet ifnot_plus.cpp ifnot_plus

    @par Possible output:

      @snippet ifnot_plus.txt ifnot_plus

  **/
  Value1 ifnot_plus(Value0 const& c, Value1 const& x, Value1 const& y);
} }
#endif

#include <boost/simd/function/scalar/ifnot_plus.hpp>
#include <boost/simd/function/simd/ifnot_plus.hpp>

#endif
