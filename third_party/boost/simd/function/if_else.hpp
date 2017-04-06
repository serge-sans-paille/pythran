//==================================================================================================
/*!
  @file

  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IF_ELSE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IF_ELSE_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-boolean
    This function object conditionally returns @c t (respectively @c f) if @c c
    is @ref True (respectively  @ref False)

    @pre If both parameters are pack, they must have same cardinal.


    @par Header <boost/simd/function/if_else.hpp>

    @par Example:

      @snippet if_else.cpp if_else

    @par Possible output:

      @snippet if_else.txt if_else

  **/
  Value1 if_else(Value0 const& c, Value1 const& t, Value1 const& f);
} }
#endif

#include <boost/simd/function/scalar/if_else.hpp>
#include <boost/simd/function/simd/if_else.hpp>

#endif
