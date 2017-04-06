//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IFNOT_NEG_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IFNOT_NEG_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-boolean

    This function object conditionally returns -x if @c c is @ref False and x otherwise.


    @par Header <boost/simd/function/ifnot_neg.hpp>

    @par Example:

      @snippet negifnot.cpp negifnot

    @par Possible output:

      @snippet negifnot.txt negifnot

  **/
  Value1 ifnot_neg(Value0 const& c, Value1 const& x);
} }
#endif

#include <boost/simd/function/scalar/ifnot_neg.hpp>
#include <boost/simd/function/simd/ifnot_neg.hpp>

#endif
