//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IF_ALLBITS_ELSE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IF_ALLBITS_ELSE_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-boolean
    This function object  returns @ref Allbits if  @c c is @ref True else returns @c f



    @par Header <boost/simd/function/if_allbits_else.hpp>

    @par Example:

      @snippet if_allbits_else.cpp if_allbits_else

    @par Possible output:

      @snippet if_allbits_else.txt if_allbits_else

    @par Alias:
    @c if_nan_else,

    @see genmask, Allbits, Nan

  **/
  Value1 if_allbits_else(Value0 const& c, Value1 const& f);
} }
#endif

#include <boost/simd/function/scalar/if_allbits_else.hpp>
#include <boost/simd/function/simd/if_allbits_else.hpp>

#endif
