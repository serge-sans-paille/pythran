//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IF_NEG_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IF_NEG_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-boolean
    This function object conditionally returns  -x if c is @ref True and x otherwise.


    @par Header <boost/simd/function/if_neg.hpp>

    @par Example:

      @snippet negif.cpp negif

    @par Possible output:

      @snippet negif.txt negif

  **/
  Value1 if_neg(Value0 const& c, Value1 const& x);
} }
#endif

#include <boost/simd/function/scalar/if_neg.hpp>
#include <boost/simd/function/simd/if_neg.hpp>

#endif
