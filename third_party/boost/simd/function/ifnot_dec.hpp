//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IFNOT_DEC_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IFNOT_DEC_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-boolean
    This function object conditionally returns  @c x (respectively @c x-1)
    if @c c is @ref True (respectively  @ref False)


    @par Header <boost/simd/function/ifnot_dec.hpp>

    @par Example:

      @snippet ifnot_dec.cpp ifnot_dec

    @par Possible output:

      @snippet ifnot_dec.txt ifnot_dec

  **/
  Value1 ifnot_dec(Value0 const& c, Value1 const& x);
} }
#endif

#include <boost/simd/function/scalar/ifnot_dec.hpp>
#include <boost/simd/function/simd/ifnot_dec.hpp>

#endif
