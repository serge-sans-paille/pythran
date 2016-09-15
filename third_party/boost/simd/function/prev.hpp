//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_PREV_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_PREV_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-ieee
    Function object implementing prev capabilities

    Returns if it exists the greatest representable value  strictly less than the parameter

    @par Semantic:

    @code
    auto r = prev(x);
    @endcode

   @par Note

    - for entries of floating types

       - prev(Valmin) is Minf

       - prev(Inf) is Valmax

       - prev(Minf) is Minf

       - prev(Nan) is Nan

    - for entries of integral type

      - prev(Valmin) is Valmax

    @see prev, nextafter, successor, predecessor

  **/
  Value prev(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/prev.hpp>
#include <boost/simd/function/simd/prev.hpp>

#endif
