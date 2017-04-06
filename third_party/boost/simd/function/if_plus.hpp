//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IF_PLUS_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IF_PLUS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-boolean
    This function object conditionally returns  @c x+y (respectively @c x)
    if @c c is @ref True (respectively  @ref False)


    @par Header <boost/simd/function/if_plus.hpp>

    @par Example:

      @snippet if_plus.cpp if_plus

    @par Possible output:

      @snippet if_plus.txt if_plus

  **/
  Value1 if_plus(Value0 const& c, Value1 const& x, Value1 const& y);
} }
#endif

#include <boost/simd/function/scalar/if_plus.hpp>
#include <boost/simd/function/simd/if_plus.hpp>

#endif
