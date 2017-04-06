//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IF_INC_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IF_INC_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-boolean
    This function object conditionally returns @c x+1 (respectively @c x)
    if @c c is @ref True (respectively  @ref False)



    @par Header <boost/simd/function/if_inc.hpp>

    @par Example:

      @snippet if_inc.cpp if_inc

    @par Possible output:

      @snippet if_inc.txt if_inc

  **/
  Value1 if_inc(Value0 const& c, Value1 const& x);
} }
#endif

#include <boost/simd/function/scalar/if_inc.hpp>
#include <boost/simd/function/simd/if_inc.hpp>

#endif
