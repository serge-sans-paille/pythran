//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IF_MINUS_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IF_MINUS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-boolean
    This function object conditionally returns @c x-y (respectively @c x)  if @c c is @ref True
    (respectively  @ref False)


    @par Header <boost/simd/function/if_minus.hpp>

    @par Example:

      @snippet if_minus.cpp if_minus

    @par Possible output:

      @snippet if_minus.txt if_minus

  **/
  Value1 if_minus(Value0 const& c, Value1 const& x, Value1 const& y);
} }
#endif

#include <boost/simd/function/scalar/if_minus.hpp>
#include <boost/simd/function/simd/if_minus.hpp>

#endif
