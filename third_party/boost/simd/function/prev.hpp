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
    This function object returns the greatest representable
    value  strictly less than the parameter except:

    - for entries of floating types

       - prev(Valmin) is Minf

       - prev(Inf) is Valmax

       - prev(Minf) is Minf

       - prev(Nan) is Nan

    - for entries of integral type

      - prev(Valmin) is Valmax

    @par Header <boost/simd/function/prev.hpp>

    @see prev, nextafter, successor, predecessor

    @par Example:

      @snippet prev.cpp prev

    @par Possible output:

      @snippet prev.txt prev

  **/
  Value prev(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/prev.hpp>
#include <boost/simd/function/simd/prev.hpp>

#endif
